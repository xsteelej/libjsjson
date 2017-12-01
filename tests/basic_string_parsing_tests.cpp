#include "catch.hpp"
#include <string>
#include "jsonSerialisation.h"

using namespace jsjson;

TEST_CASE("Tests a very basic Top level Object of an Empty Dictionary", "[top_level_object_empty_dictionary]") {
	auto parsedJson = jsonSerialisation::parse("{}");
	auto outputJSON = parsedJson->toJsonString();
	REQUIRE(outputJSON == "{}");
}

TEST_CASE("Tests a very basic Top level Object of an Empty Array", "[top_level_object_empty_array]") {
	auto parsedJson = jsonSerialisation::parse("[]");
	auto outputJSON = parsedJson->toJsonString();
	REQUIRE(outputJSON == "[]");
}

TEST_CASE("Tests a very basic Top level Object of boolean", "[top_level_object_boolean]") {
	auto parsedJson = jsonSerialisation::parse("true");
	auto outputJSON = parsedJson->toJsonString();
	REQUIRE(outputJSON == "true");
}

TEST_CASE("Tests a very basic Top level Object of string","[top_level_object_string]") {
	auto parsedJson = jsonSerialisation::parse("\"abc\"");
	auto outputJSON = parsedJson->toJsonString();
	REQUIRE(outputJSON == "\"abc\"");
}

TEST_CASE("Tests a very basic Top level Object of number","[top_level_object_number]") {
	auto parsedJson = jsonSerialisation::parse("100.101");
	auto outputJSON = parsedJson->toJsonString();
	REQUIRE(outputJSON == "100.101");
}

TEST_CASE("Tests a very basic Top level Object of type dictionary","[top_level_object_dictionary]") {
	auto parsedJson = jsonSerialisation::parse("{\"a\" : \"b\", \"def\" : true }");
	auto outputJSON = parsedJson->toJsonString();
	REQUIRE(outputJSON == "{\"a\":\"b\",\"def\":true}");
}

TEST_CASE("Tests a very basic Top level Object of type Array","[top_level_object_array]") {
	auto parsedJson = jsonSerialisation::parse("[\"a\",\"b\",\"def\",true]");
	auto outputJSON = parsedJson->toJsonString();
	REQUIRE(outputJSON == "[\"a\",\"b\",\"def\",true]");
}

TEST_CASE("Tests a dictionary with an array","[top_level_object_dictionary+array]") {
	auto parsedJson = jsonSerialisation::parse("{\"a\" : [\"abc\",\"def\"]}");
	auto outputJSON = parsedJson->toJsonString();
	REQUIRE(outputJSON == "{\"a\":[\"abc\",\"def\"]}");
}
