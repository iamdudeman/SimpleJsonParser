//file: Simple JSON Writer.h
//project: Simple JSON Writer
//Author: Tim Solum
//version: 1.37
//date: 5/14/2012

#ifndef _SIMPLE_JSON_WRITER_H_
#define _SIMPLE_JSON_WRITER_H_

#include <map>
#include <string>
#include <vector>
#include <fstream>

#include "SH Value.h"

#define null SH::Value()          //null value definition
#define null_obj SH::JsonObject() //null_obj object definition

using namespace std;

namespace SH{

//ifndef prevents conflict when using Simple JSON Parser in same project
#ifndef __JSON_OBJECT__
#define __JSON_OBJECT__
	//basic JsonObject
	struct JsonObject{
		map<Value,SH::Value> pairs;             //holds all pairs
		map<Value,JsonObject> objects;          //holds all objects
		map<Value,vector<JsonObject>> arrays;   //holds all arrays
		Value value;
	};
#endif

	typedef vector<JsonObject> JsonArray; //JsonArray type definition

	//class to create an unformatted json file
	class JsonWriter{
	public:
		JsonWriter();
		~JsonWriter();

		//adds pair to be written
		void addPair(Value name, Value value);
		//adds object to be written
		void addObject(Value name, JsonObject value);
		//adds array to be written
		void addArray(Value name, vector<JsonObject> value);
		
		//writes unformatted json file
		void write(string filename);
	private:
		JsonObject root;
		ofstream out;
		//helper function
		void writeObject(JsonObject currentObject);
	};

}
#endif