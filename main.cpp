#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


// Step cost
// 2 West
// 1 North
// 2 East
// 3 South
vector<int> cost = {2, 1, 2, 3};

/* Got the below tree code from this source
https://kalkicode.com/n-ary-tree-node-insertion-in-cpp
*/

class Step
{
	public: 
    string sN;
    bool visited;
    int f;
    int g;
    int h;
	vector < Step *> child;
	Step* parent;

    /*
    sN needs to be passed in
    f, g, and h should be passed in
    visited does not need to be passed 
    */

	Step(string sN, int f = 0, int g = 0, int h = 0, bool visited = false, Step* p = NULL)
    {
        this->sN = sN;
        this->f = f;
        this->g = g;
        this->h = h;
		this->parent = p;
        this->visited = visited;
    }
	void addChild(string sN, int f = 0, int g = 0, int h = 0, bool visited = false)
	{
		Step *t = new Step(sN, f, g, h, visited, this);
		this->child.push_back(t);
	}
};
class NAryTree
{
	public: 
    Step *root;
	NAryTree()
	{
		this->root = nullptr;
	}
	void printPreorder(Step *node)
	{
		if (node == nullptr)
		{
			return;
		}
		int i = 0;
		Step *temp = nullptr;
		cout << "  " << node->sN;
		// iterating the child of given node
		while (i < node->child.size())
		{
			temp = node->child.at(i);
			this->printPreorder(temp);
			i++;
		}
	}
};



// Example of Maze Below
/*
## 00 ## ## ## ## ## ## ## ## ## ##
## 01 02 [] [] ## [] [] [] [] [] ##
## 03 ## ## [] ## [] ## ## ## [] ##
## [] ## [] [] ## [] [] [] ## [] []
## [] ## ## ## ## ## ## [] ## ## ##
## [] [] ## [] [] [] ## [] [] [] ##
## ## [] ## [] ## ## ## [] ## [] ##
## [] [] [] [] ## [] [] [] ## [] ##
## [] ## ## ## ## [] ## [] ## ## ##
## [] [] [] [] [] [] ## [] [] [] ##
## ## ## ## ## ## ## ## ## ## ## ##
*/
vector<string> initMaze(vector<string> m) {

    return m;
}

/*
param {*} m: A vector of type strign that represents our maze
param {*} s: A vector of ADT Step that represent*/
vector<string> aStar(vector<string> m) {

    return m;
}

/* 
TO DO:
1) Add methods to go up and down tree nodes
2) Test that functionality
3) Add the initialization logic for maze
4) Test init function
5) Add heuristic function utility
6) Implement aStar logic
7) Test
*/

int main() {
    NAryTree *tree = new NAryTree();
	std::cout << "Hello my name is ";
	string x = "Hello my name is sam";
	cout << x;
	/* TEST NODE CREATION */
	// Create root node
	// Create 3 children with initialized nodes
	Step r("00");
	cout << r.sN;
	tree->root = &r;
	r.addChild("01");
	r.addChild("02");
	r.addChild("03");

	tree->printPreorder(tree->root);
	tree->printPreorder(&r);

    vector<string> maze;
    maze = initMaze(maze);
	delete tree;
    return 0;
}