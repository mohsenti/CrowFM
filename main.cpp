#include <iostream>

#include "CFMCore/CFMCoreTypes.h"
#include "CFMCore/CFMCore.h"

int main() {
    CFMCore core;
    CFMDeviceList mounts = core.getDevices();
    for (CFMDeviceList::iterator it = mounts.begin(); it != mounts.end(); it++) {
        cout << (*it)->getName() << endl;
    }
    return 0;
}