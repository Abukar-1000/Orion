#ifndef KeyboardWinStrategy_H
#define KeyboardWinStrategy_H
#include <iostream>
#include <format>
#include <memory>
#include "windows.h"
#include "IKeyboard.h"
#include <algorithm>
#include "../Logger/LoggerBase.h"

class KeyboardWinStrategy : public IKeyboard
{
    protected:
        std::unique_ptr<int[]> keyMap;
        void MapKeys(void);
        bool IsLowerCase(int _char);
        LoggerBase errLogger;
    public:
        virtual ~KeyboardWinStrategy() = default;
        KeyboardWinStrategy();
        virtual bool Write(const std::string& text) override;
        virtual bool Clear(void) override; 
};

#endif // KeyboardWinStrategy_H