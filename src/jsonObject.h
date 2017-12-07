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

#ifndef _JSON_OBJECT_H_
#define _JSON_OBJECT_H_

#include <string>
#include <map>
#include <vector>
#include <memory>

namespace jsjson {

/// jsonType - defines the various types of JSON objects
enum jsonType : std::int8_t {ARRAY,DICTIONARY,NUMBER,BOOLEAN,STRING};

/// jsonObject - base class for all jsonObjects, not intended for instatiation
class jsonObject {
public:
	jsonObject(){}
	virtual ~jsonObject() {}
	jsonType getType();
	virtual	std::string toJsonString();
protected:
	jsonObject(jsonType t) : type(t) {}
	jsonType type;
};

/// jsonArray
using jsonArrayType = std::vector<std::unique_ptr<jsonObject>>;

class jsonArray : public jsonObject {
public:
	jsonArray() : jsonObject(ARRAY) {}
	jsonArray(std::shared_ptr<jsonArrayType> aJsonArray) : jsonArray() { array = aJsonArray; }
	virtual ~jsonArray() {}
	virtual std::string toJsonString();
	void setArray(std::unique_ptr<jsonArrayType>);
private:
	std::shared_ptr<jsonArrayType> array;
};

/// jsonDictionary
using jsonDictionaryType = std::map<std::string, std::unique_ptr<jsonObject>>;

class jsonDictionary : public jsonObject {
public:
	jsonDictionary() : jsonObject(DICTIONARY){}
	jsonDictionary(std::shared_ptr<jsonDictionaryType> aJsonDictionary) : jsonDictionary() { dictionary = aJsonDictionary; }
	virtual ~jsonDictionary() {}
	virtual std::string toJsonString();
	inline void setDictionary(std::shared_ptr<jsonDictionaryType> jd) { dictionary = jd; }
	inline std::shared_ptr<jsonDictionaryType> getDictionary() { return dictionary; }
private:
	std::shared_ptr<jsonDictionaryType> dictionary;
};

/// jsonNumber
class jsonNumber : public jsonObject {
public:
	jsonNumber() : jsonObject(NUMBER){}
	jsonNumber(double aNumber) : jsonNumber() { number = aNumber; }
	virtual ~jsonNumber() {}	
	virtual std::string toJsonString();
	inline void setNumber(double aFloat) { number = aFloat; }
	inline double getNumber() { return number; }
private:
	double number;
};

/// jsonString
class jsonString : public jsonObject {
public:
	jsonString() : jsonObject(STRING){}
	jsonString(std::string aString) : jsonString() { stringValue = aString; }
	virtual ~jsonString() {}
	virtual std::string toJsonString();
	inline void setString(std::string aString) { stringValue = aString; }
	inline std::string getString() { return stringValue; }
private:
	std::string stringValue;
};

/// jsonBoolean
class jsonBoolean : public jsonObject {
public:
	jsonBoolean() : jsonObject(BOOLEAN) {}
	jsonBoolean(bool aBool) : jsonBoolean() { boolean = aBool; }
	virtual ~jsonBoolean() {}
	virtual std::string toJsonString();
	inline void setBoolean(bool aBoolean) { boolean = aBoolean; }
	inline bool getBoolean() { return boolean; }
private:
	bool boolean;
};
} // Namespace

#endif
