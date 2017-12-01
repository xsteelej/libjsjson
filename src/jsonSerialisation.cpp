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

#include "jsonSerialisation.h"
#include <string>
#include <ctype.h>
#include <sstream>

namespace jsjson {

///parseData
std::unique_ptr<jsonObject> jsonSerialisation::parseData(const std::string& jsonString, std::string::size_type& fromIndex) {
	std::unique_ptr<jsonObject> jsonObject = nullptr;

	while (fromIndex < jsonString.size() && jsonObject == nullptr) {
		const auto& chr = jsonString[fromIndex];
		auto type = (isdigit(chr)) ? '0' : chr;
		switch (type) {
			case '0':
				jsonObject = parseNumber(jsonString, fromIndex);
				break;
			case '{':
				jsonObject = parseDictionary(jsonString, fromIndex);
				break;
			case '[':
				jsonObject = parseArray(jsonString, fromIndex);
				break;
			case '"':
				jsonObject = parseString(jsonString, fromIndex);
				break;
			case 't':
			case 'f':
				jsonObject = parseBoolean(jsonString, fromIndex);
				break;
			default:
				if (isspace(chr)) { fromIndex++; }
				else { throw jsonSerialisationException("Error Parsing, invalid JSON"); }
				break;
		}
	}
	return jsonObject;
}

///parse
std::unique_ptr<jsonObject> jsonSerialisation::parse(const std::string& jsonString) {
	auto stringIdx = std::string::size_type(0);
	auto topLevelObject = parseData(jsonString, stringIdx);
	while (stringIdx++ < jsonString.size()) {
		const auto &chr = jsonString[stringIdx];
		if (!isspace(chr) && isprint(chr)) { throw jsonSerialisationException("Error Parsing, invalid JSON after top level object"); }	
	}
	return topLevelObject;
}

///parseDictionary
std::unique_ptr<jsonObject> jsonSerialisation::parseDictionary(const std::string& jsonString, std::string::size_type& index) {
	if (jsonString[index] != '{') { throw jsonSerialisationException("Error parsing dictionary, expected a \"{\""); }
	std::shared_ptr<jsonDictionaryType> dictionary(new jsonDictionaryType());

	index++;
	while (index < jsonString.size()) {
		const auto &chr = jsonString[index];
		if (chr == '}') { break; }
		else if (chr == '"') {
			auto key = parseKey(jsonString, index);
			auto data = parseData(jsonString, index);
			(*dictionary)[(*key)] = std::move(data);
			advanceToNextElement(jsonString, index,'}');
		} 
		else if (isspace(chr)) { index++; }
		else {
			std::ostringstream error;
			error << "Error parsing dictionary, expecting a quote but found a \"" << chr << "\"";
			throw jsonSerialisationException(error.str());
		}
	}		

	std::unique_ptr<jsonDictionary> jdPtr(new jsonDictionary(std::move(dictionary)));
	return jdPtr;
}

///parseKey
std::unique_ptr<std::string> jsonSerialisation::parseKey(const std::string& jsonString, std::string::size_type& index) {
	const auto colonPos = jsonString.find(':', index);
	const auto finalQuote = jsonString.rfind('\"',colonPos);
	const auto firstQuote = index;//jsonString.find("\"", index);

	if (colonPos == std::string::npos) { throw jsonSerialisationException("Error parsing key, expected a \":\""); }
	if (firstQuote == std::string::npos) { throw jsonSerialisationException("Error parsing key, first quote not found!"); }
	if (finalQuote == std::string::npos || finalQuote == firstQuote) { throw jsonSerialisationException("Error parsing key, final quote not found!"); }

	std::string key = jsonString.substr(firstQuote+1,finalQuote-firstQuote-1);
	std::unique_ptr<std::string> keyPtr(new std::string(key));
	index = colonPos+1;
	return keyPtr;
}

///advanceToNextElement
void jsonSerialisation::advanceToNextElement(const std::string& jsonString, std::string::size_type& index, const char endChar) {
	bool foundComma = false;
	std::ostringstream error;

	while (index < jsonString.size()) {
		const auto& chr = jsonString[index];
		if (foundComma) {
			if (chr == ',' || chr == endChar) {
				error << "Error, found a \"" << chr << "\" after a comma";
				throw jsonSerialisationException(error.str());
			}
			else if (!isspace(chr)) { break; }
		}
		else {
			if (chr == ',') { foundComma = true; } 
			else if (chr == endChar) { break; }
			else if (!isspace(chr)) {
				error << "Error, expecting a \",\" or \"" << endChar << "\" but found a \"" << chr << "\""; 
				throw jsonSerialisationException(error.str());
			}
		}
		index++;
	}
}

///parseArray
std::unique_ptr<jsonObject> jsonSerialisation::parseArray(const std::string& jsonString, std::string::size_type& index) {
	if (jsonString[index] != '[') { throw jsonSerialisationException("Error parsing array, expected a \"[\""); }
	std::unique_ptr<jsonArrayType>vectorPtr(new jsonArrayType());

	index++;

	while (index < jsonString.size()) {
		const auto& chr = jsonString[index];
		
		if (chr == ']') { index++; break; }
		auto data = parseData(jsonString, index);
		if (data != nullptr) { vectorPtr->push_back(std::move(data)); }
		advanceToNextElement(jsonString, index, ']');
	}

	return std::unique_ptr<jsonObject>(new jsonArray(std::move(vectorPtr)));
}

///parseString
std::unique_ptr<jsonObject> jsonSerialisation::parseString(const std::string& jString, std::string::size_type& index) {
	std::string str;

	bool escapeChar = false;

	while (index < jString.size()) {
		index++;
		const auto& chr = jString[index];
		if (!escapeChar && chr=='"') { break; }
		escapeChar = (!escapeChar && chr == '\\');
		str+=chr;
	}
	index++;
	return std::unique_ptr<jsonObject>(new jsonString(str));
}

///parseNumber
std::unique_ptr<jsonObject> jsonSerialisation::parseNumber(const std::string& jsonString, std::string::size_type& index) {
	std::string numberString;

	while(index < jsonString.size()) {
		const auto& chr = jsonString[index];
		if (!isdigit(chr) && chr != '.') { break; }
		numberString+=chr;
		index++;
	}	

	return std::unique_ptr<jsonObject>(new jsonNumber(stod(numberString)));
}

///parseBoolean
std::unique_ptr<jsonObject> jsonSerialisation::parseBoolean(const std::string& jsonString, std::string::size_type& index) {
	std::string booleanString;

	while(index < jsonString.size()) {
		const auto& chr = jsonString[index];
		if (isspace(chr) || chr == ',' || chr == ']' || chr == '}') { break; }
		booleanString+=chr;
		index++;
	}
	if (booleanString != "true" && booleanString != "false") {throw jsonSerialisationException("Error parsing boolean, expecting true or false"); }
	return std::unique_ptr<jsonObject>(new jsonBoolean(booleanString == "true"));
}

}
