// SPDX-License-Identifier: Apache-2.0

#define LOG_TAG "mm-modem-manager"

#include "ModemManager.h"

#include <memory>
#include <vector>

#include <cutils/log.h>
#include <glib.h>
#include <libmm-glib.h>

#include "ManagerObject.h"

auto ModemManager::createInstance() -> std::shared_ptr<ModemManager> {
    auto modemManager = std::shared_ptr<ModemManager>(new ModemManager());
    modemManager->mConnection = ModemManager::openConnection();
    if (!modemManager->mConnection) {
        ALOGE("Failed to open connection to ModemManager");
        return {};
    }
    modemManager->mManager = ModemManager::createManager(modemManager->mConnection.get());
    if (!modemManager->mManager) {
        ALOGE("Failed to create ModemManager");
        return {};
    }

    return modemManager;
}

SharedGDBusConnection ModemManager::openConnection() {
    GError* error = nullptr;
    auto connection = makeSharedGDBusConnection(g_bus_get_sync(G_BUS_TYPE_SYSTEM, nullptr, &error));
    if (error != nullptr) {
        ALOGE("Failed to open connection: %s", error->message);
        return {};
    }
    return connection;
}

SharedMmManager ModemManager::createManager(GDBusConnection* connection) {
    GError* error = nullptr;
    auto manager = makeSharedMmManager(mm_manager_new_sync(
            connection, G_DBUS_OBJECT_MANAGER_CLIENT_FLAGS_NONE, nullptr, &error));
    if (error != nullptr) {
        ALOGE("Failed to create manager: %s", error->message);
        return {};
    }
    return manager;
}

std::vector<SharedMmObject> getMmObjects(SharedMmManager& manager) {
    std::vector<SharedMmObject> mmObjects;
    auto* objects = g_dbus_object_manager_get_objects(G_DBUS_OBJECT_MANAGER(manager.get()));
    for (auto* object = objects; object != nullptr; object = object->next) {
        auto mmObject = makeSharedMmObject(MM_OBJECT(g_object_ref(object->data)));
        mmObjects.push_back(mmObject);
    }
    g_list_free_full(objects, g_object_unref);
    return mmObjects;
}

std::vector<std::shared_ptr<ManagerObject>> getModems(SharedMmManager& manager) {
    std::vector<std::shared_ptr<ManagerObject>> modems;
    auto mmObjects = getMmObjects(manager);
    for (auto& mmObject : mmObjects) {
        auto modem = ManagerObject::createInstance(mmObject);
        if (!modem) {
            ALOGE("Failed to create ManagerObject");
            return {};
        }
        modems.push_back(modem);
    }
    return modems;
}
