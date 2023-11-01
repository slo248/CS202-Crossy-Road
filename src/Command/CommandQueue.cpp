#include "CommandQueue.hpp"

#include <cassert>

void CommandQueue::push(const Command& command) { mQueue.push(command); }

Command CommandQueue::pop() {
    assert(!isEmpty());
    Command tmp = mQueue.front();
    mQueue.pop();
    return tmp;
}

bool CommandQueue::isEmpty() const { return mQueue.empty(); }
