#ifndef __JSON__PARSER__HEADER
#define __JSON__PARSER__HEADER

#include "Object.h"

class JsonParser{
public:
    JsonParser();
    JsonParser(const JsonParser& rhs);
    JsonParser& operator=(const JsonParser& rhs);
    ~JsonParser();

private:
    Object* object;
};

#endif
