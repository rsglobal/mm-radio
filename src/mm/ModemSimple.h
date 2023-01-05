// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "MmRaii.h"

#include <libmm-glib.h>
#include <mm-modem-simple.h>

class ModemSimple {
  public:
    static std::shared_ptr<ModemSimple> createInstance(SharedMmObject& mmObject) {
        auto mmSimple = std::shared_ptr<ModemSimple>(new ModemSimple());
        mmSimple->mMmModemSimple =
                makeSharedGObject<MMModemSimple>(mm_object_get_modem_simple(mmObject.get()));

        return mmSimple;
    }

  private:
    ModemSimple() = default;

    SharedGObject<MMModemSimple> mMmModemSimple;
};
