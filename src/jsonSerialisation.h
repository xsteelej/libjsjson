// MIT License
// Copyright (c) 2017 John Steele 
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _JSON_SERIALISATION_
#define _JSON_SERIALISATION_

#include "jsonObject.h"
#include <string>
#include <exception>

namespace jsjson {

extern const std::string genericParserError;
extern const std::string unexpectedCharactersAfterComma;
extern const std::string dictionaryKeyQuoteError;
extern const std::string keyParsingColonNotFoundError;
extern const std::string keyParsingFirstQuoteNotFoundError;
extern const std::string keyParsingFinalQuoteNotFoundError;
extern const std::string unexpectedTerminatingCharacterError;
extern const std::string booleanParsingError;

/// jsonSerialisation - parse JSON formatted strings and create, returning a top level jsonObject
class jsonSerialisation {
public:
	/// parse - taking a JSON formatted string, create jsonObject's 
	/// @param jsonString - string representation of the JSON to be parsed.
	static std::unique_ptr<jsonObject> parse(const std::string& jsonString);
private:
	static std::unique_ptr<jsonObject> parseData(const std::string&, std::string::size_type&);
	static std::unique_ptr<jsonObject> parseDictionary(const std::string&, std::string::size_type&);
	static std::unique_ptr<jsonObject> parseArray(const std::string&, std::string::size_type&);
	static std::unique_ptr<jsonObject> parseString(const std::string&, std::string::size_type&);
	static std::unique_ptr<jsonObject> parseNumber(const std::string&, std::string::size_type&);
	static std::unique_ptr<jsonObject> parseBoolean(const std::string&, std::string::size_type&);
	static std::unique_ptr<std::string> parseKey(const std::string&, std::string::size_type&); 
	static void advanceToNextElement(const std::string&, std::string::size_type&, const char);
};

/// jsonSerialisationException - used to signal that the parser has found invalid JSON whilst parsing. 
class jsonSerialisationException : public std::exception {
public:
	jsonSerialisationException(std::string anExceptionMessage) : exceptionMessage(anExceptionMessage){}
	virtual const char* what() const noexcept { return exceptionMessage.c_str(); }
private:
	std::string exceptionMessage;
};

}

#endif
