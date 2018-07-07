#ifndef __Bool__Value__HEADER
#define __Bool__Value__HEADER

#include "Value.h"

class BoolValue: public Value {
public:
    BoolValue(const bool var);
    BoolValue(const BoolValue& rhs);
    BoolValue& operator=(const BoolValue& rhs);
    virtual ~BoolValue() override;

    virtual Value* clone() const override;
	virtual void printContent(int dept, ostream& stream) const override;
	virtual void printCompactContent(ostream& stream) const override;
	virtual Value* searchPath(char** keys, int dept,
		int maxDept) const override;
private:
    bool var;
};

#endif
