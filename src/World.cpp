#include "World.hpp"

#include "Lane.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

World::World(
    TextureHolder& textures, FontHolder& fonts, sf::RenderWindow& window,
    Config::GameLevel::Type gameType, bool isLoadedFromFile
)
    : mTextures(textures),
      mFonts(fonts),
      mWindow(window),
      mGameType(gameType),
      mWorldView(window.getDefaultView()),
      //   mWorldBounds(0, 0, mWorldView.getSize().x, 2000),
      mPlayer(nullptr),
      mTopLane(nullptr),
      mScrollSpeed(0, /*-40 * getLevelFactor(gameType)*/ 0) {
    mWorldBounds = sf::FloatRect(
        0, 0, mWorldView.getSize().x,
        2 * DEFAULT_CELL_LENGTH * (NUM_LANE + BUFFER_LANE)
    );
    if (isLoadedFromFile) {
        loadGame();
    } else {
        mScores = 0;
        buildScene();
    }
    setDefaultScoreText();
}

void World::update(sf::Time dt) {
    buildBlocks();

    if (mPlayer->getWorldPosition().y <= mWorldView.getCenter().y)
        mWorldView.move(
            0, mPlayer->getWorldPosition().y - mWorldView.getCenter().y
        );
    mWorldView.move(mScrollSpeed * dt.asSeconds());

    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    removeEntitiesOutsizeView();

    mSceneGraph.removeWrecks();
    mSceneGraph.update(dt, mCommandQueue);

    int curRow = getCurrentRow(mPlayer->getWorldPosition().y);

    if (mPlayerPreRow > curRow) {
        mScores++;
        mPlayerPreRow = curRow;
    }

    mScoreText.setString("Scores: " + std::to_string(mScores));

    // std::cout << "\n";
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mScoreText);
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
        mRemainBlocks = (static_cast<int>(mGameType) + 1) * 3;
    } else
        mRemainBlocks = -1;

    Lane::Ptr top1 = nullptr;
    Lane* bot1 = nullptr;

    createMultipleLanes(
        mTextures, 2 * NUM_LANE, top1, bot1, false, getLevelFactor(mGameType)
    );
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
    mPlayerPreRow = getCurrentRow(mPlayer->getWorldPosition().y);
    mPlayer->setCurrentLane(bot3);
    mLayers[OnGround]->attachChild(std::move(player));

    mWorldView.setCenter(
        mWorldView.getSize().x / 2,
        2 * DEFAULT_CELL_LENGTH * (NUM_LANE + BUFFER_LANE) -
            mWorldView.getSize().y / 2
    );
}

void World::buildBlocks() {
    if (mRemainBlocks == -2 || mPlayer->isInMovement()) return;
    if (mRemainBlocks == 0) {
        Lane::Ptr top = nullptr;
        Lane* bot = nullptr;
        createMultipleLanes(mTextures, BUFFER_LANE * 2, top, bot, true);
        bot->attachChild(std::move(mLayers[Background]->detachChild(*mTopLane))
        );
        top->setPosition(0, DEFAULT_CELL_LENGTH / 2);
        mTopLane = top.get();
        mLayers[Background]->attachChild(std::move(top));
        mRemainBlocks = -2;

        mWorldView.move(0, DEFAULT_CELL_LENGTH * BUFFER_LANE * 2);
        mPlayer->move(0, DEFAULT_CELL_LENGTH * BUFFER_LANE * 2);

        return;
    }
    if (mWorldView.getCenter().y + mWorldView.getSize().y / 2 >
        NUM_LANE * DEFAULT_CELL_LENGTH)
        return;
    if (mRemainBlocks > 0) mRemainBlocks--;

    Lane::Ptr top = nullptr;
    Lane* bot = nullptr;

    createMultipleLanes(
        mTextures, NUM_LANE, top, bot, false, getLevelFactor(mGameType)
    );
    top->setPosition(0, DEFAULT_CELL_LENGTH / 2);

    bot->attachChild(std::move(mLayers[Background]->detachChild(*mTopLane)));
    mWorldView.move(0, DEFAULT_CELL_LENGTH * NUM_LANE);
    mPlayer->move(0, DEFAULT_CELL_LENGTH * NUM_LANE);

    mTopLane = top.get();
    mLayers[Background]->attachChild(std::move(top));

    std::cout << "Remaining blocks: " << mRemainBlocks << std::endl;
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

void World::setDefaultScoreText() {
    mScoreText.setFont(mFonts.get(Fonts::Main));
    mScoreText.setCharacterSize(20);
    mScoreText.setPosition(10, 10);
    mScoreText.setOutlineThickness(5);
    mScoreText.setOutlineColor(sf::Color::Black);
}

std::string loadPath(Config::GameLevel::Type type) {
    switch (type) {
        case Config::GameLevel::Endless: {
            return "data/endless.txt";
            break;
        }

        case Config::GameLevel::L1: {
            return "data/level1.txt";
        }

        case Config::GameLevel::L2: {
            return "data/level2.txt";
        }

        case Config::GameLevel::L3: {
            return "data/level3.txt";
        }

        case Config::GameLevel::L4: {
            return "data/level4.txt";
        }

        case Config::GameLevel::L5: {
            return "data/level5.txt";
        }

        default: {
            return "";
        }
    }
}

void World::loadGame() {
    for (int i = 0; i < LayerCount; i++) {
        // used to be new SceneNode()
        SceneNode::Ptr layer(std::make_unique<SceneNode>());
        mLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    std::ifstream in;
    in.open(loadPath(mGameType), std::ios::in);

    // problematic
    if (!in.good()) {
        std::cout << "Cannot open save file!\n";
        return;
    }

    // Load world data
    int category, type;
    in >> type >> mRemainBlocks >> mPlayerPreRow >> mScores;
    mGameType = static_cast<Config::GameLevel::Type>(type);

    // Load view
    float x, y;
    in >> x >> y;
    mWorldView.setCenter(x, y);

    // Load player data
    in >> category >> type;
    auto player = std::make_unique<Character>(
        in, static_cast<Character::Type>(type), mTextures
    );
    mPlayer = player.get();
    mLayers[OnGround]->attachChild(std::move(player));

    // Load lanes data
    in >> category >> type;
    auto top =
        std::make_unique<Lane>(in, static_cast<LaneType>(type), mTextures);
    mTopLane = top.get();
    top->setPosition(0, DEFAULT_CELL_LENGTH / 2);
    mLayers[Background]->attachChild(std::move(top));
    in.close();

    Lane* current = mTopLane;
    while (current) {
        if (current->getWorldPosition().y == mPlayer->getWorldPosition().y) {
            mPlayer->setCurrentLane(current);
            break;
        }
        current = current->getChildLane();
    }

    std::cout << "Game loaded successfully!\n";
}

void World::saveCurrentGame() const {
    std::ofstream out;
    out.open(loadPath(mGameType), std::ios::out);

    if (!out.good()) {
        std::cout << "Cannot open save file!\n";
        return;
    }

    // Save world data
    out << mGameType << ' ' << mRemainBlocks << ' ' << mPlayerPreRow << ' '
        << mScores << '\n';

    // Save view center
    out << mWorldView.getCenter().x << ' ' << mWorldView.getCenter().y << '\n';

    // Save player and lanes data
    mLayers[OnGround]->save(out);  // OnGround only has player at the moment
    mLayers[Background]->save(out);

    std::cout << "Game saved successfully!\n";
    out.close();
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
    return mGameType != Config::GameLevel::Endless && mRemainBlocks == -2 &&
           getCurrentRow(mPlayer->getWorldPosition().y) == BUFFER_LANE - 1;
}
