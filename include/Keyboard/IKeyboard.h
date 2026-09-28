#ifndef Keyboard_H
#define Keyboard_H
#include <string>

class IKeyboard
{
    public:
        virtual ~IKeyboard() = default;
        virtual bool Write(const std::string& text) = 0;
        virtual bool Clear(void) = 0;
};

#endif // Keyboard_H