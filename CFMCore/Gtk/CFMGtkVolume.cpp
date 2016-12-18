//
// Created by mohsen on 12/18/16.
//

#include "CFMGtkVolume.h"
#include "CFMGtkMount.h"

CFMGtkVolume::CFMGtkVolume(GVolume *gVolume) : gVolume(gVolume) {
}

CFMGtkVolume::~CFMGtkVolume() {
    g_object_unref(gVolume);
}

string CFMGtkVolume::getName() {
    return g_volume_get_name(gVolume);
}

CFMRef<CFMMount> CFMGtkVolume::getMount() {
    GMount *mount = g_volume_get_mount(gVolume);
    if (mount) {
        return CFMRef<CFMMount>(new CFMGtkMount(mount));
    }

    return CFMRef<CFMMount>(NULL);
}