// Algorithms Project 3

#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Bellman-Ford algorithm
void bellmanFord(vector<string> vertices, map<string, vector<tuple<string, float>>> edges, string source, map<string, float> & dist, map<string, string> &prev)
{
	// initialize the distances to "infinity"
	for (string v : vertices)
	{
		dist[v] = INFINITY;
		prev[v] = "";
	}
	dist[source] = 0;

	// relax edges repeatedly
	for (int i = 0; i < vertices.size(); i++)
	{
		for (tuple<string, float> edge : edges[vertices[i]])
		{
			if (dist[vertices[i]] + get<1>(edge) < dist[get<0>(edge)])
			{
				dist[get<0>(edge)] = dist[vertices[i]] + get<1>(edge);
				prev[get<0>(edge)] = vertices[i];
			}
		}
	}

	// check for negative-weight cycles
	for (auto edges : edges) {
		for (auto edge : edges.second) {
			if (dist[get<0>(edge)] + get<1>(edge) < dist[edges.first]) {
				cout << "ERROR: Negative-weight cycle detected.\n";
				return;
			}
		}
	}
}

// test cases for Bellman-Ford
void bellmanFordTest(bool useNegWeightCycle) {
	vector<string> vertices = { "A", "B", "C", "D" };
	auto source = vertices[0];
	auto dist = map<string, float>();
	auto prev = map<string, string>();
	auto edges = map<string, vector<tuple<string, float>>>();
	if (useNegWeightCycle) {
		edges["A"] = vector<tuple<string, float>>() = { make_tuple("B", 1), make_tuple("C", 4), make_tuple("D", 8) };
		edges["B"] = vector<tuple<string, float>>() = { make_tuple("D", 6), make_tuple("D", -2) };
		edges["C"] = vector<tuple<string, float>>() = { make_tuple("D", 5), make_tuple("B", -4) };
		edges["D"] = vector<tuple<string, float>>() = { make_tuple("C", -3) };
	}
	else {
		edges["A"] = vector<tuple<string, float>>() = { make_tuple("B", 1), make_tuple("C", 4), make_tuple("D", 8) };
		edges["B"] = vector<tuple<string, float>>() = { make_tuple("D", 6) };
		edges["C"] = vector<tuple<string, float>>() = { make_tuple("D", 5) };
		edges["D"] = vector<tuple<string, float>>() = {};
	}

	bellmanFord(vertices, edges, source, dist, prev);

	cout << "-----Bellman-Ford Algorithm-----\n";
	cout << "Source: " << source << endl;
	cout << "Distances: " << endl;
	for (auto elem : dist) {
		cout << elem.first << ", " << elem.second << endl;
	}
	cout << "--------------------------------\n\n";
}

// Dijkstra's algorithm
void dijkstra(vector<string> vertices, map<string, vector<tuple<string, float>>> edges, string source, map<string, float> &dist, map<string, string> &prev) {
	// initialization
	for (string v : vertices) {
		dist[v] = INFINITY;
		prev[v] = "";
	}

	// create priority queue, push source, set source distance to 0
	priority_queue<string> Q;
	Q.push(source);
	dist[source] = 0;

	// relaxation
	while (!Q.empty()) {
		// pop
		string u = Q.top();
		Q.pop();

		// for each edge(u, v), relax
		for (tuple<string, float> edge : edges[u]) {
			float alt = dist[u] + get<1>(edge);

			if (alt < dist[get<0>(edge)]) {
				dist[get<0>(edge)] = alt;
				prev[get<0>(edge)] = u;
				Q.push(get<0>(edge));
			}
		}
	}
}

// test case for Dijkstra's
void dijkstraTest() {
	vector<string> vertices = { "A", "B", "C", "D" };
	auto dist = map<string, float>();
	auto prev = map<string, string>();
	auto edges = map<string, vector<tuple<string, float>>>();
	edges["A"] = vector<tuple<string, float>>() = { make_tuple("B", 1), make_tuple("C", 4), make_tuple("D", 8) };
	edges["B"] = vector<tuple<string, float>>() = { make_tuple("D", 6) };
	edges["C"] = vector<tuple<string, float>>() = { make_tuple("D", 5) };
	edges["D"] = vector<tuple<string, float>>() = {};
	auto source = vertices[0];

	dijkstra(vertices, edges, source, dist, prev);

	cout << "-----Dijkstra's Algorithm-----\n";
	cout << "Source: " << source << endl;
	cout << "Distances: " << endl;
	for (auto elem : dist) {
		cout << elem.first << ", " << elem.second << endl;
	}
	cout << "------------------------------\n\n";
}

void main() {
	dijkstraTest();
	bellmanFordTest(false);
}