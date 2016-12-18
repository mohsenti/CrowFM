//
// Created by mohsen on 12/18/16.
//

#include "CFMGtkMount.h"

CFMGtkMount::CFMGtkMount(GMount *mount) : mount(mount) {}

CFMGtkMount::~CFMGtkMount() {
    g_object_unref(mount);
}

string CFMGtkMount::getName() {
    return g_mount_get_name(mount);
}

string CFMGtkMount::getMountPoint() {
    return "";
}

bool CFMGtkMount::canUnMount() {
    return g_mount_can_unmount(mount) == TRUE;
}

void CFMGtkMount::unMount() {
    g_mount_unmount_with_operation(mount, G_MOUNT_UNMOUNT_NONE, NULL, NULL, CFMGtkMount::onUnMountCallback, this);
}

bool CFMGtkMount::canEject() {
    return g_mount_can_eject(mount) == TRUE;
}

void CFMGtkMount::eject() {
    g_mount_eject_with_operation(mount, G_MOUNT_UNMOUNT_NONE, NULL, NULL, CFMGtkMount::onEjectCallback, this);
}

void CFMGtkMount::onUnMountCallback(GObject *source_object, GAsyncResult *res, gpointer user_data) {
    //Todo: implement this
}

void CFMGtkMount::onEjectCallback(GObject *source_object, GAsyncResult *res, gpointer user_data) {
    //Todo: implement this
}