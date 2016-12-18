//
// Created by mohsen on 12/16/16.
//

#ifndef CROWFM_CFMCORETYPES_H
#define CROWFM_CFMCORETYPES_H

#include <string>
#include <vector>

using namespace std;

typedef vector<string> CFMStringList;

typedef struct {
    string name;
} CFMDevice;
typedef vector<CFMDevice> CFMDeviceList;

typedef struct {
    string name;
#ifdef __linux__
    string unix_device;
#endif
    string root_path;
} CFMVolume;
typedef vector<CFMVolume> CFMVolumeList;

class CFMMount {
public:
    virtual string getName() = 0;

    virtual string getMountPoint() = 0;

    virtual bool canUnMount() = 0;

    virtual void unMount() = 0;

    virtual bool canEject() = 0;

    virtual void eject() = 0;
};

typedef vector<CFMMount *> CFMMountList;

#endif //CROWFM_CFMCORETYPES_H
