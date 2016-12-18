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

    void addRef() { refCount++; }

    bool release() { return --refCount <= 0; }
};

template<class T>
class CFMRef {
private:
    T *object;
    CFMRefCounter *refCounter;
public:

    CFMRef(T *object) : object(object) {
        refCounter = new CFMRefCounter();
        refCounter->addRef();
    }

    CFMRef(const CFMRef<T> &cfmRef) : object(cfmRef.object), refCounter(cfmRef.refCounter) {
        refCounter->addRef();
    }

    virtual ~CFMRef() {
        if (refCounter->release()) {
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

};

typedef vector<string> CFMStringList;

class CFMDevice : public CFMObject {
public:
    string name;
};

typedef vector<CFMRef<CFMDevice>> CFMDeviceList;

class CFMVolume : public CFMObject {
public:
    string name;
#ifdef __linux__
    string unix_device;
#endif
    string root_path;
};

typedef vector<CFMRef<CFMVolume>> CFMVolumeList;

class CFMMount : public CFMObject {
public:
    virtual string getName() = 0;

    virtual string getMountPoint() = 0;

    virtual bool canUnMount() = 0;

    virtual void unMount() = 0;

    virtual bool canEject() = 0;

    virtual void eject() = 0;
};

typedef vector<CFMRef<CFMMount>> CFMMountList;

#endif //CROWFM_CFMCORETYPES_H