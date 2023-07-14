#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Step cost
// 2 West
// 1 North
// 2 East
// 3 South
vector<int> cost = {2, 1, 2, 3};

string curS = "00";

int gi = 0, gj = 0;

void searchMaze(int &i, int&j, string sN, vector<vector<string>> maze) {
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
void printMaze(vector<vector<string>> maze) {
	for (int i = 0; i < maze.size(); i++) {
		for (int j = 0; j < maze[i].size(); j++) {
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// Function that takes in a string that represents a double digit that can lead with 0 and increments it 
// by 1 for example "00" would become "01"
string increment(string s) {
	stringstream ss;
	int i;
	ss << s;
	ss >> i;
	i++;
	ss.clear();
	ss << i;
	ss >> s;
	if (s.length() == 1) {
		s = "0" + s;
	}
	return s;
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

	void addChild(string sN, int f = 0, int g = 0, int h = 0, bool visited = false, vector<vector<string>> maze = {})
	{
		Step *t = new Step(sN, f, g, h, visited, this);
		t->heuristic(maze);
		this->child.push_back(t);
	}

	void heuristic(vector<vector<string>> maze) {
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
			searchMaze(pi, pj, this->parent->sN, maze);
		}
		searchMaze(ci, cj, this->sN, maze);
		if (this->parent != NULL) {
			// Calculate step cost and set g
			if (pi != ci) {
				if (ci - pi == 1) {
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
				if (cj - pj == 1) {
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

void sortSteps(vector<Step*> &steps) {
	// sort steps by f value and if a tie occurs sort by sN value
	Step *temp = NULL;
	for (int i = 0; i < steps.size(); i++) {
		for (int j = i + 1; j < steps.size(); j++) {
			if (steps[i]->f > steps[j]->f) {
				temp = steps[i];
				steps[i] = steps[j];
				steps[j] = temp;
			}
			else if (steps[i]->f == steps[j]->f) {
				if (steps[i]->sN > steps[j]->sN) {
					temp = steps[i];
					steps[i] = steps[j];
					steps[j] = temp;
				}
			}
		}
	}


}


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
vector<vector<string>> aStar(vector<vector<string>> m, Step *s, vector<Step *> fVals) {
	// Step 1 search around current node in the order of west, north, east, south
	int curI = 0, curJ = 0;
	searchMaze(curI, curJ, s->sN, m);
	// pop the front of fVals
	s->visited = true;
	fVals.erase(fVals.begin());
	// Step 1.1 check if the current node is the goal node
	if (curI == gi && curJ == gj) {
		// Step 1.1.1 if it is the goal node then return the maze
		printMaze(m);
		return m;
	}
	// Step 1.2 if it is not the goal node then add every "[]" value as a child to the current node
	if (curJ > 0 && m[curI][curJ - 1] == "[]"
	|| curJ > 0 && m[curI][curJ - 1] == "G") {
		// Add west child
		m[curI][curJ - 1] = curS;
		s->addChild(curS, 0, 0, 0, false, m);
		curS = increment(curS);
		// push this new child onto fVals
		fVals.push_back(s->child[s->child.size() - 1]);
	}
	if (curI > 0 && m[curI - 1][curJ] == "[]"
	|| curI > 0 && m[curI - 1][curJ] == "G") {
		// Add north child
		m[curI - 1][curJ] = curS;
		s->addChild(curS, 0, 0, 0, false, m);
		curS = increment(curS);
		fVals.push_back(s->child[s->child.size() - 1]);
	}
	if (curJ < m[0].size() - 1 && m[curI][curJ + 1] == "[]"
	|| curJ < m[0].size() - 1 && m[curI][curJ + 1] == "G") {
		// Add east child
		m[curI][curJ + 1] = curS;
		s->addChild(curS, 0, 0, 0, false, m);
		curS = increment(curS);
		fVals.push_back(s->child[s->child.size() - 1]);
	}
	if (curI < m.size() - 1 && m[curI + 1][curJ] == "[]"
	|| curI < m.size() - 1 && m[curI + 1][curJ] == "G") {
		// Add south child
		m[curI + 1][curJ] = curS;
		s->addChild(curS, 0, 0, 0, false, m);
		curS = increment(curS);
		fVals.push_back(s->child[s->child.size() - 1]);
	}
	sortSteps(fVals); // sort the fVals vector
	// Step 2 find the unvisited node with the lowest f value
	aStar(m, fVals[0], fVals);
    return m;
}


/* 
TO DO:
1) Implement aStar logic
2) Test
*/
int main() {
	vector<vector<string>> maze;
	int si = 0, sj = 0;
	vector<Step *> fVals;
    maze = initMaze(maze);
	searchMaze(gi, gj, "G", maze); // initialize global gi and gj
	searchMaze(si, sj, "S", maze); // initialize start point
	maze[si][sj] = curS;
	Step *root = new Step(curS);
	curS = increment(curS);
	root->heuristic(maze);
	fVals.push_back(root);
	sortSteps(fVals);
	aStar(maze, root, fVals);
    return 0;
}