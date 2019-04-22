#include "level.hpp"

Level::Level()
{
    
}

void Level::init()
{
    state = State::playing;

    tileSize = 30;
}

void Level::loadFromFile( LevelListElement *levelListElement )
{
    std::string file = levelListElement->filePath;
    std::ifstream levelFile( file );

    if( levelFile.fail() )
    {
        // TODO
        // Handle level load fail
    }
    else
    {
        // Copy the pointer
        this->levelListElement = levelListElement;

        // Get all lines from level file
        std::vector<std::string> lines;
        std::string line = "";
        std::getline( levelFile, line ); // The first line contains metadata, so we don't save it
        while( std::getline( levelFile, line ) )
        {
            lines.push_back( line );
        }

        // Load tiles into the vecor array
        for( int i = 0; i < lines.size(); ++i )
        {
            std::vector<Tile*> tileLine;
            for( int j = 0; j < lines[i].length(); ++j )
            {
                // Only push valid ASCII characters
                if( lines[i][j] > 31 )
                    tileLine.push_back( charToTile( lines[i][j] ) );
            }
            tiles.push_back( tileLine );
        }
    }

    // Initialize ball starting position
    initBall();

    // Initialize floor count
    floorTileCount = countFloorTiles();
    paintedTiles = 0;
    steps = 0;

    levelFile.close();
}

void Level::unload()
{
    state = State::playing;

    tiles.clear();
    levelTime.stop();
    floorTileCount = 0;
    paintedTiles = 0;

    tileSize = 0;

    ball.reset();
}

void Level::update()
{
    if( state == State::playing )
    {
        bool newStep = true;
        if( !ball.handleInput() ) newStep = false;

        ball.move();

        if( ball.state != Ball::State::stationary )
            paintTile();

        if( ballHittingWall() )
        {
            newStep = false;
            ball.moveBack();
            ball.setWorldPos( getBallTilePosition() );
            ball.stop();
        }

        if( newStep )
            steps++;

        if( checkWinCondition() )
        {
            setStarRating();
            state = State::finished;
        }
    }
}

void Level::draw()
{
    int levelWidth = tiles[ tiles.size() / 2 ].size() * tileSize;
    int levelHeight = tiles.size() * tileSize;

    int paddingLeft = ( SCREEN_WIDTH - levelWidth ) / 2;

    int paddingTop = 0;
    if( levelHeight < ( SCREEN_WIDTH / 2 ) )
        paddingTop = ( SCREEN_HEIGHT - levelHeight ) / 2;
    else
        paddingTop = SCREEN_HEIGHT * 0.1;

    // Draw level tiles
    for( int i = 0; i < tiles.size(); ++i )
    {
        for( int j = 0; j < tiles[ i ].size(); ++j )
        {
            Rect tileRect = Rect( 
                paddingLeft + ( j * tileSize ), 
                paddingTop + ( i * tileSize ), 
                tileSize, 
                tileSize 
            );
            tiles[i][j]->draw( tileRect );
        }
    }

    // Draw ball
    ball.draw();

    // Draw level name
    Gui::drawTextf_position( Gui::Position::centered, SCREEN_WIDTH / 2, 40, 40, "%s", levelListElement->name.c_str() );

    // Draw step count
    if( steps <= levelListElement->stepsForThreeStars )
    {
        Gui::drawTextf_color_position( Gui::Position::alignTop, 10, 10, 20, RGBA8( 220, 119, 47, 255 ), "Steps: %d/%d", steps, levelListElement->stepsForThreeStars );
        Texture::drawTexture( Texture::Sprite::doorStar1, Vec2( 100, 0 ) );
        Texture::drawTexture( Texture::Sprite::doorStar2, Vec2( 100, 0 ) );
        Texture::drawTexture( Texture::Sprite::doorStar3, Vec2( 100, 0 ) );
    }  
    else if( steps <= levelListElement->stepsForTwoStars )
    {
        Gui::drawTextf_color_position( Gui::Position::alignTop, 10, 10, 20, RGBA8( 220, 119, 47, 255 ), "Steps: %d/%d", steps, levelListElement->stepsForTwoStars );
        Texture::drawTexture( Texture::Sprite::doorStar1, Vec2( 100, 0 ) );
        Texture::drawTexture( Texture::Sprite::doorStar2, Vec2( 100, 0 ) );
    }    
    else
    {
        Gui::drawTextf_color_position( Gui::Position::alignTop, 10, 10, 20, RGBA8( 220, 119, 47, 255 ), "Steps: %d", steps );
        Texture::drawTexture( Texture::Sprite::doorStar1, Vec2( 100, 0 ) );
        
    }
        
    // TODO draw the stars next to the counter!
}

