// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
using namespace std;
#define FORWARD 0
#define TURN 1
#define MOVE_RIGHT 1
#define MOVE_LEFT 0

struct Node {
	int x;
	int y;
	double hValue;
	double pathCost;
	int facing; //0 for up; 1 for right; 2 for down; 3 for left
	int isGhost; //1 for ghost; 0 for ghost path

	bool operator==(const Node &other) const
	{
		return (x == other.x
			&& y == other.y);
	}
};

struct LessThanByDist
{
	bool operator()(const Node& lhs, const Node& rhs) const
	{
		return lhs.hValue > rhs.hValue; //This is min value first
	}
};

namespace std {

	template <>
	struct hash<Node>
	{
		std::size_t operator()(const Node& k) const
		{
			using std::size_t;
			using std::hash;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<int>()(k.x)
				^ (hash<int>()(k.y) << 3)) >> 1);
				
		}
	};

}

class CompareHeuristic {
public:
	bool operator()(Node& n1, Node& n2) // Returns true if t1 is earlier than t2
	{
		if (n1.hValue < n2.hValue) return true;
		return false;
	}
};

int getMazeInfo(char c) {
	if (c == ' ')
		return 0;
	if (c == '%')
		return 1;
	if (c == 'P')
		return 2;
	if (c == '.')
		return 3;
	if (c == 'G')
		return 4;
	if (c == 'g')
		return 5;
	return -1;
}

char getTextInfo(int i) {
	if (i == 0)
		return ' ';
	if (i == 1)
		return '%';
	if (i == 2)
		return 'P';
	if (i == 3)
		return '.';
	if (i == 4)
		return 'G';
	if (i == 5)
		return 'g';
	return -1;
}

bool isSpace(vector<vector<int> > maze, Node p) {
	if (maze[p.x][p.y] == 0 || maze[p.x][p.y] == 3 || maze[p.x][p.y] == 4 || maze[p.x][p.y] == 5)
		return true;
	return false;
}

void updateOutputMaze(vector<vector<int>> &maze) {
	ofstream myfile;
	myfile.open("output.txt");
	for (vector<int> w : maze) {
		for (auto ind : w) {
			myfile << getTextInfo(ind);
		}
		myfile << endl;
	}
	myfile.close();
}


void AStarF2T1(vector<vector<int> > &maze, Node player, Node goal) {
	const int costTurn = 1;
	const int costForward = 2;

	priority_queue<Node, vector<Node>, LessThanByDist> frontier;
	unordered_map<Node, Node> mazePath;
	unordered_map<Node, int> visited;
	player.facing = 0;
	player.hValue = abs(player.x - goal.x) + abs(player.y - goal.y);
	player.pathCost = 0;
	frontier.push(player);
	visited.emplace(player, 1);
	Node parent = { -1,-1,-1 };
	int pathCount = 0;
	int nodeExpanded = 0;
	bool found = false;

	while (!frontier.empty()) {
		Node p = frontier.top();
		frontier.pop();

		if (p.x == goal.x && p.y == goal.y) {
			found = true;
			break;
		}

		parent = p;
		nodeExpanded++;

		Node up = { p.x - 1, p.y, -1 };
		if (isSpace(maze, up) && visited.find(up) == visited.end()) {
			up.hValue = p.pathCost + abs(up.x - goal.x) + abs(up.y - goal.y);

			switch (p.facing)
			{
			case 0:
				up.pathCost = p.pathCost + costForward;
				break;
			case 1:
				up.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 2:
				up.pathCost = p.pathCost + 2* costTurn + costForward;
				break;
			default:
				up.pathCost = p.pathCost + costTurn + costForward;
			}
			up.facing = 0;

			frontier.push(up);
			mazePath.emplace(up, p);
			visited.emplace(up, 1);
		}

		Node down = { p.x + 1, p.y, -1 };
		if (isSpace(maze, down) && visited.find(down) == visited.end()) {
			down.hValue = p.pathCost + abs(down.x - goal.x) + abs(down.y - goal.y);

			switch (p.facing)
			{
			case 0:
				down.pathCost = p.pathCost + 2 * costTurn + costForward;
				break;
			case 1:
				down.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 2:
				down.pathCost = p.pathCost + costForward;
				break;
			default:
				down.pathCost = p.pathCost + costTurn + costForward;
			}
			down.facing = 2;

			frontier.push(down);
			mazePath.emplace(down, p);
			visited.emplace(down, 1);
		}

		Node left = { p.x , p.y - 1, -1 };
		if (isSpace(maze, left) && visited.find(left) == visited.end()) {
			left.hValue = p.pathCost + abs(left.x - goal.x) + abs(left.y - goal.y);

			switch (p.facing)
			{
			case 0:
				left.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 1:
				left.pathCost = p.pathCost + 2*costTurn + costForward;
				break;
			case 2:
				left.pathCost = p.pathCost + costTurn+ costForward;
				break;
			default:
				left.pathCost = p.pathCost + costForward;
			}
			left.facing = 3;

			frontier.push(left);
			mazePath.emplace(left, p);
			visited.emplace(left, 1);
		}

		Node right = { p.x , p.y + 1, -1 };
		if (isSpace(maze, right) && visited.find(right) == visited.end()) {
			right.hValue = p.pathCost + abs(right.x - goal.x) + abs(right.y - goal.y);
			right.pathCost = p.pathCost + costTurn + costForward;

			switch (p.facing)
			{
			case 0:
				right.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 1:
				right.pathCost = p.pathCost + costForward;
				break;
			case 2:
				right.pathCost = p.pathCost + costTurn + costForward;
				break;
			default:
				right.pathCost = p.pathCost + 2 * costTurn + costForward;
			}
			right.facing = 1;

			frontier.push(right);
			mazePath.emplace(right, p);
			visited.emplace(right, 1);
		}
	}

	Node p = mazePath[goal];
	pathCount++;

	while (p.x != player.x || p.y != player.y) {
		maze[p.x][p.y] = 3;
		pathCount++;
		p = mazePath[p];
	}

	cout << "pathcount " << pathCount << endl;
	cout << "#node expanded is " << nodeExpanded << endl;
}

