#include "Pathfinder.h"

void Pathfinder::Restart()
{
	
	VisitedNodes.clear();
	cheapestEdgeTo.clear();

	UnvisitedNodes.clear();

	for (TileCoord position : map->GetAllTraversableTiles())
	{
		UnvisitedNodes[position] = INFINITY;
	}
	UnvisitedNodes[startNode] = 0;
}

void Pathfinder::GetLowestCostFromNeihbors()
{
	vector<TileCoord> AjacentNodes = map->GetTraversibleTilesAdjacentTo(currentNode);
	for (TileCoord coordinates : AjacentNodes)
	{
		if (map->IsTraversible(coordinates))
		{
			visitedNode[coordinates] = map->CheckCost()


		}
	}

}
