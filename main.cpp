#include <iostream>

#include "CFMCore/CFMCoreTypes.h"
#include "CFMCore/CFMCore.h"

int main() {
    CFMCore core;
    CFMMountList mounts = core.getMounts();
    for (CFMMountList::iterator it = mounts.begin(); it != mounts.end(); it++) {
        cout << (*it)->getName() << endl;
    }
    return 0;
}