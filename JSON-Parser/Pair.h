#ifndef __PAIR__HEADER__
#define __PAIR__HEADER__

#include "String.h"
#include "Value.h"

class Pair {
public:
    Pair(String* str, Value* val);
    Pair(const Pair& rhs);
    Pair& operator=(const Pair& rhs);
    ~Pair();

private:
    void free();
    void copy(const Pair& rhs);

private:
    String* str;
    Value* val;
};

#endif
