#include "StateStack.hpp"

#include <cassert>

State::Ptr StateStack::createState(States::ID stateID) {
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());
    return found->second();
}

void StateStack::applyPendingChanges() {
    for (const PendingChange& change : mPendingList) switch (change.action) {
            case Push:
                mStack.push_back(createState(change.stateID));
                break;
            case Pop:
                mStack.pop_back();
                break;
            case Clear:
                mStack.clear();
                break;
        }
    mPendingList.clear();
}

StateStack::StateStack(State::Context context) : mContext(context) {}

void StateStack::update(sf::Time dt) {
    for (auto it = mStack.rbegin(); it != mStack.rend(); it++)
        if (!(*it)->update(dt)) break;

    applyPendingChanges();
}

void StateStack::draw() {
    for (auto& it : mStack) it->draw();
}

void StateStack::handleEvent(const sf::Event& event) {
    for (auto it = mStack.rbegin(); it != mStack.rend(); it++)
        if (!(*it)->handleEvent(event)) break;

    applyPendingChanges();
}

void StateStack::pushState(States::ID stateID) {
    mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState() { mPendingList.push_back(PendingChange(Pop)); }

void StateStack::clearStates() { mPendingList.push_back(PendingChange(Clear)); }

bool StateStack::isEmpty() const { return mStack.empty(); }

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
    : action(action), stateID(stateID) {}