void AStarF1T2(vector<vector<int> > &maze, Node player, Node goal) {
	const int costTurn = 2;
	const int costForward = 1;

	priority_queue<Node, vector<Node>, LessThanByDist> frontier;
	unordered_map<Node, Node> mazePath;
	unordered_map<Node, int> visited;
	player.facing = 0;
	player.hValue = abs(player.x - goal.x) + abs(player.y - goal.y);
	player.pathCost = 0;
	frontier.push(player);
	visited.emplace(player, 1);
	Node parent = { -1,-1,-1 };
	int pathCount = 0;
	int nodeExpanded = 0;
	bool found = false;

	while (!frontier.empty()) {
		Node p = frontier.top();
		frontier.pop();
	
		if (p.x == goal.x && p.y == goal.y) {
			found = true;
			break;
		}

		parent = p;
		nodeExpanded++;

		Node up = { p.x - 1, p.y, -1 };
		if (isSpace(maze, up) && visited.find(up) == visited.end()) {
			up.hValue = p.pathCost + abs(up.x - goal.x) + abs(up.y - goal.y);

			switch (p.facing)
			{
			case 0:
				up.pathCost = p.pathCost + costForward;
				break;
			case 1:
				up.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 2:
				up.pathCost = p.pathCost + 2 * costTurn + costForward;
				break;
			default:
				up.pathCost = p.pathCost + costTurn + costForward;
			}
			up.facing = 0;

			frontier.push(up);
			mazePath.emplace(up, p);
			visited.emplace(up, 1);
		}

		Node down = { p.x + 1, p.y, -1 };
		if (isSpace(maze, down) && visited.find(down) == visited.end()) {
			down.hValue = p.pathCost + abs(down.x - goal.x) + abs(down.y - goal.y);

			switch (p.facing)
			{
			case 0:
				down.pathCost = p.pathCost + 2 * costTurn + costForward;
				break;
			case 1:
				down.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 2:
				down.pathCost = p.pathCost + costForward;
				break;
			default:
				down.pathCost = p.pathCost + costTurn + costForward;
			}
			down.facing = 2;

			frontier.push(down);
			mazePath.emplace(down, p);
			visited.emplace(down, 1);
		}

		Node left = { p.x , p.y - 1, -1 };
		if (isSpace(maze, left) && visited.find(left) == visited.end()) {
			left.hValue = p.pathCost + abs(left.x - goal.x) + abs(left.y - goal.y);

			switch (p.facing)
			{
			case 0:
				left.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 1:
				left.pathCost = p.pathCost + 2 * costTurn + costForward;
				break;
			case 2:
				left.pathCost = p.pathCost + costTurn + costForward;
				break;
			default:
				left.pathCost = p.pathCost + costForward;
			}
			left.facing = 3;

			frontier.push(left);
			mazePath.emplace(left, p);
			visited.emplace(left, 1);
		}

		Node right = { p.x , p.y + 1, -1 };
		if (isSpace(maze, right) && visited.find(right) == visited.end()) {
			right.hValue = p.pathCost + abs(right.x - goal.x) + abs(right.y - goal.y);

			switch (p.facing)
			{
			case 0:
				right.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 1:
				right.pathCost = p.pathCost + costForward;
				break;
			case 2:
				right.pathCost = p.pathCost + costTurn + costForward;
				break;
			default:
				right.pathCost = p.pathCost + 2 * costTurn + costForward;
			}
			right.facing = 1;

			frontier.push(right);
			mazePath.emplace(right, p);
			visited.emplace(right, 1);
		}
	}

	Node p = mazePath[goal];
	pathCount++;

	while (p.x != player.x || p.y != player.y) {
		maze[p.x][p.y] = 3;
		pathCount++;
		p = mazePath[p];
	}

	cout << "pathcount " << pathCount << endl;
	cout << "#node expanded is " << nodeExpanded << endl;
}


