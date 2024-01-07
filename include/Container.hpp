#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <memory>
#include <vector>

#include "Component.hpp"

using namespace GUI;

class Container : public Component {
   public:
    typedef std::shared_ptr<Container> Ptr;

   public:
    Container();
    void pack(Component::Ptr component);
    virtual void handleEvent(const sf::Event& event);

   private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    std::vector<Component::Ptr> mChildren;
};

#endif
