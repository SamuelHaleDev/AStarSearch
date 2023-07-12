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
1) Add the initialization logic for maze
2) Test init function
3) Add heuristic function utility
4) Implement aStar logic
5) Test
*/

int main() {
    NAryTree *tree = new NAryTree();
    vector<string> maze;
    maze = initMaze(maze);
	delete tree;
    return 0;
}