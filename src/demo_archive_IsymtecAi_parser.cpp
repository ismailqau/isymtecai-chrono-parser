
#include "chrono/utils/ChUtilsValidation.h"
#include "chrono/utils/ChUtilsInputOutput.h"

#include <cassert>
#include "physics/ChGlobal.h"
#include "physics/ChSystemSMC.h"
#include "parser_isymtec_ai/ChParserIsymtecAi.h"
#include "parser_isymtec_ai/ChSimulationParameters.h"
#include "parser_isymtec_ai/ChIsymtecAiConstants.h"

#include "chrono/core/ChFileutils.h"
#include "chrono/serialization/ChArchive.h"
#include "chrono/serialization/ChArchiveJSON.h"

using namespace chrono;

#include "parser_isymtec_ai/ChSimulationIsymtecAi.h"

class ChSimulationDemo : public  ChSimulationIsymtecAi {
public:
	mutable std::vector<double> m_CoordinateXBody;
	mutable std::vector<double> m_Time;
private:
	virtual void ProcessOutputTimeStep() const override final {}
};

int main(int argc, char* argv[]) {
    std::string filename;
    if (argc > 1) {
        filename = std::string(argv[1]);
    } else {
		std::cout << "no input filename!!!";
		return -1;
    }
	ChSimulationDemo simulation;
	bool parseOk = simulation.Parse(filename);

	simulation.Simulate();


	const std::string out_dir = GetChronoOutputPath() + "DEMO_ARCHIVE";
	if (ChFileutils::MakeDirectory(out_dir.c_str()) < 0) {
		std::cout << "Error creating directory " << out_dir << std::endl;
		return -1;
	}

	std::string jsonfile = out_dir + "/foo_archive.json";
	ChStreamOutAsciiFile mfileo(jsonfile.c_str());

	// Use a JSON archive object to serialize C++ objects into the file
	ChArchiveOutJSON marchiveout(mfileo);


	auto& system = simulation.GetSystem();

	marchiveout << CHNVP(system, "system");  // store data n.1      
}