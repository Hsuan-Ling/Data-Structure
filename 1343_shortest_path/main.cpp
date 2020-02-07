#include <iostream>
using namespace std;

class Graph
{
private:
	int **length;
	int* prdecessor;
	bool* visited;
	int numNodes, startNode;
public:
	Graph(int n);
	~Graph();
	int *distance;
	void addPath(int from, int to, int value);
	void dijkstra(int startNode);
	void printPath(int x);
};

Graph::Graph(int n): numNodes(n)
{
	length = new int*[n];
	for (int i = 0; i < n; i++) length[i] = new int[n];

	prdecessor = new int[n];
	visited = new bool[n];
	distance = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			length[i][j] = 0;
}

Graph::~Graph()
{
	for (int i = 0; i < numNodes; i++) delete[] length[i];
	delete[] length;
	delete[] prdecessor;
	delete[] visited;
	delete[] distance;
}

void Graph::addPath(int from, int to, int value)
{
	if (value < length[from][to] || length[from][to] == 0)
	{
		length[from][to] = value;
		length[to][from] = value;
	}
}

void Graph::printPath(int x)
{
	if (prdecessor[x] != x)
		printPath(prdecessor[x]); //先前路徑

	cout << x + 1 << " "; //現在位置
}

void Graph::dijkstra(int startNode)
{
	this->startNode = startNode;
	for (int i = 0; i < numNodes; i++) visited[i] = false;
	for (int i = 0; i < numNodes; i++) distance[i] = 100000000;

	distance[startNode] = 0;
	prdecessor[startNode] = startNode;

	for (int k = 0; k < numNodes; k++)
	{
		int nextNode = -1;
		int min = 100000000;

		for (int i = 0; i < numNodes; i++)
			if (!visited[i] && distance[i] < min)
			{
				nextNode = i;
				min = distance[i];
			}
		
		if (nextNode == -1) break;
		visited[nextNode] = true;

		for (int i = 0; i < numNodes; i++)
			if (!visited[i] && length[nextNode][i]
				&& distance[nextNode] + length[nextNode][i] < distance[i])
			{
				distance[i] = distance[nextNode] + length[nextNode][i];
				prdecessor[i] = nextNode;
			}
	}
}

int main()
{
	int numVertexes;
	cin >> numVertexes;

	int numEdges;
	cin >> numEdges;

	int startVertex;
	cin >> startVertex;

	Graph graph(numVertexes);

	int from, to, value;

	for (int times = 0; times < numEdges; times++)
	{
		cin >> from >> to >> value;
		graph.addPath(from - 1, to - 1, value);
	}

	graph.dijkstra(startVertex - 1);

	for (int i = 0; i < numVertexes; i++)
		if (i != startVertex - 1) {
			cout << "Distance of " << startVertex << " to " << i + 1 << ": " << graph.distance[i] << endl;
			cout << "Path: ";
			graph.printPath(i);
			cout << endl;
		}

	//system("pause");
	return 0;
}
