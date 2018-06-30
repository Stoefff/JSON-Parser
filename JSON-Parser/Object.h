#ifndef __OBJECT__HEADER
#define __OBJECT__HEADER

#include "Value.h"
#include "Pair.h"

//Maybe this be viewed as the Composite class??
class Object: public Value {
public:
    Object();
    Object(const Object& rhs);
    Object& operator=(const Object& rhs);
    ~Object();

    void addPair(const Pair* pair);
    //Check the validity of this
    void removePair();

    virtual Value* clone() const override;

private:
    void resize();
    void free();
    void copy(const Object& rhs);

private:
    Pair** arr;
    int size;
    int cap;
};

#endif
