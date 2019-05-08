#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <optional>
#include <stack>
#include <vector>

template <typename V, typename E>
class Graph
{
	public:
		class VerticesIterator
		{
			private:
				VerticesIterator(const Graph<V, E> &graph, std::size_t current_vertex_id = 0u);

			public:
				// ...

				friend class Graph<V, E>;

			private:
				const Graph& m_vgraph;
				typename decltype(std::declval<Graph>().m_graph)::const_iterator m_iterator;

			public:
				bool operator==(const VerticesIterator &vi) const;
				bool operator!=(const VerticesIterator &vi) const;
				VerticesIterator& operator++();
				VerticesIterator operator++(int);
				const V& operator*() const;
				const V* operator->() const;
		};

		class EdgesIterator
		{
			private:
				EdgesIterator(const Graph<V, E> &graph, std::size_t nm_row, std::size_t nm_col);

			public:
				// ...

				friend class Graph<V, E>;

			private:
				const Graph& m_egraph;
				decltype(m_egraph.m_graph.begin()) m_row;
				decltype(m_row->second.begin()) m_column;
			public:
				bool operator==(const EdgesIterator &ei) const;
				bool operator!=(const EdgesIterator &ei) const;
				EdgesIterator& operator++();
				EdgesIterator operator++(int);
				const E& operator*() const;
				const E* operator->() const;
		};

	public:
		Graph() = default;
		// ...

	private:
		std::vector<std::pair<V, std::vector<std::optional<E>>>> m_graph{};

	public:
		VerticesIterator insertVertex(const V &vertex_data);
		std::pair<EdgesIterator, bool> insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E &label = E(), bool replace = true);
		bool removeVertex(std::size_t vertex_id);
		bool removeEdge(std::size_t vertex1_id, std::size_t vertex2_id);
		bool edgeExist(std::size_t vertex1_id, std::size_t vertex2_id) const;
		std::size_t nrOfVertices() const;
		std::size_t nrOfEdges() const;
		void printNeighborhoodMatrix() const;
		VerticesIterator vertex(std::size_t vertex_id) const;
		EdgesIterator edge(std::size_t vertex1_id, std::size_t vertex2_id) const;
		VerticesIterator begin() const;
		VerticesIterator end() const;
		VerticesIterator beginVertices() const;
		VerticesIterator endVertices() const;
		EdgesIterator beginEdges() const;
		EdgesIterator endEdges() const;
};

// Graph implementation

