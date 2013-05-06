//file: Simple JSON Parser.cpp
//project: Simple JSON Parser
//Author: Tim Solum
//version: 3.78
//date: 4/21/2012

#include <iostream>
#include <sstream>
#include "Simple JSON Parser.h"

namespace SH{

	JsonParser::JsonParser(){
		RAW_JSON_DATA = "";
		nestCount = 0;
	}

	JsonParser::~JsonParser(){
		if(inFile.is_open()){
			inFile.close();
		}
	}

	string JsonParser::getJSON_DATA() const{
		return RAW_JSON_DATA;
	}

	void JsonParser::readFile(string fileName){
		RAW_JSON_DATA = "";
		inFile.open(fileName);
		char temp;
		inFile.get(temp);
		while(inFile.good()){
			RAW_JSON_DATA += temp;
			inFile.get(temp);
		}
	}

	void JsonParser::parse(){
		int currentChar = 0;
		nestCount++;
		inArray.push_back(false);
		arrayName.push_back("");
		fill(currentChar,"\t\n\t",root);
		inFile.close();
	}

	JsonObject JsonParser::Root() const{
		return root;
	}

	//parse helper function
	string JsonParser::makeName(string jString,int& currentChar){
		while (jString[currentChar] != '"'){
			if(jString[currentChar] == '{' || jString[currentChar] == 'n'){
				currentChar--;
				return "";
			}
			else if(jString[currentChar] >= '0' || jString[currentChar] <= '9' && inArray[nestCount-1]){
				currentChar;
				return "";
			}
			currentChar++;
		}
		stringstream name;
		currentChar++;
		while(jString[currentChar] != '"'){
			name<<jString[currentChar];
			currentChar++;
		}
		return name.str();
	}

	//parse helper function
	Value makeValue(string jString,int& currentChar){
		Value value;
		stringstream temp;
		//eliminate white space
		while(jString[currentChar] != '"' && (jString[currentChar] < '0' || jString[currentChar] > '9')){
			if(jString[currentChar] == '{' || jString[currentChar] == '['){
				currentChar--;
				value = "\t\n\t";
				return value;
			}
			else if(jString[currentChar] == 't' || jString[currentChar] == 'f' || jString[currentChar] == 'n'){
				break;
			}
			currentChar++;
		}
		//check if value should be string
		if(jString[currentChar] == '"'){
			currentChar++;
			while(jString[currentChar] != '"'){
				if(jString[currentChar] == '\\' && jString[currentChar+1] == '"'){
					temp<<'"';
					currentChar+=1;
				}
				else if(jString[currentChar] == '\\' && jString[currentChar+1] == '\\'){
					temp<<'\\';
					currentChar+=1;
				}
				else{
					temp<<jString[currentChar];
				}
				currentChar++;
			}
			value = temp.str();		
		}
		//check if value should be number
		else if(jString[currentChar] >= '0' && jString[currentChar] <= '9'){
			while(jString[currentChar] != ',' && jString[currentChar] != '}' && jString[currentChar] != ']'){
				temp<<jString[currentChar];
				currentChar++;
			}
			currentChar--;
			double temp2;
			temp >> temp2;
			value = temp2;
		}
		//check if value is bool or null
		else if(jString[currentChar] == 't' || jString[currentChar] =='f' || jString[currentChar] =='n'){
			while(jString[currentChar] != ',' && jString[currentChar] != '}' && jString[currentChar] != ']'){
				if(jString[currentChar] >= 'a' && jString[currentChar] <= 'z'){
					temp<<jString[currentChar];
				}
				currentChar++;
			}
			currentChar--;
			cout<<temp.str()<<endl;//debug code
			if(temp.str() == "true"){
				value = true;
			}
			else if(temp.str()=="false"){
				value = false;
			}
			else if(temp.str()=="null"){
				value = "";
			}
		}
		return value;
	}

