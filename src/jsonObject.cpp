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

#include "jsonObject.h"
#include <sstream>
#include <iomanip>

/// jsonObject::getType
///
/// @return jsonType - the type of the JSON Object
jsonType jsonObject::getType() {
	return type;
}

/// jsobObject::toJsonString - Should not be called
///
/// @return - error text
std::string jsonObject::toJsonString() {
	return "Error: baseObject toJsonString called";
}

/// jsonArray::toJsonString
///
/// @return JSON representation string of a jsonArray
std::string jsonArray::toJsonString() {
	std::string jsonString;

	jsonString+="[";

	auto size = array->size();
	auto count = 0;
	for (auto const &item : (*array)) {
		count++;
		jsonString += item->toJsonString() + ((count<size) ? ",":"");
	}
	
	jsonString+="]";

	return jsonString;
}

/// jsonDictionary::toJsonString
///
/// @return JSON representation string of a jsonDictionary
std::string jsonDictionary::toJsonString() {
	std::string jsonString;
	
	auto size = dictionary->size();
	auto count = 0;

	jsonString+="{";
	for (auto const &item : (*dictionary)) {
		count++;
		jsonString += "\"" + item.first + "\"" + ":" + item.second->toJsonString() + ((count<size) ? "," : "");
	}
	jsonString+="}";

	return jsonString;
}

/// jsonNumber::toJsonString
///
/// @return JSON representation string of a jsonNumber
std::string jsonNumber::toJsonString() {
	std::ostringstream numberString;
	numberString << std::setprecision(8) << std::noshowpoint << number;
	return numberString.str();
}


/// jsonBoolean::toJsonString
///
/// @return JSON representation string of a jsonBoolean
std::string jsonBoolean::toJsonString() {
	return (boolean) ? "true" : "false";
}

/// jsonString::toJsonString
///
/// @return JSON representation string of a jsonString
std::string jsonString::toJsonString() {
	return std::string("\"" + stringValue + "\"");
}