bool Level::complete()
{
    return state == State::finished;
}

Vec2 Level::getWorldPosFromTilePos( Vec2 tilePos )
{
    int levelWidth = tiles[ tiles.size() / 2 ].size() * tileSize;
    int levelHeight = tiles.size() * tileSize;
    int paddingLeft = ( SCREEN_WIDTH - levelWidth ) / 2;

    int paddingTop = 0;
    if( levelHeight < ( SCREEN_WIDTH / 2 ) )
        paddingTop = ( SCREEN_HEIGHT - levelHeight ) / 2;
    else
        paddingTop = SCREEN_HEIGHT * 0.1;

    Vec2 worldPos = Vec2( paddingLeft + ( tilePos.x * tileSize ) + ( tileSize / 2 ), paddingTop + ( tilePos.y * tileSize ) + ( tileSize / 2 ) );
    return worldPos;
}

Vec2 Level::getBallTile()
{
    Vec2 ballTile = Vec2( 0, 0 );

    // Find the tile that is the nearest to the ball
    for( int i = 0; i < tiles.size(); ++i )
    {
        for( int j = 0; j < tiles[ i ].size(); ++j )
        {
            // Check what tile the ball origin is on
            if( ball.getRect().x + ( ball.getRect().w / 2 ) > getWorldPosFromTilePos( Vec2( j, i ) ).x && 
                ball.getRect().y + ( ball.getRect().h / 2 ) > getWorldPosFromTilePos( Vec2( j, i ) ).y && 
                ball.getRect().x + ( ball.getRect().w / 2 ) < getWorldPosFromTilePos( Vec2( j, i ) ).x + ball.getRect().w && 
                ball.getRect().y + ( ball.getRect().h / 2 ) < getWorldPosFromTilePos( Vec2( j, i ) ).y + ball.getRect().h
            )
            {
                return Vec2( j, i );
            }
        }
    }

    return ballTile;
}

Vec2 Level::getBallTilePosition()
{
    return getWorldPosFromTilePos( getBallTile() );
}

void Level::initBall()
{
    int startTileCounter = 0;

    // Find the spawn tile
    for( int i = 0; i < tiles.size(); ++i )
    {
        for( int j = 0; j < tiles[ i ].size(); ++j )
        {
            if( dynamic_cast<StartTile*>( tiles[i][j] ) )
            {
                ball.setWorldPos( getWorldPosFromTilePos( Vec2( j, i ) ) );
                startTileCounter++;
            }
        }
    }

    if( startTileCounter == 0 )
    {
        // TODO Handle no starting tile found
    }
    if( startTileCounter > 1 )
    {
        // TODO Handle more then one starting tile found
    }
}

bool Level::checkCollision( Rect a, Rect b )
{
    int leftA = a.x; 
    int rightA = a.x + a.w; 
    int topA = a.y; 
    int bottomA = a.y + a.h;

    int leftB = b.x; 
    int rightB = b.x + b.w; 
    int topB = b.y; 
    int bottomB = b.y + b.h;

    if( bottomA <= topB )
        return false;
    if( topA >= bottomB )
        return false;
    if( rightA <= leftB )
        return false; 
    if( leftA >= rightB )
        return false;

    return true;
}

bool Level::ballHittingWall()
{
    for( int i = 0; i < tiles.size(); ++i )
    {
        for( int j = 0; j < tiles[ i ].size(); ++j )
        {
            if( dynamic_cast<WallTile*>( tiles[i][j] ) )
            {
                if( checkCollision( ball.getRect(), getWorldPosFromTilePos( Vec2( j, i ) ).toRect( tileSize, tileSize ) ) )
                    return true;
            }
        }
    }

    return false;
}

