#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include <vector>

class SceneNode : public sf::Transformable,
                  public sf::NonCopyable,
                  public sf::Drawable {
   public:
    typedef std::unique_ptr<SceneNode> Ptr;

   public:
    SceneNode();

    void update(sf::Time dt);

    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode& node);

    sf::Vector2f getWorldPosition() const;
    sf::Transform getWorldTransform() const;

   private:
    // supporting
    virtual void updateCurrent(sf::Time dt);
    void updateChildren(sf::Time dt);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const;
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

   private:
    SceneNode* mParent;
    std::vector<Ptr> mChildren;
};

#endif  // SCENENODE_HPP
