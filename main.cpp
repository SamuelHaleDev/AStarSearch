#include <iostream>
#include <string>
#include <fstream>

using namespace std;


// Step cost
// 2 West
// 1 North
// 2 East
// 3 South
vector<int> cost = [2, 1, 2, 3];

/* Got the below tree code from this source
https://kalkicode.com/n-ary-tree-node-insertion-in-cpp
*/

class Step
{
	public: 
    string id;
    bool visited;
    int f;
    int g;
    int h;
	vector < Step *> child;

    /*
    id needs to be passed in
    f, g, and h should be passed in
    visited does not need to be passed 
    */

	Step(string id, int f = 0, int g = 0, int h = 0, bool visited = false)
    {
        this->id = id;
        this.f = f;
        this.g = g;
        this.h = h;
        this.visited = visited;
    }
	void addChild(int id)
	{
		Step *t = new Step(id);
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
		cout << "  " << node->key;
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
    vector<string> maze;
    maze = initMaze(maze);
    return 0;
}