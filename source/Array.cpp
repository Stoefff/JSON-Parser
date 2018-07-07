#include "Array.h"
#include <iostream>

using std::cout;

Array::Array()
    :arr(nullptr)
    ,size(0)
    ,cap(2){
    this->arr = new Value*[cap];
}

Array::Array(const Array& rhs){
    copy(rhs);
}

Array& Array::operator=(const Array& rhs){
    if (this != &rhs){
        free();
        copy(rhs);
    }
    return *this;
}

Array::~Array(){
    free();
}

void Array::free(){
    for(int i = 0; i < size; i++){
        delete arr[i];
    }
    delete[] arr;
    arr = nullptr;
    size = 0;
    cap = 0;
}

void Array::copy(const Array& rhs){
    this->cap = rhs.cap;
    this->size = rhs.size;
    this->arr = new Value*[cap];
    for(int i = 0; i < size; i++){
        arr[i] = rhs.arr[i]->clone();
    }
}

void Array::resize(){
    Value** temp = new Value*[cap*2];
    for(int i = 0; i < size; i++){
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
    temp = nullptr;
    cap *= 2;
}

void Array::addElement(const Value* val){
    if (val == nullptr){
        std::cerr << "Enter valid val to add" << std::endl;
    }
    if(size == cap){
        resize();
    }
    arr[size] = val->clone();
    size++;
}

//Implement this later
void Array::removeElement(){

}

Value* Array::clone() const {
    return new Array(*this);
}

void Array::printContent(int dept, ostream& stream) const {
	char* tabs = getTabs(dept);
	stream << '['<< '\n';
	for (int i = 0; i < size; i++) {
		stream << tabs;
		arr[i]->printContent(dept+1, stream);
		if (i != size - 1) {
			stream << ',' << '\n';
		}
		else {
			stream << '\n';
		}
	}
	tabs = getTabs(dept - 1);
	stream << tabs << ']';
	delete[] tabs;
}

Value* Array::operator[](size_t pos) {
	return (pos >= size) ? nullptr : arr[pos];
}

void Array::printCompactContent(ostream& stream) const {
	stream << '[';
	for (int i = 0; i < size; i++) {
		arr[i]->printCompactContent(stream);
		if (i != size - 1) {
			stream << ',';
		}
	}
	stream << ']';
}

Value* Array::searchPath(char** keys, int dept,
	int maxDept) const {
	return nullptr;
}