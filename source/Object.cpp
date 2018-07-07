#include "Object.h"
#include <iostream>

using std::cout;

Object::Object()
    :arr(nullptr)
    ,size(0)
    ,cap(2){
    arr = new Pair*[cap];
}

Object::Object(const Object& rhs){
    copy(rhs);
}

Object& Object::operator=(const Object& rhs){
    if(this != &rhs){
        free();
        copy(rhs);
    }
    return *this;
}

Object::~Object(){
    free();
}

void Object::free(){
    for(int i = 0; i < size; i++){
        delete arr[i];
    }
    delete[] arr;
    arr = nullptr;
    size = 0;
    cap = 0;
}

void Object::copy(const Object& rhs){
    this->cap = rhs.cap;
    this->size = rhs.size;
    this->arr = new Pair*[cap];
    for(int i = 0; i < size; i++){
        arr[i] = rhs.arr[i]; //Here meybe it will fuck up
    }
}

void Object::resize(){
    Pair** temp = new Pair*[cap * 2];
    for(int i = 0; i < size; i++){
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
    temp = nullptr;
    cap *= 2;
}

void Object::addPair(Pair* pair){
    if(pair == nullptr){
        std::cerr << "Enter valid val to add" << std::endl;
    }
    if(size == cap){
        resize();
    }
    arr[size] = pair;
    size++;
}

void Object::removePair(Pair* pair){
	for (int i = 0; i < size; i) {
		if (arr[i] == pair) {
			delete pair;
			for (int j = i; j < size - 1; j++) {
				arr[j] = arr[j + 1];
			}
		}
	}
}


Value* Object::clone() const {
    return new Object(*this);
}

Pair* Object::operator[](size_t pos){
    return (pos >= size) ? nullptr : arr[pos];
}
/*
Object& Object::operator+=(const Object& obj){
    for (int i = 0; i < obj.size; i++){

    }
}
*/

void Object::printContent(int dept, ostream& stream) const {
	char* tabs = getTabs(dept);
	stream << '{' << '\n';
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
	stream << tabs << '}';
	delete[] tabs;
}

void Object::printCompactContent(ostream& stream) const {
	stream << '{';
	for (int i = 0; i < size; i++) {
		arr[i]->printCompactContent(stream);
		if (i != size - 1) {
			stream << ',';
		}
	}
	stream << '}';
}

//value*
Value* Object::searchPath(char** keys, int dept,
	int maxDept) const {
	if (dept == maxDept) {
		Array* temp = findKey(keys[dept]);
		return temp;
	}
	String neededKey(keys[dept]);
	for (int i = 0; i < size; i++) {
		if (neededKey == *(arr[i]->getKey())) {
			Value* temp = arr[i]->getValue()
				->searchPath(keys, dept + 1, maxDept);
			if (temp != nullptr) {
				return temp;
			}
		}
	}
	return nullptr;
}

//Array*
Array* Object::findKey(char* key) const{
	Array* temp = new Array();
	String neededKey(key);
	for (int i = 0; i < size; i++) {
		if (neededKey == *arr[i]->getKey()) {
			Object* obj = new Object();
			// * because the copy constructor want a object
			//Not a pointer
			String* key = new String(*arr[i]->getKey());
			Value* val = arr[i]->getValue()->clone();
			Pair* pair = new Pair(key, val);
			obj->addPair(pair);
			temp->addElement(obj);
		}
	}
	if (&temp[0] == nullptr) {
		return nullptr;
	}
	else {
		return temp;
	}
}

Object* Object::searchObject(char** keys, int dept, int maxDept){
	String neededKey(keys[dept]);
	for (int i = 0; i < size; i++) {
		if (neededKey == *(arr[i]->getKey())) {
            if (dept == maxDept - 1) {
                return dynamic_cast<Object*>(arr[i]->getValue());
        	} else {
                return searchObject(keys, dept+1, maxDept);
            }
		}
	}
	return nullptr;
}

Pair* Object::searchObjectFull(char** keys, int dept, int maxDept) {
	String neededKey(keys[dept]);
	for (int i = 0; i < size; i++) {
		String chechThis(*(arr[i]->getKey()));
		if (neededKey == *(arr[i]->getKey())) {
			if (dept == maxDept) {
				return arr[i];
			}
			else {
				return searchObjectFull(keys, dept + 1, maxDept);
			}
		}
	}
	return nullptr;
}
