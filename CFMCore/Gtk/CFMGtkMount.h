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

    string getName() override;

    string getMountPoint() override;

    bool canUnMount() override;

    void unMount() override;

    bool canEject() override;

    void eject() override;

    virtual string getRootPath() override;
};



#endif //CROWFM_CFMGTKMOUNT_H
