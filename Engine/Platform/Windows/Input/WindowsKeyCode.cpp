#include"Platform/Windows/Input/WindowsKeyCode.h"
#include"Core/pch.h"
#include"Core/Logger/Logger.h"
#include<Xinput.h>

namespace VIEngine {
    EKeyCode WindowsToEngineKeyCode(WPARAM wparam) 
    {
        switch (wparam) {
            // Numbers
            case '0':           return EKeyCode::NUM_0;
            case '1':           return EKeyCode::NUM_1;
            case '2':           return EKeyCode::NUM_2;
            case '3':           return EKeyCode::NUM_3;
            case '4':           return EKeyCode::NUM_4;
            case '5':           return EKeyCode::NUM_5;
            case '6':           return EKeyCode::NUM_6;
            case '7':           return EKeyCode::NUM_7;
            case '8':           return EKeyCode::NUM_8;
            case '9':           return EKeyCode::NUM_9;

            // Letters
            case 'A':           return EKeyCode::A;
            case 'B':           return EKeyCode::B;
            case 'C':           return EKeyCode::C;
            case 'D':           return EKeyCode::D;
            case 'E':           return EKeyCode::E;
            case 'F':           return EKeyCode::F;
            case 'G':           return EKeyCode::G;
            case 'H':           return EKeyCode::H;
            case 'I':           return EKeyCode::I;
            case 'J':           return EKeyCode::J;
            case 'K':           return EKeyCode::K;
            case 'L':           return EKeyCode::L;
            case 'M':           return EKeyCode::M;
            case 'N':           return EKeyCode::N;
            case 'O':           return EKeyCode::O;
            case 'P':           return EKeyCode::P;
            case 'Q':           return EKeyCode::Q;
            case 'R':           return EKeyCode::R;
            case 'S':           return EKeyCode::S;
            case 'T':           return EKeyCode::T;
            case 'U':           return EKeyCode::U;
            case 'V':           return EKeyCode::V;
            case 'W':           return EKeyCode::W;
            case 'X':           return EKeyCode::X;
            case 'Y':           return EKeyCode::Y;
            case 'Z':           return EKeyCode::Z;

            // Controls & Special
            case VK_SPACE:      return EKeyCode::SPACE;
            case VK_OEM_7:      return EKeyCode::APOSTROPHE;
            case VK_OEM_COMMA:  return EKeyCode::COMMA;
            case VK_OEM_MINUS:  return EKeyCode::MINUS;
            case VK_OEM_PERIOD: return EKeyCode::PERIOD;
            case VK_OEM_2:      return EKeyCode::SLASH;
            case VK_OEM_1:      return EKeyCode::SEMICOLON;
            case VK_OEM_PLUS:   return EKeyCode::EQUAL;
            case VK_OEM_4:      return EKeyCode::LEFT_BRACKET;
            case VK_OEM_5:      return EKeyCode::BACKSLASH;
            case VK_OEM_6:      return EKeyCode::RIGHT_BRACKET;
            case VK_OEM_3:      return EKeyCode::GRAVE_ACCENT;

            // System Keys
            case VK_ESCAPE:     return EKeyCode::ESCAPE;
            case VK_RETURN:     return EKeyCode::ENTER;
            case VK_TAB:        return EKeyCode::TAB;
            case VK_BACK:       return EKeyCode::BACKSPACE;
            case VK_INSERT:     return EKeyCode::INSERT;
            case VK_DELETE:     return EKeyCode::DEL;
            case VK_RIGHT:      return EKeyCode::RIGHT;
            case VK_LEFT:       return EKeyCode::LEFT;
            case VK_DOWN:       return EKeyCode::DOWN;
            case VK_UP:         return EKeyCode::UP;
            case VK_PRIOR:      return EKeyCode::PAGE_UP;
            case VK_NEXT:       return EKeyCode::PAGE_DOWN;
            case VK_HOME:       return EKeyCode::HOME;
            case VK_END:        return EKeyCode::END;
            case VK_CAPITAL:    return EKeyCode::CAPS_LOCK;
            case VK_SCROLL:     return EKeyCode::SCROLL_LOCK;
            case VK_NUMLOCK:    return EKeyCode::NUM_LOCK;
            case VK_SNAPSHOT:   return EKeyCode::PRINT_SCREEN;
            case VK_PAUSE:      return EKeyCode::PAUSE;

            // Function Keys
            case VK_F1:         return EKeyCode::F1;
            case VK_F2:         return EKeyCode::F2;
            case VK_F3:         return EKeyCode::F3;
            case VK_F4:         return EKeyCode::F4;
            case VK_F5:         return EKeyCode::F5;
            case VK_F6:         return EKeyCode::F6;
            case VK_F7:         return EKeyCode::F7;
            case VK_F8:         return EKeyCode::F8;
            case VK_F9:         return EKeyCode::F9;
            case VK_F10:        return EKeyCode::F10;
            case VK_F11:        return EKeyCode::F11;
            case VK_F12:        return EKeyCode::F12;
            case VK_F13:        return EKeyCode::F13;
            case VK_F14:        return EKeyCode::F14;
            case VK_F15:        return EKeyCode::F15;
            case VK_F16:        return EKeyCode::F16;
            case VK_F17:        return EKeyCode::F17;
            case VK_F18:        return EKeyCode::F18;
            case VK_F19:        return EKeyCode::F19;
            case VK_F20:        return EKeyCode::F20;
            case VK_F21:        return EKeyCode::F21;
            case VK_F22:        return EKeyCode::F22;
            case VK_F23:        return EKeyCode::F23;
            case VK_F24:        return EKeyCode::F24;

            // Keypad
            case VK_NUMPAD0:    return EKeyCode::KP_0;
            case VK_NUMPAD1:    return EKeyCode::KP_1;
            case VK_NUMPAD2:    return EKeyCode::KP_2;
            case VK_NUMPAD3:    return EKeyCode::KP_3;
            case VK_NUMPAD4:    return EKeyCode::KP_4;
            case VK_NUMPAD5:    return EKeyCode::KP_5;
            case VK_NUMPAD6:    return EKeyCode::KP_6;
            case VK_NUMPAD7:    return EKeyCode::KP_7;
            case VK_NUMPAD8:    return EKeyCode::KP_8;
            case VK_NUMPAD9:    return EKeyCode::KP_9;
            case VK_DECIMAL:    return EKeyCode::KP_DECIMAL;
            case VK_DIVIDE:     return EKeyCode::KP_DIVIDE;
            case VK_MULTIPLY:   return EKeyCode::KP_MULTIPLY;
            case VK_SUBTRACT:   return EKeyCode::KP_SUBTRACT;
            case VK_ADD:        return EKeyCode::KP_ADD;

            // Modifiers
            case VK_LSHIFT:     return EKeyCode::LEFT_SHIFT;
            case VK_LCONTROL:   return EKeyCode::LEFT_CONTROL;
            case VK_LMENU:      return EKeyCode::LEFT_ALT;
            case VK_LWIN:       return EKeyCode::LEFT_SUPER;
            case VK_RSHIFT:     return EKeyCode::RIGHT_SHIFT;
            case VK_RCONTROL:   return EKeyCode::RIGHT_CONTROL;
            case VK_RMENU:      return EKeyCode::RIGHT_ALT;
            case VK_RWIN:       return EKeyCode::RIGHT_SUPER;
            case VK_APPS:       return EKeyCode::MENU;

            default:            return EKeyCode::NONE;
        }

        CORE_LOG_WARN("Invalid windows key {0}, return EKeyCode::NONE", wparam);
        return EKeyCode::NONE;
    }