template <typename V, typename E>
std::size_t Graph<V, E>::nrOfVertices() const
{
	return m_graph.size();
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::begin() const
{
	return beginVertices();
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::end() const
{


	return endVertices();
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::beginVertices() const
{
	return VerticesIterator(*this);
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::endVertices() const
{
	return ++VerticesIterator(*this, m_graph.size() - 1);
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::vertex(std::size_t vertex_id) const
{
	return VerticesIterator(*this, vertex_id);
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::insertVertex(const V& vertex_data)
{
	int n = 0;
	for(const auto& elem : m_graph)
	{
		if(elem.first == vertex_data)
			n++;
	}
	if(n == 0)
	{	
		for (auto& vertex : m_graph) 
		{
			vertex.second.push_back({});
		}
		
		m_graph.push_back(std::make_pair(vertex_data, std::vector<std::optional<E>>(m_graph.size() + 1)));

		return VerticesIterator(*this, m_graph.size() - 1);
	}

	return VerticesIterator(*this, m_graph.size() - 1);
}

template <typename V, typename E>
bool Graph<V, E>::removeVertex(std::size_t vertex_id)
{
	if (vertex_id < 0 || vertex_id >= m_graph.size())
		return false;
	
	m_graph.erase(m_graph.begin() + vertex_id);
	
	for( auto& elem : m_graph)
	{
		elem.second.erase(elem.second.begin() + vertex_id);	
	}
	return true;
}

template <typename V, typename E>
std::size_t Graph<V, E>::nrOfEdges() const
{
	std::size_t out{0};
	for (const auto& i : m_graph)
		for (const auto& j : i.second)
			if (j.has_value())
				++out;
	return out;
}

template <typename V, typename E>
typename Graph<V, E>::EdgesIterator Graph<V, E>::beginEdges() const
{
	return EdgesIterator(*this, 0, 0);
}

template <typename V, typename E>
typename Graph<V, E>::EdgesIterator Graph<V, E>::endEdges() const
{
	auto tmp = EdgesIterator(*this, 0, 0);
	tmp.m_row = m_graph.end();
	return tmp;
}

template <typename V, typename E>
typename Graph<V, E>::EdgesIterator
Graph<V, E>::edge(std::size_t vertex1_id, std::size_t vertex2_id) const
{
	return EdgesIterator{*this, vertex1_id, vertex2_id};
}

template <typename V, typename E>
bool Graph<V, E>::edgeExist(std::size_t vertex1_id, std::size_t vertex2_id)
	const
{
	return m_graph[vertex1_id].second[vertex2_id].has_value();
}

template <typename V, typename E>
std::pair<typename Graph<V, E>::EdgesIterator, bool> Graph<V, E>::insertEdge(std::size_t vertex1_id, std::size_t vertex2_id, const E& label, bool replace)
{
	if (edgeExist(vertex1_id, vertex2_id) && !replace)
		return std::make_pair(EdgesIterator(*this, 0, 0), false);
	m_graph[vertex1_id].second[vertex2_id] = label;
	return std::make_pair(EdgesIterator(*this, vertex1_id, vertex2_id), true);
}

template <typename V, typename E>
bool Graph<V, E>::removeEdge(std::size_t vertex1_id, std::size_t vertex2_id)
{
	if (vertex1_id < 0 || vertex2_id >= m_graph.size() || vertex2_id < 0 || vertex2_id >= m_graph.size())
		return false;

	auto& tmp = m_graph[vertex1_id].second[vertex2_id];
	if (!tmp.has_value())
		return false;
	tmp.reset();
	return true;
}

template <typename V, typename E>
void Graph<V, E>::printNeighborhoodMatrix() const
{
	for (const auto& i : m_graph) {
		for (const auto& j : i.second) {
			if (j)
				std::cout << std::setw(8) << *j;
			else
				std::cout << std::setw(8) << ".0";
		}
		std::cout << std::endl;
	}
}

// Edges implementation

template <typename V, typename E>
bool Graph<V, E>::EdgesIterator::
operator==(const typename Graph<V, E>::EdgesIterator& ei) const
{
	return m_row == ei.m_row
		&& (m_row == m_egraph.m_graph.end() || m_column == ei.m_column);
}

template <typename V, typename E>
bool Graph<V, E>::EdgesIterator::operator!=(const EdgesIterator& ei) const
{
	return !(*this == ei);
}

	template <typename V, typename E>
typename Graph<V, E>::EdgesIterator& Graph<V, E>::EdgesIterator::operator++()
{
	// past-the-end
	if (m_row == m_egraph.m_graph.end()) {
		return *this;
	}

	do {
		++m_column;
		if (m_column == m_row->second.end()) {
			++m_row;
			if (m_row == m_egraph.m_graph.end()) {
				return *this;
			}
			m_column = m_row->second.begin();
		}
	} while (!m_column->has_value());
	return *this;
}

	template <typename V, typename E>
typename Graph<V, E>::EdgesIterator Graph<V, E>::EdgesIterator::operator++(int)
{
	auto tmp = *this;
	this->operator++();
	return tmp;
}

template <typename V, typename E>
const E& Graph<V, E>::EdgesIterator::operator*() const
{
	return m_column->value();
}

template <typename V, typename E>
const E* Graph<V, E>::EdgesIterator::operator->() const
{
	return m_column->value();
}

template <typename V, typename E>
Graph<V, E>::EdgesIterator::EdgesIterator(const Graph& graph, std::size_t nm_row, std::size_t nm_col)
	: m_egraph{graph}, m_row{m_egraph.m_graph.begin() + nm_row}, m_column{m_row->second.begin() + nm_col}
{
	if (m_row != m_egraph.m_graph.end() && !m_column->has_value())
		++(*this);
}

// Vertex implementation

template <typename V, typename E>
bool Graph<V, E>::VerticesIterator::
operator==(const typename Graph<V, E>::VerticesIterator& vi) const
{
	return m_iterator == vi.m_iterator;
}

template <typename V, typename E>
bool Graph<V, E>::VerticesIterator::
operator!=(const typename Graph<V, E>::VerticesIterator& vi) const
{
	return !(*this == vi);
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator& Graph<V, E>::VerticesIterator::
operator++()
{
	++m_iterator;
	return *this;
}

template <typename V, typename E>
typename Graph<V, E>::VerticesIterator Graph<V, E>::VerticesIterator::
operator++(int)
{
	auto tmp = *this;
	this->operator++();
	return tmp;
}

template <typename V, typename E>
const V& Graph<V, E>::VerticesIterator::operator*() const
{
	return m_iterator->first;
}

template <typename V, typename E>
const V* Graph<V, E>::VerticesIterator::operator->() const
{
	return m_iterator->first;
}

template <typename V, typename E>
Graph<V, E>::VerticesIterator::VerticesIterator(const Graph& graph,std::size_t current_vertex_id)
	: m_vgraph{graph}, m_iterator{m_vgraph.m_graph.begin() + current_vertex_id}
{
}

#endif /* GRAPH_HPP */
