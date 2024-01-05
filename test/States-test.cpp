#include <iostream>

#include "Application.hpp"
#include "ChooseModeState.hpp"
#include "CreditState.hpp"
#include "GameState.hpp"
#include "LevelState.hpp"
#include "LoseState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "RankingState.hpp"
#include "SettingState.hpp"
#include "WinState.hpp"
using namespace std;

FontHolder fonts;
TextureHolder textures;
SoundEffectPlayer sounds;
MusicPlayer musics;
vector<int> highScores;

sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
Player player;

int main() {
    fonts.loadFontFromFile();
    textures.loadTextureFromFile();

    cerr << "1. Creating context" << endl;
    State::Context context(
        window, textures, fonts, musics, sounds, player, highScores
    );

    cerr << "2. Creating state stack" << endl;
    StateStack stateStack(context);

    cerr << "3. Creating menu state" << endl;
    MenuState menuState(stateStack, context);

    cerr << "4. Creating choose mode state" << endl;
    ChooseModeState chooseModeState(stateStack, context);

    cerr << "5. Creating setting state" << endl;
    SettingState settingState(stateStack, context);

    cerr << "6. Creating ranking state" << endl;
    RankingState rankingState(stateStack, context);

    cerr << "7. Creating credit state" << endl;
    CreditState creditState(stateStack, context);

    cerr << "8. Creating level state" << endl;
    LevelState levelState(stateStack, context);

    cerr << "9. Creating game state" << endl;
    GameState gameState(stateStack, context);

    cerr << "10. Creating pause state" << endl;
    PauseState pauseState(stateStack, context);

    cerr << "11. Creating win state" << endl;
    WinState winState(stateStack, context);

    cerr << "12. Creating lose state" << endl;
    LoseState loseState(stateStack, context);
    return 0;
}
