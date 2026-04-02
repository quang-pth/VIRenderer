#include"Platform/Windows/Input/WindowsKeyCode.h"
#include"Core/pch.h"

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
        return EMouseButton::NONE;
    }
}