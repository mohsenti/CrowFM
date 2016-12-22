//
// Created by mohsen on 12/18/16.
//

#include "CFMGtkMount.h"

CFMGtkMount::CFMGtkMount(GMount *mount) : gMount(mount) {}

CFMGtkMount::~CFMGtkMount() {
    g_object_unref(gMount);
}

string CFMGtkMount::GetName() {
    return g_mount_get_name(gMount);
}

string CFMGtkMount::GetMountPoint() {
    return "";
}

bool CFMGtkMount::CanUnMount() {
    return g_mount_can_unmount(gMount) == TRUE;
}

void CFMGtkMount::UnMount() {
    g_mount_unmount_with_operation(gMount, G_MOUNT_UNMOUNT_NONE, NULL, NULL, CFMGtkMount::onUnMountCallback, this);
}

bool CFMGtkMount::CanEject() {
    return g_mount_can_eject(gMount) == TRUE;
}

void CFMGtkMount::Eject() {
    g_mount_eject_with_operation(gMount, G_MOUNT_UNMOUNT_NONE, NULL, NULL, CFMGtkMount::onEjectCallback, this);
}

string CFMGtkMount::GetRootPath() {
    return g_file_get_path(g_mount_get_root(gMount));
}

void CFMGtkMount::onUnMountCallback(GObject *source_object, GAsyncResult *res, gpointer user_data) {
    //Todo:Not implemented yet(CFMGtkMount::onUnMountCallback)
}

void CFMGtkMount::onEjectCallback(GObject *source_object, GAsyncResult *res, gpointer user_data) {
    //Todo:Not implemented yet(CFMGtkMount::onEjectCallback)
}