    uint8_t EngineToWindowsKeyCode(EKeyCode keyCode) 
    {
        switch (keyCode) {
            // Numbers
            case EKeyCode::NUM_0:                       return '0';
            case EKeyCode::NUM_1:                       return '1';
            case EKeyCode::NUM_2:                       return '2';
            case EKeyCode::NUM_3:                       return '3';
            case EKeyCode::NUM_4:                       return '4';
            case EKeyCode::NUM_5:                       return '5';
            case EKeyCode::NUM_6:                       return '6';
            case EKeyCode::NUM_7:                       return '7';
            case EKeyCode::NUM_8:                       return '8';
            case EKeyCode::NUM_9:                       return '9';

            // Letters
            case EKeyCode::A:                           return 'A';
            case EKeyCode::B:                           return 'B';
            case EKeyCode::C:                           return 'C';
            case EKeyCode::D:                           return 'D';
            case EKeyCode::E:                           return 'E';
            case EKeyCode::F:                           return 'F';
            case EKeyCode::G:                           return 'G';
            case EKeyCode::H:                           return 'H';
            case EKeyCode::I:                           return 'I';
            case EKeyCode::J:                           return 'J';
            case EKeyCode::K:                           return 'K';
            case EKeyCode::L:                           return 'L';
            case EKeyCode::M:                           return 'M';
            case EKeyCode::N:                           return 'N';
            case EKeyCode::O:                           return 'O';
            case EKeyCode::P:                           return 'P';
            case EKeyCode::Q:                           return 'Q';
            case EKeyCode::R:                           return 'R';
            case EKeyCode::S:                           return 'S';
            case EKeyCode::T:                           return 'T';
            case EKeyCode::U:                           return 'U';
            case EKeyCode::V:                           return 'V';
            case EKeyCode::W:                           return 'W';
            case EKeyCode::X:                           return 'X';
            case EKeyCode::Y:                           return 'Y';
            case EKeyCode::Z:                           return 'Z';

            // Controls & Special
            case EKeyCode::SPACE:                       return VK_SPACE;
            case EKeyCode::APOSTROPHE:                  return VK_OEM_7;
            case EKeyCode::COMMA:                       return VK_OEM_COMMA;
            case EKeyCode::MINUS:                       return VK_OEM_MINUS;
            case EKeyCode::PERIOD:                      return VK_OEM_PERIOD;
            case EKeyCode::SLASH:                       return VK_OEM_2;
            case EKeyCode::SEMICOLON:                   return VK_OEM_1;
            case EKeyCode::EQUAL:                       return VK_OEM_PLUS;
            case EKeyCode::LEFT_BRACKET:                return VK_OEM_4;
            case EKeyCode::BACKSLASH:                   return VK_OEM_5;
            case EKeyCode::RIGHT_BRACKET:               return VK_OEM_6;
            case EKeyCode::GRAVE_ACCENT:                return VK_OEM_3;

            // System Keys
            case EKeyCode::ESCAPE:                      return VK_ESCAPE;
            case EKeyCode::ENTER:                       return VK_RETURN;
            case EKeyCode::TAB:                         return VK_TAB;
            case EKeyCode::BACKSPACE:                   return VK_BACK;
            case EKeyCode::INSERT:                      return VK_INSERT;
            case EKeyCode::DEL:                         return VK_DELETE;
            case EKeyCode::RIGHT:                       return VK_RIGHT;
            case EKeyCode::LEFT:                        return VK_LEFT;
            case EKeyCode::DOWN:                        return VK_DOWN;
            case EKeyCode::UP:                          return VK_UP;
            case EKeyCode::PAGE_UP:                     return VK_PRIOR;
            case EKeyCode::PAGE_DOWN:                   return VK_NEXT;
            case EKeyCode::HOME:                        return VK_HOME;
            case EKeyCode::END:                         return VK_END;
            case EKeyCode::CAPS_LOCK:                   return VK_CAPITAL;
            case EKeyCode::SCROLL_LOCK:                 return VK_SCROLL;
            case EKeyCode::NUM_LOCK:                    return VK_NUMLOCK;
            case EKeyCode::PRINT_SCREEN:                return VK_SNAPSHOT;
            case EKeyCode::PAUSE:                       return VK_PAUSE;

            // Function Keys
            case EKeyCode::F1:                          return VK_F1;
            case EKeyCode::F2:                          return VK_F2;
            case EKeyCode::F3:                          return VK_F3;
            case EKeyCode::F4:                          return VK_F4;
            case EKeyCode::F5:                          return VK_F5;
            case EKeyCode::F6:                          return VK_F6;
            case EKeyCode::F7:                          return VK_F7;
            case EKeyCode::F8:                          return VK_F8;
            case EKeyCode::F9:                          return VK_F9;
            case EKeyCode::F10:                         return VK_F10;
            case EKeyCode::F11:                         return VK_F11;
            case EKeyCode::F12:                         return VK_F12;
            case EKeyCode::F13:                         return VK_F13;
            case EKeyCode::F14:                         return VK_F14;
            case EKeyCode::F15:                         return VK_F15;
            case EKeyCode::F16:                         return VK_F16;
            case EKeyCode::F17:                         return VK_F17;
            case EKeyCode::F18:                         return VK_F18;
            case EKeyCode::F19:                         return VK_F19;
            case EKeyCode::F20:                         return VK_F20;
            case EKeyCode::F21:                         return VK_F21;
            case EKeyCode::F22:                         return VK_F22;
            case EKeyCode::F23:                         return VK_F23;
            case EKeyCode::F24:                         return VK_F24;

            // Keypad
            case EKeyCode::KP_0:                        return VK_NUMPAD0;
            case EKeyCode::KP_1:                        return VK_NUMPAD1;
            case EKeyCode::KP_2:                        return VK_NUMPAD2;
            case EKeyCode::KP_3:                        return VK_NUMPAD3;
            case EKeyCode::KP_4:                        return VK_NUMPAD4;
            case EKeyCode::KP_5:                        return VK_NUMPAD5;
            case EKeyCode::KP_6:                        return VK_NUMPAD6;
            case EKeyCode::KP_7:                        return VK_NUMPAD7;
            case EKeyCode::KP_8:                        return VK_NUMPAD8;
            case EKeyCode::KP_9:                        return VK_NUMPAD9;
            case EKeyCode::KP_DECIMAL:                  return VK_DECIMAL;
            case EKeyCode::KP_DIVIDE:                   return VK_DIVIDE;
            case EKeyCode::KP_MULTIPLY:                 return VK_MULTIPLY;
            case EKeyCode::KP_SUBTRACT:                 return VK_SUBTRACT;
            case EKeyCode::KP_ADD:                      return VK_ADD;

            // Modifiers
            case EKeyCode::LEFT_SHIFT:                  return VK_LSHIFT;  
            case EKeyCode::LEFT_CONTROL:                return VK_LCONTROL;
            case EKeyCode::LEFT_ALT:                    return VK_LMENU;  
            case EKeyCode::LEFT_SUPER:                  return VK_LWIN;    
            case EKeyCode::RIGHT_SHIFT:                 return VK_RSHIFT;  
            case EKeyCode::RIGHT_CONTROL:               return VK_RCONTROL;
            case EKeyCode::RIGHT_ALT:                   return VK_RMENU;   
            case EKeyCode::RIGHT_SUPER:                 return VK_RWIN;    
            case EKeyCode::MENU:                        return VK_APPS;    
        }
        
        CORE_LOG_WARN("Invalid engine key {0}, return oxff", static_cast<uint16_t>(keyCode));
        return 0x00;
    }

