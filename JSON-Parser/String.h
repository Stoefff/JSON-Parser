#ifndef __STRING__HEADER
#define __STRING__HEADER

#include "Value.h"

class String: public Value{
public:
    String(const char* str);
    String(const String& rhs);
    String& operator=(const String& rhs);
    virtual ~String() override;

    //int getSize() const;

    virtual Value* clone() const override;

private:
    void free();
    void copy(const String& rhs);

private:
    char* str;
    int size;
};

#endif
