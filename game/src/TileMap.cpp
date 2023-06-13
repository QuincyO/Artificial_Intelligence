#include "TileMap.h"

Tile Tilemap::GetTile(Vector2 tilePosition) 
{
	int x = tilePosition.x;
	int y = tilePosition.y;
	return tiles[x][y];
}

void Tilemap::SetTile(int x, int y, Tile type)
{
	tiles[x][y] = type;
}

bool Tilemap::IsInsideGrid(Vector2 tilePosition)
{
	if ((tilePosition.x <= MAP_WIDTH ||
		tilePosition.x >= MAP_WIDTH) &&
		(tilePosition.y <= MAP_HEIGHT ||
		tilePosition.y >= MAP_HEIGHT))
		return true;
	else return false;
}

Vector2 Tilemap::TilePosToScreenPos(int x, int y)
{	
	return { (float)x * tileSizeX, (float)y * tileSizeY };
}

bool Tilemap::IsTraversible(Vector2 tilePosition)
{
	if (IsInsideGrid(tilePosition))
	{
		if (GetTile(tilePosition) == Tile::Floor) return true;
	}
	return false;
}

void Tilemap::DrawBorders(Color color)
{
	for (int x = 0; x < GetGridWidth()+1; x++)
	{
		DrawLine(x * tileSizeX, 0, x * tileSizeX, GetGridHeight() * tileSizeX, color);
	}

	for (int y = 0; y < GetGridHeight(); y++)
		DrawLine(0, y * tileSizeY, GetGridWidth() * tileSizeX, y * tileSizeY, color);
}

void Tilemap::DrawTiles()
{
	for (int x = 0; x < GetGridWidth(); x++)
	{
		for (int y = 0; y < GetGridHeight(); y++)
		{
			Tile tileType = tiles[x][y];
			Vector2 tilePosition = TilePosToScreenPos(x, y);
			Color colorToDraw = PINK;
			if (tileType == Tile::Floor) colorToDraw = WHITE;
			else if (tileType == Tile::Wall) colorToDraw = BLACK;

			DrawRectangle(tilePosition.x, tilePosition.y, tileSizeX, tileSizeY, colorToDraw);
		}
	}
}

void Tilemap::RegnerateLevel(int chanceofWall)
{
	float floatChance = static_cast<float>(chanceofWall) / 100;
	for (int x = 0; x < GetGridWidth(); x++)
	{
		for (int y = 0; y < GetGridHeight(); y++)
		{
			
			if ((float)rand() / RAND_MAX < floatChance)
			{
				SetTile(x, y, Tile::Wall);
			}
			else SetTile(x, y, Tile::Floor);
		}
	}
}

void Tilemap::DrawNodes()
{
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)

		{
			Vector2 tempVec = { x,y };
			if (IsTraversible(tempVec))
			{
				Vector2 center = { (x * tileSizeX)+(tileSizeX/2),(y * tileSizeY)+(tileSizeY/2)};
				std::vector<Vector2> connections = GetTraversibleTilesAdjacentTo(tempVec);
				for (Vector2 connection : connections)
				{
					DrawLineV(center, connection, GREEN);
				}
				DrawCircleV(center, 15, GREEN);
			}
		}
	}
}

void Tilemap::DrawConnections()
{

}

std::vector<Vector2> Tilemap::GetTraversibleTilesAdjacentTo(Vector2 tilePosition)
{
	{
		std::vector<Vector2> adjacentTilePositions;
		Vector2 N = tilePosition + NORTH;
		Vector2 S = tilePosition + SOUTH;
		Vector2 E = tilePosition + EAST;
		Vector2 W = tilePosition + WEST;
		if (IsTraversible(N)) adjacentTilePositions.push_back(N);
		if (IsTraversible(S)) adjacentTilePositions.push_back(S);
		if (IsTraversible(E)) adjacentTilePositions.push_back(E);
		if (IsTraversible(W)) adjacentTilePositions.push_back(W);
		return adjacentTilePositions;
	}
}
