#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <fstream>
#include <memory>
#include <set>
#include <utility>
#include <vector>

#include "Category.hpp"
#include "CommandQueue.hpp"
#include "ResourceIdentifiers.hpp"

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
    virtual void attachChild(SceneNode::Ptr child);
    virtual Ptr detachChild(const SceneNode& node);

    // Parent Method
    SceneNode* getParent();

    // Update Method
    void update(sf::Time dt, CommandQueue& commands);

    // Save Method
    void save(std::ostream& out) const;

    // Load Method
    // void load(std::istream& in, const TextureHolder& textures);

    // Position Methods
    sf::Vector2f getWorldPosition() const;
    sf::Transform getWorldTransform() const;

    // Command Methods
    void onCommand(const Command& command, sf::Time dt);
    virtual unsigned int getCategory() const;

    // Collision Methods
    virtual sf::FloatRect getBoundingRect() const;
    virtual sf::FloatRect getLocalBounds() const;
    virtual bool isMarkedForRemoval() const;
    void destroy();
    void removeWrecks();

   private:
    // Update Methods
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
    virtual void updateChildren(sf::Time dt, CommandQueue& commands);

    // Draw Methods
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states)
        const;
    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawBoundingRect(
        sf::RenderTarget& target, sf::RenderStates states
    ) const;

    // Save methods
    virtual void saveCurrent(std::ostream& out) const;
    virtual void saveChildren(std::ostream& out) const;

    // Load methods
    // There should be two methods right below for better encapsulation
    // virtual void loadIndependentInformation(std::istream& in);
    // virtual void loadDependentInformation(
    //     std::istream& in, const TextureHolder& textures
    // );
    virtual void loadCurrent(std::istream& in);
    virtual void loadChildren(std::istream& in, const TextureHolder& textures);

   protected:
    std::vector<Ptr> mChildren;

   private:
    unsigned int mCategory;
    SceneNode* mParent;
    bool mIsMarkedForRemoval;
};

bool collision(
    const sf::FloatRect& lhs, const sf::FloatRect& rhs, float reduce = 0
);
float distance(const SceneNode& lhs, const SceneNode& rhs);

#endif  // SCENENODE_HPP
