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

#define DEFAULT_SPAWN_INTERVAL sf::seconds(5.0)

#define LEVEL_ONE_COEFFICIENT 1.0
#define LEVEL_TWO_COEFFICIENT 1.1
#define LEVEL_THREE_COEFFICIENT 1.2
#define LEVEL_FOUR_COEFFICIENT 1.3
#define LEVEL_FIVE_COEFFICIENT 1.4

namespace Config {
namespace GameLevel {
enum Type { L1, L2, L3, L4, L5, Endless, Count };
}  // namespace GameLevel
}  // namespace Config

#endif  // CONFIG_HPP
