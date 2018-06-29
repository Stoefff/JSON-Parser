#ifndef __Bool__Value__HEADER
#define __Bool__Value__HEADER

#include "Value.h"

class BoolValue: public Value {
public:
    BoolValue(const bool* var);
    BoolValue(const BoolValue& rhs);
    BoolValue& operator=(const BoolValue& rhs);
    ~BoolValue();

    virtual Value* clone() const override;

private:
    bool var;
};

#endif
