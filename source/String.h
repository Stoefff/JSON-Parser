#ifndef __STRING__HEADER
#define __STRING__HEADER

#include "Value.h"

#include <iostream>

using std::ofstream;

class String: public Value{
public:
    String(const char* str);
    String(const String& rhs);
    String& operator=(const String& rhs);
    virtual ~String() override;

	unsigned int getStringWeigth() const;

    virtual Value* clone() const override;
	virtual void printContent(int dept, ostream& stream) const override;
	virtual void printCompactContent(ostream& stream) const override;
	virtual Value* searchPath(char** keys, int dept,
		int maxDept) const override;

private:
    void free();
    void copy(const String& rhs);

private:
    char* str;
    int size;
};

bool operator==(const String& str1, const String& str2);

#endif
