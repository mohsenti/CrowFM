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
    virtual string GetName() = 0;

    virtual CFMVolumeList GetVolumes() = 0;
};

class CFMVolume : public CFMObject {
public:
    virtual string GetName() = 0;

    virtual CFMRef<CFMMount> GetMount() = 0;

    virtual bool CanMount() = 0;

    virtual void Mount() = 0;
};

class CFMMount : public CFMObject {
public:
    virtual string GetName() = 0;

    virtual string GetRootPath() = 0;

#ifdef __linux__

    virtual string GetMountPoint() = 0;

    virtual bool CanUnMount() = 0;

    virtual void UnMount() = 0;

#endif

    virtual bool CanEject() = 0;

    virtual void Eject() = 0;
};

#endif //CROWFM_CFMINTERFACES_H
