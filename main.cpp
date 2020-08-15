#include <iostream>
#include <fstream>
#include "Graph.h"
#include "shortestPath.h"

int main()
{

	std::ifstream myFile;//("./Dependencies/road-distances.csv");
	myFile.open(
		"./Dependencies/road-distances.csv");

	if (!myFile.is_open())
	{
		std::cout << "NOT OPEN" << std::endl;
	}

	std::vector<std::vector<std::string>> parse;

	while (std::getline(myFile, line))
	{
		size_t pos = 0;
		std::vector<std::string> holdTokens;
		std::string token;
		while ((pos = line.find(',')) != std::string::npos)
		{
			token = line.substr(0, pos);
			holdTokens.push_back(token);
			line.erase(0, pos + 1);
		}
		parse.push_back(holdTokens);
	}

	Graph<std::string, float> graph;
	std::vector<size_t> IDs;

	for (int i = 0; i < parse.size(); i++)
	{
		for (int j = 1; j < parse[i].size(); j++)
		{
			if (i == 0)
			{
				IDs.push_back(graph.addVertex(parse[i][j]));
			} else if (!parse[i][j].empty())
			{
				graph.addEdge(IDs[i - 1], IDs[j - 1], std::stof(parse[i][j]));
			}

		}
	}

	graph.printAdjList();

	std::cout << "---------------------------" << std::endl;
	std::string find1 = "Goulds";
	std::cout << graph.getIDFromData(find1) << std::endl;

	std::string find2 = "Bay Bulls";
	std::cout << graph.getIDFromData(find2) << std::endl;

	std::cout << "Distance: " << graph.getPathDistance(graph.getIDFromData(find1), graph.getIDFromData(find2));

	// find1 = "CB" ;
	// std::cout<<graph.getIDFromData(find1)<<std::endl;

	/* std::vector<std::tuple<int,int>> set ={{1,2},{1,3},{3,4},{2,4},{2,4},
										{3,4},{4,5},{4,6},{7,1},{4,7}};
	int start = 2;
	int end = 7;
	auto result = shortestPath(start,end,set);

	std::cout<<"path: ";
	for (auto i : result)
	{
		std::cout<<i<<", ";
	} */
	return 0;
}
