#ifndef Keyboard_H
#define Keyboard_H
#include <string>

class IKeyboard
{
    protected:
        short MaxLineLength = 1024;
        short UNDEFINED_KEY = 0x3F;
    public:
        virtual ~IKeyboard() = default;
        virtual bool Write(const std::string& text) = 0;
        virtual bool Clear(void) = 0;
};

#endif // Keyboard_H