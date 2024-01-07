#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

namespace sf {
class Event;
}

namespace GUI {

class Component : public sf::Drawable,
                  public sf::Transformable,
                  private sf::NonCopyable {
   public:
    typedef std::shared_ptr<Component> Ptr;

   public:
    Component();

   public:
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void select();
    virtual void deselect();
    bool isSelected() const;
    bool isActive() const;
    void isSelectable(bool isSelectable);
    void activate();
    void deactivate();

   protected:
    bool mIsSelectable;
    bool mIsSelected;
    bool mIsActive;
};

}  // namespace GUI

#endif
