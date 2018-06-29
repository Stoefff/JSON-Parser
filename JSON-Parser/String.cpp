#include "String.h"
#include <cstring>

String::String(const char* str)
    :str(nullptr)
    ,size(strlen(str)){
    str = new char[size + 1];
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

Value* String::clone() const{
    return new String(*this);
}

/*
int String::getSize() const {
    return this->size;
}
*/
