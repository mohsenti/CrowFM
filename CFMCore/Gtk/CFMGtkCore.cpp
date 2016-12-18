//
// Created by mohsen on 12/17/16.
//

#include "../CFMCore.h"

#include "CFMGtkMount.h"
#include "../CFMCoreTypes.h"
#include "CFMGtkVolume.h"
#include "CFMGtkDrive.h"

#include <gio/gio.h>

CFMDeviceList CFMCore::getDevices() {
    CFMDeviceList devices;

    GVolumeMonitor *g_monitor = g_volume_monitor_get();
    GList *g_devices = g_volume_monitor_get_connected_drives(g_monitor);

    while (g_devices) {
        CFMDrive *device = new CFMGtkDrive(G_DRIVE(g_devices->data));
        devices.push_back(CFMRef<CFMDrive>(device));
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
        CFMVolume *volume = new CFMGtkVolume(G_VOLUME(g_volumes->data));
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