	void JsonParser::fill(int& currentChar,string name,JsonObject& currentObject){
		Value value = "\t\n\t";
		currentChar++;
		name = makeName(RAW_JSON_DATA,currentChar);
		while (currentChar < RAW_JSON_DATA.length()){
			if(RAW_JSON_DATA[currentChar] == ','){
				name = makeName(RAW_JSON_DATA,currentChar);
			}
			
			else if(RAW_JSON_DATA[currentChar] == ':'){
				value = makeValue(RAW_JSON_DATA,currentChar);
				if(value.asString() != "\t\n\t" && name != ""){
					cout<<name<<endl;//debug code
					cout<<value<<endl;//debug code
					currentObject.pairs[name] = value;
				}
			}

			else if(RAW_JSON_DATA[currentChar] == '{'){
				cout<<"----new object----"<<endl;//debug code
				if(inArray[nestCount-1]){
					currentObject.arrays[arrayName[nestCount-1]].push_back(JsonObject());
					nestCount++;
					inArray.push_back(false);
					arrayName.push_back("");
					fill(currentChar,name,currentObject.arrays[arrayName[nestCount-2]][currentObject.arrays[arrayName[nestCount-2]].size()-1]);
				}
				else{
					nestCount++;
					inArray.push_back(false);
					arrayName.push_back("");
					fill(currentChar,name,currentObject.objects[name]);
				}
			}
			else if(RAW_JSON_DATA[currentChar] == '}'){
				nestCount--;
				inArray.pop_back();
				arrayName.pop_back();
				return;
			}
			
			else if(RAW_JSON_DATA[currentChar] == '['){
				cout<<"----new array----"<<endl;//debug code
				cout<<name<<endl;//debug code
				vector<JsonObject> temp;
				nestCount++;
				arrayName.push_back(name);
				currentObject.arrays[arrayName[nestCount-1]] = temp;
				inArray.push_back(true);
			}
			else if(RAW_JSON_DATA[currentChar] == ']'){
				nestCount--;
				inArray.pop_back();
				arrayName.pop_back();
			}

			else if(RAW_JSON_DATA[currentChar] == 'n' && inArray[nestCount-1]){
				cout<<"----null object----"<<endl;//debug code
				currentObject.arrays[arrayName[nestCount-1]].push_back(JsonObject());
				currentChar+=3;
			}

			else if((RAW_JSON_DATA[currentChar] == 't' || RAW_JSON_DATA[currentChar] == 'f') && inArray[nestCount-1]){
				cout<<"----bool object----"<<endl;//debug code
				SH::Value temp = makeValue(RAW_JSON_DATA,currentChar);
				if(temp.isBool()){
					currentObject.arrays[arrayName[nestCount-1]].push_back(JsonObject());
					currentObject.arrays[arrayName[nestCount-1]][currentObject.arrays[arrayName[nestCount-1]].size()-1].value = temp;
				}
			}
			
			else if((RAW_JSON_DATA[currentChar] >= '0' && RAW_JSON_DATA[currentChar] <= '9') && inArray[nestCount-1]){
				cout<<"----number object----"<<endl;//debug code
				SH::Value temp = makeValue(RAW_JSON_DATA,currentChar);
				if(temp.isNumber()){
					currentObject.arrays[arrayName[nestCount-1]].push_back(JsonObject());
					currentObject.arrays[arrayName[nestCount-1]][currentObject.arrays[arrayName[nestCount-1]].size()-1].value = temp;
				}
			}

			else if(RAW_JSON_DATA[currentChar] == '"' && inArray[nestCount-1]){
				cout<<"----string object----"<<endl;//debug code
				SH::Value temp = makeValue(RAW_JSON_DATA,currentChar);
				if(temp.isString()){
					currentObject.arrays[arrayName[nestCount-1]].push_back(JsonObject());
					currentObject.arrays[arrayName[nestCount-1]][currentObject.arrays[arrayName[nestCount-1]].size()-1].value = temp;
				}
			}

			currentChar++;
		}
	}
}