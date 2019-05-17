#include <iostream>
#include <string>

#include "Graph.hpp"

int main()
{
	Graph<std::string, double> g;

	for(std::size_t i = 0u; i < 6u; ++i)
	{
		g.insertVertex("data " + std::to_string(i));
	}

	for(std::size_t i = 0u; i < g.nrOfVertices(); ++i)
	{
		for(std::size_t j = 0u; j < g.nrOfVertices(); ++j)
		{
			if((i + j) & 1u || i & 1u)
			{
				g.insertEdge(i, j, ((i != j) ? (i+j)/2. : 1.));
			}
		}
	}
	g.insertEdge(0, 2, 4.);
	std::cout << (g.removeVertex(1) ? "Udalo sie" : "Nie udalo sie") << std::endl;
	std::cout << (g.removeEdge(2, 2) ? "Udalo sie" : "Nie udalo sie") << std::endl;
	std::cout << (g.removeEdge(2, 3) ? "Udalo sie" : "Nie udalo sie") << std::endl;
	std::cout << (g.removeEdge(4, 3) ? "Udalo sie" : "Nie udalo sie") << std::endl;
	std::cout << "Nr of vertices: " << g.nrOfVertices() << std::endl;
	std::cout << "Nr of edges: " << g.nrOfEdges() << std::endl;
	std::cout << std::endl;
	g.printNeighborhoodMatrix();
	std::cout << "Vertices data:" << std::endl;
	for(auto v_it = g.beginVertices(); v_it != g.endVertices(); ++v_it)
	{
		std::cout << *v_it << ", ";
	}
	std::cout << std::endl << std::endl;
}

