//
// Created by mohsen on 12/18/16.
//

#ifndef CROWFM_CFMGTKVOLUME_H
#define CROWFM_CFMGTKVOLUME_H

#include "../CFMCoreTypes.h"
#include "../CFMInterfaces.h"
#include <gio/gio.h>

class CFMGtkVolume : public CFMVolume {
private:
    GVolume *gVolume;
public:
    CFMGtkVolume(GVolume *gVolume);

    virtual ~CFMGtkVolume();

    virtual string getName() override;

    virtual CFMRef<CFMMount> getMount() override;
};


#endif //CROWFM_CFMGTKVOLUME_H
