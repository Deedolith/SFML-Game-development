#pragma once

#include "State.h"

namespace States
{
    class SettingState :
        public State
    {
    private:
    public:
        SettingState(StateStack& stack, State::Context context);
    };
}

