#include "../../include/Keyboard/KeyAction.h"


KeyAction KeyAction::Build(void)
{
    while (!this->keysHeldDown.empty())
    {
        short index = this->keysHeldDown[0];
        this->keys.push_back(INPUT {
            .type = INPUT_KEYBOARD,
            .ki {
                .wVk = this->keys[index].ki.wVk,
                .dwFlags = KEYEVENTF_KEYUP
            }
        });

        this->keysHeldDown.erase(this->keysHeldDown.begin());
    }

    return *this;
}

KeyAction KeyAction::WithKey(WORD key, bool keepDown = false)
{
    if (keepDown)
    {
        this->keys.push_back(INPUT {
            .type = INPUT_KEYBOARD,
            .ki {
                .wVk = key
            }
        });

        short index = this->keys.size() - 1;
        this->keysHeldDown.push_back(index);
    }
    else {
        this->keys.push_back(INPUT {
            .type = INPUT_KEYBOARD,
            .ki {
                .wVk = key
            }
        });

        this->keys.push_back(INPUT {
            .type = INPUT_KEYBOARD,
            .ki {
                .wVk = key,
                .dwFlags = KEYEVENTF_KEYUP 
            }
        });
    }

    return *this;
}

Keys KeyAction::Get(void)
{
    if (!this->keysHeldDown.empty())
    {
        this->Build();
    }
    
    return this->keys;
}

KeyAction::KeyAction()
{}