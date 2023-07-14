#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Step cost
// 2 West
// 1 North
// 2 East
// 3 South
vector<int> cost = {2, 1, 2, 3};

int gi = 0, gj = 0;

vector<vector<string>> maze;

void searchMaze(int &i, int&j, string sN) {
	for (i = 0; i < maze.size(); i++) {
		for (j = 0; j < maze[i].size(); j++) {
			if (maze[i][j] == sN) {
				return;
			}
			else continue;
		}
	}
}

// Function to print the maze
void printMaze() {
	for (int i = 0; i < maze.size(); i++) {
		for (int j = 0; j < maze[i].size(); j++) {
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
}


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
		t->heuristic();
		t->test_heuristic();
		this->child.push_back(t);
	}

	void heuristic() {
		int pi = 0;
		int pj = 0;
		int ci = 0;
		int cj = 0;
		int i = 0;
		int j = 0;
		// f = g + h
		// g = parents.g + step cost
		// h = manhattan distance
		
		/* CALCULATE G */
		// Find parent and childs index
		if (this->parent != NULL) {
			searchMaze(pi, pj, this->parent->sN);
		}
		searchMaze(ci, cj, this->sN);
		if (this->parent != NULL) {
			// Calculate step cost and set g
			if (pi != ci) {
				ci -= pi;
				if (ci == 1) {
					if (this->parent != NULL) {
						// Child is south
						this->g = this->parent->g + cost[3];
					}
					else this->g = cost[3];
				}
				else {
					if (this->parent != NULL) {
						// Child is north
						this->g = this->parent->g + cost[1];
					}
					else this->g = cost[1];
				}
			}
			if (pj != cj) {
				cj -= pj;
				if (cj == 1) {
					if (this->parent != NULL) {
						// Child is east
						this->g = this->parent->g + cost[2];
					}
					else this->g = cost[2];
				}
				else {
					if (this->parent != NULL) {
						// Child is west
						this->g = this->parent->g + cost[0];
					}
					else this->g = cost[0];
				}
			}
			/* END CALCULATE G */
		}
		/* CALCULATE H */
		i = ci - gi;
		j = cj - gj;
		// -i means gi is south
		// +i means gi is north
		// -j means gj is east
		// +j means gj is west
		// Using the step cost function where cost[0] is west, cost[1] is north, cost[2] is east, and cost[3] is south
		if (i < 0) {
			i *= -1;
			this->h = i * cost[3];
		}
		else this->h = i * cost[1];
		if (j < 0) {
			j *= -1;
			this->h += j * cost[2];
		}
		else this->h += j * cost[0];

		/* END CALCULATE H */
		this->f = this->g + this->h;
	}

	// write a function that will test the heuristic function
	void test_heuristic() {
		cout << "Testing heuristic function" << endl;
		if (this->parent != NULL) cout << "Parent: " << this->parent->sN << endl;
		cout << "Child: " << this->sN << endl;
		cout << "f: " << this->f << endl;
		cout << "g: " << this->g << endl;
		cout << "h: " << this->h << endl;
		cout << endl;
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



vector<vector<string>> initMaze(vector<vector<string>> m) {
	vector<string> temp = {};
	fstream f;
	f.open("maze.txt");
	// reading from files
	string input = "";
	while (getline(f, input)) {
		stringstream s(input); // throws input into the stream
		string symb = "";
		// Loop through the symbols on a line and push them onto temp vector
		while (s >> symb) {
			temp.push_back(symb);
		}
		// After a line has been looped through push the temp vector onto the maze 
		m.push_back(temp);
		temp = {};
	}
    return m;
}


/*
param {*} m: A vector of type strign that represents our maze
param {*} s: A vector of ADT Step that represent*/
vector<vector<string>> aStar(vector<vector<string>>& m, NAryTree *tree) {

    return m;
}


/* 
TO DO:
1) Implement aStar logic
2) Test
*/
int main() {
	int si = 0, sj = 0;
    NAryTree *tree = new NAryTree();
    maze = initMaze(maze);
	searchMaze(gi, gj, "G"); // initialize global gi and gj
	searchMaze(si, sj, "S"); // initialize start point
	maze[si][sj] = "00";
	Step *root = new Step("00");
	root->heuristic();
	delete tree;
    return 0;
}