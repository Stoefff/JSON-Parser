#include "iostream"

#include "Value.h"
#include "Array.h"
#include "BoolValue.h"
#include "JsonParser.h"
#include "NullValue.h"
#include "Number.h"
#include "Object.h"
#include "Pair.h"
#include "String.h"
#include "Value.h"

#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ios;

int main(int argc, char* argv[]) {

	JsonParser parser(argv[1]);
	parser.run();

	return 0;
}
