#include "World.hpp"

#include "ResourceHolder.hpp"

World::World(
    TextureHolder& textures, FontHolder& fonts, sf::RenderWindow& window,
    Config::GameType gameType
)
    : mTextures(textures),
      mFonts(fonts),
      mWindow(window),
      mWorldView(window.getDefaultView()),
      mWorldBounds(0, 0, mWorldView.getSize().x, 2000),
      mPlayer(nullptr),
      mGameType(gameType) {
    buildScene();
}

void World::update(sf::Time dt) {
    mWorldView.setCenter(mPlayer->getWorldPosition());

    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    removeEntitiesOutsizeView();

    mSceneGraph.update(dt, mCommandQueue);
}

CommandQueue& World::getCommandQueue() { return mCommandQueue; }

void World::buildScene() {
    // soon
}

void World::removeEntitiesOutsizeView() {
    Command command;
    command.category = Category::Character | Category::Obstacle |
                       Category::Decoration | Category::Lane |
                       Category::TrafficLight;
    command.action = derivedAction<Entity>([this](Entity& e, sf::Time) {
        if (!getViewBounds().intersects(e.getBoundingRect())) e.remove();
    });

    mCommandQueue.push(command);
}

sf::FloatRect World::getViewBounds() const {
    return sf::FloatRect(
        mWorldView.getCenter() - mWorldView.getSize() / 2.f,
        mWorldView.getSize()
    );
}