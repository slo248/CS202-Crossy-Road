#include "World.hpp"

#include <fstream>

#include "Lane.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

World::World(State::Context& context)
    : mTextures(*context.textures),
      mFonts(*context.fonts),
      mWindow(*context.window),
      mGameLevel(context.gameLevel),
      mWorldView((*context.window).getDefaultView()),
      mPlayerSkin(nullptr),
      mTopLane(nullptr),
      mContext(&context),
      // The sequence of initializer list is not the sequence of initialization
      // -> fucked up
      mTotalBlocks(gameLevelToBlocks(context.gameLevel)),
      mScrollSpeed(0, -20),
      mWorldBounds(sf::FloatRect(
          0, 0, mWorldView.getSize().x,
          2 * DEFAULT_CELL_LENGTH * (NUM_LANE + BUFFER_LANE)
      )) {
    if (mContext->isLoadedFromFile) {
        load();
    } else {
        mScores = 0;
        buildScene();
    }
    setDefaultScoreText();
}

void World::update(sf::Time dt) {
    buildBlocks();

    if (mPlayerSkin->getWorldPosition().y <= mWorldView.getCenter().y)
        mWorldView.move(
            0, mPlayerSkin->getWorldPosition().y - mWorldView.getCenter().y
        );
    mWorldView.move(mScrollSpeed * dt.asSeconds());

    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    removeEntitiesOutsizeView();

    mSceneGraph.removeWrecks();
    mSceneGraph.update(dt, mCommandQueue);

    updateBoard();
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mScoreText);
    mWindow.draw(mGameModeText);
}

CommandQueue& World::getCommandQueue() { return mCommandQueue; }

void World::buildScene() {
    // Build all layers
    buildLayers();

    // Remained blocks count
    if (mGameLevel != Config::GameLevel::Survival) {
        mRemainBlocks = mTotalBlocks - 2;
    } else {
        mRemainBlocks = -1;
    }

    // Build lanes
    Lane::Ptr top1 = nullptr;
    Lane* bottom1 = nullptr;

    // Normal lanes
    // 2 * NUM_LANE -> what a surprise, then mTotalBlocks should -2
    createMultipleLanes(
        mTextures, 2 * NUM_LANE, top1, bottom1, false,
        getLevelFactor(mGameLevel)
    );
    top1->setPosition(0, DEFAULT_HALF_CELL_LENGTH);
    mTopLane = top1.get();
    mLayers[Background]->attachChild(std::move(top1));

    // Buffer lanes
    Lane::Ptr top3 = nullptr;
    Lane* bottom3 = nullptr;
    createMultipleLanes(mTextures, BUFFER_LANE, top3, bottom3, true);
    Lane* initialLane = top3.get();
    bottom1->attachChild(std::move(top3));

    Lane::Ptr top4 = nullptr;
    Lane* bottom4 = nullptr;
    createMultipleLanes(mTextures, BUFFER_LANE, top4, bottom4, true);
    bottom3->attachChild(std::move(top4));

    // Player's initial position
    // locally created but still not be destroyed? ->problematic
    Character::Ptr playerSkin(new Character(
        static_cast<Character::Type>(
            Character::Type::Archer + mContext->playerSkinNumber
        ),
        mTextures
    ));
    mPlayerSkin = playerSkin.get();
    mPlayerSkin->setPosition(
        slotToPosition(DEFAULT_PLAYER_SLOT),
        DEFAULT_CELL_LENGTH * (2 * NUM_LANE) + DEFAULT_HALF_CELL_LENGTH
    );
    mPlayerPreRow = getCurrentRow(mPlayerSkin->getWorldPosition().y);
    mPlayerSkin->setCurrentLane(initialLane);
    mLayers[OnGround]->attachChild(std::move(playerSkin));

    // Set view
    mWorldView.setCenter(
        mWorldView.getSize().x / 2,
        2 * DEFAULT_CELL_LENGTH * (NUM_LANE + BUFFER_LANE) -
            mWorldView.getSize().y / 2
    );
}

void World::buildBlocks() {
    // Not allow to build blocks when player is in movement -> if not player
    // will be shifted
    if (mRemainBlocks == -2 || mPlayerSkin->isInMovement()) return;

    // Build end block
    if (mRemainBlocks == 0) {
        Lane::Ptr top = nullptr;
        Lane* bottom = nullptr;
        createMultipleLanes(mTextures, BUFFER_LANE * 2, top, bottom, true);
        bottom->attachChild(std::move(mLayers[Background]->detachChild(*mTopLane
        )));
        top->setPosition(0, DEFAULT_HALF_CELL_LENGTH);
        mTopLane = top.get();
        mLayers[Background]->attachChild(std::move(top));
        mRemainBlocks = -2;

        // Move view and player to maintain the same position (duplicate)
        mWorldView.move(0, DEFAULT_CELL_LENGTH * BUFFER_LANE * 2);
        mPlayerSkin->move(0, DEFAULT_CELL_LENGTH * BUFFER_LANE * 2);

        mPlayerPreRow = getCurrentRow(mPlayerSkin->getWorldPosition().y);

        std::cout << "Last buffer block!\n";
        return;
    }

    if (mWorldView.getCenter().y + mWorldView.getSize().y / 2 >
        NUM_LANE * DEFAULT_CELL_LENGTH) {
        return;
    }

    // Build as normal
    if (mRemainBlocks > 0) {
        --mRemainBlocks;
    }

    // Build block
    Lane::Ptr top = nullptr;
    Lane* bottom = nullptr;
    createMultipleLanes(
        mTextures, NUM_LANE, top, bottom, false, getLevelFactor(mGameLevel)
    );
    bottom->attachChild(std::move(mLayers[Background]->detachChild(*mTopLane)));
    top->setPosition(0, DEFAULT_HALF_CELL_LENGTH);
    mTopLane = top.get();
    mLayers[Background]->attachChild(std::move(top));

    // Move view and player to maintain the same position
    mWorldView.move(0, DEFAULT_CELL_LENGTH * NUM_LANE);
    mPlayerSkin->move(0, DEFAULT_CELL_LENGTH * NUM_LANE);

    // Setup player's pre row for scoring
    mPlayerPreRow = getCurrentRow(mPlayerSkin->getWorldPosition().y);

    std::cout << "Remaining blocks: " << mRemainBlocks << std::endl;
}

