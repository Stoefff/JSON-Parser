#include "JsonParser.h"
#include <fstream>
#include <iostream>
#include <cstring>

using std::ifstream;
using std::ios;
using std::cerr;
using std::endl;
using std::cout;
using std::cin;

JsonParser::JsonParser(const char* filename){
    char* json = getJsonString(filename);
    //cout << json << endl;
	char* itt = json;
    this->obj = parseObject(itt);
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
	char* buffer = new char[fileSize + 1];
    while(file.getline(buffer, fileSize)){
        strcat(json, buffer);
    }
	delete[] buffer;
    file.close();
    return json;
}

void JsonParser::skipWhiteSpace(char*& str){
    while((*str == ' ')||(*str == '\n')
        ||(*str == '\t')||(*str == '\f')
        ||(*str == '\r')||(*str == '\v')){
        str++;
    }
}

Object* JsonParser::parseObject(char*& str){
    Object* obj = new Object();
    skipWhiteSpace(str);
    if(*str != '{'){
        cerr << "No valid starting { found in object!" << endl;
        return nullptr;
    }
    str++;
    while(true) {
        skipWhiteSpace(str);
        if(*str != '\"'){
            cerr << "No valid key found in object!" << endl;
            return nullptr;
        }
        String* key = parseString(str);
        if(key == nullptr){
            return nullptr;
        }
        str++;
        skipWhiteSpace(str);
        if(*str != ':'){
            cerr << "No valid syntax for a pair of key - value" << endl;
            return nullptr;
        }
        str++;
        skipWhiteSpace(str);
        Value* val = parseValue(str);
        if(val == nullptr){
            return nullptr;
        }
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
        return nullptr;
    }
    return obj;
}

String* JsonParser::parseString(char*& str){
    if(*str != '\"'){
        cerr << "No valid start \" of string found!" << endl;
        return nullptr;
    }
    str++;
    char* itt = str;
    int size = 0;
    while(*itt != '\"'){
        itt++;
        size++;
    }
    char* temp = new char[size+1];
	itt = temp;
    for(int i = 0; i < size; i++){
        *itt = *str;
        itt++;
        str++;
    }
    temp[size] = '\0';
    return new String(temp);
}

