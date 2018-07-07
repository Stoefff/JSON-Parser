#ifndef __OBJECT__HEADER
#define __OBJECT__HEADER

#include "Value.h"
#include "Pair.h"
#include "Array.h"

//Maybe this be viewed as the Composite class??
class Object: public Value {
public:
    Object();
    Object(const Object& rhs);
    Object& operator=(const Object& rhs);
    virtual ~Object() override;

    void addPair(Pair* pair);
    //Check the validity of this
    void removePair(Pair* pair);

	Pair* operator[](size_t pos);
    //Adds a key
    Object& operator+=(const Object&);

    friend bool operator==(const Object&, const Object&);
    friend bool operator!=(const Object&, const Object&);

    virtual Value* clone() const override;
	virtual void printContent(int dept, ostream& stream) const override;
	virtual void printCompactContent(ostream& stream) const override;
	virtual Value* searchPath(char** keys, int dept,
		int maxDept) const override;

    Object* searchObject(char** keys, int dept, int maxDept);
	Pair* searchObjectFull(char** keys, int dept, int maxDept);

	Array* findKey(char* key) const;

private:
    void resize();
    void free();
    void copy(const Object& rhs);

private:
    Pair** arr;
    int size;
    int cap;
};

// Add a key to a new object
//const Object operator+(const Object&, const Object&)

#endif
