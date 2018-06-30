#ifndef __JSON__PARSER__HEADER
#define __JSON__PARSER__HEADER

#include "Value.h"
#include "Object.h"
#include "Array.h"
#include "BoolValue.h"
#include "NullValue.h"
#include "Number.h"
#include "Pair.h"
#include "String.h"
#include "Value.h"

class JsonParser{
public:
    JsonParser(const char* filename);
    JsonParser(const JsonParser& rhs);
    JsonParser& operator=(const JsonParser& rhs);
    ~JsonParser();

    //void run();

private:
    void free();
    void copy(const JsonParser& rhs);

    char* getJsonString(const char* filename);
    int getFileSize(const char* filename);

    void skipWhiteSpace(char*& str);
    Object* parseObject(char*& str);
    String* parseString(char*& str);
    Array* parseArray(char*& str);
    BoolValue* parseBoolValue(char*& str);
    NullValue* parseNullValue(char*& str);
    Number* parseNumber(char*& str);
    Value* parseValue(char*& str);

private:
    Object* obj;
};

#endif
