#include "graph.h"
#include <math.h>
#include <queue>
#include <stack>


bool is_perfect_square(int n) {
	if (n < 0)
		return false;
	int root(round(sqrt(n)));
	return n == root * root;
}


graph::graph(int _size)
{
	d_size = _size;
	d_nodes = new Node[d_size];
	for (int i = 0; i < d_size; ++i) {
		d_nodes[i].name = i + 1;
		for (int j = 0; j < d_size; ++j) {
			if (is_perfect_square(i + j + 2)) {
				d_nodes[i].neighbors.push_back(&d_nodes[j]);
			}
		}
	}

}
/*graph::~graph()
{
	delete d_nodes;
}*/

bool graph::isConnected()
{
	bool* visted = new bool[d_size];
	for (int i = 0; i < d_size; ++i) 
		visted[i] = false;
	int componentsCount = 0;
	for (int v = 0; v < d_size; ++v) {
		if (!visted[v]) {
			++componentsCount;
			std::queue<int> q;
			q.push(v);
			visted[v] = true;
			while (!q.empty())
			{
				auto w = q.front();
				q.pop();
				for (auto neighbor : d_nodes[w].neighbors) {
					int k = neighbor->name - 1;
					if (!visted[k]) {
						visted[k] = true;
						q.push(k);
					}
				}
			}
		}
	}
	
	
	delete visted;
	return componentsCount == 1;
}

bool graph::hasCycle()
{
	if (!isConnected()) {
		return false;
	}
	//todo
	int v = 0;
	bool hasStart = false;
	for (int i = 0; i < d_size; ++i) {
		if (d_nodes[i].neighbors.size() == 1) {
			v = i;
			hasStart = true;
		}
	}


	bool* visted = new bool[d_size];
	for (int i = 0; i < d_size; ++i)
		visted[i] = false;
	std::queue<int>* queues = new std::queue<int>[d_size];
	std::stack<int> path;
	if (hasStart) {
		while (true) {
			if (!visted[v]) {
				path.push(v);
				visted[v] = true;
				if (path.size() == d_size)
				{
					return true;
				}
				for (auto neighbor : d_nodes[v].neighbors) {
					int k = neighbor->name - 1;
					if (!visted[k]) {
						queues[v].push(k);
					}
				}
			}
			if (queues[v].empty()) {
				path.pop();
				visted[v] = false;
				if (path.empty()) {
					return false;
				}
				else {
					v = path.top();
				}
			}
			else {
				int k = queues[v].front();
				queues[v].pop();
				v = k;
			}
		}
	}
	else {
		for (v = 0; v < d_size; ++v) {
			bool broke = false;
			while (true) {
				if (!visted[v]) {
					path.push(v);
					visted[v] = true;
					if (path.size() == d_size)
					{
						return true;
					}
					for (auto neighbor : d_nodes[v].neighbors) {
						int k = neighbor->name - 1;
						if (!visted[k]) {
							queues[v].push(k);
						}
					}
				}
				if (queues[v].empty()) {
					path.pop();
					visted[v] = false;
					if (path.empty()) {
						broke = false;
						break;
					}
					else {
						v = path.top();
					}
				}
				else {
					int k = queues[v].front();
					queues[v].pop();
					v = k;
				}
				if (broke) {
					break;
				}
			}
		}
	}
	return false;
}
