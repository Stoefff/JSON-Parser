#include "Object.h"
#include <iostream>

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
        *arr[i] = *rhs.arr[i]; //Here meybe it will fuck up
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

void Object::addPair(const Pair* pair){
    if(pair == nullptr){
        std::cerr << "Enter valid val to add" << std::endl;
    }
    if(size == cap){
        resize();
    }
    *arr[size] = *pair; //Calling the copy constructor of the object
    // Not just shallow coping the pointers
    size++;
}

// Implement this later
void Object::removePair(){

}

Value* Object::clone() const {
    return new Object(*this);
}
