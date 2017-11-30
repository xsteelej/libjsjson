#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "jsonSerialisation.h"

using jsonObjectPtr = std::unique_ptr<jsonObject>;
using jsonDictionaryPtr = std::unique_ptr<jsonDictionaryType>;
using jsonVectorPtr = std::unique_ptr<jsonArrayType>;

TEST_CASE("Test the creation of a json Dictionary object", "[json_object_creation_dictionary]") {
	jsonDictionaryPtr jsonMap (new jsonDictionaryType());

	(*jsonMap)["a"] = jsonObjectPtr(new jsonBoolean(true));
	(*jsonMap)["b"] = jsonObjectPtr(new jsonNumber(100.1));

	jsonDictionary jsonDict(std::move(jsonMap));

	auto outputJSON = jsonDict.toJsonString();
	REQUIRE(outputJSON == "{\"a\":true,\"b\":100.1}");
}

TEST_CASE("Test the creation of a json Array object", "[json_object_creation_array]") {
	jsonVectorPtr jsonVector (new jsonArrayType());
	jsonVector->push_back(jsonObjectPtr(new jsonString("A")));
	jsonVector->push_back(jsonObjectPtr(new jsonNumber(200)));
	jsonArray jsonArr(std::move(jsonVector));
	REQUIRE(jsonArr.toJsonString() == "[\"A\",200]");
}
