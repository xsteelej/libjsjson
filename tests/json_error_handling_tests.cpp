#include "catch.hpp"
#include "jsonSerialisation.h"

using namespace jsjson;

TEST_CASE("Test that garbage in throws an exception","[error_handling_garbage]") {
	std::string thrownErrorString = "";
	try {
		auto parsedJSON = jsonSerialisation::parse("john steele");
	} catch (jsonSerialisationException e) {
		thrownErrorString = std::string(e.what());
	}

	REQUIRE(thrownErrorString == "Error Parsing, invalid JSON");

}
