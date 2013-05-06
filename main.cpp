//file: main.cpp
//project: Simple JSON Parser
//Author: Tim Solum
//version: 1.00
//date: 4/21/2012

#include <iostream>
#include <map>
#include <string>


using namespace std;

#include "Simple JSON Parser.h"
#include "Simple JSON Writer.h"

int main(){
	SH::JsonParser parser;
	
	parser.readFile("blah.json");//PASS

	//parser.readFile("Test Map One.json");//PASS!!!
	//parser.readFile("array bug test.json");//PASS!!!!!
	//parser.readFile("test4.json");//PASS
	//parser.readFile("simple test.json");//PASS
	//parser.readFile("test1.json");//PASS
	//parser.readFile("test2.json");//PASS
	//parser.readFile("test3.json");//PASS
	
	//parser.readFile("myJsonTest.json");//PASS
	parser.parse();

	return 0;

	//parsing escape characters
	/*
	SH::JsonWriter writer;
	writer.addPair("hello",2);
	writer.addPair("hi",null);
	writer.addPair("rawr",true);
	writer.addPair("a",false);
	writer.addPair("Tim","isawesome");

	SH::JsonObject test;
	test.pairs["ohayo"] = 1.443;

	SH::JsonObject ed;
	ed.pairs["meh"] = "gh";
	ed.pairs["rargarga"] = "\\\"how are you?\\\""; 

	writer.addObject("ed",ed);

	SH::JsonArray tim;
	tim.push_back(null_obj);
	tim.push_back(null_obj);
	tim.push_back(test);

	writer.addArray("tim",tim);
	writer.write("myJsonTest.json");
	
	///////////////////////////
	
	SH::JsonParser parser;
	parser.readFile("myJsonTest.json");
	parser.parse();
	
	cout<<parser.Root().arrays["n"][0].pairs["m"]<<endl;
	/*
	cout<<parser.Root().pairs["Tim"]<<endl;
	cout<<parser.Root().pairs["a"]<<endl;
	cout<<parser.Root().pairs["hello"]<<endl;
	cout<<parser.Root().pairs["hi"]<<endl;
	cout<<parser.Root().pairs["rawr"]<<endl;
	cout<<parser.Root().objects["ed"].pairs["rargarga"]<<endl;
	cout<<parser.Root().arrays["tim"][2].pairs["ohayo"]<<endl;
	*/
}



/*

HOW TO ACCESS JSON IN JAVASCRIPT
parser.menu.id  -> "file"
parser.menu.popup.menuitem[0].value -> "New"

HOW I WANT TO DO IT IN C++
parser["menu"]["id"] -> "file"
parser["menu"]["popup"]["menuitem"][0]["value"] -> "New"
*/