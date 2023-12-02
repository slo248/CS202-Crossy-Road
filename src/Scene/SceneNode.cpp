#include "SceneNode.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

#include "Command.hpp"

SceneNode::SceneNode(unsigned int category)
    : mParent(nullptr), mCategory(category), mMarkedForRemoval(false) {}

void SceneNode::attachChild(Ptr child) {
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) {
        return p.get() == &node;
    });
    assert(found != mChildren.end());

    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

SceneNode* SceneNode::getParent() { return mParent; }

void SceneNode::update(sf::Time dt, CommandQueue& commands) {
    updateCurrent(dt, commands);
    updateChildren(dt, commands);
}

bool SceneNode::isMarkedForRemoval() const { return mMarkedForRemoval; }

void SceneNode::remove() { mMarkedForRemoval = true; }

void SceneNode::removeWrecks() {
    auto wreckfieldBegin = std::remove_if(
        mChildren.begin(), mChildren.end(),
        std::mem_fn(&SceneNode::isMarkedForRemoval)
    );
    mChildren.erase(wreckfieldBegin, mChildren.end());
    std::for_each(
        mChildren.begin(), mChildren.end(),
        std::mem_fn(&SceneNode::removeWrecks)
    );
}

sf::Vector2f SceneNode::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node; node = node->mParent) {
        transform = node->getTransform() * transform;
    }

    return transform;
}

void SceneNode::onCommand(const Command& command, sf::Time dt) {
    if (command.category & getCategory()) {
        command.action(*this, dt);
    }

    for (Ptr& child : mChildren) {
        child->onCommand(command, dt);
    }
}

unsigned int SceneNode::getCategory() const { return mCategory; }

sf::FloatRect SceneNode::getBoundingRect() const { return sf::FloatRect(); }

sf::FloatRect SceneNode::getLocalBounds() const { return sf::FloatRect(); }

void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands) {
    // For derived classes
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands) {
    for (Ptr& child : mChildren) {
        child->update(dt, commands);
    }
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Get the current transform
    states.transform *= getTransform();
    if (getCategory() == Category::Lane)
        std::cout << "Lane: " << this->getWorldPosition().x << ' '
                  << this->getWorldPosition().y << std::endl;

    // Draw recursively
    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const {
    // For derived classes
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states)
    const {
    // states.transform *= getTransform();
    for (const Ptr& child : mChildren) {
        child->draw(target, states);
    }
}

void SceneNode::drawBoundingRect(
    sf::RenderTarget& target, sf::RenderStates states
) const {
    sf::FloatRect rect = getBoundingRect();

    sf::RectangleShape shape;
    shape.setPosition(sf::Vector2f(rect.left, rect.top));
    shape.setSize(sf::Vector2f(rect.width, rect.height));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(1.f);

    target.draw(shape);
}

bool collision(const sf::FloatRect& lhs, const sf::FloatRect& rhs) {
    return lhs.intersects(rhs);
}

float length(sf::Vector2f vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float distance(const SceneNode& lhs, const SceneNode& rhs) {
    return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}
