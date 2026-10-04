#ifndef KeyboardWinStrategy_H
#define KeyboardWinStrategy_H
#include <format>
#include <memory>
#include <iostream>
#include "windows.h"
#include <algorithm>
#include "IKeyboard.h"
#include "./KeyAction.h"
#include <unordered_map>
#include "../Logger/LoggerBase.h"

using KeyMap = std::unordered_map<char, KeyAction>;
class KeyboardWinStrategy : public IKeyboard
{
    protected:
        LoggerBase errLogger;
        std::unique_ptr<KeyMap> keyMap;
        void BuildKeyMap(void);
        KeyAction MapKey(const char& _char);
    
    public:
        KeyboardWinStrategy();
        virtual ~KeyboardWinStrategy() = default;
        virtual bool Write(const std::string& text) override;
        virtual bool Clear(void) override; 
};

#endif // KeyboardWinStrategy_H