#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <queue>

template<typename V, typename E>
std::vector<V> getNeighbours(V vertex, std::vector<E> edges);

/* for undirected graph,
 * E is type <tuple> where tuple is pair <from, to> */
template<typename V, typename E>
std::vector<V> shortestPath(V startPoint, V endPoint, std::vector<E> edges)
{
	std::vector<E> path;        /**/
	V current = startPoint;     /**/
	std::set<V> visited;        /**/

	std::queue<V> unvisited;
	std::vector<V> finalPath;   /**/

	unvisited.push(current);            /**/

	while (unvisited.size() > 0)
	{
		current = unvisited.front();     /**/
		visited.insert(current);

		unvisited.pop(); //queue implementation

		if (current == endPoint)
			break;
		std::vector<V> neighbours = getNeighbours(current, edges);
		for (auto n : neighbours)
		{
			if (visited.find(n) == visited.end())
			{
				unvisited.push(n);          /**/
				path.push_back({current, n});
			}
		}
	}
	if (current != endPoint)
	{
		std::vector<V> noPath;
		return noPath;
	}

	V previousNode = current;
	finalPath.push_back(current);

	for (int i = path.size() - 1; i >= 0; i--)
	{
		if (previousNode == std::get<1>(path[i]))
		{
			previousNode = std::get<0>(path[i]);
			finalPath.push_back(previousNode);
		}
	}

	std::vector<V> reversePath;
	for (int i = finalPath.size() - 1; i >= 0; i--)
	{
		reversePath.push_back(finalPath[i]);
	}
	finalPath = reversePath;
	return finalPath;
}

/* returns vector of vertices connected to param vertex
 * E is type <tuple> where tuple is pair <from, to>*/
template<typename V, typename E>
std::vector<V> getNeighbours(V vertex, std::vector<E> edges)
{
	std::vector<V> connections;
	for (auto e : edges)
	{
		if (std::get<0>(e) == vertex)
		{
			connections.push_back(std::get<1>(e));
		}
		if (std::get<1>(e) == vertex)
		{
			connections.push_back(std::get<0>(e));
		}
	}
	return connections;
}

// Write a (template) function to calculate the shortest paths through an unweighted graph.