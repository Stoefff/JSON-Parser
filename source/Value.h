#ifndef __VALUE__HEADER
#define __VALUE__HEADER

#include <iostream>

using std::ostream;

class Value {
public:
    Value();
    virtual ~Value();

    virtual Value* clone() const = 0;
	virtual void printContent(int dept, ostream& stream) const = 0;
	virtual void printCompactContent(ostream& stream) const = 0;
	char* getTabs(int dept) const;
	virtual Value* searchPath(char** keys, int dept,
		int maxDept) const = 0;
};

#endif