/*
condition 0 : prefer forward
condition 1 : prefer turn
*/
double getHValue(vector<vector<int> > &maze, Node node, Node goal) { 
	
	int curX = node.x;
	int curY = node.y;
	
	if (node.x == goal.x || node.y == goal.y)
		return 0;
	return abs(node.x - goal.x) + abs(node.y - goal.y);
}

void AStarF2T1BetterHeuristic(vector<vector<int> > &maze, Node player, Node goal) {
	const int costTurn = 1;
	const int costForward = 2;

	priority_queue<Node, vector<Node>, LessThanByDist> frontier;
	unordered_map<Node, Node> mazePath;
	unordered_map<Node, int> visited;
	player.facing = 0;
	player.hValue = abs(player.x - goal.x) + abs(player.y - goal.y);
	player.pathCost = 0;
	frontier.push(player);
	visited.emplace(player, 1);
	Node parent = { -1,-1,-1 };
	int pathCount = 0;
	int nodeExpanded = 0;
	bool found = false;

	while (!frontier.empty()) {
		Node p = frontier.top();
		frontier.pop();

		if (p.x == goal.x && p.y == goal.y) {
			found = true;
			break;
		}

		parent = p;
		nodeExpanded++;

		Node up = { p.x - 1, p.y, -1 };
		if (isSpace(maze, up) && visited.find(up) == visited.end()) {
			up.facing = 0;
			up.hValue = 0.25*p.pathCost + abs(up.x - goal.x) + abs(up.y - goal.y);
			switch (p.facing)
			{
			case 0:
				up.pathCost = p.pathCost + costForward;
				break;
			case 1:
				up.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 2:
				up.pathCost = p.pathCost + 2 * costTurn + costForward;
				break;
			default:
				up.pathCost = p.pathCost + costTurn + costForward;
			}

			frontier.push(up);
			mazePath.emplace(up, p);
			visited.emplace(up, 1);
		}

		Node down = { p.x + 1, p.y, -1 };
		if (isSpace(maze, down) && visited.find(down) == visited.end()) {
			down.facing = 2;
			down.hValue = 0.25*p.pathCost + abs(down.x - goal.x) + abs(down.y - goal.y);

			switch (p.facing)
			{
			case 0:
				down.pathCost = p.pathCost + 2 * costTurn + costForward;
				break;
			case 1:
				down.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 2:
				down.pathCost = p.pathCost + costForward;
				break;
			default:
				down.pathCost = p.pathCost + costTurn + costForward;
			}

			frontier.push(down);
			mazePath.emplace(down, p);
			visited.emplace(down, 1);
		}

		Node left = { p.x , p.y - 1, -1 };
		if (isSpace(maze, left) && visited.find(left) == visited.end()) {
			left.facing = 3;
			left.hValue = 0.25*p.pathCost + abs(left.x - goal.x) + abs(left.y - goal.y);

			switch (p.facing)
			{
			case 0:
				left.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 1:
				left.pathCost = p.pathCost + 2 * costTurn + costForward;
				break;
			case 2:
				left.pathCost = p.pathCost + costTurn + costForward;
				break;
			default:
				left.pathCost = p.pathCost + costForward;
			}

			frontier.push(left);
			mazePath.emplace(left, p);
			visited.emplace(left, 1);
		}

		Node right = { p.x , p.y + 1, -1 };
		if (isSpace(maze, right) && visited.find(right) == visited.end()) {
			right.facing = 1;
			right.hValue = p.pathCost + abs(right.x - goal.x) + abs(right.y - goal.y);
			right.pathCost = 0.25*p.pathCost + costTurn + costForward;
			switch (p.facing)
			{
			case 0:
				right.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 1:
				right.pathCost = p.pathCost + costForward;
				break;
			case 2:
				right.pathCost = p.pathCost + costTurn + costForward;
				break;
			default:
				right.pathCost = p.pathCost + 2 * costTurn + costForward;
			}

			frontier.push(right);
			mazePath.emplace(right, p);
			visited.emplace(right, 1);
		}
	}

	Node p = mazePath[goal];
	pathCount++;

	while (p.x != player.x || p.y != player.y) {
		maze[p.x][p.y] = 3;
		pathCount++;
		p = mazePath[p];
	}

	cout << "pathcount " << pathCount << endl;
	cout << "#node expanded is " << nodeExpanded << endl;
}

