//file: SH Value.cpp
//project: SH Value
//Author: Tim Solum
//version: 1.42
//date: 4/21/2012

#include "SH Value.h"
#include <iostream>
#include <sstream>
//begin SH namespace
namespace SH{

//Value class/////////////////////////////////////////
	Value::Value(){
		isItNumber = false;
		isItString = false;
		isItBool = false;
		str = NULL;
		number = NULL;
		boolean = NULL;
	};
	Value::Value(const Value& copy){ //copy constructor
		isItNumber = copy.isNumber();
		isItString = copy.isString();
		isItBool = copy.isBool();
		if(isNumber()){
			number = new double;
			*number = copy.asNumber();
			str = NULL;
			boolean = NULL;
		}
		else if(isString()){
			str = new string;
			*str = copy.asString();
			number = NULL;
			boolean = NULL;
		}
		else if(isBool()){
			boolean = new bool;
			*boolean = copy.asBool();
			number = NULL;
			str = NULL;
		}
		
	}
	Value::Value(double num){
		isItNumber = true;
		isItString = false;
		isItBool = false;
		str = NULL;
		boolean = NULL;
		number = new double;
		*number = num;
	}
	Value::Value(int num){
		isItNumber = true;
		isItString = false;
		isItBool = false;
		str = NULL;
		boolean = NULL;
		number = new double;
		*number = num;
	}
	Value::Value(string setString){
		isItString = true;
		isItNumber = false;
		isItBool = false;
		number = NULL;
		boolean = NULL;
		str = new string;
		*str = setString;
	}
	Value::Value(const char setString[]){
		isItString = true;
		isItNumber = false;
		isItBool = false;
		number = NULL;
		boolean = NULL;
		str = new string;
		*str = setString;
	}
	Value::Value(bool setBool){
		isItBool = true;
		isItNumber = false;
		isItString = false;
		number = NULL;
		str = NULL;
		boolean = new bool;
		*boolean = setBool;
	}
	Value::~Value(){
		if(isNumber()){
			delete number;
			number = NULL;
			isItNumber = false;
		}
		if(isString()){
			delete str;
			str = NULL;
			isItString = false;
		}
		if(isBool()){
			delete boolean;
			boolean = NULL;
			isItBool = false;
		}
	}
	
	
	string Value::asString() const{
		if(isString()){
			return *str;
		}
		else if(isNumber()){
			ostringstream result;
			result << *number;
			return result.str();
		}
		else if(isBool()){
			ostringstream result;
			result << *boolean;
			return result.str();
		}
	}
	double Value::asNumber() const{
		if(isNumber()){
			return *number;
		}
		else if(isString()){
			double result;
			istringstream ss(*str);
			ss >> result;
			if (!ss) throw invalid_argument( "StrToInt" );
			return result;
		}
		else if(isBool()){
			return *boolean;
		}
	}
	bool Value::asBool() const{
		if(isBool()){
			return *boolean;
		}
		else if(isString()){
			if(*str == "true"){
				return true;
			}
			else if(*str == "false"){
				return false;
			}
		}
		else{
			cout<<"Not a bool.\n";
		}
	}
	bool Value::isNumber() const{
		return isItNumber;
	}
	bool Value::isString() const{
		return isItString;
	}
	bool Value::isBool() const{
		return isItBool;
	}

