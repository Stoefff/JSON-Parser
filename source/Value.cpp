#include "Value.h"
#include <cstring>

Value::Value() {
}

Value::~Value(){
}

char* Value::getTabs(int dept) const {
	char* tabs = new char[dept + 1];
	*tabs = '\0';
	for (int i = 0; i < dept; i++) {
		strcat(tabs, "\t");
	}
	return tabs;
}
