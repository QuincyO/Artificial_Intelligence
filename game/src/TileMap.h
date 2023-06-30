#pragma once
#include <vector>
#include "rlImGui.h"
#include "TileCoord.h"
#include "raylib.h"
#include "Sprite.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MAP_WIDTH (SCREEN_WIDTH/64)
#define MAP_HEIGHT (SCREEN_HEIGHT/64)

using namespace std;
enum class Tile 
{
	Floor = 0, //Floor tiles can be walked on
	Wall, //Wall tiles cannot be walked on
	Count

};




class Tilemap
{

public:
	Tilemap(const char* filepath) : player(filepath) {}
	Tilemap() {}
private:


	Tile tiles[MAP_WIDTH][MAP_HEIGHT]; //Standard array cannot be chaged at runtime

	const TileCoord NORTH = { 0,-1 };
	const TileCoord SOUTH = { 0,1 };
	const TileCoord EAST = { 1,0 };
	const TileCoord WEST = { -1,0 };

	TileCoord* tilePosition;
	TileCoord startPosition = {};
	TileCoord endPosition = {};


	int width = 0;
	int height = 0;
	vector<vector<Tile>> v_Tiles; //Dynamic Array that can be changed during Runtime

public:
	Sprite player;

	int tileSizeX = 64;
	int tileSizeY = 64;

public:


	int GetWidth()const { return width; }
	int GetHeight() const { return height; }

	int GetGridWidth() {return MAP_WIDTH; } //Get Number of columns in the grid
	int GetGridHeight() { return MAP_HEIGHT; } //Get Number of rows in the grid
	Tile GetTile(int x, int y); //Get the tile at the specified coordinate in the grid
	Tile GetTile(TileCoord tilePosition) ; //Get the tile at the specified coordinate in the grid
	void SetTile(int x, int y, Tile type); //St the tile at the specified coordinate in the grid
	bool IsInsideGrid(int x, int y); //Returns true of the coordinate is insdie the grid, false otherwise
	bool IsInsideGrid(TileCoord tilePosition); //Returns true of the coordinate is insdie the grid, false otherwise
	TileCoord TilePosToScreenPos(TileCoord tilePosition); //Convert from a tile coordinate to a screen position
	TileCoord TilePosToScreenPos(int x, int y); //Convert from a tile coordinate to a screen positon
	TileCoord ScreenPosToTilePos(Vector2 postionOnScreen);//Find a tile coordinate given a position on the screen over a tile
	
	bool IsTraversible(TileCoord tilePosition);

	void DrawBorders(Color color = BLACK);
	void DrawTiles();
	void RegnerateLevel(int chanceofWall = 50);

	Vector2 GetTileCenter(TileCoord tilePosition);

	void MoveSpriteUp( );
	void MoveSpriteLeft();
	void MoveSpriteDown();
	void MoveSpriteRight();

	void ReplacePlayer();

	void DrawNodes();

	void DrawConnections();

	void DrawSprite();

	std::vector<TileCoord> GetTraversibleTilesAdjacentTo(TileCoord tilePosition);

	vector<TileCoord> GetAllTraversableTiles();

};