    EMouseButton WindowsToEngineMouseButton(WPARAM wparam) {
        switch (wparam)
        {
            case MK_LBUTTON:        return EMouseButton::BUTTON_LEFT;
            case MK_RBUTTON:        return EMouseButton::BUTTON_RIGHT;
            case MK_MBUTTON:        return EMouseButton::BUTTON_MIDDLE;
        }

        WORD xButton = GET_XBUTTON_WPARAM(wparam);
        switch (xButton)
        {
            case XBUTTON1:          return EMouseButton::BUTTON_BACK;
            case XBUTTON2:          return EMouseButton::BUTTON_FORWARD;
        }

        CORE_LOG_WARN("Invalid windows mouse button {0}, return EMouseButton::NONE", wparam);
        return EMouseButton::NONE;
    }

    uint8_t EngineToWindowsMouseButton(EMouseButton mouseButton) {
        switch (mouseButton)
        {
            case EMouseButton::BUTTON_LEFT:        return VK_LBUTTON;
            case EMouseButton::BUTTON_RIGHT:       return VK_RBUTTON;
            case EMouseButton::BUTTON_MIDDLE:      return VK_MBUTTON;
            case EMouseButton::BUTTON_BACK:        return VK_XBUTTON1;
            case EMouseButton::BUTTON_FORWARD:     return VK_XBUTTON2;
        }

        CORE_LOG_WARN("Invalid engine mouse button {0}, return oxff", static_cast<uint8_t>(mouseButton));
        return 0x00;
    }

