#include "TileMap.h"

Tile Tilemap::GetTile(TileCoord tilePosition)
{
	int x = tilePosition.x;
	int y = tilePosition.y;
	return tiles[x][y];
}

void Tilemap::SetTile(int x, int y, Tile type)
{
	tiles[x][y] = type;
}

bool Tilemap::IsInsideGrid(TileCoord tilePosition)
{
	if (tilePosition.x < MAP_WIDTH && tilePosition.x >= 0 &&
		tilePosition.y < MAP_HEIGHT && tilePosition.y >= 0)
		return true;
	else return false;
}

TileCoord Tilemap::TilePosToScreenPos(int x, int y)
{	
	return { (float)x * tileSizeX, (float)y * tileSizeY };
}

TileCoord Tilemap::ScreenPosToTilePos(Vector2 postionOnScreen)
{return { (float)postionOnScreen.x / tileSizeX, (float)postionOnScreen.y / tileSizeY };
}

bool Tilemap::IsTraversible(TileCoord tilePosition)
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

	for (int y = 0; y < GetGridHeight()+1; y++)
		DrawLine(0, y * tileSizeY, GetGridWidth() * tileSizeX, y * tileSizeY, color);
}

void Tilemap::DrawTiles()
{
	for (int x = 0; x < GetGridWidth(); x++)
	{
		for (int y = 0; y < GetGridHeight(); y++)
		{
			Tile tileType = tiles[x][y];
			TileCoord tilePosition = TilePosToScreenPos(x, y);
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
	ReplacePlayer();
}

Vector2 Tilemap::GetTileCenter(TileCoord tilePosition)
{
	return { (float)tilePosition.x*tileSizeX + (tileSizeX / 2),(float)tilePosition.y*tileSizeY + (tileSizeY / 2) };
}

void Tilemap::MoveSpriteUp()
{
	Vector2 playerPos = { player.GetDest().x,player.GetDest().y };
	TileCoord tileCord = ScreenPosToTilePos(playerPos);
	tileCord.y -= 1;

	if (IsTraversible(tileCord))
	{
		player.SetPosition(TilePosToScreenPos(tileCord.x, tileCord.y));
	}
	
}

void Tilemap::MoveSpriteLeft()
{
	Vector2 playerPos = { player.GetDest().x,player.GetDest().y };
	TileCoord tileCord = ScreenPosToTilePos(playerPos);
	tileCord.x -= 1;

	if (IsTraversible(tileCord))
	{
		player.SetPosition(TilePosToScreenPos(tileCord.x, tileCord.y));
	}
}

void Tilemap::MoveSpriteDown()
{
	Vector2 playerPos = { player.GetDest().x,player.GetDest().y };
	TileCoord tileCord = ScreenPosToTilePos(playerPos);
	tileCord.y += 1;

	if (IsTraversible(tileCord))
	{
		player.SetPosition(TilePosToScreenPos(tileCord.x, tileCord.y));
	}

}

void Tilemap::MoveSpriteRight()
{
	Vector2 playerPos = { player.GetDest().x,player.GetDest().y };
	TileCoord tileCord = ScreenPosToTilePos(playerPos);
	tileCord.x += 1;

	if (IsTraversible(tileCord))
	{
		player.SetPosition(TilePosToScreenPos(tileCord.x, tileCord.y));
	}
}

void Tilemap::ReplacePlayer()
{
	bool breakFlag = false;
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			TileCoord tileCoord = { x,y };
			if (IsTraversible(tileCoord))
			{
				breakFlag = true;
				TileCoord centerOfTile = TilePosToScreenPos(x,y);

				player.SetPosition(centerOfTile.x, centerOfTile.y);
				break;
			}
		}
			if (breakFlag) break;
	}

}

void Tilemap::DrawNodes()
{
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)

		{
			TileCoord tempVec = { x,y };
			if (IsTraversible(tempVec))
			{
				DrawCircleV(GetTileCenter(tempVec), 15, GREEN);
				std::vector<TileCoord> connections = GetTraversibleTilesAdjacentTo(tempVec);
				for (TileCoord& connection : connections)
				{

					DrawLineV(GetTileCenter(tempVec), GetTileCenter(connection), GREEN);
				}
					

				
			}
		}
	}
}

void Tilemap::DrawConnections()
{

}

void Tilemap::DrawSprite()
{
	Vector2 origin = { player.GetDest().x + (player.GetDest().width / 2)
					, player.GetDest().y + (player.GetDest().height / 2) };
	DrawTexturePro(player.GetTexture(), player.GetSource(), player.GetDest(), {}, 0, WHITE);
}

std::vector<TileCoord> Tilemap::GetTraversibleTilesAdjacentTo(TileCoord tilePosition)
{
	{
		std::vector<TileCoord> adjacentTilePositions;
		TileCoord N = tilePosition + NORTH;
		TileCoord S = tilePosition + SOUTH;
		TileCoord E = tilePosition + EAST;
		TileCoord W = tilePosition + WEST;
		if (IsTraversible(N)) adjacentTilePositions.push_back(N);
		if (IsTraversible(S)) adjacentTilePositions.push_back(S);
		if (IsTraversible(E)) adjacentTilePositions.push_back(E);
		if (IsTraversible(W)) adjacentTilePositions.push_back(W);
		return adjacentTilePositions;
	}
}

vector<TileCoord> Tilemap::GetAllTraversableTiles()
{
	vector<TileCoord> tempVector;
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			if (tiles[x][y] == Tile::Floor)
			{
				TileCoord tempCoor = { x,y };
				tempVector.push_back(tempCoor);
			}
		}
	}
	return tempVector;
}
