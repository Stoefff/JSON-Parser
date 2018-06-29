#include "NullValue.h"

NullValue::NullValue(){
}

NullValue::NullValue(const NullValue& rhs){
}

NullValue::~NullValue(){
}

Value* NullValue::clone() const {
    return new NullValue(*this);
}
