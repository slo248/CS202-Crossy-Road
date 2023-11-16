#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include <set>
#include <utility>
#include <vector>

#include "Category.hpp"
#include "CommandQueue.hpp"

struct Command;

class SceneNode : public sf::Transformable,
                  public sf::Drawable,
                  private sf::NonCopyable {
   public:
    typedef std::unique_ptr<SceneNode> Ptr;
    typedef std::pair<SceneNode*, SceneNode*> Pair;

   public:
    // Constructor
    SceneNode(unsigned int category = Category::None);

    // Child Methods
    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode& node);

    // Update Method
    void update(sf::Time dt, CommandQueue& commands);

    // Position Methods
    sf::Vector2f getWorldPosition() const;
    sf::Transform getWorldTransform() const;

    // Command Methods
    void onCommand(const Command& command, sf::Time dt);
    virtual unsigned int getCategory() const;

    // Collision Methods
    void checkSceneCollision(
        SceneNode& sceneGraph, std::set<Pair>& collisionPairs
    );
    void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
    virtual sf::FloatRect getBoundingRect() const;

   private:
    // Update Methods
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
    void updateChildren(sf::Time dt, CommandQueue& commands);

    // Draw Methods
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const;
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states)
        const;

   private:
    unsigned int mCategory;
    SceneNode* mParent;
    std::vector<Ptr> mChildren;
};

bool collision(const SceneNode& lhs, const SceneNode& rhs);
float distance(const SceneNode& lhs, const SceneNode& rhs);

#endif  // SCENENODE_HPP
