#include "Pair.h"

Pair::Pair(String* str, Value* val){
    *this->str = *str;
    *this->val = *val;
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

void Pair::copy(const Pair& rhs){
    *this->str = *rhs.str;
    *this->val = *rhs.val;
}
