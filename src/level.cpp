#include "level.hpp"

Level::Level()
{
    tileSize = 30;
}

void Level::loadFromFile( std::string file )
{
    std::ifstream levelFile( file );

    if( levelFile.fail() )
    {
        // Handle level load fail
    }
    else
    {
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

    levelFile.close();
}

void Level::update()
{
    ball.handleInput();
    ball.move();

    if( ballHittingWall() )
    {
        ball.moveBack();
        ball.stop();
    }
    
}

void Level::draw()
{
    int levelWidth = tiles[ tiles.size() / 2 ].size() * tileSize;
    int levelHeight = tiles.size() * tileSize;
    int paddingLeft = ( SCREEN_WIDTH - levelWidth ) / 2;
    int paddingTop = ( SCREEN_HEIGHT - levelHeight ) / 2;

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

    // DEBUG
    if( ball.state == Ball::State::stationary )
        Gui::drawText( 100, 200, 20, "Stationary" );
    else
        Gui::drawText( 100, 200, 20, "Moving" );

    if( ballHittingWall() )
        Gui::drawText( 100, 300, 20, "HITTING WALL!" );
}

Vec2 Level::getWorldPosFromTilePos( Vec2 tilePos )
{
    int levelWidth = tiles[ tiles.size() / 2 ].size() * tileSize;
    int levelHeight = tiles.size() * tileSize;
    int paddingLeft = ( SCREEN_WIDTH - levelWidth ) / 2;
    int paddingTop = ( SCREEN_HEIGHT - levelHeight ) / 2;

    Vec2 worldPos = Vec2( paddingLeft + ( tilePos.x * tileSize ) + ( tileSize / 2 ), paddingTop + ( tilePos.y * tileSize ) + ( tileSize / 2 ) );
    return worldPos;
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
                ball.setTilePos( Vec2( i, j ) );
                ball.setWorldPos( getWorldPosFromTilePos( Vec2( i, j ) ) );
                startTileCounter++;
            }
        }
    }

    if( startTileCounter == 0 )
    {
        // Handle no starting tile found
    }
    if( startTileCounter > 1 )
    {
        // Handle more then one starting tile found
    }
}

bool Level::checkCollision( Rect a, Rect b )
{
    int leftA, leftB; 
    int rightA, rightB; 
    int topA, topB; 
    int bottomA, bottomB;

    leftA = a.x; 
    rightA = a.x + a.w; 
    topA = a.y; 
    bottomA = a.y + a.h;

    leftB = b.x; 
    rightB = b.x + b.w; 
    topB = b.y; 
    bottomB = b.y + b.h;

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

Tile::Tile()
{

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
            return new WallTile();

        case 'f':
            return new FloorTile();
            
        case 's':
            return new StartTile();

        default:
            return new Tile();
    }
}


void FloorTile::draw( Rect rect )
{
    vita2d_draw_rectangle( rect.x, rect.y, rect.w, rect.h, RGBA8( 0, 0, 0, 255) );
}


void WallTile::draw( Rect rect )
{
    vita2d_draw_rectangle( rect.x, rect.y, rect.w, rect.h, RGBA8( 255, 255, 255, 255) );
}