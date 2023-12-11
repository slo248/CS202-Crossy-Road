#ifndef STATEID_HPP
#define STATEID_HPP

namespace States {
enum ID {
    None,
    Title,
    Menu,
    Setting,
    SettingInGame,
    Game,
    Level,
    Loading,
    Pause,
    Win,
    Lose,
    Credit,
    Ranking,
    ChooseMode,
    ChooseModeSaved,
};
}

#endif  // STATEID_HPP
