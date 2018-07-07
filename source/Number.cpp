#include "Number.h"
#include <cstring>
#include <iostream>

using std::cout;
using std::ofstream;

Number::Number(const char* str)
	:num(nullptr)
	,size(strlen(str)) {
	this->num = new char[size + 1];
	strcpy(this->num, str);
}

Number::Number(const Number& rhs) {
	copy(rhs);
}

Number& Number::operator=(const Number& rhs) {
	if (this != &rhs) {
		free();
		copy(rhs);
	}
	return *this;
}

Number::~Number() {
	free();
}

void Number::free() {
	delete[] num;
	num = nullptr;
	size = 0;
}

void Number::copy(const Number& rhs) {
	this->size = rhs.size;
	this->num = new char[this->size + 1];
	strcpy(this->num, rhs.num);
}

Value* Number::clone() const {
	return new Number(*this);
}

void Number::printContent(int dept, ostream& stream) const {
	stream << this->num;
}

void Number::printCompactContent(ostream& stream) const {
	stream << this->num;
}

Value* Number::searchPath(char** keys, int dept,
	int maxDept) const {
	return nullptr;
}