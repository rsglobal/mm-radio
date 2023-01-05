// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "mm/MmRaii.h"
#include "mm/Modem.h"
#include "mm/ModemManager.h"

#include "RadioConfig.h"
#include "RadioData.h"
#include "RadioMessaging.h"
#include "RadioModem.h"
#include "RadioNetwork.h"
#include "RadioSim.h"
#include "RadioVoice.h"

#include <thread>

using android::hardware::radio::mm::RadioConfig;
using android::hardware::radio::mm::RadioData;
using android::hardware::radio::mm::RadioMessaging;
using android::hardware::radio::mm::RadioModem;
using android::hardware::radio::mm::RadioNetwork;
using android::hardware::radio::mm::RadioSim;
using android::hardware::radio::mm::RadioVoice;

class FrontendElements {
  public:
    std::shared_ptr<RadioData> mRadioData;
    std::shared_ptr<RadioMessaging> mRadioMessaging;
    std::shared_ptr<RadioModem> mRadioModem;
    std::shared_ptr<RadioNetwork> mRadioNetwork;
    std::shared_ptr<RadioSim> mRadioSim;
    std::shared_ptr<RadioVoice> mRadioVoice;
};

class RadioHalManager {
  public:
    static std::shared_ptr<RadioHalManager> getInstance() {
        static std::shared_ptr<RadioHalManager> instance = createInstance();
        return instance;
    }

    void schedule(std::function<void()> task);

    void registerFrontendRadioConfig(std::function<void(const char*, const char*)> addService) {
        auto aidlHal = std::make_shared<RadioConfig>();
        const auto instance = RadioConfig::descriptor + "/default"s;
        aidlHal->registerAsService(instance, addService);
    }
    void registerFrontendElements(int slotId,
                                  std::function<void(const char*, const char*)> addService);

  private:
    static auto createInstance() -> std::shared_ptr<RadioHalManager>;

    static void glibLoopThreadFunc(std::shared_ptr<RadioHalManager> instance);

    RadioHalManager() = default;

    std::shared_ptr<ModemManager> mModemManager;

    std::map<int /* slotId */, FrontendElements> mFrontendElements;
    std::shared_ptr<RadioConfig> mRadioConfig;
};
