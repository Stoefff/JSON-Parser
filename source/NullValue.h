#ifndef __NULL__VALUE__HEADER
#define __NULL__VALUE__HEADER

#include "Value.h"

class NullValue : public Value {
public:
    NullValue();
    virtual ~NullValue() override;

    virtual Value* clone() const override;
	virtual void printContent(int dept, ostream& stream) const override;
	virtual void printCompactContent(ostream& stream) const override;
	virtual Value* searchPath(char** keys, int dept,
		int maxDept) const override;
};

#endif