	//assignment operator overloads for Value
	void Value::operator=(const Value& newValue){
		if(newValue.isNumber()){
			*this = newValue.asNumber();
		}
		else if(newValue.isString()){
			*this = newValue.asString();
		}
		else if(newValue.isBool()){
			*this = newValue.asBool();
		}
	}
	void Value::operator=(double newValue){
		if(!isNumber()){
			number = new double;
			isItNumber = true;
		}
		if(isString()){
			delete str;
			str = NULL;
			isItString = false;
		}
		if(isBool()){
			delete boolean;
			boolean = NULL;
			isItBool = false;
		}
		*number = newValue;
	}
	void Value::operator=(int newValue){
		if(!isNumber()){
			number = new double;
			isItNumber = true;
		}
		if(isString()){
			delete str;
			str = NULL;
			isItString = false;
		}
		if(isBool()){
			delete boolean;
			boolean = NULL;
			isItBool = false;
		}
		*number = newValue;
	}
	void Value::operator=(string newValue){
		if(!isString()){
			str = new string;
			isItString = true;
		}
		if(isNumber()){
			delete number;
			number = NULL;
			isItNumber = false;
		}
		if(isBool()){
			delete boolean;
			boolean = NULL;
			isItBool = false;
		}
		*str = newValue;
	}
	void Value::operator=(const char newValue[]){
		if(!isString()){
			str = new string;
			isItString = true;
		}
		if(isNumber()){
			delete number;
			number = NULL;
			isItNumber = false;
		}
		if(isBool()){
			delete boolean;
			boolean = NULL;
			isItBool = false;
		}
		*str = newValue;
	}
	void Value::operator=(bool newValue){
		if(!isBool()){
			boolean = new bool;
			isItBool = true;
		}
		if(isNumber()){
			delete number;
			number = NULL;
			isItNumber = false;
		}
		if(isString()){
			delete str;
			str = NULL;
			isItString = false;
		}
		*boolean = newValue;
	}

	//addition operators for Value
	Value Value::operator+(const Value& addValue){
		if(isNumber() && addValue.isNumber()){
			return *this + addValue.asNumber();
			//return Value(asNumber() + addValue.asNumber());
		}
		else if(isString() && addValue.isString()){
			return *this + addValue.asString();
			//return Value(asString() + addValue.asString());
		}
		else{
			cout<<"Incompatible types.\n";
		}	
	}
	double Value::operator+(double addValue){
		if(isNumber()){
			return *number + addValue;
		}
		else{
			cout<<"Incompatible types.\n";
		}
	}
	string Value::operator+(string addValue){
		if(isString()){
			return asString() + addValue;
		}
		else{
			cout<<"Incompatible types.\n";
		}
	}
	string Value::operator+(const char addValue[]){
		if(isString()){
			return asString() + addValue;
		}
		else{
			cout<<"Incompatible types.\n";
		}
	}

	//subtraction operators (number)
	Value Value::operator-(const Value& subtractValue){
		if(isNumber() && subtractValue.isNumber()){
			return *this - subtractValue.asNumber();
		}
		else if(isString() && subtractValue.isString()){
			cout<<"Cannot subtract strings\n";
		}
		else{
			cout<<"Incompatible types.\n";
		}
	}
	double Value::operator-(double subtractValue){
		return *number - subtractValue;
	}

	//plus equals operators
	void Value::operator+=(const Value& plusEqualValue){
		if(isNumber() && plusEqualValue.isNumber()){
			*this = *this + plusEqualValue.asNumber();
		}
		else if(isString() && plusEqualValue.isString()){
			*this = asString() + plusEqualValue.asString();
		}
		else{
			cout<<"Incompatible types.\n";
		}
	}
	void Value::operator+=(double plusEqualValue){
		if(isNumber()){
			*this = *this + plusEqualValue;
		}
		else{
			cout<<"Incompatible types.\n";
		}
	}
	void Value::operator+=(string plusEqualValue){
		if(isString()){
			*this = *this + plusEqualValue;
		}
		else{
			cout<<"Incompatible types.\n";
		}
	}
	void Value::operator+=(const char plusEqualValue[]){
		if(isString()){
			*this = *this + plusEqualValue;
		}
		else{
			cout<<"Incompatible types.\n";
		}
	}

	///minus equals operators (number)
	void Value::operator-=(const Value& minusEqualValue){
		if(isNumber() && minusEqualValue.isNumber()){
			*this = *this - minusEqualValue.asNumber();
		}
		else if(isString() && minusEqualValue.isString()){
			cout<<"Cannot subtract string.\n";
		}
		else{
			cout<<"Incompatible types.\n";
		}
	}
	void Value::operator-=(double minusEqualValue){
		if(isNumber()){
			*this = *this - minusEqualValue;
		}
		else{
			cout<<"Incompatible types.\n";
		}
	}
	//postfix (for number)
	double Value::operator++(){
		if(isNumber()){
			*this+=1;
			return asNumber();
		}
		else{
			cout<<"Cant't increment type.\n";
		}
	}
	//prefix (for number)
	double Value::operator++(int){
		if(isNumber()){
			*this+=1;
			return asNumber()-1;
		}
		else{
			cout<<"Cant't increment type.\n";
		}
	}

