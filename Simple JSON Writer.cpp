//file: Simple JSON Writer.cpp
//project: Simple JSON Writer
//Author: Tim Solum
//version: 1.37
//date: 5/14/2012

#include "Simple JSON Writer.h"
#include <iostream>
namespace SH{

	JsonWriter::JsonWriter(){
		
	}
	JsonWriter::~JsonWriter(){
		if(out.is_open()){
			out.close();
		}
	}
	
	void JsonWriter::addPair(Value name, Value value){
		root.pairs[name] = value;
	}
	void JsonWriter::addObject(Value name, JsonObject value){
		root.objects[name] = value;
	}
	void JsonWriter::addArray(Value name, vector<JsonObject> value){
		root.arrays[name] = value;
	}

	void JsonWriter::write(string filename){
		out.open(filename);
		writeObject(root);
		out.close();
	}

//helper function
	void JsonWriter::writeObject(JsonObject currentObject){
		out<<"{";
		//iterate through pairs
		typedef  map<Value,Value>::iterator it_type;
		for(it_type i = currentObject.pairs.begin(); i != currentObject.pairs.end(); i++){
			out<<'"'<<i->first<<'"';
			out<<": ";
			if(i->second == true){
				out<<"true";
			}
			else if(i->second == false){
				out<<"false";
			}
			else if(i->second.isNumber() == false && i->second.isString() == false && i->second.isBool() == false){
				out<<"null";
			}
			else if(i->second.isString()){
				out<<'"'<<i->second<<'"';
			}
			else{
				out<<i->second;
			}

			if(i == --currentObject.pairs.end() && currentObject.objects.size() == 0 && currentObject.arrays.size() == 0){
				out<<endl;
			}
			else{
				out<<",";
			}
		}

		//iterate through objects
		typedef  map<Value,JsonObject>::iterator it_type2;
		for(it_type2 i = currentObject.objects.begin(); i != currentObject.objects.end(); i++){
			
			out<<'"'<<i->first<<'"';
			out<<": ";
			writeObject(i->second);
			if(!(i == --currentObject.objects.end() && currentObject.arrays.size() == 0)){
				out<<",";
			}
			
		}

		//iterate through arays
		typedef  map<Value,vector<JsonObject>>::iterator it_type3;
		for(it_type3 i = currentObject.arrays.begin(); i != currentObject.arrays.end(); i++){
			out<<'"'<<i->first<<'"';
			out<<": ";
			out<<"[";
			for(int j=0;j<i->second.size();j++){
				if(i->second[j].arrays.size() == 0 && i->second[j].objects.size() == 0 && i->second[j].pairs.size() == 0){
					out<<"null";
				}
				else{
					writeObject(i->second[j]);
				}
				if(!(j+1 == i->second.size())){
					out<<",";
				}
			}
			out<<"]";
			if(!(i == --currentObject.arrays.end())){
				out<<",";
			}
		}
		out<<"}";
	}
}