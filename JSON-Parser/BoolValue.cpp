#include "BoolValue.h"

BoolValue::BoolValue(const bool* var)
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
