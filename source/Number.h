#ifndef __NUMBER__HEADER
#define __NUMBER__HEADER

#include "Value.h"

// The number will be represented as string because
// of its parse complexity which i do not know
// how to parse as a primitive type in c++
class Number : public Value{
public:
	Number(const char* str);
	Number(const Number& rhs);
	Number& operator=(const Number& rhs);
	virtual ~Number() override;

	virtual Value* clone() const override;
	virtual void printContent(int dept, ostream& stream) const override;
	virtual void printCompactContent(ostream& stream) const override;
	virtual Value* searchPath(char** keys, int dept,
		int maxDept) const override;

private:
	void free();
	void copy(const Number& rhs);

private:
	char* num; // :(
	int size;

};

#endif
