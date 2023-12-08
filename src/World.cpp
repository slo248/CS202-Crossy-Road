#include "World.hpp"

#include "Lane.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

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
      mScrollSpeed(0, -20),
      mTopLane(nullptr) {
    buildScene();
}

void World::update(sf::Time dt) {
    buildBlocks();
    mWorldView.move(mScrollSpeed * dt.asSeconds());

    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    removeEntitiesOutsizeView();

    mSceneGraph.removeWrecks();
    mSceneGraph.update(dt, mCommandQueue);

    // std::cout << "\n";
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

    // Lane::Ptr top1 = nullptr, top2 = nullptr;
    // Lane *bot1 = nullptr, *bot2 = nullptr;

    if (mGameType != Config::GameLevel::Endless) {
        mRemainBlocks = (static_cast<int>(mGameType) + 1) * 2 + 3;
    } else
        mRemainBlocks = -1;

    // createMultipleLanes(mTextures, NUM_LANE, top1, bot1, mGameType);
    // createMultipleLanes(mTextures, NUM_LANE, top2, bot2, mGameType);
    // top2->setPosition(0, DEFAULT_CELL_LENGTH);
    // bot1->attachChild(std::move(top2));

    // top1->setPosition(0, DEFAULT_CELL_LENGTH / 2);
    // mLayers[OnGround]->attachChild(std::move(top1));
}

void World::buildBlocks() {
    if (mRemainBlocks == 0) return;
    if (mTopLane && mWorldView.getCenter().y + mWorldView.getSize().y / 2 >
                        NUM_LANE * DEFAULT_CELL_LENGTH)
        return;
    if (mRemainBlocks > 0) mRemainBlocks--;

    Lane::Ptr top1 = nullptr;
    Lane* bot1 = nullptr;

    createMultipleLanes(mTextures, NUM_LANE, top1, bot1, mGameType);
    top1->setPosition(0, DEFAULT_CELL_LENGTH / 2);

    if (mTopLane == nullptr) {
        Lane::Ptr top2 = nullptr;
        Lane* bot2 = nullptr;
        createMultipleLanes(mTextures, NUM_LANE, top2, bot2, mGameType);
        top2->setPosition(0, DEFAULT_CELL_LENGTH);
        bot1->attachChild(std::move(top2));
        mWorldView.setCenter(
            mWorldView.getSize().x / 2,
            DEFAULT_CELL_LENGTH * 2 * NUM_LANE - mWorldView.getSize().y / 2
        );
    } else {
        mTopLane->setPosition(0, DEFAULT_CELL_LENGTH);
        bot1->attachChild(std::move(mLayers[OnGround]->detachChild(*mTopLane)));
        mWorldView.move(0, DEFAULT_CELL_LENGTH * NUM_LANE);
    }

    mTopLane = top1.get();
    mLayers[OnGround]->attachChild(std::move(top1));
}

void World::removeEntitiesOutsizeView() {
    Command command;
    command.category = Category::Enemy | Category::Obstacle | Category::Lane |
                       Category::Decoration;
    command.action = derivedAction<SceneNode>([this](SceneNode& e, sf::Time) {
        if (!getViewBounds().intersects(e.getBoundingRect())) e.remove();
    });

    mCommandQueue.push(command);
}

sf::FloatRect World::getViewBounds() const {
    return sf::FloatRect(
        sf::Vector2f(-DEFAULT_CELL_LENGTH, -DEFAULT_CELL_LENGTH),
        sf::Vector2f(
            DEFAULT_CELL_LENGTH * (DEFAULT_CELLS_PER_LANE + 2),
            DEFAULT_CELL_LENGTH * (2 * NUM_LANE + 2)
        )
    );
}
