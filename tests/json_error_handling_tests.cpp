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

	REQUIRE(thrownErrorString == jsjson::genericParserError);
}

TEST_CASE("Test unexpected characters after a comma","[error_handling_invalid_after_comma]") {
	std::string thrownErrorString = "";
	try {
		auto parsedJSON = jsonSerialisation::parse("{\"test1\":\"def\",\"t2\":\"1\", }");
	} catch (jsonSerialisationException e) {
		thrownErrorString = std::string(e.what());
	}

	REQUIRE(thrownErrorString == jsjson::unexpectedCharactersAfterComma);
}

TEST_CASE("Test no colon in a dictionary","[error_handling_no_colon_after_key]") {
	std::string thrownErrorString = "";
 
	try {
		auto parsedJSON = jsonSerialisation::parse("{\"test1\":\"def\",\"t2\"   \"1\", }");
	} catch (jsonSerialisationException e) {
		thrownErrorString = std::string(e.what());
	}
	REQUIRE(thrownErrorString == jsjson::keyParsingColonNotFoundError);
}

TEST_CASE("Test no quote at start of dictionary key","[error_handling_no_quote_before_dictionary_key]") {
	std::string thrownErrorString = "";
 
	try {
		auto parsedJSON = jsonSerialisation::parse("{\"test1\":\"def\",t2\":\"1\"}");
	} catch (jsonSerialisationException e) {
		thrownErrorString = std::string(e.what());
	}
	REQUIRE(thrownErrorString == jsjson::keyParsingFirstQuoteNotFoundError);
}

TEST_CASE("Test no quote at the end of the dictionary key","[error_handling_no_quote_after_dictionary_key]") {
	std::string thrownErrorString = "";
 
	try {
		auto parsedJSON = jsonSerialisation::parse("{\"test1\":\"def\",\"t2:\"1\"}");
	} catch (jsonSerialisationException e) {
		thrownErrorString = std::string(e.what());
	}
	REQUIRE(thrownErrorString == jsjson::keyParsingFinalQuoteNotFoundError);
}

TEST_CASE("Test unexpected characters after dictionary elemment ","[error_handling_invalid_chars_after_element]") {
	std::string thrownErrorString = "";
 
	try {
		auto parsedJSON = jsonSerialisation::parse("{\"test1\":\"def\",\"t2\":\"1\" crud");
	} catch (jsonSerialisationException e) {
		thrownErrorString = std::string(e.what());
	}
	REQUIRE(thrownErrorString == jsjson::unexpectedTerminatingCharacterError);
}

TEST_CASE("Test errors parsing boolean","[error_handling_invalid_boolean]") {
	std::string thrownErrorStringFalse = "";
	std::string thrownErrorStringTrue = "";
 
	try {
		auto parsedJSON = jsonSerialisation::parse("{\"test1\":\"def\",\"t2\":fals");
	} catch (jsonSerialisationException e) {
		thrownErrorStringFalse = std::string(e.what());
	}
	
	try {
		auto parsedJSON = jsonSerialisation::parse("{\"test1\":\"def\",\"t2\":tre");
	} catch (jsonSerialisationException e) {
		thrownErrorStringTrue = std::string(e.what());
	}

	REQUIRE(thrownErrorStringFalse == jsjson::booleanParsingError);
	REQUIRE(thrownErrorStringTrue == jsjson::booleanParsingError);
}
