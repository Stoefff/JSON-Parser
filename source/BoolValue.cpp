#include "BoolValue.h"
#include <iostream>

using std::cout;

BoolValue::BoolValue(const bool var)
    :var(var){
}

BoolValue::BoolValue(const BoolValue& rhs){
    var = rhs.var;
}

BoolValue& BoolValue::operator=(const BoolValue& rhs){
    if (this != &rhs){
        var = rhs.var;
    }
    return *this;
}

BoolValue::~BoolValue(){
}

Value* BoolValue::clone() const {
    return new BoolValue(*this);
}

void BoolValue::printContent(int dept, ostream& stream) const {
	if (var) {
		stream << "true";
	}
	else {
		stream << "false";
	}
}

void BoolValue::printCompactContent(ostream& stream) const {
	if (var) {
		stream << "true";
	}
	else {
		stream << "false";
	}
}

Value* BoolValue::searchPath(char** keys, int dept,
	int maxDept) const {
	return nullptr;
}