    EGamepad WindowsToEngineGamepad(uint16_t button) {
        if (button == XINPUT_GAMEPAD_A)                     return EGamepad::BUTTON_A;
        if (button == XINPUT_GAMEPAD_B)                     return EGamepad::BUTTON_B;
        if (button == XINPUT_GAMEPAD_X)                     return EGamepad::BUTTON_X;
        if (button == XINPUT_GAMEPAD_Y)                     return EGamepad::BUTTON_Y;
        if (button == XINPUT_GAMEPAD_LEFT_SHOULDER)         return EGamepad::BUTTON_LB;
        if (button == XINPUT_GAMEPAD_RIGHT_SHOULDER)        return EGamepad::BUTTON_RB;
        if (button == XINPUT_GAMEPAD_DPAD_UP)               return EGamepad::BUTTON_UP;
        if (button == XINPUT_GAMEPAD_DPAD_DOWN)             return EGamepad::BUTTON_DOWN;
        if (button == XINPUT_GAMEPAD_DPAD_RIGHT)            return EGamepad::BUTTON_RIGHT;
        if (button == XINPUT_GAMEPAD_DPAD_LEFT)             return EGamepad::BUTTON_LEFT;
        if (button == XINPUT_GAMEPAD_START)                 return EGamepad::BUTTON_MENU;
        if (button == XINPUT_GAMEPAD_BACK)                  return EGamepad::BUTTON_VIEW;
        if (button == XINPUT_GAMEPAD_LEFT_THUMB)            return EGamepad::LEFT_THUMBSTICK;
        if (button == XINPUT_GAMEPAD_RIGHT_THUMB)           return EGamepad::RIGHT_THUMBSTICK;

        CORE_LOG_WARN("Invalid windows gamepad button {0}, return EGamepad::NONE", button);
        return EGamepad::NONE;
    }

