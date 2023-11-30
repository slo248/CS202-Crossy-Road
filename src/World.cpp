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
      mScrollSpeed(0, -40) {
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
        SceneNode::Ptr layer(new SceneNode());
        mLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    Lane::Ptr btm = nullptr;
    int numRows;

    switch (mGameType) {
        case Config::GameLevel::L1:
            btm = createMultipleLanes(mTextures, numRows = 20);
            break;
        case Config::GameLevel::L2:
            btm = createMultipleLanes(mTextures, numRows = 40);
            break;
        case Config::GameLevel::L3:
            btm = createMultipleLanes(mTextures, numRows = 60);
            break;
        case Config::GameLevel::L4:
            btm = createMultipleLanes(mTextures, numRows = 80);
            break;
        case Config::GameLevel::L5:
            btm = createMultipleLanes(mTextures, numRows = 100);
            break;
        default:
            break;
    }

    btm->setPosition(
        0, mWorldBounds.height + DEFAULT_CELL_LENGTH * (numRows - 0.5)
    );
    mLayers[OnGround]->attachChild(std::move(btm));

    mWorldView.setCenter(
        mWorldBounds.width / 2, mWorldBounds.height - mWorldView.getSize().y / 2
    );
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
