#pragma once

namespace hazel {
typedef enum class KeyCode : uint16_t
{
    // From glfw3.h
    Space = 32,
    Apostrophe = 39, /* ' */
    Comma = 44,      /* , */
    Minus = 45,      /* - */
    Period = 46,     /* . */
    Slash = 47,      /* / */

    D0 = 48, /* 0 */
    D1 = 49, /* 1 */
    D2 = 50, /* 2 */
    D3 = 51, /* 3 */
    D4 = 52, /* 4 */
    D5 = 53, /* 5 */
    D6 = 54, /* 6 */
    D7 = 55, /* 7 */
    D8 = 56, /* 8 */
    D9 = 57, /* 9 */

    Semicolon = 59, /* ; */
    Equal = 61,     /* = */

    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,

    LeftBracket = 91,  /* [ */
    Backslash = 92,    /* \ */
    RightBracket = 93, /* ] */
    GraveAccent = 96,  /* ` */

    World1 = 161, /* non-US #1 */
    World2 = 162, /* non-US #2 */

    /* Function keys */
    Escape = 256,
    Enter = 257,
    Tab = 258,
    Backspace = 259,
    Insert = 260,
    Delete = 261,
    Right = 262,
    Left = 263,
    Down = 264,
    Up = 265,
    PageUp = 266,
    PageDown = 267,
    Home = 268,
    End = 269,
    CapsLock = 280,
    ScrollLock = 281,
    NumLock = 282,
    PrintScreen = 283,
    Pause = 284,
    F1 = 290,
    F2 = 291,
    F3 = 292,
    F4 = 293,
    F5 = 294,
    F6 = 295,
    F7 = 296,
    F8 = 297,
    F9 = 298,
    F10 = 299,
    F11 = 300,
    F12 = 301,
    F13 = 302,
    F14 = 303,
    F15 = 304,
    F16 = 305,
    F17 = 306,
    F18 = 307,
    F19 = 308,
    F20 = 309,
    F21 = 310,
    F22 = 311,
    F23 = 312,
    F24 = 313,
    F25 = 314,

    /* Keypad */
    KP0 = 320,
    KP1 = 321,
    KP2 = 322,
    KP3 = 323,
    KP4 = 324,
    KP5 = 325,
    KP6 = 326,
    KP7 = 327,
    KP8 = 328,
    KP9 = 329,
    KPDecimal = 330,
    KPDivide = 331,
    KPMultiply = 332,
    KPSubtract = 333,
    KPAdd = 334,
    KPEnter = 335,
    KPEqual = 336,

    LeftShift = 340,
    LeftControl = 341,
    LeftAlt = 342,
    LeftSuper = 343,
    RightShift = 344,
    RightControl = 345,
    RightAlt = 346,
    RightSuper = 347,
    Menu = 348
} Key;

inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
{
    os << static_cast<int32_t>(keyCode);
    return os;
}
} // namespace hazel

// From glfw3.h
#define HZ_KEY_SPACE ::hazel::Key::Space
#define HZ_KEY_APOSTROPHE ::hazel::Key::Apostrophe /* ' */
#define HZ_KEY_COMMA ::hazel::Key::Comma           /* , */
#define HZ_KEY_MINUS ::hazel::Key::Minus           /* - */
#define HZ_KEY_PERIOD ::hazel::Key::Period         /* . */
#define HZ_KEY_SLASH ::hazel::Key::Slash           /* / */
#define HZ_KEY_0 ::hazel::Key::D0
#define HZ_KEY_1 ::hazel::Key::D1
#define HZ_KEY_2 ::hazel::Key::D2
#define HZ_KEY_3 ::hazel::Key::D3
#define HZ_KEY_4 ::hazel::Key::D4
#define HZ_KEY_5 ::hazel::Key::D5
#define HZ_KEY_6 ::hazel::Key::D6
#define HZ_KEY_7 ::hazel::Key::D7
#define HZ_KEY_8 ::hazel::Key::D8
#define HZ_KEY_9 ::hazel::Key::D9
#define HZ_KEY_SEMICOLON ::hazel::Key::Semicolon /* ; */
#define HZ_KEY_EQUAL ::hazel::Key::Equal         /* = */
#define HZ_KEY_A ::hazel::Key::A
#define HZ_KEY_B ::hazel::Key::B
#define HZ_KEY_C ::hazel::Key::C
#define HZ_KEY_D ::hazel::Key::D
#define HZ_KEY_E ::hazel::Key::E
#define HZ_KEY_F ::hazel::Key::F
#define HZ_KEY_G ::hazel::Key::G
#define HZ_KEY_H ::hazel::Key::H
#define HZ_KEY_I ::hazel::Key::I
#define HZ_KEY_J ::hazel::Key::J
#define HZ_KEY_K ::hazel::Key::K
#define HZ_KEY_L ::hazel::Key::L
#define HZ_KEY_M ::hazel::Key::M
#define HZ_KEY_N ::hazel::Key::N
#define HZ_KEY_O ::hazel::Key::O
#define HZ_KEY_P ::hazel::Key::P
#define HZ_KEY_Q ::hazel::Key::Q
#define HZ_KEY_R ::hazel::Key::R
#define HZ_KEY_S ::hazel::Key::S
#define HZ_KEY_T ::hazel::Key::T
#define HZ_KEY_U ::hazel::Key::U
#define HZ_KEY_V ::hazel::Key::V
#define HZ_KEY_W ::hazel::Key::W
#define HZ_KEY_X ::hazel::Key::X
#define HZ_KEY_Y ::hazel::Key::Y
#define HZ_KEY_Z ::hazel::Key::Z
#define HZ_KEY_LEFT_BRACKET ::hazel::Key::LeftBracket   /* [ */
#define HZ_KEY_BACKSLASH ::hazel::Key::Backslash        /* \ */
#define HZ_KEY_RIGHT_BRACKET ::hazel::Key::RightBracket /* ] */
#define HZ_KEY_GRAVE_ACCENT ::hazel::Key::GraveAccent   /* ` */
#define HZ_KEY_WORLD_1 ::hazel::Key::World1             /* non-US #1 */
#define HZ_KEY_WORLD_2 ::hazel::Key::World2             /* non-US #2 */

