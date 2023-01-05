// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "MmRaii.h"

#include <cutils/log.h>
#include <libmm-glib.h>
#include <mm-modem.h>

#include <mm-sim.h>

class ModemSim {
  public:
    // create createInstance function
    static std::shared_ptr<ModemSim> createInstance(SharedGObject<MMSim>& mMmSim) {
        auto modemInstance = std::shared_ptr<ModemSim>(new ModemSim());
        modemInstance->mMmSim = mMmSim;

        return modemInstance;
    }

  private:
    ModemSim() = default;

    SharedGObject<MMSim> mMmSim;
};

class Modem {
  public:
    static std::shared_ptr<Modem> createInstance(SharedMmObject& mmObject) {
        auto modemInstance = std::shared_ptr<Modem>(new Modem());
        modemInstance->mMmModem = makeSharedGObject<MMModem>(mm_object_get_modem(mmObject.get()));

        return modemInstance;
    }

    std::string getImei() { return mm_modem_get_equipment_identifier(mMmModem.get()); }

    void enable(std::function<void(bool)> callback) {
        mm_modem_enable(mMmModem.get(), nullptr, enableCallback, &callback);
    }

    void disable(std::function<void(bool)> callback) {
        mm_modem_disable(mMmModem.get(), nullptr, disableCallback, &callback);
    }

    std::shared_ptr<ModemSim> getSim() {
        GError* error = nullptr;
        auto sim = SharedGObject<MMSim>(mm_modem_get_sim_sync(mMmModem.get(), nullptr, &error));
        if (error != nullptr) {
            ALOGE("Failed to get SIM: %s", error->message);
            return {};
        }
        return ModemSim::createInstance(sim);
    }

  private:
    Modem() = default;

    static void enableCallback(_GObject* sourceObject, _GAsyncResult* res, void* userData) {
        auto callback = static_cast<std::function<void(bool)>*>(userData);
        GError* error = nullptr;
        auto result = mm_modem_enable_finish(MM_MODEM(sourceObject), res, &error);
        if (error) ALOGE("Failed to enable modem: %s", error->message);
        (*callback)(result);
    }

    static void disableCallback(_GObject* sourceObject, _GAsyncResult* res, void* userData) {
        auto callback = static_cast<std::function<void(bool)>*>(userData);
        GError* error = nullptr;
        auto result = mm_modem_disable_finish(MM_MODEM(sourceObject), res, &error);
        if (error) ALOGE("Failed to disable modem: %s", error->message);
        (*callback)(result);
    }

    SharedGObject<MMModem> mMmModem;
};
