#include "Container.hpp"

#include <SFML/Window/Event.hpp>

#include "Foreach.hpp"

Container::Container() : mChildren() {}

void Container::pack(Component::Ptr component) {
    mChildren.push_back(component);
}

void Container::handleEvent(const sf::Event& event) {
    for (auto& child : mChildren) child->handleEvent(event);
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    for (const Component::Ptr& child : mChildren) {
        target.draw(*child, states);
    }
}