/* Function keys */
#define HZ_KEY_ESCAPE ::hazel::Key::Escape
#define HZ_KEY_ENTER ::hazel::Key::Enter
#define HZ_KEY_TAB ::hazel::Key::Tab
#define HZ_KEY_BACKSPACE ::hazel::Key::Backspace
#define HZ_KEY_INSERT ::hazel::Key::Insert
#define HZ_KEY_DELETE ::hazel::Key::Delete
#define HZ_KEY_RIGHT ::hazel::Key::Right
#define HZ_KEY_LEFT ::hazel::Key::Left
#define HZ_KEY_DOWN ::hazel::Key::Down
#define HZ_KEY_UP ::hazel::Key::Up
#define HZ_KEY_PAGE_UP ::hazel::Key::PageUp
#define HZ_KEY_PAGE_DOWN ::hazel::Key::PageDown
#define HZ_KEY_HOME ::hazel::Key::Home
#define HZ_KEY_END ::hazel::Key::End
#define HZ_KEY_CAPS_LOCK ::hazel::Key::CapsLock
#define HZ_KEY_SCROLL_LOCK ::hazel::Key::ScrollLock
#define HZ_KEY_NUM_LOCK ::hazel::Key::NumLock
#define HZ_KEY_PRINT_SCREEN ::hazel::Key::PrintScreen
#define HZ_KEY_PAUSE ::hazel::Key::Pause
#define HZ_KEY_F1 ::hazel::Key::F1
#define HZ_KEY_F2 ::hazel::Key::F2
#define HZ_KEY_F3 ::hazel::Key::F3
#define HZ_KEY_F4 ::hazel::Key::F4
#define HZ_KEY_F5 ::hazel::Key::F5
#define HZ_KEY_F6 ::hazel::Key::F6
#define HZ_KEY_F7 ::hazel::Key::F7
#define HZ_KEY_F8 ::hazel::Key::F8
#define HZ_KEY_F9 ::hazel::Key::F9
#define HZ_KEY_F10 ::hazel::Key::F10
#define HZ_KEY_F11 ::hazel::Key::F11
#define HZ_KEY_F12 ::hazel::Key::F12
#define HZ_KEY_F13 ::hazel::Key::F13
#define HZ_KEY_F14 ::hazel::Key::F14
#define HZ_KEY_F15 ::hazel::Key::F15
#define HZ_KEY_F16 ::hazel::Key::F16
#define HZ_KEY_F17 ::hazel::Key::F17
#define HZ_KEY_F18 ::hazel::Key::F18
#define HZ_KEY_F19 ::hazel::Key::F19
#define HZ_KEY_F20 ::hazel::Key::F20
#define HZ_KEY_F21 ::hazel::Key::F21
#define HZ_KEY_F22 ::hazel::Key::F22
#define HZ_KEY_F23 ::hazel::Key::F23
#define HZ_KEY_F24 ::hazel::Key::F24
#define HZ_KEY_F25 ::hazel::Key::F25

/* Keypad */
#define HZ_KEY_KP_0 ::hazel::Key::KP0
#define HZ_KEY_KP_1 ::hazel::Key::KP1
#define HZ_KEY_KP_2 ::hazel::Key::KP2
#define HZ_KEY_KP_3 ::hazel::Key::KP3
#define HZ_KEY_KP_4 ::hazel::Key::KP4
#define HZ_KEY_KP_5 ::hazel::Key::KP5
#define HZ_KEY_KP_6 ::hazel::Key::KP6
#define HZ_KEY_KP_7 ::hazel::Key::KP7
#define HZ_KEY_KP_8 ::hazel::Key::KP8
#define HZ_KEY_KP_9 ::hazel::Key::KP9
#define HZ_KEY_KP_DECIMAL ::hazel::Key::KPDecimal
#define HZ_KEY_KP_DIVIDE ::hazel::Key::KPDivide
#define HZ_KEY_KP_MULTIPLY ::hazel::Key::KPMultiply
#define HZ_KEY_KP_SUBTRACT ::hazel::Key::KPSubtract
#define HZ_KEY_KP_ADD ::hazel::Key::KPAdd
#define HZ_KEY_KP_ENTER ::hazel::Key::KPEnter
#define HZ_KEY_KP_EQUAL ::hazel::Key::KPEqual

#define HZ_KEY_LEFT_SHIFT ::hazel::Key::LeftShift
#define HZ_KEY_LEFT_CONTROL ::hazel::Key::LeftControl
#define HZ_KEY_LEFT_ALT ::hazel::Key::LeftAlt
#define HZ_KEY_LEFT_SUPER ::hazel::Key::LeftSuper
#define HZ_KEY_RIGHT_SHIFT ::hazel::Key::RightShift
#define HZ_KEY_RIGHT_CONTROL ::hazel::Key::RightControl
#define HZ_KEY_RIGHT_ALT ::hazel::Key::RightAlt
#define HZ_KEY_RIGHT_SUPER ::hazel::Key::RightSuper
#define HZ_KEY_MENU ::hazel::Key::Menu