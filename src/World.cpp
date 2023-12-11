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
      //   mWorldBounds(0, 0, mWorldView.getSize().x, 2000),
      mPlayer(nullptr),
      mGameType(gameType),
      mScrollSpeed(0, -40),
      mTopLane(nullptr) {
    buildScene();
}

void World::update(sf::Time dt) {
    buildBlocks();

    // if (mPlayer->getWorldPosition().y <= mWorldView.getCenter().y)
    //     mWorldView.move(
    //         0, mPlayer->getWorldPosition().y - mWorldView.getCenter().y
    //     );
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

    if (mGameType != Config::GameLevel::Endless) {
        mRemainBlocks = (static_cast<int>(mGameType) + 1) * 2 + 3;
    } else
        mRemainBlocks = -1;

    Lane::Ptr top1 = nullptr;
    Lane* bot1 = nullptr;

    createMultipleLanes(mTextures, 2 * NUM_LANE, top1, bot1, mGameType);
    top1->setPosition(0, DEFAULT_CELL_LENGTH / 2);
    mTopLane = top1.get();
    mLayers[Background]->attachChild(std::move(top1));

    Lane::Ptr top3 = nullptr;
    Lane* bot3 = nullptr;
    createMultipleLanes(mTextures, BUFFER_LANE, top3, bot3, true);
    bot1->attachChild(std::move(top3));

    Lane::Ptr top4 = nullptr;
    Lane* bot4 = nullptr;
    createMultipleLanes(mTextures, BUFFER_LANE, top4, bot4, true);
    bot3->attachChild(std::move(top4));

    Character::Ptr player(new Character(Character::Type::Archer, mTextures));
    mPlayer = player.get();
    mPlayer->setPosition(
        slotToPosition(DEFAULT_PLAYER_SLOT),
        DEFAULT_CELL_LENGTH * (2 * NUM_LANE + BUFFER_LANE) -
            DEFAULT_CELL_LENGTH / 2
    );
    mPlayer->setCurrentLane(bot3);
    mLayers[OnGround]->attachChild(std::move(player));

    mWorldView.setCenter(
        mWorldView.getSize().x / 2,
        2 * DEFAULT_CELL_LENGTH * (NUM_LANE + BUFFER_LANE) -
            mWorldView.getSize().y / 2
    );

    mWorldBounds = sf::FloatRect(
        0, -DEFAULT_CELL_LENGTH * 2, mWorldView.getSize().x,
        2 * DEFAULT_CELL_LENGTH * (NUM_LANE + BUFFER_LANE)
    );
}

void World::buildBlocks() {
    if (mRemainBlocks == -2) return;
    if (mRemainBlocks == 0) {
        Lane::Ptr top = nullptr;
        Lane* bot = nullptr;
        createMultipleLanes(mTextures, BUFFER_LANE * 2, top, bot, true);
        bot->attachChild(std::move(mLayers[OnGround]->detachChild(*mTopLane)));
        top->setPosition(
            0, DEFAULT_CELL_LENGTH / 2 - DEFAULT_CELL_LENGTH * BUFFER_LANE * 2
        );
        mTopLane = top.get();
        mLayers[OnGround]->attachChild(std::move(top));
        mRemainBlocks = -2;
        return;
    }
    if (mWorldView.getCenter().y + mWorldView.getSize().y / 2 >
        NUM_LANE * DEFAULT_CELL_LENGTH)
        return;
    if (mRemainBlocks > 0) mRemainBlocks--;

    Lane::Ptr top = nullptr;
    Lane* bot = nullptr;

    createMultipleLanes(mTextures, NUM_LANE, top, bot, mGameType);
    top->setPosition(0, DEFAULT_CELL_LENGTH / 2);

    bot->attachChild(std::move(mLayers[Background]->detachChild(*mTopLane)));
    mWorldView.move(0, DEFAULT_CELL_LENGTH * NUM_LANE);

    mTopLane = top.get();
    mLayers[Background]->attachChild(std::move(top));

    mPlayer->move(0, DEFAULT_CELL_LENGTH * NUM_LANE);
}

void World::removeEntitiesOutsizeView() {
    Command command;
    command.category = Category::Enemy | Category::Obstacle | Category::Lane |
                       Category::Decoration;
    command.action = derivedAction<SceneNode>([this](SceneNode& e, sf::Time) {
        if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
            e.destroy();
    });

    mCommandQueue.push(command);
}

sf::FloatRect World::getBattlefieldBounds() const {
    return sf::FloatRect(
        mWorldBounds.getPosition().x - DEFAULT_CELL_LENGTH,
        mWorldBounds.getPosition().y - DEFAULT_CELL_LENGTH,
        mWorldBounds.getSize().x + DEFAULT_CELL_LENGTH * 2,
        mWorldBounds.getSize().y + DEFAULT_CELL_LENGTH * 2
    );
}

bool World::hasAlivePlayer() const {
    sf::FloatRect bounds(
        mWorldView.getCenter() - mWorldView.getSize() / 2.f,
        mWorldView.getSize()
    );
    return !mPlayer->isMarkedForRemoval() &&
           bounds.contains(mPlayer->getWorldPosition());
}

bool World::hasPlayerReachedEnd() const {
    return !mWorldBounds.contains(mPlayer->getPosition());
}
