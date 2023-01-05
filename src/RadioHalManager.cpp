// SPDX-License-Identifier: Apache-2.0

#define LOG_TAG "mm-radio-hal-manager"

#include "RadioHalManager.h"

void RadioHalManager::glibLoopThreadFunc(std::shared_ptr<RadioHalManager> instance) {
    GMainLoop* loop = g_main_loop_new(nullptr, FALSE);
    g_main_loop_run(loop);
}

void RadioHalManager::RadioHalManager(std::function<void()> task) {
    g_main_context_invoke(
            nullptr,
            [](gpointer data) {
                auto task = reinterpret_cast<std::function<void()>*>(data);
                (*task)();
                delete task;
                return G_SOURCE_REMOVE;
            },
            new std::function<void()>(task));
}

auto RadioHalManager::createInstance() -> std::shared_ptr<RadioHalManager> {
    auto instance = std::shared_ptr<RadioHalManager>(new RadioHalManager());

    instance->mModemManager = ModemManager::createInstance();
    instance->mModemManager->subscribeModemAdded([](SharedMmObject mmObject) {
        auto modem = Modem::createInstance(mmObject);
        ALOGI("Modem added: %s", modem->getImei().c_str());
    });

    std::thread(&RadioHalManager::glibLoopThreadFunc, instance).detach();

    return instance;
}
