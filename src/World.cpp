#include "World.hpp"

#include "Lane.hpp"
#include "ResourceHolder.hpp"

World::World(
    TextureHolder& textures, FontHolder& fonts, sf::RenderWindow& window,
    Config::GameLevel::Type gameType
)
    : mTextures(textures),
      mFonts(fonts),
      mWindow(window),
      mWorldView(window.getDefaultView()),
      mWorldBounds(0, 0, mWorldView.getSize().x, 2000),
      mPlayer(nullptr),
      mGameType(gameType),
      mScrollSpeed(0, -20) {
    buildScene();
}

void World::update(sf::Time dt) {
    mWorldView.move(mScrollSpeed * dt.asSeconds());

    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    removeEntitiesOutsizeView();

    mSceneGraph.update(dt, mCommandQueue);
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue() { return mCommandQueue; }

void World::buildScene() {
    for (int i = 0; i < LayerCount; i++) {
        // used to be new SceneNode()
        SceneNode::Ptr layer(std::make_unique<SceneNode>());
        mLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    Lane::Ptr topLane = nullptr;
    int numRows;

    switch (mGameType) {
        case Config::GameLevel::L1:
            topLane = createMultipleLanes(mTextures, numRows = 50);
            break;
        case Config::GameLevel::L2:
            topLane = createMultipleLanes(mTextures, numRows = 70);
            break;
        case Config::GameLevel::L3:
            topLane = createMultipleLanes(mTextures, numRows = 100);
            break;
        case Config::GameLevel::L4:
            topLane = createMultipleLanes(mTextures, numRows = 150);
            break;
        case Config::GameLevel::L5:
            topLane = createMultipleLanes(mTextures, numRows = 200);
            break;
        default:
            break;
    }

    topLane->setPosition(0, DEFAULT_CELL_LENGTH / 2);
    mLayers[OnGround]->attachChild(std::move(topLane));

    mWorldView.setCenter(
        mWorldView.getSize().x / 2,
        DEFAULT_CELL_LENGTH * numRows - mWorldView.getSize().y / 2
    );
}

void World::removeEntitiesOutsizeView() {
    Command command;
    command.category = Category::Enemy | Category::Obstacle | Category::Lane;
    command.action = derivedAction<SceneNode>([this](SceneNode& e, sf::Time) {
        if (!getViewBounds().intersects(e.getBoundingRect())) e.remove();
    });

    mCommandQueue.push(command);
}

sf::FloatRect World::getViewBounds() const {
    return sf::FloatRect(
        mWorldView.getCenter() - mWorldView.getSize() / 2.f -
            sf::Vector2f(100, 100),
        mWorldView.getSize() + sf::Vector2f(200, 200)
    );
}
