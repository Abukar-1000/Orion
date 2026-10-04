#ifndef KeyAction_h
#define KeyAction_h
#include <vector>
#include <windows.h>

using Keys = std::vector<INPUT>;
class KeyAction
{
    protected:
        Keys keys;
        std::vector<short> keysHeldDown;
    public:
        KeyAction();
        ~KeyAction() = default;
        KeyAction Build(void);
        KeyAction WithKey(WORD key, bool keepDown);
        Keys Get(void);
};

#endif