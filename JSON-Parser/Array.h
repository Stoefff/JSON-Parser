#ifndef __ARRAY__HEADER
#define __ARRAY__HEADER

#include "Value.h"

class Array : public Value{
public:
    Array();
    Array(const Array& rhs);
    Array& operator=(const Array& rhs);
    virtual ~Array() override;

    void addElement(const Value* val);
    //Clear this!
    void removeElement();

    virtual Value* clone() const override;

private:
    void resize();
    void free();
    void copy(const Array& rhs);

private:
    Value** arr;
    int size;
    int cap;
};

#endif
