//
// Created by mohsen on 12/18/16.
//

#ifndef CROWFM_CFMGTKMOUNT_H
#define CROWFM_CFMGTKMOUNT_H


#include <gio/gio.h>

#include "../CFMCoreTypes.h"
#include "../CFMInterfaces.h"

class CFMGtkMount : public CFMMount {
private:
    GMount *gMount;

    static void onUnMountCallback(GObject *source_object, GAsyncResult *res, gpointer user_data);

    static void onEjectCallback(GObject *source_object, GAsyncResult *res, gpointer user_data);

public:
    CFMGtkMount(GMount *mount);

    virtual ~CFMGtkMount();

    string GetName() override;

    string GetMountPoint() override;

    bool CanUnMount() override;

    void UnMount() override;

    bool CanEject() override;

    void Eject() override;

    virtual string GetRootPath() override;
};



#endif //CROWFM_CFMGTKMOUNT_H
