#pragma once
#include <unordered_map>

#include <vector>
#include "TileMap.h"

using namespace std;

class Pathfinder
{
public:

	Tilemap* map = nullptr;

	Pathfinder(Tilemap* Map, TileCoord startTile, TileCoord endTile)
		:startNode{startTile},
		endNode{endTile},
		currentNode{startTile},
		map{Map}
	{
		Restart();
	}

	void Restart() ;

private:

	float GetCostBetweenNodes(const TileCoord& node1, const TileCoord& node_2);


	unordered_map<TileCoord, float, hash<TileCoord>, equal_to<TileCoord>> UnvisitedNodes;
	unordered_map<TileCoord, float, hash<TileCoord>, equal_to<TileCoord>> VisitedNodes;

	unordered_map<TileCoord, TileCoord, hash<TileCoord>, equal_to<TileCoord>> cheapestEdgeTo;

	TileCoord startNode;
	TileCoord currentNode;
	TileCoord endNode;

	TileCoord bestNode;



	float totalCost;


};