Array* JsonParser::parseArray(char*& str){
    Array* arr = new Array();
    if(*str != '['){
        cerr << "No valid start [ of array found!" << endl;
        return nullptr;
    }
    str++;
    while(true){
        skipWhiteSpace(str);
        Value* val = parseValue(str);
        if(val == nullptr){
            return nullptr;
        }
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
        return nullptr;
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
	itt = temp;
    while((*str >= 97)&&(*str <= 122)){
        *itt = *str;
        itt++;
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
	itt = temp;
    while((*str >= 97)&&(*str <= 122)){
        *itt = *str;
        itt++;
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


Number* JsonParser::parseNumber(char*& str){
	char* itt = str;
	int size = 0;
	while ((*itt == '-') || ((*itt >= '0') && (*itt <= '9'))
		||(*itt == 'e') || (*itt == 'E')
		||(*itt == '+') || (*itt == '-')){
		itt++;
		size++;
	}
	if ((*itt != ' ') && (*itt != '\n')
		&& (*itt != '\t')&&(*itt != ',')
		&& (*itt != ']')&&(*itt != '}')) {
		cerr << "Invalid number provided!" << endl;
        return nullptr;
	}
	char* temp = new char[size + 1];
	itt = temp;
	for (int i = 0; i < size; i++) {
		*itt = *str;
		itt++;
		str++;
	}
	temp[size] = '\0';
	str--;
	return new Number(temp);
}

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
    } else if ((*str == '-')||((*str >= '0')&&(*str <= '9'))){
        val = parseNumber(str);
    } else {
        cerr << "No valid value provided!" << endl;
        return nullptr;
    }
    return val;
}
/*
char** JsonParser::parseKeyPath(char* keyPath, int& size) {
	char* itt = keyPath;
	while (isWhiteSpace(*itt)) {
		if (*itt == '/') {
			size++;
		}
		itt++;
	}
	size++;
	char** keys = new char*[size];
	itt = keyPath;
	for (int i = 0; i < size; i++) {
		char* itt2 = itt;
		int keySize = 0;
		while ((*itt != '/')&&(!isWhiteSpace(*itt))) {
			itt++;
			keySize++;
		}
		keys[i] = new char[keySize + 1];
		itt = itt2;
		itt2 = keys[i];
		for (int i = 0; i < keySize; i++) {
			*itt2 = *itt;
			itt2++;
			itt++;
		}
		keys[i][keySize] = '\0';
		itt++;
	}
	return keys;

}
*/

char** JsonParser::parseKeyPath(char* keyPath, int& size) {
	char* itt = keyPath;
	while ((*itt != '\0')&&(*itt != ' ')) {
		if (*itt == '/') {
			size++;
		}
		itt++;
	}
	size++;
	itt = keyPath;
	char** keys = new char*[size];
	for (int i = 0; i < size; i++) {
		if (*itt != '\"') {
			cerr << "No valid start \" of string found!" << endl;
		}
		itt++;
		char* itt1 = itt;
		int keySize = 0;
		while (*itt1 != '\"') {
			itt1++;
			keySize++;
		}
		keys[i] = new char[keySize + 1];
		itt1 = keys[i];
		for (int i = 0; i < keySize; i++) {
			*itt1 = *itt;
			itt1++;
			itt++;
		}
		keys[i][keySize] = '\0';
		itt += 2;
	}
	return keys;

}

bool JsonParser::isWhiteSpace(char s) {
	if ((s == ' ') || (s == '\n') || (s == '\t')) {
		return true;
	}
	else {
		return false;
	}
}

void JsonParser::printPrettyJson(ostream& stream) {
	this->obj->printContent(1, stream);
	stream << endl;
}

void JsonParser::printCompactJson(ostream& stream) {
	this->obj->printCompactContent(stream);
	stream << endl;
}

void JsonParser::run() {
	char command[64];
	char arg1[1024];
	char arg2[1024];
	//char arg3[1024];
	cout << "Enter ? to see supported commands." << endl;
	while (true) {
        if (obj == nullptr){
            cout << "Problems with parsin file, please restart!" << endl;
            break;
        }
		cout << "Enter a command: ";
		cin >> command;
		if (!_stricmp(command, "print-json")) {
			printPrettyJson(cout);
		}
		else if (!_stricmp(command, "print-in-file")) {
			cin >> arg1;
			cin >> arg2;
			ifstream f(arg1);
			if (f.good()) {
				char option[4];
				cout << "File with such name already exits!" << endl;
				cout << "Enter (yes) if you want to override the file" << endl;
				cout << "Or (no) if you want to enter the command again" << endl;
				cin >> option;
				if (!_stricmp(option, "yes")) {
				}
				else if (!_stricmp(option, "no")) {
					continue;
				}
				else {
					cerr << "Please enter a valid answer!" << endl;
				}
			}
			ofstream file(arg1, ios::out|ios::trunc);
			if (!file.good()) {
				cerr << "Failed loading file" << endl;
				continue;
			}
			if (!_stricmp(arg2, "-c")) {
				printCompactJson(file);
			}
			else if (!_stricmp(arg2, "-p")) {
				printPrettyJson(file);
			}
			else {
				cerr << "Please enter valid formatting" << endl;
			}
		}
		else if (!_stricmp(command, "print-key-values")) {
			cin >> arg1;
			int maxDepth = 0;
			char** keyPath = parseKeyPath(arg1, maxDepth);
			maxDepth--;
			Value* keyValues = obj->searchPath(keyPath, 0, maxDepth);
			if (keyValues == nullptr) {
				cerr << "No such key was found!" << endl;
			}
			else {
				keyValues->printContent(1, cout);
				cout << endl;
				delete keyValues;
			}
			delete[] keyPath;
		}
        else if (!_stricmp(command, "add-key")) {
			cin >> arg1;
			cin >> arg2;
            char* itt = arg2;
			int maxDepth = 0;
			char** keyPath = parseKeyPath(arg1, maxDepth);
			maxDepth--;
            Value* val = parseValue(itt);
			Object* temp = obj->searchObject(keyPath, 0, maxDepth);
			if (temp == nullptr) {
				cerr << "No such key was found!" << endl;
			}
			else {
				String* str = new String(keyPath[maxDepth]);
                Pair* pair = new Pair(str,val);
                temp->addPair(pair);
                cout << "Key was added!" << endl;
			}
			delete[] keyPath;
		}
		else if (!_stricmp(command, "delete-key")) {
			cin >> arg1;
			int maxDepth = 0;
			char** keyPath = parseKeyPath(arg1, maxDepth);
			maxDepth--;
			Object* obj1 = obj->searchObject(keyPath, 0, maxDepth);
			Pair* pair = obj->searchObjectFull(keyPath, 0, maxDepth);
			if ((obj == nullptr)||(pair == nullptr)) {
				cerr << "No such key was found!" << endl;
			}
			else {
				obj1->removePair(pair);
				cout << "Key was deleted!" << endl;
			}
			delete[] keyPath;
		}
		else if (!_stricmp(command, "?")) {
			cout << "Command: exit" << endl;
			cout << "------------------------------------------------" << endl;
			cout << "Command: print-json" << endl;
			cout << "------------------------------------------------" << endl;
			cout << "Command: print-in-file (filename) (-p or -c)" << endl;
			cout << "-p stand for pretty printing of the json" << endl;
			cout << "-c stand for compact printing of the json" << endl;
			cout << "------------------------------------------------" << endl;
			cout << "Command: print-key-values (path to key)" << endl;
			cout << "path to key is in the format: \"key1\"/\"key2\"/\"key3" << endl;
			cout << "------------------------------------------------" << endl;
		}
		else if (!_stricmp(command, "exit")) {
			break;
		}
		else {
			cout << "Invalid command, enter a new one: " << endl;
			cin.ignore();
		}
	}
}
