// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <functional>
#include <memory>

#include "MmRaii.h"

class ModemManager {
  public:
    static auto createInstance() -> std::shared_ptr<ModemManager>;

    // Subscribe to the modem added signal
    void subscribeModemAdded(std::function<void(SharedMmObject)> callback) {
        g_signal_connect(mManager.get(), "object-added", G_CALLBACK(modemCallback), &callback);
    }

    // Callback for the modem removed event
    void subscribeModemRemoved(std::function<void(SharedMmObject)> callback) {
        g_signal_connect(mManager.get(), "object-removed", G_CALLBACK(modemCallback), &callback);
    }

  private:
    ModemManager() = default;

    static void modemCallback(MMManager* manager, MMObject* object, gpointer data) {
        auto callback = reinterpret_cast<std::function<void(SharedMmObject)>*>(data);
        (*callback)(SharedMmObject(object));
    }

    static auto openConnection() -> SharedGDBusConnection;
    static auto createManager(GDBusConnection* connection) -> SharedMmManager;

    SharedGDBusConnection mConnection;
    SharedMmManager mManager;
};
