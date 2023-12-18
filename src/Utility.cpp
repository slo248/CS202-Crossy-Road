#include "Utility.hpp"

#include <SFML/Graphics/Text.hpp>
#include <cstdlib>

std::string toString(sf::Keyboard::Key key) {
#define KEYTOSTRING_CASE(KEY) \
    case sf::Keyboard::KEY:   \
        return #KEY;

    switch (key) {
        KEYTOSTRING_CASE(Unknown)
        KEYTOSTRING_CASE(A)
        KEYTOSTRING_CASE(B)
        KEYTOSTRING_CASE(C)
        KEYTOSTRING_CASE(D)
        KEYTOSTRING_CASE(E)
        KEYTOSTRING_CASE(F)
        KEYTOSTRING_CASE(G)
        KEYTOSTRING_CASE(H)
        KEYTOSTRING_CASE(I)
        KEYTOSTRING_CASE(J)
        KEYTOSTRING_CASE(K)
        KEYTOSTRING_CASE(L)
        KEYTOSTRING_CASE(M)
        KEYTOSTRING_CASE(N)
        KEYTOSTRING_CASE(O)
        KEYTOSTRING_CASE(P)
        KEYTOSTRING_CASE(Q)
        KEYTOSTRING_CASE(R)
        KEYTOSTRING_CASE(S)
        KEYTOSTRING_CASE(T)
        KEYTOSTRING_CASE(U)
        KEYTOSTRING_CASE(V)
        KEYTOSTRING_CASE(W)
        KEYTOSTRING_CASE(X)
        KEYTOSTRING_CASE(Y)
        KEYTOSTRING_CASE(Z)
        KEYTOSTRING_CASE(Num0)
        KEYTOSTRING_CASE(Num1)
        KEYTOSTRING_CASE(Num2)
        KEYTOSTRING_CASE(Num3)
        KEYTOSTRING_CASE(Num4)
        KEYTOSTRING_CASE(Num5)
        KEYTOSTRING_CASE(Num6)
        KEYTOSTRING_CASE(Num7)
        KEYTOSTRING_CASE(Num8)
        KEYTOSTRING_CASE(Num9)
        KEYTOSTRING_CASE(Escape)
        KEYTOSTRING_CASE(LControl)
        KEYTOSTRING_CASE(LShift)
        KEYTOSTRING_CASE(LAlt)
        KEYTOSTRING_CASE(LSystem)
        KEYTOSTRING_CASE(RControl)
        KEYTOSTRING_CASE(RShift)
        KEYTOSTRING_CASE(RAlt)
        KEYTOSTRING_CASE(RSystem)
        KEYTOSTRING_CASE(Menu)
        KEYTOSTRING_CASE(LBracket)
        KEYTOSTRING_CASE(RBracket)
        KEYTOSTRING_CASE(SemiColon)
        KEYTOSTRING_CASE(Comma)
        KEYTOSTRING_CASE(Period)
        KEYTOSTRING_CASE(Quote)
        KEYTOSTRING_CASE(Slash)
        KEYTOSTRING_CASE(BackSlash)
        KEYTOSTRING_CASE(Tilde)
        KEYTOSTRING_CASE(Equal)
        KEYTOSTRING_CASE(Dash)
        KEYTOSTRING_CASE(Space)
        KEYTOSTRING_CASE(Return)
        KEYTOSTRING_CASE(BackSpace)
        KEYTOSTRING_CASE(Tab)
        KEYTOSTRING_CASE(PageUp)
        KEYTOSTRING_CASE(PageDown)
        KEYTOSTRING_CASE(End)
        KEYTOSTRING_CASE(Home)
        KEYTOSTRING_CASE(Insert)
        KEYTOSTRING_CASE(Delete)
        KEYTOSTRING_CASE(Add)
        KEYTOSTRING_CASE(Subtract)
        KEYTOSTRING_CASE(Multiply)
        KEYTOSTRING_CASE(Divide)
        KEYTOSTRING_CASE(Left)
        KEYTOSTRING_CASE(Right)
        KEYTOSTRING_CASE(Up)
        KEYTOSTRING_CASE(Down)
        KEYTOSTRING_CASE(Numpad0)
        KEYTOSTRING_CASE(Numpad1)
        KEYTOSTRING_CASE(Numpad2)
        KEYTOSTRING_CASE(Numpad3)
        KEYTOSTRING_CASE(Numpad4)
        KEYTOSTRING_CASE(Numpad5)
        KEYTOSTRING_CASE(Numpad6)
        KEYTOSTRING_CASE(Numpad7)
        KEYTOSTRING_CASE(Numpad8)
        KEYTOSTRING_CASE(Numpad9)
        KEYTOSTRING_CASE(F1)
        KEYTOSTRING_CASE(F2)
        KEYTOSTRING_CASE(F3)
        KEYTOSTRING_CASE(F4)
        KEYTOSTRING_CASE(F5)
        KEYTOSTRING_CASE(F6)
        KEYTOSTRING_CASE(F7)
        KEYTOSTRING_CASE(F8)
        KEYTOSTRING_CASE(F9)
        KEYTOSTRING_CASE(F10)
        KEYTOSTRING_CASE(F11)
        KEYTOSTRING_CASE(F12)
        KEYTOSTRING_CASE(F13)
        KEYTOSTRING_CASE(F14)
        KEYTOSTRING_CASE(F15)
        KEYTOSTRING_CASE(Pause)
    }

    return "";
}

int random(int left, int right) { return left + rand() % (right - left + 1); }

float slotToPosition(int slot) {
    return (2 * slot + 1) * DEFAULT_HALF_CELL_LENGTH;
}

int positionToSlot(float x) {
    return (x - DEFAULT_HALF_CELL_LENGTH) / DEFAULT_CELL_LENGTH;
}

int getCurrentRow(int y) { return y / DEFAULT_CELL_LENGTH; }

float getLevelFactor(Config::GameLevel::Type gameType) {
    return 1.f + static_cast<float>(gameType) / 20;
}

std::string savedGamePath(Config::GameLevel::Type type) {
    switch (type) {
        case Config::GameLevel::Endless: {
            return SAVED_GAME_ENDLESS_PATH;
            break;
        }

        case Config::GameLevel::L1: {
            return SAVED_GAME_L1_PATH;
        }

        case Config::GameLevel::L2: {
            return SAVED_GAME_L2_PATH;
        }

        case Config::GameLevel::L3: {
            return SAVED_GAME_L3_PATH;
        }

        case Config::GameLevel::L4: {
            return SAVED_GAME_L4_PATH;
        }

        case Config::GameLevel::L5: {
            return SAVED_GAME_L5_PATH;
        }

        default: {
            return "";
        }
    }
}

std::string gameModeToString(Config::GameLevel::Type type) {
    switch (type) {
        case Config::GameLevel::Endless: {
            return "Endless";
            break;
        }

        case Config::GameLevel::L1: {
            return "Level 1";
        }

        case Config::GameLevel::L2: {
            return "Level 2";
        }

        case Config::GameLevel::L3: {
            return "Level 3";
        }

        case Config::GameLevel::L4: {
            return "Level 4";
        }

        case Config::GameLevel::L5: {
            return "Level 5";
        }

        default: {
            return "";
        }
    }
}
