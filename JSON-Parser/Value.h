#ifndef __VALUE__HEADER
#define __VALUE__HEADER

class Value {
public:
    Value();
    Value(const Value& rhs);
    //Value& operator=(const Value& rhs);
    virtual ~Value();

    virtual Value* clone() const = 0;
};

#endif
