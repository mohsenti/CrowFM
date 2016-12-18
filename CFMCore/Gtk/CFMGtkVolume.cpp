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

void CFMGtkVolume::mount() {
    g_volume_mount(gVolume, G_MOUNT_MOUNT_NONE, NULL, NULL, CFMGtkVolume::onMountCallback, this);
}

void CFMGtkVolume::onMountCallback(GObject *source_object, GAsyncResult *res, gpointer user_data) {
    //Todo:Not implemented yet(CFMGtkVolume::onMountCallback)
}

bool CFMGtkVolume::canMount() {
    return g_volume_can_mount(gVolume) == TRUE;
}