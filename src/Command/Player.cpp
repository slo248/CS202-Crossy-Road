#include "Player.hpp"

#include <iostream>

#include "Character.hpp"
#include "CommandQueue.hpp"
#include "Config.hpp"
#include "SceneNode.hpp"

Player::Player() : mActionBinding(), mKeyBinding() {
    initKeys();
    initActions();
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
    for (const auto& pair : mKeyBinding)
        if (event.type == sf::Event::KeyReleased &&
            !isRealtimeAction(pair.second) && pair.first == event.key.code)
            commands.push(mActionBinding[pair.second]);
}

void Player::handleRealtimeInput(CommandQueue& commands) {
    for (const auto& pair : mKeyBinding)
        if (isRealtimeAction(pair.second) &&
            sf::Keyboard::isKeyPressed(pair.first)) {
            commands.push(mActionBinding[pair.second]);
            std::cout << "real time pushed" << std::endl;
        }
}

void Player::assignKey(Action action, sf::Keyboard::Key key) {
    for (auto it = mKeyBinding.begin(); it != mKeyBinding.end();)
        if (it->first == key || it->second == action)
            mKeyBinding.erase(it++);
        else
            ++it;

    mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getKey(Action action) const {
    for (const auto& pair : mKeyBinding)
        if (pair.second == action) return pair.first;

    return sf::Keyboard::Unknown;
}

bool Player::isRealtimeAction(Action action) {
    // switch (action) {
    //     case MoveUp:
    //     case MoveDown:
    //     case MoveLeft:
    //     case MoveRight:
    //         return true;
    //     default:
    //         return false;
    // }
    return false;
}

void Player::initKeys() {
    mKeyBinding[sf::Keyboard::W] = MoveUp;
    mKeyBinding[sf::Keyboard::S] = MoveDown;
    mKeyBinding[sf::Keyboard::A] = MoveLeft;
    mKeyBinding[sf::Keyboard::D] = MoveRight;
    mKeyBinding[sf::Keyboard::P] = ShowPosition;
}

void Player::initActions() {
    mActionBinding[ShowPosition].action = [](SceneNode& a, sf::Time dt) {
        sf::Vector2f pos = a.getWorldPosition();
        std::cout << "Player is at row "
                  << (pos.y + DEFAULT_HALF_CELL_LENGTH) / DEFAULT_CELL_LENGTH
                  << std::endl;
    };
    mActionBinding[MoveUp].action =
        derivedAction<Character>([](Character& a, sf::Time dt) {
            a.moveCharacter(Character::Direction::ToUpper);
        });
    mActionBinding[MoveDown].action =
        derivedAction<Character>([](Character& a, sf::Time dt) {
            a.moveCharacter(Character::Direction::ToLower);
        });
    mActionBinding[MoveLeft].action =
        derivedAction<Character>([](Character& a, sf::Time dt) {
            a.moveCharacter(Character::Direction::ToLeft);
        });
    mActionBinding[MoveRight].action =
        derivedAction<Character>([](Character& a, sf::Time dt) {
            a.moveCharacter(Character::Direction::ToRight);
        });

    for (auto& pair : mActionBinding) pair.second.category = Category::Player;
}
