//file: Simple JSON Parser.h
//project: Simple JSON Parser
//Author: Tim Solum
//version: 2.00
//date: 4/21/2012

#ifndef _SIMPLE_JSON_PARSER_H_
#define _SIMPLE_JSON_PARSER_H_

#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "SH Value.h"

using namespace std;

namespace SH{

//ifndef prevents conflict when using Simple JSON Writer in same project
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


	//does the parsing of the JSON file
	//supports valid JSON, will fail epicly if not a valid Json File
	/* simple example  file: blah.json
	{
		"test": {
			"test2": "neato"
		},
		"test3": [
			null,
			{
			"thanks": "you are welcome"
			},
			3.43,
			"rawr",
			true,
			false
		]
	}

	//code snippet
	SH::JsonParser parser;
	parser.openFile("blah.json");
	parser.parse();
	parser.Root().objects["test"].pairs["test2"];  // would return "neato"
	parser.Root().arrays["test3"][1].pairs["thanks"];  // would return "you are welcome"
	parser.Root().arrays["test3"][2].value  // would return 3.43
	parser.Root().arrays["test3"][5].value  // would return false
	
	*/
	//yup, it is that simple
	class JsonParser{
	public:
		//basic constructor, inits JSON_DATA to ""
		JsonParser();
		
		//closes in and out files if opened
		~JsonParser();
		
		//returns unparsed JSON_DATA
		string getJSON_DATA() const;
		
		//opens inFile and reads in a string of JSON data.
		//ignores white space, tab, and newline char
		void readFile(string fileName);
		
		//fills root with parsed json data
		//null objects will be 0
		void parse();

		//returns root safely so no data can be changed
		JsonObject Root() const;

	private:
		JsonObject root;       //root for all parsed json data
		string RAW_JSON_DATA;  //holds raw json string
		ifstream inFile;       //for JSON parsing


		//helper stuff for parse
		string makeName(string jString,int& currentChar);
		void fill(int& currentChar,string name,JsonObject& currentObject);//don't mess with this!!!!!
		vector<string> arrayName;//don't mess with this!!!!!
		vector<bool> inArray;//don't mess with this!!!!!
		int nestCount;//don't mess with this!!!!!
	};

}

#endif

