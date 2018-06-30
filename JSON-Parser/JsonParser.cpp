#include "JsonParser.h"
#include <fstream>
#include <iostream>
#include <cstring>

using std::ifstream;
using std::ios;
using std::cerr;
using std::endl;
using std::cout;

JsonParser::JsonParser(const char* filename){
    char* json = getJsonString(filename);
    cout << json << endl;
    this->obj = parseObject(json);
    delete[] json;
}

JsonParser::JsonParser(const JsonParser& rhs){
    copy(rhs);
}

JsonParser& JsonParser::operator=(const JsonParser& rhs){
    if(this != &rhs){
        free();
        copy(rhs);
    }
    return *this;
}

JsonParser::~JsonParser(){
    free();
}

void JsonParser::free() {
    delete obj;
    obj = nullptr;
}

void JsonParser::copy(const JsonParser& rhs){
    *this->obj = *rhs.obj;
}

//This is supposed to work for text file ???
//Will trust this for now
int JsonParser::getFileSize(const char* filename){
    ifstream file(filename, ifstream::in | ifstream::binary);
    if(!file.good()){
        cerr << "Failed loading JSON file" << endl;
        return -1;
    }

    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    file.close();

    return fileSize;
}

char* JsonParser::getJsonString(const char* filename){
    ifstream file (filename, ios::in);
    if(!file.good()){
        cerr << "Failed loading JSON file" << endl;
        return nullptr;
    }
    int fileSize = getFileSize(filename);
    char* json = new char[fileSize + 1];
    *json = '\0';
    char buffer[fileSize];
    while(file.getline(buffer, fileSize)){
        strcat(json, buffer);
    }
    file.close();
    return json;
}

void JsonParser::skipWhiteSpace(char*& str){
    while((*str == ' ')||(*str == '\n')
        ||(*str == '\t')){
        str++;
    }
}

Object* JsonParser::parseObject(char*& str){
    Object* obj = new Object();
    skipWhiteSpace(str);
    if(*str != '{'){
        cerr << "No valid starting { found in object!" << endl;
    }
    str++;
    while(true) {
        skipWhiteSpace(str);
        if(*str != '\"'){
            cerr << "No valid key found in object!" << endl;
        }
        String* key = parseString(str);
        str++;
        skipWhiteSpace(str);
        if(*str != ':'){
            cerr << "No valid syntax for a pair of key - value" << endl;
        }
        str++;
        skipWhiteSpace(str);
        Value* val = parseValue(str);
        Pair* pair = new Pair(key, val);
        obj->addPair(pair);
        str++;// Check validity
        skipWhiteSpace(str);
        if(*str != ','){
            break;
        } else {
            str++;
        }
    }
    if (*str != '}'){
        cerr << "No valid ending } found in object!" << endl;
    }
    return obj;
}

String* JsonParser::parseString(char*& str){
    if(*str != '\"'){
        cerr << "No valid start \" of string found!" << endl;
    }
    str++;
    char* itt = str;
    int size = 0;
    while(*itt != '\"'){//Possible memory leak
        itt++;
        size++;
    }
    char* temp = new char[size+1];
    for(int i = 0; i < size; i++){
        *temp = *str;
        temp++;
        str++;
    }
    temp[size] = '\0';
    return new String(temp);
}

Array* JsonParser::parseArray(char*& str){
    Array* arr = new Array();
    if(*str != '['){
        cerr << "No valid start [ of array found!" << endl;
    }
    str++;
    while(true){
        skipWhiteSpace(str);
        Value* val = parseValue(str);
        arr->addElement(val);
        str++;
        skipWhiteSpace(str);
        if(*str != ','){
            break;
        }
        str++;
    }
    if(*str != ']'){
        cerr << "No valid end ] of array found!" << endl;
    }
    return arr;
}

BoolValue* JsonParser::parseBoolValue(char*& str){
    char* itt = str;
    int size = 0;
    while((*itt >= 97)&&(*itt <= 122)){
        itt++;
        size++;
    }
    char* temp = new char[size + 1];
    while((*str >= 97)&&(*str <= 122)){
        *temp = *str;
        temp++;
        str++;
    }
    temp[size] = '\0';
    str--;//Next symbol could be a valid one, shoud not miss it
    if (!strcmp(temp, "true")){
        bool var = true;
        return new BoolValue(var);
    } else if (!strcmp(temp, "false")){
        bool var = false;
        return new BoolValue(var);
    } else {
        cerr << "No valid value provided!" << endl;
        return nullptr;
    }
}

NullValue* JsonParser::parseNullValue(char*& str){
    char* itt = str;
    int size = 0;
    while((*itt >= 97)&&(*itt <= 122)){
        itt++;
        size++;
    }
    char* temp = new char[size + 1];
    while((*str >= 97)&&(*str <= 122)){
        *temp = *str;
        temp++;
        str++;
    }
    temp[size] = '\0';
    str--;
    if(!strcmp(temp, "null")){
        return new NullValue();
    } else {
        cerr << "No valid value provided!" << endl;
        return nullptr;
    }
}

/*
Number* JsonParser::parseNumber(char*& str){

}
*/

Value* JsonParser::parseValue(char*& str){
    Value* val;
    if(*str == '{'){
        val = parseObject(str);
    } else if (*str == '['){
        val = parseArray(str);
    } else if (*str == '\"'){
        val = parseString(str);
    } else if ((*str == 't')||(*str == 'f')){
        val = parseBoolValue(str);
    } else if (*str == 'n'){
        val = parseNullValue(str);
    }/* else if ((*str == '-')||((*str >= '0')&&(*str <= '9'))){
        //val = parserNumber(str);
    }*/ else {
        cerr << "No valid value provided!" << endl;
        return nullptr;
    }
    return val;
}