void AStarF1T2BetterHeuristic(vector<vector<int> > &maze, Node player, Node goal) {
	const int costTurn = 2;
	const int costForward = 1;

	priority_queue<Node, vector<Node>, LessThanByDist> frontier;
	unordered_map<Node, Node> mazePath;
	unordered_map<Node, int> visited;
	player.facing = 0;
	player.hValue = getHValue(maze, player, goal);
	player.pathCost = 0;
	frontier.push(player);
	visited.emplace(player, 1);
	Node parent = { -1,-1,-1 };
	int pathCount = 0;
	int nodeExpanded = 0;
	bool found = false;

	while (!frontier.empty()) {
		Node p = frontier.top();
		frontier.pop();
	
		if (p.x == goal.x && p.y == goal.y) {
			found = true;
			break;
		}

		parent = p;
		nodeExpanded++;

		Node up = { p.x - 1, p.y, -1 };
		if (isSpace(maze, up) && visited.find(up) == visited.end()) {
			up.facing = 0;
			up.hValue = p.pathCost + getHValue(maze, up, goal);
			switch (p.facing)
			{
			case 0:
				up.pathCost = p.pathCost + costForward;
				break;
			case 1:
				up.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 2:
				up.pathCost = p.pathCost + 2 * costTurn + costForward;
				break;
			default:
				up.pathCost = p.pathCost + costTurn + costForward;
			}

			frontier.push(up);
			mazePath.emplace(up, p);
			visited.emplace(up, 1);
		}

		Node down = { p.x + 1, p.y, -1 };
		if (isSpace(maze, down) && visited.find(down) == visited.end()) {
			down.facing = 2;
			down.hValue = p.pathCost + getHValue(maze, down, goal);

			switch (p.facing)
			{
			case 0:
				down.pathCost = p.pathCost + 2 * costTurn + costForward;
				break;
			case 1:
				down.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 2:
				down.pathCost = p.pathCost + costForward;
				break;
			default:
				down.pathCost = p.pathCost + costTurn + costForward;
			}

			frontier.push(down);
			mazePath.emplace(down, p);
			visited.emplace(down, 1);
		}

		Node left = { p.x , p.y - 1, -1 };
		if (isSpace(maze, left) && visited.find(left) == visited.end()) {
			left.facing = 3;
			left.hValue = p.pathCost + getHValue(maze, left, goal);

			switch (p.facing)
			{
			case 0:
				left.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 1:
				left.pathCost = p.pathCost + 2 * costTurn + costForward;
				break;
			case 2:
				left.pathCost = p.pathCost + costTurn + costForward;
				break;
			default:
				left.pathCost = p.pathCost + costForward;
			}

			frontier.push(left);
			mazePath.emplace(left, p);
			visited.emplace(left, 1);
		}

		Node right = { p.x , p.y + 1, -1 };
		if (isSpace(maze, right) && visited.find(right) == visited.end()) {
			right.facing = 1;
			right.hValue = p.pathCost + getHValue(maze, right, goal);
			switch (p.facing)
			{
			case 0:
				right.pathCost = p.pathCost + costTurn + costForward;
				break;
			case 1:
				right.pathCost = p.pathCost + costForward;
				break;
			case 2:
				right.pathCost = p.pathCost + costTurn + costForward;
				break;
			default:
				right.pathCost = p.pathCost + 2 * costTurn + costForward;
			}

			frontier.push(right);
			mazePath.emplace(right, p);
			visited.emplace(right, 1);
		}
	}

	Node p = mazePath[goal];
	pathCount++;

	while (p.x != player.x || p.y != player.y) {
		maze[p.x][p.y] = 3;
		pathCount++;
		p = mazePath[p];
	}

	cout << "pathcount " << pathCount << endl;
	cout << "#node expanded is " << nodeExpanded << endl;
}


