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
	Value* operator[](size_t pos);

    virtual Value* clone() const override;
	virtual void printContent(int dept, ostream& stream) const override;
	virtual void printCompactContent(ostream& stream) const override;
	virtual Value* searchPath(char** keys, int dept,
		int maxDept) const override;

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
