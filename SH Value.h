//file: SH Value.h
//project: SH Value
//Author: Tim Solum
//version: 1.42
//date: 4/21/2012

#ifndef _JSON_VALUE_H_
#define _JSON_VALUE_H_

#include <string>
using namespace std;

//can hold int, float, double, string, bool
//can be used in arrays perfectly (have not tested other ADTs, should work fine)
//operators =  +  -  +=  -= prefix postfix ++ -- relational operators
//please note, this class does not use exceptions (for now)
//errors are put to cout and the screen
namespace SH{
	
	class Value{
	public:
		//default constructor
		//str = NULL   else = NULL
		//isItString = false   else = false
		Value();
		//copy constructor
		Value(const Value& copy);
		//double constructor
		//str = NULL   else = new double
		//isItString = false    else = true
		Value(double num);
		//int constructor
		//str = NULL   else = new double
		//isItString = false    else = true
		Value(int num);
		//string constructor
		//str = new string   else = NULL
		//isItString = true    else = false
		Value(string setString);
		//const char[] constructor
		//str = new string   else = NULL
		//isItString = true    else = false
		Value(const char setString[]);
		//bool constructor
		//boolean = new bool   else = NULL
		//isItBool = true    else = false
		Value(bool setBool);
		//deconstructor
		//deletes dynamic memory
		//str = NULL    number = NULL    boolean = NULL
		~Value();
		
		//return Value as a string
		string asString() const;
		//return Value as a number
		double asNumber() const;
		//return Value as a bool if Value is a bool
		bool asBool() const;

		//check to see if Value is a number
		bool isNumber() const;
		//check to see if Value is a string
		bool isString() const;
		//check to see if Value is a bool
		bool isBool() const;

		//assignment operators
		void operator=(const Value& newValue);
		void operator=(double newValue);
		void operator=(int newValue);
		void operator=(string newValue);
		void operator=(const char newValue[]);
		void operator=(bool newValue);
		
		//addition operators
		Value operator+(const Value& addValue);
		double operator+(double addValue);
		string operator+(string addValue);
		string operator+(const char addValue[]);

		//subtraction operators (number)
		Value operator-(const Value& subtractValue);
		double operator-(double subtractValue);

		//plus equals operators
		void operator+=(const Value& plusEqualValue);
		void operator+=(double plusEqualValue);
		void operator+=(string plusEqualValue);
		void operator+=(const char plusEqualValue[]);

		//minus equals operators (number)
		void operator-=(const Value& minusEqualValue);
		void operator-=(double minusEqualValue);

		//prefix (for number)
		double operator++();
		//postfix (for number)
		double operator++(int);

		//prefix (for number)
		double operator--();
		//postfix (for number)
		double operator--(int);

		//index (for string)
		char operator[](int index);

		//comparison operators for Values
		bool operator==(const Value& other) const;
		bool operator!=(const Value& other) const;
		bool operator>(const Value& other) const;
		bool operator>=(const Value& other) const;
		bool operator<(const Value& other) const;
		bool operator<=(const Value& other) const;

		//comparison operators for numbers
		bool operator==(double other) const;
		bool operator!=(double other) const;
		bool operator>(double other) const;
		bool operator>=(double other) const;
		bool operator<(double other) const;
		bool operator<=(double other) const;
		bool operator==(int other) const;
		bool operator!=(int other) const;
		bool operator>(int other) const;
		bool operator>=(int other) const;
		bool operator<(int other) const;
		bool operator<=(int other) const;

		//comparison operators for strings
		bool operator==(string other) const;
		bool operator!=(string other) const;
		bool operator>(string other) const;
		bool operator>=(string other) const;
		bool operator<(string other) const;
		bool operator<=(string other) const;

		//comparison operators for bools
		bool operator==(bool other) const;
		bool operator!=(bool other) const;

	private:
		double *number;   //pointer to double, where number is held
		bool isItNumber;  //holds if Value is a number or not

		string *str;      //pointer to string, where string is held
		bool isItString;  //holds if Value is a string or not

		bool* boolean;    //pointer to bool, where bool is held
		bool isItBool;    //holds if Value is a bool or not
	};

	//outputs to ostream
	//will output Value as the data type it currently is
	//if str == NULL and number == NULL
	//will output empty string
	ostream& operator<<(ostream& out, const Value &value);

}

#endif