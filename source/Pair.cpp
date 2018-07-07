#include "Pair.h"
#include <iostream>

using std::cout;

Pair::Pair(String* str, Value* val){
    this->str = str;
    this->val = val;
}

Pair::Pair(const Pair& rhs){
    copy(rhs);
}

Pair& Pair::operator=(const Pair& rhs){
    if(this != &rhs){
        free();
        copy(rhs);
    }
    return *this;
}

Pair::~Pair(){
    free();
}

void Pair::free(){
    delete str; 
    str = nullptr;
    delete val;
    val = nullptr;
}

// Should it be shollow or deep copy ???
void Pair::copy(const Pair& rhs){
    this->str = rhs.str;
    this->val = rhs.val;
}

void Pair::printContent(int dept, ostream& stream) const {
	str->printContent(dept, stream);
	stream << " : ";
	val->printContent(dept, stream);
}

void Pair::printCompactContent(ostream& stream) const {
	str->printCompactContent(stream);
	stream << ":";
	val->printCompactContent(stream);
}

String* Pair::getKey() const{
	return this->str;
}

Value* Pair::getValue() const {
	return this->val;
}