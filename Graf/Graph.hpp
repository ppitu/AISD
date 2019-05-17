#include <cstdint>
#include <vector>
#include <optional>
#include <limits>
#include <stack>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>

template <typename V, typename E>
class Graph
{
	class VerticesIterator
	{
		private:
			VerticesIterator(Graph<V, E> &graph, std::size_t current_vertex_id = 0u);

		public:
			// ...

			friend class Graph<V, E>;

		private:
			const Graph& ver_graph;			
			std::vector<V> viter_graph{};

		public:
			bool operator==(const VerticesIterator &vi) const;
			bool operator!=(const VerticesIterator &vi) const;
			VerticesIterator& operator++();
			VerticesIterator operator++(int);
			V& operator*() const;
			V* operator->() const;
	};

	class EdgesIterator
	{
		private:
			EdgesIterator(Graph<V, E> &graph, std::size_t nm_row, std::size_t nm_col);

		public:
			// ...

			friend class Graph<V, E>;

		private:
			// ...

		public:
			bool operator==(const EdgesIterator &ei) const;
			bool operator!=(const EdgesIterator &ei) const { return !(*this == ei); }
			EdgesIterator& operator++();
			EdgesIterator operator++(int);
			E& operator*() const;
			E* operator->() const;
	};

	public:
	Graph() = default;

	private:
	std::vector<V> v_graph{};		
	std::vector<std::vector<std::optional<E>>> e_graph{};
	int nrofedges = 0;		
	public:
	/*VerticesIterator*/ void insertVertex(const V &vertex_data);
	/*std::pair<EdgesIterator, bool>*/ void insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label = E(), bool replace = true);
	bool removeVertex(std::size_t vertex_id);
	bool removeEdge(std::size_t vertex1_id, std::size_t vertex2_id);
	bool edgeExist(std::size_t vertex1_id, std::size_t vertex2_id) const;
	std::size_t nrOfVertices() const;
	std::size_t nrOfEdges() const;
	void printNeighborhoodMatrix() const;
	VerticesIterator vertex(std::size_t vertex_id);
	EdgesIterator edge(std::size_t vertex1_id, std::size_t vertex2_id);
	VerticesIterator begin();
	VerticesIterator end();
	VerticesIterator beginVertices();
	VerticesIterator endVertices();
	EdgesIterator beginEdges();
	EdgesIterator endEdges();
};

template <typename V, typename E>
void Graph<V, E>::insertVertex(const V &vertex_data)
{
	int n = 0;

	for(std::size_t i = 0; i < v_graph.size(); i++)
		if(v_graph[i] == vertex_data)
			n++;

	if(n == 0)
	{
		e_graph.resize(v_graph.size() + 1);


		for(std::size_t i = 0; i < (v_graph.size() + 1); i++)
			e_graph[i].resize(v_graph.size() + 1);

		v_graph.push_back(vertex_data);	
	}
}

template <typename V, typename E>
void Graph<V, E>::insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label, bool replace)
{
	if(edgeExist(vertex1_id, vertex2_id) && !replace)
		return;
	else	
		e_graph[vertex1_id][vertex2_id].emplace(label);
	nrofedges++;
}

template <typename V, typename E>
bool Graph<V, E>::removeVertex(std::size_t vertex_id)
{
	if(vertex_id < 0 || vertex_id > v_graph.size())
		return false;

	v_graph.erase(v_graph.begin() + vertex_id);

	for(std::size_t i = 0; i < (v_graph.size() + 1); i++)
	{
		if(e_graph[vertex_id][i].has_value())	
			nrofedges--;
		if(e_graph[i][vertex_id].has_value())
			if(i != vertex_id)
				nrofedges--;
	}

	e_graph.erase(e_graph.begin() + vertex_id);

	for(std::size_t i = 0; i < (v_graph.size() + 1); i++)
		e_graph[i].erase(e_graph[i].begin() + vertex_id);

	return true;
}

template <typename V, typename E>
bool Graph<V, E>::removeEdge(std::size_t vertex1_id, std::size_t vertex2_id)
{
	//if(vertex1_id < 0 && vertex2_id < 0 && vertex1_id > v_graph.size() && vertex2_id > v_graph.size())
	//	return false;

	if(!e_graph[vertex1_id][vertex2_id].has_value())
		return false;

	e_graph[vertex1_id][vertex2_id].reset();
	nrofedges--;	
	return true;
}

template <typename V, typename E>
bool Graph<V, E>::edgeExist(std::size_t vertex1_id, std::size_t vertex2_id) const
{
	return e_graph[vertex1_id][vertex2_id].has_value();
}

template <typename V, typename E>
std::size_t Graph<V, E>::nrOfVertices() const
{
	return v_graph.size();
}

template <typename V, typename E>
std::size_t Graph<V, E>::nrOfEdges() const
{
	return nrofedges;
}

template <typename V, typename E>
void Graph<V, E>::printNeighborhoodMatrix() const
{
	for(const auto &vertex : v_graph)
		std::cout << vertex << std::endl;
	std::cout << std::endl;

	for(const auto &elem : e_graph)
	{
		for(const auto &el : elem)
		{
			if(el.has_value())
				std::cout << std::setw(8) << el.value();
			else
				std::cout << std::setw(8) << ".0 ";
		}
		std::cout << std::endl;
	}
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::vertex(std::size_t vertex_id)
{
	return VerticesIterator(*this, vertex_id);
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::begin() 
{ 
	return beginVertices(); 
}
	
template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::end() 
{ 
	return endVertices(); 
}
	
template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::beginVertices()
{
	return VerticesIterator(*this);
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::endVertices()
{
	return VerticesIterator(*this, v_graph.size() - 1);
}

/////////////////////////////////////////////////////////////////////////
//Vertex class implementacja

template <typename V, typename E>
bool Graph<V, E>::VerticesIterator::operator==(const VerticesIterator &vi) const
{
	return viter_graph == vi.viter_graph;
}
			
template <typename V, typename E>
bool Graph<V, E>::VerticesIterator::operator!=(const VerticesIterator &vi) const 
{
	return !(*this == vi); 
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator& Graph<V, E>::VerticesIterator::operator++()
{
	viter_graph++;
	return *this;
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::VerticesIterator::operator++(int)
{
	auto tmp = viter_graph;
	++(*this);
	return tmp;
}

template <typename V, typename E>			
V& Graph<V, E>::VerticesIterator::operator*() const
{
	return *viter_graph;
}

template <typename V, typename E>
V* Graph<V, E>::VerticesIterator::operator->() const
{
	return *viter_graph;
}

template <typename V, typename E>
Graph<V, E>::VerticesIterator::VerticesIterator(Graph<V, E> &graph, std::size_t current_vertex_id) : ver_graph{graph}, viter_graph{v_graph.begin() + current_vertex_id}
{
}
