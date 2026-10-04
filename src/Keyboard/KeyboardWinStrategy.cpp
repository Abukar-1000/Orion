#include "../../include/Keyboard/KeyboardWinStrategy.h"

bool KeyboardWinStrategy::Write(const std::string& msg)
{
    const size_t count = msg.length() * 2;
    std::vector<INPUT> characters;
    // characters.reserve(count);

    for (auto &&str: msg)
    {
        auto actions = this->MapKey(str);

        for (auto action: actions.Get())
        {
            characters.push_back(action);
        }
    }

    UINT uSent = SendInput((UINT)characters.size(), characters.data(), sizeof(INPUT));

    if (uSent != characters.size())
    {
        std::cout << "err branch\n";
        auto err = HRESULT_FROM_WIN32(GetLastError());
        std::string msg = std::format("Failed to write with error: {}", err);
        std::cout << msg << "\n";
        throw std::runtime_error(msg);
    }

    return true;
}

KeyAction KeyboardWinStrategy::MapKey(const char& _char)
{
    const WORD SHIFT = 0x10;
    const KeyAction NoOP = KeyAction().WithKey(SHIFT, false).Build();
    try
    {
        if (this->keyMap == nullptr)
        {
            return NoOP;
        }

        return (*(this->keyMap))[_char];
    }
    catch(...)
    {
        return NoOP;
    }
}

bool KeyboardWinStrategy::Clear(void)
{
    return true;
}

void KeyboardWinStrategy::BuildKeyMap(void)
{
    const WORD A = 0x41;
    const WORD Z = A + 26;

    for (int letter = A; letter < Z; ++letter)
    {
        char uppercase = static_cast<char>(letter);
        KeyAction uppercaseAction = KeyAction().WithKey(letter, false).Build();
        this->keyMap->insert(std::pair<char, KeyAction>(uppercase, uppercaseAction));
        
        WORD lowercaseLetter = letter ^ 0x20;
        char lowercase = static_cast<char>(lowercaseLetter);
        KeyAction lowercaseAction = KeyAction().WithKey(lowercaseLetter, false).Build();
        this->keyMap->insert(std::pair<char, KeyAction>(lowercase, uppercaseAction));
    }

    const WORD SHIFT = 0x10;
    const std::pair<char, KeyAction> specialChars[] = 
    {
        { ';', KeyAction().WithKey(0xBA, false).Build() },
        { '+', KeyAction().WithKey(0xBB, false).Build() },
        { ',', KeyAction().WithKey(0xBC, false).Build() },
        { '-', KeyAction().WithKey(0xBD, false).Build() },
        { '.', KeyAction().WithKey(0xBE, false).Build() },
        { '/', KeyAction().WithKey(0xBF, false).Build() },
        { ' ', KeyAction().WithKey(0x20, false).Build() },
        { '[', KeyAction().WithKey(0xDB, false).Build() },
        { ']', KeyAction().WithKey(0xDD, false).Build() },
        { '\\', KeyAction().WithKey(0xDC, false).Build() },
        { '>', KeyAction().WithKey(SHIFT, true).WithKey(0xBF, false).Build() },
        { '_', KeyAction().WithKey(SHIFT, true).WithKey(0xBD, false).Build() },
        { '|', KeyAction().WithKey(SHIFT, true).WithKey(0xDC, false).Build() },
        { '{', KeyAction().WithKey(SHIFT, true).WithKey(0xDB, false).Build() },
        { '}', KeyAction().WithKey(SHIFT, true).WithKey(0xDD, false).Build() }
    };

    for (short i = 0; i < 15; ++i)
    {
        this->keyMap->insert(specialChars[i]);
    }
}

KeyboardWinStrategy::KeyboardWinStrategy()
:   keyMap(std::make_unique<KeyMap>()),
    errLogger(LogLevel::Lvl_ERROR)
{
    this->keyMap->reserve(68);
    this->BuildKeyMap();
    
    auto start = this->keyMap->begin();
    auto end = this->keyMap->end();

    for (auto it = start; it != end; ++it)
    {
        if (it == nullptr) continue;

        std::string chars = "";
        for (auto action : it->second.Get())
        {
            if (action.ki.dwFlags == KEYEVENTF_KEYUP) continue;
            chars += static_cast<char>(action.ki.wVk);
        }

        std::cout << it->first << " => " << chars << "\n";
    }
}