void World::buildLayers() {
    for (int i = 0; i < LayerCount; i++) {
        SceneNode::Ptr layer(std::make_unique<SceneNode>());
        mLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }
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
    mGameModeText.setFont(mFonts.get(Fonts::Main));
    mGameModeText.setCharacterSize(20);
    mGameModeText.setPosition(10, 10);
    mGameModeText.setOutlineThickness(5);
    mGameModeText.setOutlineColor(sf::Color::Black);
    mGameModeText.setString("Game Mode: " + gameModeToString(mGameLevel));

    mScoreText.setFont(mFonts.get(Fonts::Main));
    mScoreText.setCharacterSize(20);
    mScoreText.setPosition(10, 40);
    mScoreText.setOutlineThickness(5);
    mScoreText.setOutlineColor(sf::Color::Black);
}

void World::load() {
    // Build all layers
    buildLayers();

    std::ifstream in(savedGamePath(mGameLevel), std::ios::in);

    // problematic
    if (!in.good()) {
        std::cout << "Cannot open save file!\n";
        return;
    }

    int dummy;
    // Check if saved
    in >> dummy;

    // Load world data
    int category, type;
    in >> type >> mRemainBlocks >> mPlayerPreRow >> mScores;
    mGameLevel = static_cast<Config::GameLevel::Type>(type);

    // Load view
    float x, y;
    in >> x >> y;
    mWorldView.setCenter(x, y);

    // Load player data
    in >> category >> type;
    // problematic
    mContext->playerSkinNumber = type - Character::Type::Archer;
    std::cout << mContext->playerSkinNumber << '\n';
    auto player = std::make_unique<Character>(
        in, static_cast<Character::Type>(type), mTextures
    );
    mPlayerSkin = player.get();
    mLayers[OnGround]->attachChild(std::move(player));

    // Load lanes data
    in >> category >> type;
    auto top =
        std::make_unique<Lane>(in, static_cast<LaneType>(type), mTextures);
    mTopLane = top.get();
    top->setPosition(0, DEFAULT_HALF_CELL_LENGTH);
    mLayers[Background]->attachChild(std::move(top));
    in.close();

    Lane* current = mTopLane;
    int playerLaneNumber =
        (int)mPlayerSkin->getWorldPosition().y / DEFAULT_CELL_LENGTH;

    while (current) {
        int currentLaneNumber =
            (int)current->getWorldPosition().y / DEFAULT_CELL_LENGTH;
        if (currentLaneNumber == playerLaneNumber) {
            mPlayerSkin->setCurrentLane(current);
            break;
        }
        current = current->getChildLane();
    }

    // std::ofstream out(savedGamePath(mGameLevel));
    // out << "0\n";
    // out.close();

    std::cout << "Game loaded successfully!\n";
}

void World::updateBoard() {
    int curRow = getCurrentRow(mPlayerSkin->getWorldPosition().y);

    if (mPlayerPreRow > curRow) {
        ++mScores;
        std::cout << "Score: " << mScores << std::endl;
        mPlayerPreRow = curRow;
    }

    if (mGameLevel == Config::GameLevel::Survival) {
        mScoreText.setString("Score: " + std::to_string(mScores));
    } else {
        int percentage = (mScores * 100) / (mTotalBlocks * NUM_LANE);
        mScoreText.setString("Progress: " + std::to_string(percentage) + '%');
    }
}

void World::save() const {
    std::ofstream out(savedGamePath(mGameLevel), std::ios::out);

    if (!out.good()) {
        std::cout << "Cannot open save file!\n";
        return;
    }

    // Mark as saved
    out << "1\n";

    // Save world data
    out << mGameLevel << ' ' << mRemainBlocks << ' ' << mPlayerPreRow << ' '
        << mScores << '\n';

    // Save view center
    out << mWorldView.getCenter().x << ' ' << mWorldView.getCenter().y << '\n';

    // Save player data
    mPlayerSkin->save(out);

    // Save lanes data
    mLayers[Background]->save(out);

    std::cout << "Game saved successfully!\n";
    out.close();
}

int World::getScore() const { return mScores; }

Config::GameLevel::Type World::getGameType() const { return mGameLevel; }

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

    return !mPlayerSkin->isMarkedForRemoval() &&
           bounds.contains(mPlayerSkin->getWorldPosition());
}

bool World::hasPlayerReachedEnd() const {
    return mGameLevel != Config::GameLevel::Survival && mRemainBlocks == -2 &&
           getCurrentRow(mPlayerSkin->getWorldPosition().y) ==
               2 * BUFFER_LANE - 1;
}
