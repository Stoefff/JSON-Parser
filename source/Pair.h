#ifndef __PAIR__HEADER__
#define __PAIR__HEADER__

#include "String.h"
#include "Value.h"
#include <iostream>

using std::ostream;

class Pair {
public:
    Pair(String* str, Value* val);
    Pair(const Pair& rhs);
    Pair& operator=(const Pair& rhs);
    ~Pair();

	String* getKey() const;
	Value* getValue() const;

	void printContent(int dept, ostream& stream) const;
	void printCompactContent(ostream& stream) const;

private:
    void free();
    void copy(const Pair& rhs);

private:
    String* str;
    Value* val;
};

#endif