Node currentGhostPos(vector<Node> &ghostPath, int numSteps) {
	Node R; R.x = ghostPath[0].x; R.y = ghostPath[0].y;
	int round = 2 * (ghostPath.size() - 1);
	int i = 0;
	while (ghostPath[i].isGhost != 1) i++;

	int offset = (numSteps+i) % round;
	if (offset <= round / 2)
		R.y += offset;
	else
		R.y += round - offset;
		
	return R;
}

void moveGhostOnMap(vector<vector<int> > &maze, vector<Node> &ghostPath, int &currentGhostOffset, int &currentGhostDirection) {
	maze[ghostPath[currentGhostOffset].x][ghostPath[currentGhostOffset].y] = 5;

	if (currentGhostDirection == MOVE_RIGHT && currentGhostOffset == ghostPath.size() - 1) {
		currentGhostOffset--;
		currentGhostDirection = MOVE_LEFT;
	}
	else if (currentGhostDirection == MOVE_LEFT && currentGhostOffset == 0) {
		currentGhostOffset++;
		currentGhostDirection = MOVE_RIGHT;
	}
	else if (currentGhostDirection == MOVE_LEFT) {
		currentGhostOffset--;
	}
	else if (currentGhostDirection == MOVE_RIGHT) {
		currentGhostOffset++;
	}

	maze[ghostPath[currentGhostOffset].x][ghostPath[currentGhostOffset].y] = 4;

}

