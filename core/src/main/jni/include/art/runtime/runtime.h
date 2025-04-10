/*
 * This file is part of LSPosed.
 *
 * LSPosed is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LSPosed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LSPosed.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2020 EdXposed Contributors
 * Copyright (C) 2021 LSPosed Contributors
 */

#pragma once

#include "utils/hook_helper.hpp"

namespace art {

    class Runtime {
    private:
        inline static Runtime *instance_;
        CREATE_MEM_FUNC_SYMBOL_ENTRY(void, SetJavaDebuggable, void *thiz, bool value) {
            if (SetJavaDebuggableSym) [[likely]] {
                SetJavaDebuggableSym(thiz, value);
            }
        }

    public:
        inline static Runtime *Current() {
            return instance_;
        }

        void SetJavaDebuggable(bool value) {
            SetJavaDebuggable(this, value);
        }

        // @ApiSensitive(Level.LOW)
        inline static void Setup(const lsplant::HookHandler &handler) {
            void **instance = nullptr;
            RETRIEVE_FIELD_SYMBOL(instance, "_ZN3art7Runtime9instance_E");
            RETRIEVE_MEM_FUNC_SYMBOL(SetJavaDebuggable, "_ZN3art7Runtime17SetJavaDebuggableEb");
            void *thiz = *instance;
            LOGD("_ZN3art7Runtime9instance_E = {}", thiz);
            instance_ = reinterpret_cast<Runtime*>(thiz);
        }
    };

}
