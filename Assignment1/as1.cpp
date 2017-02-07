#include <iostream>
#include <fstream>
#include "stack.h"
#include "node.h"

using namespace std;


int main(){

	std::cout<<"Yo World!"<<std::endl; //Statement for checking how the program is working, also given this program uses
									   //the terminal for output this statement is helpful as a marker when the program is run again
	ifstream maze;

	maze.open ("bigmaze.txt");			// maze is opened


	string firstline;

	getline(maze, firstline);		//get first line

	int j = firstline.length();		//find width of maze
	int i = 1;
	string line;

	while(!maze.eof()){
		getline(maze, line);		//finds height of maze
		i++;
	}

	j = j + 1;			//adds one to the width of maze to include end line character	

	int m, n;

	ifstream maze1;
	maze1.open ("bigmaze.txt");		//reopens the maze

	int arr_maze [j][i];		//creates array ints the size of the maze
	node path [j][i];			//creates an array of nodes for path tracking

	for(int x = 0; x < i; x++){
		for(int y = 0; y < j; y++){

				path[y][x].y = -1;		//sets all the nodes to root to -1,-1, this means they are beginning of a path
				path[y][x].x = -1;


		}
	}




	char single;			//sets a char

	for(int x = 0; x < i; x++){
		for(int y = 0; y < j; y++){

			maze1.get(single);			//get char from maze file

			if(x==(i-1) && y==(j-1))	//exception case for when the new line character isn't read
				single = '\n';
			cout<<single;				//prints char so that we know the maze has be properly indexed for searching
			if(single == '%')			//if walls set index in matrix to 1
				arr_maze[y][x] = 1;

			if(single == ' ')			//if space set index in matrix to 0
				arr_maze[y][x] = 0;

			if(single == 'P'){			//if start set index in matrix to 1
				arr_maze[y][x] = 2;			
				n = y;					//save start point
				m = x;
			}

			if(single == '.')			//if end point set matrix to 3
				arr_maze[y][x] = 3;
			if(single == '\n')			//if endpoint is newline then set matrix to 4
				arr_maze[y][x] = 4;

		}


	}

		//cout<<arr_maze[0][0];
	bool visited[j][i];				//matrix of bool for visited
	for(int x = 0; x < i; x++){
		for(int y = 0; y < j; y++){
			visited[y][x] = false;		//set all to false
		}
	}

	Stack <node> dfs;			//set stack
	//Stack <node> route;

	node start;		//start node
	node inloop;	//loop currently being analyzed
	int w;
	int u;
	int size = 0;	//nodes expanded
	start.x=m;
	start.y=n;
	start.pathcost = 0;

	dfs.push(start);	//push node on stack

	while(!dfs.isEmpty()){

		inloop = dfs.pop();		//pop

		size = size + 1;		//increase number of nodes expanded

		visited[inloop.y][inloop.x] = true;		//set node as visited

		if( inloop.x!=1 && !visited[inloop.y][inloop.x-1]){			//look at node upwards if not wall or visited

			if(arr_maze[inloop.y][inloop.x-1]==0){				//if space
				node up;										//create new node
				up.x = inloop.x-1;								//set new node to up of current node
				up.y = inloop.y;
				up.pathcost = inloop.pathcost + 1;				//set pathcost of up node


				visited[up.y][up.x] = true;						// set up node as visited to prevent node from being pushed multiple times by
																//surrounding nodes
				dfs.push(up);

				path[up.y][up.x].y = inloop.y;					//set path of node up to have root at inloop node so path is traceable
				path[up.y][up.x].x = inloop.x;


			}

			if(arr_maze[inloop.y][inloop.x-1]==3){				//if the node being pushed is the end then save and break loop
				w = inloop.y;
				u = inloop.x;

				break;
			}

		}

		if( inloop.y!=(j-2) && !visited[inloop.y+1][inloop.x]){		//same exact process as above but checks node to the right

			if(arr_maze[inloop.y+1][inloop.x]==0){
				node up;
				up.x = inloop.x;
				up.y = inloop.y+1;
				up.pathcost = inloop.pathcost + 1;


				visited[up.y][up.x] = true;

				dfs.push(up);

				path[up.y][up.x].y = inloop.y;
				path[up.y][up.x].x = inloop.x;

			}

			if(arr_maze[inloop.y+1][inloop.x]==3){
				w = inloop.y;
				u = inloop.x;

				break;
			}

		}


		if( inloop.x!=(i-1) && !visited[inloop.y][inloop.x+1]){		//same exact process as above but checks node below

			if(arr_maze[inloop.y][inloop.x+1]==0){
				node up;
				up.x = inloop.x+1;
				up.y = inloop.y;
				up.pathcost = inloop.pathcost + 1;


				visited[up.y][up.x] = true;

				dfs.push(up);

				path[up.y][up.x].y = inloop.y;
				path[up.y][up.x].x = inloop.x;

			}

			if(arr_maze[inloop.y][inloop.x+1]==3){
				w = inloop.y;
				u = inloop.x;

				break;
			}

		}


		if( inloop.y!=1 && !visited[inloop.y-1][inloop.x]){		//same exact process as above but checks node to the left

			if(arr_maze[inloop.y-1][inloop.x]==0){
				node up;
				up.x = inloop.x;
				up.y = inloop.y-1;
				up.pathcost = inloop.pathcost + 1;

				visited[up.y][up.x] = true;

				dfs.push(up);

				path[up.y][up.x].y = inloop.y;
				path[up.y][up.x].x = inloop.x;

			}



			if(arr_maze[inloop.y-1][inloop.x]==3){
				w = inloop.y;
				u = inloop.x;

				break;
				}
		}




	}



	

	//cout<<w<<" "<<u<<" "<<endl;
	//cout<<path[w][u].y<<" "<<path[w][u].x<<" "<<endl;

	int d;
	while(1){		

			arr_maze[w][u] = 3;					//set node before end node as a 3
			//cout<<arr_maze[w][u]<<endl;

			d = w;								//follow solution path recorded in the node array path to backtrace solution
			w = path[w][u].y;
			u = path[d][u].x;
			

			if(path[w][u].y==-1)				//when path==-1 beginning is found and backtracing in complete and break from loop
				break;

		
	}

	cout<<"Pathcost: "<<inloop.pathcost<<endl;
	cout<<"Expansion: "<<size<<endl;			//print number of nodes expanded

		//arr_maze[35][34] = 3;
		//arr_maze[m][n]=2;

	for(int x = 0; x < i; x++){				//double for loop to print out solution
		for(int y = 0; y < j; y++){			//uses the numbers stored in arr_maze to print proper char

			if(arr_maze[y][x]==0){
				cout<<" ";

			}

			if(arr_maze[y][x]==1){
				cout<<"%";

			}

			if(arr_maze[y][x]==2){
				cout<<"P";

			}

			if(arr_maze[y][x]==3){
				cout<<".";

			}

			if(arr_maze[y][x]==4){
				cout<<"\n";

			}



			
		}

	}

	





}