void AStarGhost(vector<vector<int> > &maze, Node player, Node goal, vector<vector<Node>> &ghostPath) {

	priority_queue<Node, vector<Node>, LessThanByDist> frontier;
	unordered_map<Node, Node> mazePath;
	unordered_map<Node, int> visited;
	player.hValue = abs(player.x - goal.x) + abs(player.y - goal.y);
	player.pathCost = 0;
	frontier.push(player);
	visited.emplace(player, 1);
	Node parent = { -1,-1,-1 };
	int nodeExpanded = 0;
	bool found = false;

	while (!frontier.empty()) {
		Node p = frontier.top();
		frontier.pop();

		if (p.x == goal.x && p.y == goal.y) {
			found = true;
			break;
		}

		parent = p;
		nodeExpanded++;

		Node up = { p.x - 1, p.y, -1 };
		if (isSpace(maze, up) && visited.find(up) == visited.end()) {
			up.hValue = p.pathCost + abs(up.x - goal.x) + abs(up.y - goal.y);
			up.pathCost = p.pathCost + 1;
			frontier.push(up);

			mazePath.emplace(up, p);
			visited.emplace(up, 1);
		}

		Node down = { p.x + 1, p.y, -1 };
		if (isSpace(maze, down) && visited.find(down) == visited.end()) {
			down.hValue = p.pathCost + abs(down.x - goal.x) + abs(down.y - goal.y);
			down.pathCost = p.pathCost + 1;
			frontier.push(down);
			mazePath.emplace(down, p);
			visited.emplace(down, 1);
		}

		Node left = { p.x , p.y - 1, -1 };
		if (isSpace(maze, left) && visited.find(left) == visited.end()) {
			left.hValue = p.pathCost + abs(left.x - goal.x) + abs(left.y - goal.y);
			left.pathCost = p.pathCost + 1;
			frontier.push(left);
			mazePath.emplace(left, p);
			visited.emplace(left, 1);
		}

		Node right = { p.x , p.y + 1, -1 };
		if (isSpace(maze, right) && visited.find(right) == visited.end()) {
			right.hValue = p.pathCost + abs(right.x - goal.x) + abs(right.y - goal.y);
			right.pathCost = p.pathCost + 1;
			frontier.push(right);
			mazePath.emplace(right, p);
			visited.emplace(right, 1);
		}
	}

	int pathCount = 0;
	int pathToGhost = 0;
	int pathToGhost1 = 0;
	vector<Node> vGhost;
	vector<Node> vGhost1;

	//Params for ghost1
	int enX=0;
	int enY=0;
	int prev_enX;
	int prev_enY;
	bool previousIsGhost = false;
	bool previousIsEn = false;
	bool encountered = false;
	int stalltime = 0;

	//Params for ghost2
	int enX1 = 0;
	int enY1 = 0;
	int prev_enX1;
	int prev_enY1;
	bool previousIsGhost1 = false;
	bool previousIsEn1 = false;
	bool encountered1 = false;
	int stalltime1 = 0;


	Node p = mazePath[goal];
	pathCount++;
	unordered_map<Node, Node> mazePath_inorder;
	mazePath_inorder.emplace(p,goal);

	while (p.x != player.x || p.y != player.y) {
		if (maze[p.x][p.y] == 4 || maze[p.x][p.y] == 5) {
			if (p.x == ghostPath[0][0].x) {
				encountered = true;
				Node ghost;
				ghost.x = p.x;
				ghost.y = p.y;
				vGhost.emplace_back(ghost);
				previousIsGhost = true;
			}

			else if (p.x == ghostPath[1][0].x) {
				encountered1 = true;
				Node ghost1;
				ghost1.x = p.x;
				ghost1.y = p.y;
				vGhost1.emplace_back(ghost1);
				previousIsGhost1 = true;
			}
		}

		if (encountered) {
			if (previousIsGhost && maze[p.x][p.y] == 0) {
				previousIsGhost = false;
				previousIsEn = true;
				enX = p.x;
				enY = p.y;
			}
			else if (previousIsEn == true && maze[p.x][p.y] == 0) {
				previousIsEn = false;
				prev_enX = p.x;
				prev_enY = p.y;
			}
			pathToGhost++;
		} 

		if (encountered1) {
			if (previousIsGhost1 && maze[p.x][p.y] == 0) {
				previousIsGhost1 = false;
				previousIsEn1 = true;
				enX1 = p.x;
				enY1 = p.y;
			}
			else if (previousIsEn1 == true && maze[p.x][p.y] == 0) {
				previousIsEn1 = false;
				prev_enX1 = p.x;
				prev_enY1 = p.y;
			}
			pathToGhost1++;
		}

		//maze[p.x][p.y] = 3;
		pathCount++;
		Node nextp = mazePath[p];
		mazePath_inorder.emplace(nextp, p);
		p = nextp;
	}

	while (1) {
		bool canPass = true;
		for (int i = 0; i < vGhost1.size(); i++) {
			Node g = currentGhostPos(ghostPath[1], pathToGhost1 - i);
			Node gprev = currentGhostPos(ghostPath[1], pathToGhost1 - i - 1);
			if (g.x == vGhost1.at(i).x && g.y == vGhost1.at(i).y) {
				canPass = false;
				pathToGhost1 += 2;
				stalltime1++;
				break;
			}
			else if ((g.x == vGhost1.at(i).x && g.y - 1 == vGhost1.at(i).y && gprev.x == vGhost1.at(i).x && gprev.y == vGhost1.at(i).y)
				|| (g.x == vGhost1.at(i).x && g.y + 1 == vGhost1.at(i).y && gprev.x == vGhost1.at(i).x && gprev.y == vGhost1.at(i).y)) {
				if (i != vGhost1.size() - 1) {
					canPass = false;
					pathToGhost1 += 2;
					stalltime1++;
					break;
				}
			}
		}
		
		if (canPass)
			break;
	}
	pathToGhost += stalltime1*2;

	while (1) {
		bool canPass = true;
		for (int i = 0; i < vGhost.size(); i++) {
			Node g = currentGhostPos(ghostPath[0], pathToGhost - i);
			Node gprev = currentGhostPos(ghostPath[0], pathToGhost - i - 1);
			if (g.x == vGhost.at(i).x && g.y == vGhost.at(i).y) {
				canPass = false;
				pathToGhost += 2;
				stalltime++;
				break;
			}
			else if ((g.x == vGhost.at(i).x && g.y - 1 == vGhost.at(i).y && gprev.x == vGhost.at(i).x && gprev.y == vGhost.at(i).y)
				|| (g.x == vGhost.at(i).x && g.y + 1 == vGhost.at(i).y && gprev.x == vGhost.at(i).x && gprev.y == vGhost.at(i).y)) {
				if (i != vGhost.size() - 1) {
					canPass = false;
					pathToGhost += 2;
					stalltime++;
					break;
				}
			}
		}
		if(canPass)
			break;
	}

	
	//Animation starts
	int currentGhostOffset = 0;
	while (ghostPath[0][currentGhostOffset].isGhost != 1) currentGhostOffset++;
	int currentGhostDirection = MOVE_RIGHT;
	Node current = player;
	bool restore = false;

	int currentGhostOffset1 = 0;
	while (ghostPath[1][currentGhostOffset1].isGhost != 1) currentGhostOffset1++;
	int currentGhostDirection1 = MOVE_RIGHT;

	while (current.x != goal.x || current.y != goal.y) {
		Node next;
		if (stalltime > 0 && current.x == enX && current.y == enY) {
			next.x = prev_enX;
			next.y = prev_enY;
			stalltime--;
		}
		else if (stalltime1 > 0 && current.x == enX1 && current.y == enY1) {
			next.x = prev_enX1;
			next.y = prev_enY1;
			stalltime1--;
		}
		else {
			next = mazePath_inorder[current];
		}

		if (restore) {
			maze[current.x][current.y] = 5;
			restore = false;
		}
		else
			maze[current.x][current.y] = 0;

		if (maze[next.x][next.y] == 5 || maze[next.x][next.y] == 4)
			restore = true;


		current = next;
		moveGhostOnMap(maze, ghostPath[0], currentGhostOffset, currentGhostDirection);
		moveGhostOnMap(maze, ghostPath[1], currentGhostOffset1, currentGhostDirection1);
		maze[next.x][next.y] = 2;
		updateOutputMaze(maze);	
	}

	cout << "pathcount " << pathCount << endl;
	cout << "#node expanded is " << nodeExpanded << endl;
	return;
}


