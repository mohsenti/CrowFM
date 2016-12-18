//
// Created by mohsen on 12/18/16.
//

#ifndef CROWFM_CFMINTERFACES_H
#define CROWFM_CFMINTERFACES_H

#include <string>
#include <vector>

#include "CFMCoreTypes.h"

using namespace std;

class CFMDrive;

class CFMVolume;

class CFMMount;

typedef vector<string> CFMStringList;
typedef vector<CFMRef<CFMDrive>> CFMDeviceList;
typedef vector<CFMRef<CFMVolume>> CFMVolumeList;
typedef vector<CFMRef<CFMMount>> CFMMountList;

class CFMDrive : public CFMObject {
public:
    virtual string getName() = 0;

    virtual CFMVolumeList getVolumes() = 0;
};

class CFMVolume : public CFMObject {
public:
    virtual string getName() = 0;

    virtual CFMRef<CFMMount> getMount() = 0;
};

class CFMMount : public CFMObject {
public:
    virtual string getName() = 0;

    virtual string getRootPath() = 0;

#ifdef __linux__

    virtual string getMountPoint() = 0;

    virtual bool canUnMount() = 0;

    virtual void unMount() = 0;

#endif

    virtual bool canEject() = 0;

    virtual void eject() = 0;
};

#endif //CROWFM_CFMINTERFACES_H