void Level::paintTile()
{
    Tile* ballTile = tiles[ getBallTile().y ][ getBallTile().x ];

    if( dynamic_cast<FloorTile*>( ballTile ) )
    {
        if( ballTile->paintable() )
        {
            paintedTiles++;
            ballTile->paint();
        }
    }
    else
    {
        // TODO
        // Why isn't the player on a floor tile? Throw some error maybe
    }
}

int Level::countFloorTiles()
{
    int floorCount = 0;

    for( int i = 0; i < tiles.size(); ++i )
    {
        for( int j = 0; j < tiles[ i ].size(); ++j )
        {
            if( dynamic_cast<FloorTile*>( tiles[i][j] ) )
            {
                floorCount++;
            }
        }
    }

    return floorCount;
}

bool Level::checkWinCondition()
{
    return ( paintedTiles == floorTileCount );
}

int Level::getStarRating()
{
    if( steps <= levelListElement->stepsForThreeStars )
        return 3;
    else if( steps <= levelListElement->stepsForTwoStars )
        return 2;
    else
        return 1;
}

void Level::setStarRating()
{
    if( getStarRating() > levelListElement->stars )
        levelListElement->stars = getStarRating();
}


Tile::Tile() { }

void Tile::paint() { }

bool Tile::paintable()
{
    return false;
}

void Tile::draw( Rect rect )
{
    vita2d_draw_rectangle( rect.x, rect.y, rect.w, rect.h, RGBA8( 255, 0, 0, 255) );
}

Tile* Level::charToTile( char c )
{
    switch( c )
    {
        case 'w':
        case '#':
            return new WallTile();

        case 'f':
        case '.':
            return new FloorTile();
            
        case 's':
            return new StartTile();

        default:
            return new Tile();
    }
}

void FloorTile::draw( Rect rect )
{
    if( state == State::blank )
    {
        Texture::drawTexture( Texture::Sprite::floorBlank, Vec2( rect.x, rect.y ) );
    }
        
    else if( state == State::painted )
    {
        Texture::drawTexture( Texture::Sprite::floorPainted, Vec2( rect.x, rect.y ) );
    }
}

void FloorTile::paint()
{
    state = State::painted;
}

bool FloorTile::paintable()
{
    if( state == State::blank )
        return true;
    else
        return false;
}

void WallTile::draw( Rect rect )
{
    Texture::drawTexture( Texture::Sprite::wall, Vec2( rect.x, rect.y ) );
}


LevelListElement::LevelListElement( std::string filePath )
{
    unlocked = false;
    completed = false;
    this->filePath = filePath;
    name = "test";

    stepsForTwoStars = 0;
    stepsForThreeStars = 0;

    stars = 0;
}

void LevelListElement::drawLevelMenuElement( Vec2 pos, bool selected )
{
    int itemWidth = vita2d_texture_get_width( Texture::getTexture( Texture::Sprite::doorOpened ) );
    int itemHeight = vita2d_texture_get_height( Texture::getTexture( Texture::Sprite::doorOpened ) );

    int indexSize = 35;

    if( selected && unlocked )
    {
        Texture::drawTexture( Texture::Sprite::doorOpened, Vec2( pos.x, pos.y ) );
    }
    else if( unlocked )
    {
        Texture::drawTexture( Texture::Sprite::doorClosed, Vec2( pos.x, pos.y ) );
        Gui::drawTextf_color_position( Gui::Position::centered, pos.x + ( itemWidth / 2 ), pos.y + ( itemHeight / 2 ) - 20, indexSize, RGBA8( 65, 11, 25, 255 ), "%i", index );
    }
    else if( selected )
    {
        Texture::drawTexture( Texture::Sprite::doorLockedOutline, Vec2( pos.x, pos.y ) );
        Texture::drawTexture( Texture::Sprite::doorClosed, Vec2( pos.x, pos.y ) );
        Gui::drawTextf_color_position( Gui::Position::centered, pos.x + ( itemWidth / 2 ), pos.y + ( itemHeight / 2 ) - 20, indexSize, RGBA8( 65, 11, 25, 255 ), "%i", index );
        Texture::drawTexture( Texture::Sprite::doorLocked, Vec2( pos.x, pos.y ) );
    }
    else
    {
        Texture::drawTexture( Texture::Sprite::doorClosed, Vec2( pos.x, pos.y ) ); 
        Gui::drawTextf_color_position( Gui::Position::centered, pos.x + ( itemWidth / 2 ), pos.y + ( itemHeight / 2 ) - 20, indexSize, RGBA8( 65, 11, 25, 255 ), "%i", index );
        Texture::drawTexture( Texture::Sprite::doorLocked, Vec2( pos.x, pos.y ) );
    }
    
    /* DEBUG turned off for now
    if( stars > 0 )
        Texture::drawTexture( Texture::Sprite::doorStar1, Vec2( pos.x, pos.y ) );
    if( stars > 1 )
        Texture::drawTexture( Texture::Sprite::doorStar2, Vec2( pos.x, pos.y ) );
    if( stars > 2 )
        Texture::drawTexture( Texture::Sprite::doorStar3, Vec2( pos.x, pos.y ) );
    */
    
}


