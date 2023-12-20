#include "SceneNode.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>
#include <cassert>
#include <cmath>

#include "Command.hpp"
#include "Utility.hpp"

SceneNode::SceneNode(unsigned int category)
    : mParent(nullptr), mCategory(category), mIsMarkedForRemoval(false) {}

void SceneNode::attachChild(SceneNode::Ptr child) {
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

bool SceneNode::isMarkedForRemoval() const { return mIsMarkedForRemoval; }

void SceneNode::destroy() { mIsMarkedForRemoval = true; }

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
    // Draw recursively
    drawCurrent(target, states);
    drawChildren(target, states);

    drawBoundingRect(target, states);
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

void SceneNode::save(std::ostream& out) const {
    // Lanes must be saved from bottom to top
    saveCurrent(out);
    saveChildren(out);
}

// void SceneNode::load(std::istream& in, const TextureHolder& textures) {
//     loadCurrent(in);
//     loadChildren(in, textures);
// }

void SceneNode::saveCurrent(std::ostream& out) const {
    // For derived classes
}

void SceneNode::saveChildren(std::ostream& out) const {
    for (const Ptr& child : mChildren) {
        child->save(out);
    }
}

// void SceneNode::loadIndependentInformation(std::istream& in) {
//     // For derived classes
// }

// void SceneNode::loadDependentInformation(
//     std::istream& in, const TextureHolder& textures
// ) {
//     // For derived classes
// }

void SceneNode::loadCurrent(std::istream& in) {
    // For derived classes
}

void SceneNode::loadChildren(std::istream& in, const TextureHolder& textures) {
    // For derived classes
}

bool collision(
    const sf::FloatRect& lhs, const sf::FloatRect& rhs, float reduce
) {
    // Normally, people could use the reverse, that is when lhs does not
    // intersect with rhs

    // Ensure lhs and rhs are certainly intersected horizontally (for this game)
    sf::FloatRect lhsInnerBound = sf::FloatRect(
        lhs.left + reduce, rhs.top, lhs.width - reduce, rhs.height
    );
    sf::FloatRect rhsInnerBound = sf::FloatRect(
        rhs.left + reduce, rhs.top, rhs.width - reduce, rhs.height
    );

    return lhsInnerBound.intersects(rhsInnerBound);

    // float leftPos = lhs.left + lhs.width / 2.f;
    // float rightPos = rhs.left + rhs.width / 2.f;
    // return std::abs(leftPos - rightPos) < 0.5 * (lhs.width + rhs.width
    // - 30.f);
}

float length(sf::Vector2f vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float distance(const SceneNode& lhs, const SceneNode& rhs) {
    return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}
