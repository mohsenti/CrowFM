//
// Created by mohsen on 12/18/16.
//

#ifndef CROWFM_CFMGTKDRIVE_H
#define CROWFM_CFMGTKDRIVE_H

#include "../CFMInterfaces.h"
#include "../CFMCoreTypes.h"
#include <gio/gio.h>

class CFMGtkDrive : public CFMDrive {
private:
    GDrive *gDrive;
public:
    CFMGtkDrive(GDrive *gDrive);

    virtual ~CFMGtkDrive();

    string GetName() override;

    CFMVolumeList GetVolumes() override;
};


#endif //CROWFM_CFMGTKDRIVE_H