	//postfix (for number)
	double Value::operator--(){
		if(isNumber()){
			*this-=1;
			return asNumber();
		}
		else{
			cout<<"Cant't decrement type.\n";
		}
	}
	//prefix (for number)
	double Value::operator--(int){
		if(isNumber()){
			*this-=1;
			return asNumber()+1;
		}
		else{
			cout<<"Cant't decrement type.\n";
		}
	}

	//index (for string)
	char Value::operator[](int index){
		if(isString()){
			return (*str)[index];
		}
		else{
			cout<<"Can't index an current type.\n";
		}
	}

	//comparison operators for Values
	bool Value::operator==(const Value& other) const{
		bool equal = false;
		if(isNumber() && other.isNumber()){
			equal = asNumber() == other.asNumber();
		}
		else if(isString() && other.isString()){
			equal = asString() == other.asString();
		}
		else if(isBool() && other.isBool()){
			equal = asBool() == other.asBool();
		}
		else{
			cout<<"Incompatible types.\n";
		}
		return equal;
	}
	bool Value::operator!=(const Value& other) const{
		return !(*this == other);
	}
	bool Value::operator>(const Value& other) const{
		bool greater = false;
		if(isNumber() && other.isNumber()){
			greater = asNumber() > other.asNumber();
		}
		else if(isString() && other.isString()){
			greater = asString() > other.asString();
		}
		else{
			cout<<"Incompatible types.\n";
		}
		return greater;
	}
	bool Value::operator>=(const Value& other) const{
		return (*this > other || *this == other);
	}
	bool Value::operator<(const Value& other) const{
		return !(*this >= other);
	}
	bool Value::operator<=(const Value& other) const{
		return !(*this > other);
	}

	//comparison operators for numbers
	bool Value::operator==(double other) const{
		bool equal = false;
		if(isNumber()){
			equal = *number == other;
		}
		return equal;
	}
	bool Value::operator!=(double other) const{
		return !(*this == other);
	}
	bool Value::operator>(double other) const{
		bool greater = false;
		if(isNumber()){
			greater = *number > other;
		}
		return greater;
	}
	bool Value::operator>=(double other) const{
		return (*this > other || *this == other);
	}
	bool Value::operator<(double other) const{
		return !(*this >= other);
	}
	bool Value::operator<=(double other) const{
		return (*this < other || *this == other);
	}
	bool Value::operator==(int other) const{
		bool equal = false;
		if(isNumber()){
			equal = *number == other;
		}
		return equal;
	}
	bool Value::operator!=(int other) const{
		return !(*this == other);
	}
	bool Value::operator>(int other) const{
		bool greater = false;
		if(isNumber()){
			greater = *number > other;
		}
		return greater;
	}
	bool Value::operator>=(int other) const{
		return (*this > other || *this == other);
	}
	bool Value::operator<(int other) const{
		return !(*this >= other);
	}
	bool Value::operator<=(int other) const{
		return (*this < other || *this == other);
	}

	//comparison operators for strings
	bool Value::operator==(string other) const{
		bool equal = false;
		if(isString()){
			equal = *str == other;
		}
		return equal;
	}
	bool Value::operator!=(string other) const{
		return !(*this == other); 
	}
	bool Value::operator>(string other) const{
		bool greater = false;
		if(isString()){
			greater = *str > other;
		}
		return greater;
	}
	bool Value::operator>=(string other) const{
		return (*this > other || *this == other);
	}
	bool Value::operator<(string other) const{
		return !(*this >= other);
	}
	bool Value::operator<=(string other) const{
		return (*this < other || *this == other);
	}
	//comparison operators for bools
	bool Value::operator==(bool other) const{
		bool equal = false;
		if(isBool()){
			equal = *boolean == other;
		}
		return equal;
	}
	bool Value::operator!=(bool other) const{
		return !(*this == other); 
	}

	///ostream operator<<
	ostream& operator<<(ostream& out, const Value& value){
		if(value.isNumber()){
			out<<value.asNumber();
		}
		else if(value.isString()){
			out<<value.asString();
		}
		else if(value.isBool()){
			out<<value.asBool();
		}
		return out;
	}

//end Value class////////////////////////////////////////////////////////////////////////////////////

}

////////end SH namespace