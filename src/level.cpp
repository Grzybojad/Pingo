#include "level.hpp"

Level::Level()
{
    
}

void Level::init()
{
    state = State::playing;

    levelName = "";

    tileSize = 30;
}

void Level::loadFromFile( std::string file )
{
    std::ifstream levelFile( file );

    if( levelFile.fail() )
    {
        // TODO
        // Handle level load fail
    }
    else
    {
        // Get level name
        readLevelName( file );

        // Get all lines from level file
        std::vector<std::string> lines;
        std::string line = "";
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
        ball.handleInput();
        ball.move();

        if( ball.state != Ball::State::stationary )
            paintTile();

        if( ballHittingWall() )
        {
            ball.moveBack();
            ball.setWorldPos( getBallTilePosition() );
            ball.stop();
        }

        if( checkWinCondition() )
            state = State::finished;
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
    Gui::drawTextf_position( Gui::Position::centered, SCREEN_WIDTH / 2, 40, 40, "Level %s", levelName.c_str() );
}

bool Level::complete()
{
    return state == State::finished;
}

void Level::readLevelName( std::string fileName )
{
    std::string start = "levels/level";
    std::string end = ".txt";
    int startPos = fileName.find( start );
    int endPos = fileName.find( end );

    levelName = fileName.substr( startPos + start.length(), endPos - ( startPos + start.length() ) );
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
                if( checkCollision( ball.getRect(), getWorldPosFromTilePos( Vec2( j, i ) ).toRect( tileSize-5, tileSize-5 ) ) )
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
        vita2d_draw_rectangle( rect.x, rect.y, rect.w, rect.h, RGBA8( 0, 0, 0, 255 ) );
    else if( state == State::painted )
    {
        vita2d_draw_rectangle( rect.x, rect.y, rect.w, rect.h, RGBA8( 0, 0, 0, 255 ) );
        vita2d_draw_rectangle( rect.x + 10, rect.y + 10, rect.w - 20, rect.h - 20, RGBA8( 0, 255, 0, 255 ) );
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
    vita2d_draw_rectangle( rect.x, rect.y, rect.w, rect.h, RGBA8( 255, 255, 255, 255) );
}


LevelListElement::LevelListElement( std::string filePath )
{
    completed = false;
    this->filePath = filePath;
}


LevelList::LevelList()
{
    levels.push_back( LevelListElement( "app0:levels/level0.txt" ) );
    currentLevel = 1;
}

void LevelList::add( std::string filePath )
{
    levels.push_back( LevelListElement( "app0:levels/" + filePath ) );
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

int LevelList::getNrOfLevels()
{
    return levels.size();
}

void LevelList::nextLevel()
{
    if( currentLevel < levels.size() - 1 )
        currentLevel++;
}