#pragma once

#include "MmRaii.h"
#include "Modem.h"
#include "ModemSimple.h"

class ManagerObject {
  public:
    static std::shared_ptr<ManagerObject> createInstance(SharedMmObject& mmObject) {
        auto modemInstance = std::shared_ptr<ManagerObject>(new ManagerObject(mmObject));

        modemInstance->mModemSimple = ModemSimple::createInstance(mmObject);
        modemInstance->mModem = Modem::createInstance(mmObject);

        return modemInstance;
    }

    auto& getSimple() { return mModemSimple; }

  private:
    explicit ManagerObject(SharedMmObject& mmObject) : mMmObject(mmObject) {}

    SharedMmObject mMmObject;

    std::shared_ptr<ModemSimple> mModemSimple;
    std::shared_ptr<Modem> mModem;
};
