#ifndef CONFIG_HPP
#define CONFIG_HPP

#define SAVED_GAME_SURVIVAL_PATH "data/survival.txt"
#define SAVED_GAME_L1_PATH "data/level1.txt"
#define SAVED_GAME_L2_PATH "data/level2.txt"
#define SAVED_GAME_L3_PATH "data/level3.txt"
#define SAVED_GAME_L4_PATH "data/level4.txt"
#define SAVED_GAME_L5_PATH "data/level5.txt"

#define RANKING_PATH "data/ranking.txt"
#define SETTING_PATH "data/setting.txt"

#define DEFAULT_PLAYER_SLOT 6
#define DEFAULT_RANKING_SLOTS 5
#define NUMBER_OF_SKINS 6

#define DEFAULT_CELLS_PER_LANE 14
#define DEFAULT_CELL_LENGTH 64.f
#define DEFAULT_HALF_CELL_LENGTH 32.f
#define DEFAULT_SCREEN_WIDTH 896.f
#define DEFAULT_SCREEN_HEIGHT 640.f
#define DEFAULT_CELL_RECT \
    sf::IntRect(0, 0, DEFAULT_CELL_LENGTH, DEFAULT_CELL_LENGTH)
#define DEFAULT_LANE_RECT                                                      \
    sf::IntRect(                                                               \
        0, 0, DEFAULT_CELL_LENGTH* DEFAULT_CELLS_PER_LANE, DEFAULT_CELL_LENGTH \
    )
#define DEFAULT_BACK_BUTTON_X 836.f
#define DEFAULT_BACK_BUTTON_Y 4.f

#define DEFAULT_AIR_ENEMY_SPEED 450.f
#define DEFAULT_GROUND_ENEMY_SPEED 140.f
#define DEFAULT_PLAYER_SPEED 500.f
#define DEFAULT_LOG_SPEED 120.f

#define DEFAULT_TIME_PER_FRAME sf::seconds(1.f / 60.f)
#define DEFAULT_ANIMATION_DURATION sf::seconds(1.5)
#define DEFAULT_COUNTDOWN_DURATION sf::seconds(3)
#define DEFAULT_SPAWN_INTERVAL sf::seconds(3.5)
#define GREEN_LIGHT_INTERVAL sf::seconds(3.0)
#define YELLOW_LIGHT_INTERVAL sf::seconds(2.0)
#define RED_LIGHT_INTERVAL sf::seconds(3.0)
#define AVERAGE_MOVEMENT_DURATION 0.23

#define LEVEL_ONE_COEFFICIENT 0.6
#define LEVEL_TWO_COEFFICIENT 0.8
#define LEVEL_THREE_COEFFICIENT 1.0
#define LEVEL_FOUR_COEFFICIENT 1.2
#define LEVEL_FIVE_COEFFICIENT 1.4
#define SURVIVAL_COEFFICIENT 0.8

#define WEATHER_NORMAL_FACTOR 1.f
#define WEATHER_RAIN_FACTOR 0.75
#define WEATHER_SNOW_FACTOR 0.7

namespace Config {
namespace Game {
enum Level { L1, L2, L3, L4, L5, Survival, Count };
enum Weather { Rain, Snow, Normal };
}  // namespace Game
namespace WinState {
enum Mode { Win, HighScore };
}
namespace LoseState {
enum Mode { Lose, Survival };
}
namespace ChooseModeState {
enum Mode { NewGame, Continue };
}
namespace LevelState {
enum Mode { NewGame, Continue };
}
namespace SettingState {
enum Mode { NonSkin, Skin };
}
}  // namespace Config
#endif  // CONFIG_HPP
