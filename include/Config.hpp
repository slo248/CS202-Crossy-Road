#ifndef CONFIG_HPP
#define CONFIG_HPP

#define DEFAULT_CELLS_PER_LANE 14
#define DEFAULT_CELL_LENGTH 64
#define DEFAULT_CELL_RECT \
    sf::IntRect(0, 0, DEFAULT_CELL_LENGTH, DEFAULT_CELL_LENGTH)
#define DEFAULT_LANE_RECT                                                      \
    sf::IntRect(                                                               \
        0, 0, DEFAULT_CELL_LENGTH* DEFAULT_CELLS_PER_LANE, DEFAULT_CELL_LENGTH \
    )

#define DEFAULT_SPAWN_INTERVAL sf::seconds(3.5)
#define DEFAULT_PLAYER_SLOT 6
#define DEFAULT_AIR_ENEMY_SPEED 350.f
#define DEFAULT_GROUND_ENEMY_SPEED 150.f
#define DEFAULT_PLAYER_SPEED 500.f
#define DEFAULT_LOG_SPEED 100.f

#define LEVEL_ONE_COEFFICIENT 1.0
#define LEVEL_TWO_COEFFICIENT 1.1
#define LEVEL_THREE_COEFFICIENT 1.2
#define LEVEL_FOUR_COEFFICIENT 1.3
#define LEVEL_FIVE_COEFFICIENT 1.4

#define NUMBER_OF_BUFFER_LANE 5

namespace Config {
namespace GameLevel {
enum Type { L1, L2, L3, L4, L5, Endless, Count };
}  // namespace GameLevel
}  // namespace Config

#endif  // CONFIG_HPP
