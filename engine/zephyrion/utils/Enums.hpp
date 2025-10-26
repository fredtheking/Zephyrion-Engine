#pragma once
#include "zephyrion/pch.hpp"
#define ENUM(NAME) enum class NAME
#define BITMASK_ENUMCLASS_OPERATORS(NAME) inline NAME operator|(NAME a, NAME b) {                    \
                                    return static_cast<NAME>(                                    \
                                        static_cast<int>(a) | static_cast<int>(b)                 \
                                    );                                                             \
                                  }                                                                 \
                                  inline NAME operator|=(NAME a, NAME b) {                           \
                                    return a = a | b;                                                 \
                                  }                                                                    \
                                  inline bool operator^(NAME a, NAME b) {                               \
                                    return static_cast<int>(a) & static_cast<int>(b);                    \
                                  }                                                                       \
                                  inline NAME operator&(NAME a, NAME b) {                                  \
                                    return static_cast<NAME>(static_cast<int>(a) & static_cast<int>(b));    \
                                  }                                                                          \
                                  inline NAME operator-(NAME a, NAME b) {                                     \
                                    return static_cast<NAME>(                                                  \
                                      static_cast<int>(a) & ~static_cast<int>(b)                                \
                                    );                                                                           \
                                  }                                                                               \
                                  inline NAME operator-=(NAME a, NAME b) {                                         \
                                    return a = a - b;                                                               \
                                  }

namespace ZE::Enums {
  ENUM(ZE_BackendRenderer) {
    OpenGL,
    Vulkan,
    Metal,
  };

  ENUM(ZE_WindowPosition) {
    Centered,
    TopLeft,
    Custom,
  };

  ENUM(ZE_WindowMode) {
    Windowed,
    Maximized,
    Fullscreen,
    Exclusive,
  };

  ENUM(ZE_WindowRenderOption) {
    AspectRatio,
    Stretch,
    TopLeftClip,
    BottomLeftClip,
  };

  ENUM(ZE_WindowResolutionOption) {
    WindowSize,
    Custom,
  };

