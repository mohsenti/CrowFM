//
// Created by mohsen on 12/17/16.
//

#ifndef CROWFM_CFMGTKCORE_H
#define CROWFM_CFMGTKCORE_H

#include <gio/gio.h>
#include "../CFMCoreTypes.h"

class CFMGtkMount : public CFMMount {
private:
    GMount *mount;

    static void onUnMountCallback(GObject *source_object, GAsyncResult *res, gpointer user_data);

    static void onEjectCallback(GObject *source_object, GAsyncResult *res, gpointer user_data);

public:
    CFMGtkMount(GMount *mount);

    virtual ~CFMGtkMount();

    string getName() override;

    string getMountPoint() override;

    bool canUnMount() override;

    void unMount() override;

    bool canEject() override;

    void eject() override;
};

#endif //CROWFM_CFMGTKCORE_H
