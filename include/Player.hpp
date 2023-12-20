#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Event.hpp>
#include <map>

#include "Command.hpp"

class CommandQueue;

class Player {
   public:
    enum Action { MoveUp, MoveDown, MoveLeft, MoveRight, ShowPosition, Count };

   public:
    Player();

    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void handleRealtimeInput(CommandQueue& commands);

    void assignKey(Action action, sf::Keyboard::Key key);
    sf::Keyboard::Key getKey(Action action) const;

    static bool isRealtimeAction(Action action);


   private:
    void initKeys();
    // still developing
    void initActions();

   private:
    std::map<sf::Keyboard::Key, Action> mKeyBinding;
    std::map<Action, Command> mActionBinding;
};

#endif  // PLAYER_HPP
