//
// Created by mohsen on 12/16/16.
//

#ifndef CROWFM_CFMCORETYPES_H
#define CROWFM_CFMCORETYPES_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class CFMObject {
};

class CFMRefCounter {
private:
    int refCount;
public:
    CFMRefCounter() : refCount(0) {}

    void AddRef() { refCount++; }

    bool Release() { return --refCount <= 0; }
};

template<class T>
class CFMRef {
private:
    T *object;
    CFMRefCounter *refCounter;
public:

    CFMRef(T *object) : object(object) {
        refCounter = new CFMRefCounter();
        refCounter->AddRef();
    }

    CFMRef(const CFMRef<T> &cfmRef) : object(cfmRef.object), refCounter(cfmRef.refCounter) {
        refCounter->AddRef();
    }

    virtual ~CFMRef() {
        if (refCounter->Release()) {
            delete object;
            delete refCounter;
        }
    }

    T &operator*() {
        return *object;
    }

    T *operator->() {
        return object;
    }

    bool IsValid() {
        return object != NULL;
    }
};

#endif //CROWFM_CFMCORETYPES_H