  ENUM(ZE_Keys) {
    #define PAIR(X, Y) X = SDL_SCANCODE_ ##Y,
    #define PAIR_SINGLE(X) PAIR(X, X)

    Unknown = SDL_SCANCODE_UNKNOWN,
    PAIR_SINGLE(A)
    PAIR_SINGLE(B)
    PAIR_SINGLE(C)
    PAIR_SINGLE(D)
    PAIR_SINGLE(E)
    PAIR_SINGLE(F)
    PAIR_SINGLE(G)
    PAIR_SINGLE(H)
    PAIR_SINGLE(I)
    PAIR_SINGLE(J)
    PAIR_SINGLE(K)
    PAIR_SINGLE(L)
    PAIR_SINGLE(M)
    PAIR_SINGLE(N)
    PAIR_SINGLE(O)
    PAIR_SINGLE(P)
    PAIR_SINGLE(Q)
    PAIR_SINGLE(R)
    PAIR_SINGLE(S)
    PAIR_SINGLE(T)
    PAIR_SINGLE(U)
    PAIR_SINGLE(V)
    PAIR_SINGLE(W)
    PAIR_SINGLE(X)
    PAIR_SINGLE(Y)
    PAIR_SINGLE(Z)

    PAIR(Zero, 0)
    PAIR(One, 1)
    PAIR(Two, 2)
    PAIR(Three, 3)
    PAIR(Four, 4)
    PAIR(Five, 5)
    PAIR(Six, 6)
    PAIR(Seven, 7)
    PAIR(Eight, 8)
    PAIR(Nine, 9)

    PAIR(Return, RETURN)
    PAIR(Escape, ESCAPE)
    PAIR(Backspace, BACKSPACE)
    PAIR(Tab, TAB)
    PAIR(Space, SPACE)

    PAIR(Minus, MINUS)
    PAIR(Equals, EQUALS)
    PAIR(LeftBracket, LEFTBRACKET)
    PAIR(RightBracket, RIGHTBRACKET)
    PAIR(Backslash, BACKSLASH)
    //PAIR(Nonusbackslash, NONUSBACKSLASH)
    //PAIR(Nonusash, NONUSHASH)
    PAIR(Semicolon, SEMICOLON)
    PAIR(Apostrophe, APOSTROPHE)
    PAIR(Grave, GRAVE)
    PAIR(Comma, COMMA)
    PAIR(Period, PERIOD)
    PAIR(Slash, SLASH)

    PAIR(Capslock, CAPSLOCK)

    PAIR_SINGLE(F1)
    PAIR_SINGLE(F2)
    PAIR_SINGLE(F3)
    PAIR_SINGLE(F4)
    PAIR_SINGLE(F5)
    PAIR_SINGLE(F6)
    PAIR_SINGLE(F7)
    PAIR_SINGLE(F8)
    PAIR_SINGLE(F9)
    PAIR_SINGLE(F10)
    PAIR_SINGLE(F11)
    PAIR_SINGLE(F12)
    PAIR_SINGLE(F13)
    PAIR_SINGLE(F14)
    PAIR_SINGLE(F15)
    PAIR_SINGLE(F16)
    PAIR_SINGLE(F17)
    PAIR_SINGLE(F18)
    PAIR_SINGLE(F19)
    PAIR_SINGLE(F20)
    PAIR_SINGLE(F21)
    PAIR_SINGLE(F22)
    PAIR_SINGLE(F23)
    PAIR_SINGLE(F24)

    PAIR(PrintScreen, PRINTSCREEN)
    PAIR(ScrollLock, SCROLLLOCK)
    PAIR(Pause, PAUSE)
    PAIR(Insert, INSERT)

    PAIR(Home, HOME)
    PAIR(PageUp, PAGEUP)
    PAIR(Delete, DELETE)
    PAIR(End, END)
    PAIR(PageDown, PAGEDOWN)
    PAIR(Right, RIGHT)
    PAIR(Left, LEFT)
    PAIR(Down, DOWN)
    PAIR(Up, UP)

    PAIR(NumLockClear, NUMLOCKCLEAR)

    PAIR(Keypad_Divide, KP_DIVIDE)
    PAIR(Keypad_Multiply, KP_MULTIPLY)
    PAIR(Keypad_Minus, KP_MINUS)
    PAIR(Keypad_Plus, KP_PLUS)
    PAIR(Keypad_Enter, KP_ENTER)
    PAIR(Keypad_Zero, KP_0)
    PAIR(Keypad_One, KP_1)
    PAIR(Keypad_Two, KP_2)
    PAIR(Keypad_Three, KP_3)
    PAIR(Keypad_Four, KP_4)
    PAIR(Keypad_Five, KP_5)
    PAIR(Keypad_Six, KP_6)
    PAIR(Keypad_Seven, KP_7)
    PAIR(Keypad_Eight, KP_8)
    PAIR(Keypad_Nine, KP_9)
    PAIR(Keypad_Period, KP_PERIOD)
    PAIR(Keypad_Equals, KP_EQUALS)
    PAIR(Keypad_Comma, KP_COMMA)

    PAIR(Sleep, SLEEP)
    PAIR(Wake, WAKE)
    PAIR(ContextMenu, APPLICATION)
    PAIR(Execute, EXECUTE)
    PAIR(Help, HELP)
    PAIR(Menu, MENU)
    PAIR(Select, SELECT)
    PAIR(Stop, STOP)
    PAIR(Redo, AGAIN)
    PAIR(Undo, UNDO)
    PAIR(Cut, CUT)
    PAIR(Copy, COPY)
    PAIR(Paste, PASTE)
    PAIR(Find, FIND)
    PAIR(Mute, MUTE)
    PAIR(VolumeUp, VOLUMEUP)
    PAIR(VolumeDown, VOLUMEDOWN)

    PAIR(LeftControl, LCTRL)
    PAIR(LeftShift, LSHIFT)
    PAIR(LeftAlt, LALT)
    PAIR(LeftMeta, LGUI)
    PAIR(RightControl, RCTRL)
    PAIR(RightShift, RSHIFT)
    PAIR(RightAlt, RALT)
    PAIR(RightMeta, RGUI)

    #undef PAIR_SINGLE
    #undef PAIR
  };

  ENUM(ZE_Mouse) {
    Unknown = 0,
    Left = 1 << 0,
    Right = 1 << 1,
    Middle = 1 << 2,
    Extra1 = 1 << 3,
    Extra2 = 1 << 4,
  };
  BITMASK_ENUMCLASS_OPERATORS(ZE_Mouse)
}

#undef BITMASK_ENUMCLASS_OPERATORS
#undef ENUM