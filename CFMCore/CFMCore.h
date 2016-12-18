//
// Created by mohsen on 12/16/16.
//

#ifndef CROWFM_CFMCORE_H
#define CROWFM_CFMCORE_H

#include <string>
#include <vector>
#include "CFMCoreTypes.h"

using namespace std;

class CFMCore {
public:

    CFMDeviceList getDevices();
    CFMVolumeList getVolumes();
    CFMMountList getMounts();

};


#endif //CROWFM_CFMCORE_H
