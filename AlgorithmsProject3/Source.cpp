// Algorithms Project 3

#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

void dijkstra(list<string> vertices, map<string, vector<tuple<string, int>>> edges, string source, map<string, int> &dist, map<string, string> &prev) {
	// initialization
	for (string v : vertices) {
		dist[v] = INT_MAX;
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
		for (tuple<string, int> edge : edges[u]) {
			int alt = dist[u] + get<1>(edge);

			if (alt < dist[get<0>(edge)]) {
				dist[get<0>(edge)] = alt;
				prev[get<0>(edge)] = u;
				Q.push(get<0>(edge));
			}
		}
	}
}

void main() {
	/* TEST CASE FOR DIJKSTRA'S ALGORITHM
	list<string> vertices = { "A", "B", "C", "D" };
	auto dist = map<string, int>();
	auto prev = map<string, string>();

	auto edges = map<string, vector<tuple<string, int>>>();
	edges["A"] = vector<tuple<string, int>>() = { make_tuple("B", 1), make_tuple("C", 4), make_tuple("D", 8) };
	edges["B"] = vector<tuple<string, int>>() = { make_tuple("D", 6) };
	edges["C"] = vector<tuple<string, int>>() = { make_tuple("D", 5) };
	edges["D"] = vector<tuple<string, int>>() = { };

	dijkstra(vertices, edges, vertices.front(), dist, prev);
	*/
}