LevelList::LevelList()
{
    currentLevel = 1;
}

void LevelList::add( std::string filePath )
{
    levels.push_back( LevelListElement( "app0:levels/" + filePath ) );

    // Load level file meta data
    std::ifstream levelFile( "app0:levels/" + filePath );
    if( levelFile.fail() )
    {
        // TODO
        // Handle level load fail
    }
    else
    {
        std::string line = "";
        std::getline( levelFile, line );

        int end = line.find_first_of( ">" );
        levels[ levels.size() - 1 ].index = std::stoi( line.substr( 1, end - 1 ) );
        line.erase( 0, end + 1 );

        end = line.find_first_of( ">" );
        levels[ levels.size() - 1 ].name = line.substr( 1, end - 1 );
        line.erase( 0, end + 1 );

        end = line.find_first_of( ">" );
        levels[ levels.size() - 1 ].stepsForTwoStars = std::stoi( line.substr( 1, end - 1 ) );
        line.erase( 0, end + 1 );

        end = line.find_first_of( ">" );
        levels[ levels.size() - 1 ].stepsForThreeStars = std::stoi( line.substr( 1, end - 1 ) );
        line.erase( 0, end + 1 );
    }
    levelFile.close();
}

std::string LevelList::getLevelPath( int index )
{
    return levels[ index ].filePath;
}

bool LevelList::getCompletion( int index )
{
    return levels[ index ].completed;
}

int LevelList::getCurrentLevel()
{
    return currentLevel;
}

void LevelList::setCurrentLevel( int index )
{
    currentLevel = index;
}

int LevelList::lastUnlockedLevel()
{
    int lastUnlocked = 0;
    for( int i = 0; i < levels.size(); ++i )
        if( accessElement( i )->unlocked )
            lastUnlocked = i;

    return lastUnlocked + 1;
}

void LevelList::compleateCurrentLevel()
{
    // The level 1 is levels[ 0 ], so we have to access the vector with a -1
    levels[ currentLevel - 1 ].completed = true;

    // Unlock the next level
    if( currentLevel < levels.size() )
        levels[ currentLevel ].unlocked = true;
}

int LevelList::getNrOfLevels()
{
    return levels.size();
}

void LevelList::nextLevel()
{
    if( currentLevel < levels.size() )
        currentLevel++;
}

LevelListElement * LevelList::accessElement( int index )
{
    LevelListElement *level = & levels[ index ];
    return level;
}

void LevelList::saveProgress()
{
    std::ofstream saveData;
    sceIoMkdir( "ux0:/data/Pingo", 0777 );
    saveData.open( "ux0:/data/Pingo/saveData.txt" );

    saveData << currentLevel << "\n";

    for( int i = 0; i < levels.size(); ++i )
    {
        saveData << accessElement( i )->index << "\t"  << accessElement( i )->unlocked << "\t" << accessElement( i )->completed << "\t" << accessElement( i )->stars << "\n";
    }

    saveData.close();
}

void LevelList::loadProgress()
{
    std::ifstream saveData;
    saveData.open( "ux0:/data/Pingo/saveData.txt" );

    saveData >> currentLevel;

    int loadIndex = 0;
    for( int i = 0; i < levels.size(); ++i )
    {
        saveData >> loadIndex;
        saveData >> accessElement( i )->unlocked;
        saveData >> accessElement( i )->completed;
        saveData >> accessElement( i )->stars;
    }

    saveData.close();
}
