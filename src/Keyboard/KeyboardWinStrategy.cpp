#include "../../include/Keyboard/KeyboardWinStrategy.h"

bool KeyboardWinStrategy::Write(const std::string& msg)
{
    const size_t count = msg.length() * 2;
    std::vector<INPUT> characters;

    for (auto &&str: msg)
    {
        auto ascii = static_cast<WORD>(str);
        if (IsLowerCase(ascii))
        {
            ascii = ascii ^ 0x20;
        }

        // down press
        characters.push_back(
            INPUT {
                .type = INPUT_KEYBOARD,
                .ki {
                    .wVk = ascii
                }
            }
        );
        
        // up press
        characters.push_back(
            INPUT {
                .type = INPUT_KEYBOARD,
                .ki {
                    .wVk = ascii,
                    .dwFlags = KEYEVENTF_KEYUP 
                }
            }
        );
    }

    UINT uSent = SendInput((UINT)characters.size(), characters.data(), sizeof(INPUT));

    if (uSent != characters.size())
    {
        std::cout << "err branch\n";
        auto err = HRESULT_FROM_WIN32(GetLastError());
        std::string msg = std::format("Failed to write with error: {}", err);
        std::cout << msg << "\n";
        // throw std::runtime_error(msg);
    }

    return true;
}

bool KeyboardWinStrategy::IsLowerCase(int _char)
{
    return _char > static_cast<int>('Z');
}

bool KeyboardWinStrategy::Clear(void)
{
    return true;
}

void KeyboardWinStrategy::MapKeys(void)
{
    for (int i = 0; i < 26; ++i)
    {
        this->keyMap[i] = static_cast<int>('A' + i);
    }
}

KeyboardWinStrategy::KeyboardWinStrategy()
:   keyMap(std::make_unique<int[]>(36)),
    errLogger(LogLevel::Lvl_ERROR)
{
    std::fill_n(keyMap.get(), 36, 0);
    this->MapKeys();
}