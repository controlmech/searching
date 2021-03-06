// AdjacencyList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <stack>
#include <string>
#include <iostream>

int index2;
bool goal = false;

struct Node {
	bool visited = false;
	std::vector<int> connectionIndex;
};

void PrintStack(std::stack<int> &stk) {
	if (stk.empty()) std::cout << "No path\n";
	else {
		std::string str = "";
		while (!stk.empty()) {
			str.insert(0, std::to_string(stk.top()) + " ");
			stk.pop();
		}
		std::cout << "Path : " << str << "\n";
	}
}

void DFS(std::vector<Node> &nodes, std::stack<int>& stk) {
	// End if full graph traversed or if goal is reached
	if (stk.empty() || stk.top() == index2) {
		PrintStack(stk);
		goal = true;
		return;
	}
	
	// Mark current node as visited
	nodes[stk.top()].visited = true;
	
	// Search for next node by checking all of the current node's connections
	for (size_t i = 0; i < nodes[stk.top()].connectionIndex.size(); ++i) {
		if (nodes[nodes[stk.top()].connectionIndex[i]].visited == false) {
			stk.push(nodes[stk.top()].connectionIndex[i]);
			DFS(nodes, stk); // Search at new node if found
		}
		if (goal)return;
	}

	// If no more new nodes are found from current node check previous node
	stk.pop();
	DFS(nodes, stk);	
}

int main()
{
	int index1, nodesAmt, edgesAmt;
	bool isDirected;

	std::cout << "undirected(0) or directed(1) graph :\n";
	std::cin >> isDirected;

	std::cout << "Enter amount of nodes and edges :\n";
	std::cin >> nodesAmt >> edgesAmt;
	std::vector<Node> nodes(nodesAmt);

	std::cout << "Enter edge values :\n";
	for (edgesAmt; edgesAmt --> 0;) {
		std::cin >> index1 >> index2;

		nodes[index1].connectionIndex.push_back(index2);
		if (!isDirected)
			nodes[index2].connectionIndex.push_back(index1); // Makes connection two-way for undirected graph
	}

	std::cout << "Enter starting and ending nodes :\n";
	std::cin >> index1 >> index2;

	std::stack<int> stk;
	stk.push(index1);

	DFS(nodes, stk);

	return 0;
}