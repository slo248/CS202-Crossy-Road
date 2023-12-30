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
    virtual ~Component();

   public:
    virtual void isSelectable(bool isSelectable) {
        mIsSelectable = isSelectable;
    }
    bool isSelected() const;
    virtual void select();
    virtual void deselect();

    virtual bool isActive() const;
    virtual void handleEvent(const sf::Event& event) = 0;

   protected:
    bool mIsSelectable;
    bool mIsSelected;
    bool mIsActive;
};

}  // namespace GUI

#endif
