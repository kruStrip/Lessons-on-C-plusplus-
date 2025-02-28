#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <set>
#include <random>
#include <algorithm>

std::random_device dev;
std::mt19937 gen(dev());
std::uniform_int_distribution<int> dist(1, 10000);

class Graph
{
	

	std::vector<std::vector<int>> matrix;

public:
	using Edge = std::pair<size_t, size_t>;
	Graph(size_t rows = 10, size_t cols = 10) : matrix(rows* rows, std::vector<int>(cols* cols, 0.0))
	{

	}

	void setValue(size_t i, size_t j, double value)
	{
		matrix[i][j] = value;
	}

	std::list<Edge> buildTree()
	{
		std::list<Edge> l;
		std::list<size_t> q;

		for (size_t i = 1; i < matrix[0].size(); ++i) {
			q.push_back(i);
		}

		std::list<size_t> p = { 0 };
		while (!q.empty()) {
			int min = 10001;
			size_t v1, v2;

			for (size_t el : p) {
				for (size_t j = 0; j < matrix[0].size(); ++j) {
					if (matrix[el][j] == 0 || std::find(p.begin(), p.end(), j) != p.end()) continue;

					if (matrix[el][j] < min) {
						min = matrix[el][j];
						v1 = el;
						v2 = j;
					}
				}
			}
			p.push_back(v2);
			q.erase(std::find(q.begin(), q.end(), v2));
			l.push_back({ v1, v2 });
		}

		return l;
	}
};

void fill(Graph& g)
{
	// Угловые вершины
	// Левая верхняя
	g.setValue(0, 1, dist(gen));
	g.setValue(0, 10, dist(gen));
	// Правая верхняя
	g.setValue(9, 8, dist(gen));
	g.setValue(9, 19, dist(gen));
	// Левая нижняя
	g.setValue(90, 91, dist(gen));
	g.setValue(90, 80, dist(gen));
	// Правая нижняя
	g.setValue(99, 98, dist(gen));
	g.setValue(99, 89, dist(gen));

	// Верхняя граница
	for (size_t i = 1; i <= 8; ++i)
	{
		g.setValue(i, i - 1, dist(gen));
		g.setValue(i, i + 1, dist(gen));
		g.setValue(i, i + 10, dist(gen));
	}

	// Нижняя граница
	for (size_t i = 91; i <= 98; ++i)
	{
		g.setValue(i, i - 1, dist(gen));
		g.setValue(i, i + 1, dist(gen));
		g.setValue(i, i - 10, dist(gen));
	}

	// Левая граница
	for (size_t i = 10; i <= 80; i += 10)
	{
		g.setValue(i, i - 10, dist(gen));
		g.setValue(i, i + 10, dist(gen));
		g.setValue(i, i + 1, dist(gen));
	}
	// Левая граница
	for (size_t i = 19; i <= 89; i += 10)
	{
		g.setValue(i, i - 10, dist(gen));
		g.setValue(i, i + 10, dist(gen));
		g.setValue(i, i - 1, dist(gen));
	}

	// Внутренние вершины
	for (size_t i = 1; i <= 8; ++i)
	{
		for (size_t j = 1; j <= 8; ++j)
		{
			g.setValue(i * 10 + j, i * 10 + j - 1, dist(gen));
			g.setValue(i * 10 + j, i * 10 + j + 1, dist(gen));
			g.setValue(i * 10 + j, i * 10 + j - 10, dist(gen));
			g.setValue(i * 10 + j, i * 10 + j + 10, dist(gen));
		}
	}
}

std::vector<std::vector<char>> generateField(std::list<Graph::Edge> const& r) {
	std::vector<std::vector<char>> field(21, std::vector<char>(21, '#'));
	for (int i = 0; i < 2 * 10 + 1;++i) {
		for (int j = 0; j < 2 * 10 + 1; ++j) {
			if (i % 2 == 1 && j % 2 == 1) {
				field[i][j] = ' ';
			}
		}
	}
	for (auto const& edge : r) {
		size_t v1 = edge.first;
		size_t v2 = edge.second;

		size_t r1 = v1 / 10, r2 = v2 / 10 ;
		size_t c1 = v1 % 10, c2 = v2 % 10;

		field[r1 + r2 + 1][c1 + c2 + 1] = ' ';
	}

	return field;
}

int main()
{
	Graph g(10, 10);
	fill(g);

	auto field = generateField(g.buildTree());
	for (auto const& v : field) {
		for (auto const& c : v) {
			std::cout << c;
		}
		std::cout << '\n';
	}
	std::cout << std::endl;

	return 0;
}