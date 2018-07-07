#include "String.h"
#include <cstring>
#include <iostream>

using std::cout;
using std::ofstream;

String::String(const char* str)
    :str(nullptr)
    ,size(strlen(str)){
    this->str = new char[size + 1];
    strcpy(this->str, str);
}

String::String(const String& rhs){
    copy(rhs);
}

String& String::operator=(const String& rhs){
    if (this != &rhs){
        free();
        copy(rhs);
    }
    return *this;
}

String::~String(){
    free();
}

void String::free(){
    delete[] str;
    str = nullptr;
    size = 0;
}

void String::copy(const String& rhs){
    this->size = rhs.size;
    this->str = new char[this->size + 1];
    strcpy(this->str, rhs.str);
}

unsigned int String::getStringWeigth() const{
	unsigned int result = 0;
	char * itt = str;
	while (*itt){
		result += (unsigned int)(*itt);
		itt++;
	}
	return result;
}

Value* String::clone() const{
    return new String(*this);
}

void String::printContent(int dept, ostream& stream) const {
	stream << '\"' << this->str << '\"';
}

void String::printCompactContent(ostream& stream) const {
	stream << '\"' << this->str << '\"';
}

Value* String::searchPath(char** keys, int dept,
	int maxDept) const {
	return nullptr;
}

bool operator==(const String& str1, const String& str2) {
	unsigned int str1Weigth = str1.getStringWeigth();
	unsigned int str2Weigth = str2.getStringWeigth();
	return ((str1Weigth == str2Weigth) ? true : false);
}