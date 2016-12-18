//
// Created by mohsen on 12/17/16.
//

#include "../CFMCoreTypes.h"
#include "../CFMCore.h"
#include "CFMGtkCore.h"

#include <gio/gio.h>

CFMDeviceList CFMCore::getDevices() {
    CFMDeviceList devices;

    GVolumeMonitor *g_monitor = g_volume_monitor_get();
    GList *g_devices = g_volume_monitor_get_connected_drives(g_monitor);

    while (g_devices) {
        CFMDevice *device = new CFMDevice();
        device->name = g_drive_get_name(G_DRIVE(g_devices->data));
        devices.push_back(CFMRef<CFMDevice>(device));
        g_object_unref(G_DRIVE(g_devices->data));
        g_devices = g_devices->next;
    }
    g_list_free(g_devices);

    return devices;
}

CFMVolumeList CFMCore::getVolumes() {
    GVolumeMonitor *g_monitor = g_volume_monitor_get();
    GList *g_volumes = g_volume_monitor_get_volumes(g_monitor);

    CFMVolumeList volumes;

    while (g_volumes) {
        CFMVolume *volume = new CFMVolume();
        volume->name = g_volume_get_name(G_VOLUME(g_volumes->data));
        volume->unix_device = g_volume_get_identifier(G_VOLUME(g_volumes->data), G_VOLUME_IDENTIFIER_KIND_UNIX_DEVICE);
        volumes.push_back(CFMRef<CFMVolume>(volume));
        g_object_unref(G_VOLUME(g_volumes->data));
        g_volumes = g_volumes->next;
    }
    return volumes;
}

CFMMountList CFMCore::getMounts() {
    GVolumeMonitor *g_monitor = g_volume_monitor_get();
    GList *g_mounts = g_volume_monitor_get_mounts(g_monitor);

    CFMMountList mounts;

    while (g_mounts) {
        string mount;
        mount = g_mount_get_name(G_MOUNT(g_mounts->data));
        mounts.push_back(CFMRef<CFMMount>(new CFMGtkMount(G_MOUNT(g_mounts->data))));
        g_mounts = g_mounts->next;
    }
    g_list_free(g_mounts);

    return mounts;
}

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