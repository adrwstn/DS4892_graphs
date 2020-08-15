#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <random>

/*  July 15th exercises:
 * Question 1: What is a DAG?
 * Answer: Directed Acyclic Graph. basically a set of vertices/nodes that have paths organized in such a way that
 * the general direction of the paths/edges that link vertices together are uniform, i.e. cannot travel backwards to the
 * previous vertex once you arrived at current vertex.
 * In summary: (in this context) Directed-Acyclic means mono-directional and an inability to "back-travel"
 *
 * Question 2: Asymptotically speaking, how does the maximum number of edges |E|
 * in an undirected graph vary with the number of vertices |V| ?
 * StackOverFlow says: "if you have N nodes, there are N - 1 directed edges than can lead from it
 * (going to every other node). Therefore, the maximum number of edges is N * (N - 1)"
 * source:
 *  https://stackoverflow.com/questions/5058406/what-is-the-maximum-number-of-edges-in-a-directed-graph-with-n-nodes
 *
 * Implement an adjacency matrix for a graph where the number of vertices is known in advance.
 * Use the following class template: Anyone actually get time to do this yet between?
 *
 *  July 17th exercises:
 * Given the following table of road distances between selected locations on the Avalon Peninsula.
 * Write a program that will parse road-distances.csv into a graph representation.
 * You may use either an adjacency matrix or an adjacency list to store this data in memory.
 *
 *  July 20th exercises:
 * 1. Using the algorithm in the Shortest Paths video and the data from Friday’s exercises, calculate (by hand) the
 *  distances from Portugal Cove to all other locations in the table.
 * 2. Starting from the code you wrote on Friday, write a method of your graph class that will calculate the
 *  total road distance between any two points in the graph.
 *
 *  TODO: haven't had time to do 20th exercises yet
 */

template<typename V, typename E>
class Graph
{
public:
	using VertexID = size_t;

	struct Vertex
	{
		VertexID ID_;
		V data_;
		// std::vector<VertexID> inDeg_;   // for june 27th exercise
		// std::vector<VertexID> outDeg_;  // for june 27th exercise

		Vertex(VertexID id, V data)
			: ID_(id), data_(data)
		{}

		VertexID getID() const
		{
			return ID_;
		}

		V getData() const
		{
			return data_;
		}
	};

	Graph()
	{
		generator.seed(std::time(0));
	};

	/* if theres a ID_ member that matches findID, data_ of vertex is returned */
	V getDataFromID(VertexID findID)
	{
		for (auto found: vertices_)
		{
			if (found.getID() == findID)
			{
				return found.getData();
			}
		}
		// TODO error handling for ID not found
		return NULL;
	}

	/* if theres a data_ member that matches findData, ID of vertex is returned */
	VertexID getIDFromData(V findData)
	{
		for (auto i : vertices_)
		{
			if (findData == i.getData())
			{
				return i.getID();
			}
		}
		// TODO error handling for no data member found
		std::cout << "\nNO MATCHES!\n";
		return 0;
	}

	/* add vertex to vertices vector, assigning random ID to vertex*/
	VertexID addVertex(V data)
	{
		auto genID = genRandomID();
		vertices_.push_back(Vertex(genID, data));
		return genID;
	}

	E getPathDistance(VertexID fromID, VertexID toID)
	{
		for (auto i : adjList_)
		{
			// remove condition after || for Directed Graphs
			if (std::get<0>(i) == fromID && std::get<1>(i) == toID ||
			    std::get<0>(i) == toID && std::get<1>(i) == fromID)
			{
				return std::get<2>(i);
			} else
			{
				/*TODO: add "look for neighbor" function that finds neighbor of 2 vertices displace >2 edges*/
			}
		}
	}

	/*  VertexID <- ID of starting vertex
	 *  VertexID <- ID of ending vertex
	 *  E <- edge length */
	Graph &addEdge(VertexID fromID, VertexID toID, E edgeLength)
	{
		adjList_.push_back({fromID, toID, edgeLength});
		return *this;
	}

	/* vertices_ holds vector of Vertex's. Idea is to use this container
	 * to store all the vertices and iterate over to find data of vertex by VertexID */
	std::vector<Vertex> vertices_;

	/* tuple order: {from-vertex, to-vertex,distance}*/
	std::vector<std::tuple<VertexID, VertexID, E>> adjList_;

	void printAdjList()
	{
		for (auto i : adjList_)
		{
			// std::cout<<std::get<0>(i)<<", "<<std::get<1>(i)<<" "<<std::get<2>(i)<<std::endl;
			std::cout << getDataFromID(std::get<0>(i)) << ", " << getDataFromID(std::get<1>(i))
			          << " " << std::get<2>(i) << std::endl;
		}

		// used for testing only
		/*for (auto i : adjList_)
		{
			std::cout<<std::get<0>(i)<<", "<<std::get<1>(i)<<" "<<std::get<2>(i)<<std::endl;
		}*/
	}

private:
	/*Random number generator to create 3-digit ID between 100-999*/
	std::mt19937 generator;

	uint16_t genRandomID()
	{
		std::uniform_int_distribution<uint16_t> ID(100, 999);
		uint32_t id = ID(generator);
		return id;
	};

};