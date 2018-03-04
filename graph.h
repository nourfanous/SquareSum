#ifndef GRAPH
#define GRAPH
#include<vector>
struct graph
{
	struct Node
	{
		int name;
		std::vector<Node*> neighbors;
	};
	Node* d_nodes;
	int d_size;
	graph(int _size);
	//~graph();
	bool isConnected();
	bool hasCycle();
};


#endif // !GRAPH
