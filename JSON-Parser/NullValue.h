#ifndef __NULL__VALUE__HEADER
#define __NULL__VALUE__HEADER

#include "Value.h"

class NullValue : public Value {
    NullValue();
    NullValue(const NullValue& rhs);
    //NullValue& operator=(const NullValue& rhs);
    ~NullValue();

    virtual Value* clone() const override;
};

#endif