int main()
{
	ifstream inputMaze;
	inputMaze.open("bigGhost.txt");
	string line;
	vector<vector<int> > maze;
	Node player;
	Node goal;
	vector<vector<Node>> ghostPaths;

	//Initialize Maze
	while (!inputMaze.eof()) {
		getline(inputMaze, line);
		vector<int> v;
		vector<Node> ghostPath;
		
		for (int i = 0; i < line.size(); i++) {
			if (getMazeInfo(line[i]) == 2) {
				player.x = maze.size();
				player.y = i;
				player.hValue = -1;
			}
			else if (getMazeInfo(line[i]) == 3) {
				goal.x = maze.size();
				goal.y = i;
				goal.hValue = -1;
			}   
			else if (getMazeInfo(line[i]) == 4) {
				Node g;
				g.x = maze.size();
				g.y = i;
				g.isGhost = 1;
				ghostPath.emplace_back(g);
			}
			else if (getMazeInfo(line[i]) == 5) {
				Node g;
				g.x = maze.size();
				g.y = i;
				g.isGhost = 0;
				ghostPath.emplace_back(g);
			}
				
			v.emplace_back(getMazeInfo(line[i]));
		}
		if(ghostPath.size() > 0)
			ghostPaths.emplace_back(ghostPath);
		maze.emplace_back(v);
	}

	cout << "Maze search starts!" << endl;

	/***1.1***/
	//Depth First Search
	//DFS(maze, player, goal);
	
	//Breadth First Search
	//BFS(maze, player, goal);

	//Best First Search
	//GreedyBestSearch(maze, player, goal);

	//A*
	//AStar(maze, player, goal);

	/***1.2***/
	//AStarF2T1(maze, player, goal);
	//AStarF1T2(maze, player, goal);

	//AStarF2T1BetterHeuristic(maze, player, goal);
	//AStarF1T2BetterHeuristic(maze, player, goal);

	/***1.3***/
	AStarGhost(maze, player, goal, ghostPaths);

	cout << "Maze search finished." << endl;

	//Output the maze
	updateOutputMaze(maze);

    return 0;
}
