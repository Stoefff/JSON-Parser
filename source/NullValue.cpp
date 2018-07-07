#include "NullValue.h"
#include <iostream>

using std::cout;

NullValue::NullValue(){
}

NullValue::~NullValue(){
}

Value* NullValue::clone() const {
    return new NullValue(*this);
}

void NullValue::printContent(int dept, ostream& stream) const {
	stream << "null";
}

void NullValue::printCompactContent(ostream& stream) const {
	stream << "null";
}

Value* NullValue::searchPath(char** keys, int dept,
	int maxDept) const {
	return nullptr;
}