    uint16_t EngineToWindowsGamepad(EGamepad gamepad) {
        switch (gamepad)
        {
            case EGamepad::BUTTON_A:             return XINPUT_GAMEPAD_A;
            case EGamepad::BUTTON_B:             return XINPUT_GAMEPAD_B;
            case EGamepad::BUTTON_X:             return XINPUT_GAMEPAD_X;
            case EGamepad::BUTTON_Y:             return XINPUT_GAMEPAD_Y;
            case EGamepad::BUTTON_LB:            return XINPUT_GAMEPAD_LEFT_SHOULDER;
            case EGamepad::BUTTON_RB:            return XINPUT_GAMEPAD_RIGHT_SHOULDER;
            case EGamepad::BUTTON_UP:            return XINPUT_GAMEPAD_DPAD_UP;
            case EGamepad::BUTTON_DOWN:          return XINPUT_GAMEPAD_DPAD_DOWN;
            case EGamepad::BUTTON_RIGHT:         return XINPUT_GAMEPAD_DPAD_RIGHT;
            case EGamepad::BUTTON_LEFT:          return XINPUT_GAMEPAD_DPAD_LEFT;
            case EGamepad::BUTTON_MENU:          return XINPUT_GAMEPAD_START;
            case EGamepad::BUTTON_VIEW:          return XINPUT_GAMEPAD_BACK;
            case EGamepad::LEFT_THUMBSTICK:      return XINPUT_GAMEPAD_LEFT_THUMB;
            case EGamepad::RIGHT_THUMBSTICK:     return XINPUT_GAMEPAD_RIGHT_THUMB;
        }

        CORE_LOG_WARN("Invalid engine gamepad button {0}, return 0xffff", static_cast<uint8_t>(gamepad));
        return 0x0000;
    }
}