//
// Created by mohsen on 12/18/16.
//

#include "CFMGtkDrive.h"
#include "CFMGtkVolume.h"

CFMGtkDrive::CFMGtkDrive(GDrive *gDrive) : gDrive(gDrive) {}

CFMGtkDrive::~CFMGtkDrive() {
    g_object_unref(gDrive);
}

string CFMGtkDrive::getName() {
    return g_drive_get_name(gDrive);
}

CFMVolumeList CFMGtkDrive::getVolumes() {
    GList *g_volumes = g_drive_get_volumes(gDrive);

    CFMVolumeList volumes;

    while (g_volumes) {
        CFMVolume *volume = new CFMGtkVolume(G_VOLUME(g_volumes->data));
        volumes.push_back(CFMRef<CFMVolume>(volume));
        g_object_unref(G_VOLUME(g_volumes->data));
        g_volumes = g_volumes->next;
    }
    return volumes;
}
