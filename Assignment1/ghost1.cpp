#include <iostream>
#include <fstream>
#include "minheap1.cpp"
#include <queue>
#include "node.h"
#include <vector>
#include <cmath>

using namespace std;

int main(){

	std::cout<<"Yo World!"<<std::endl;

	ifstream maze;

	maze.open ("smallmaze3.txt");


	string firstline;

	getline(maze, firstline);

	int j = firstline.length();
	int i = 1;
	string line;

	while(!maze.eof()){
		getline(maze, line);
		i++;
	}

	j = j + 1;

	int m, n;

	ifstream maze1;
	maze1.open ("smallmaze3.txt");

	int arr_maze [j][i];
	node path [j][i];

	for(int x = 0; x < i; x++){
		for(int y = 0; y < j; y++){

				path[y][x].y = -1;
				path[y][x].x = -1;


		}
	}


	int a;
	int b;
	int ghost_spot;
	int pstartx;
	int pstarty;
	node path_node;

	char single;
	vector <node> ghost;
	int ghostzone = -1;

	for(int x = 0; x < i; x++){
		for(int y = 0; y < j; y++){

			maze1.get(single);
			if(x==(i-1) && y==(j-1))
				single = '\n';
			//cout<<single;
			if(single == '%')
				arr_maze[y][x] = 1;

			if(single == ' ')
				arr_maze[y][x] = 0;

			if(single == 'P'){
				arr_maze[y][x] = 2;
				n = y;
				m = x;
			}

			if(single == '.'){
				arr_maze[y][x] = 3;
				a = x;
				b = y;
			}
			if(single == '\n')
				arr_maze[y][x] = 4;

			if(single == 'g'){
				arr_maze[y][x] = 5;
				path_node.y = y;
				path_node.x = x;
				ghost.push_back(path_node);
				ghostzone = ghostzone + 1;
			}

			if(single == 'G'){
				arr_maze[y][x] = 6;
				pstarty = y;
				pstartx = x;
				path_node.y = y;
				path_node.x = x;
				ghost.push_back(path_node);
				ghostzone = ghostzone + 1;
				ghost_spot = ghostzone;
			}

		}


	}



	cout<<ghost.size()<<endl;
	cout<<ghost_spot<<endl;


	bool visited[j][i];
	for(int x = 0; x < i; x++){
		for(int y = 0; y < j; y++){
			visited[y][x] = false;
		}
	}

	MinHeap greedy;
	//Stack <node> route;

	node start;
	node inloop;
	int w = 0;
	int u = 0;
	start.x=m;
	start.y=n;
	start.pathcost = 0;

	node peek;

	bool direction_ghost = 1; //1 is right, 0 is left

	int size = 0;

	start.hfunc = abs(start.x-a) + abs(start.y-b);
	greedy.Insert(start);

				//cout<<w<<" "<<u<<" "<<endl;


	while(greedy._vector.empty()!=1){

		inloop = greedy.GetMin();
		greedy.DeleteMin();

		ghost.push_back(inloop);
		//cout<<inloop.y<<" "<<inloop.x<<" "<<endl;


		size = size + 1;

		visited[inloop.y][inloop.x] = true;

		if(direction_ghost){
				peek = ghost.at(ghost_spot);
				arr_maze[peek.y][peek.x] = 6;
				arr_maze[peek.y-1][peek.x] = 5;
				if(arr_maze[peek.x][peek.y+1]==1){
					direction_ghost = 0;
					cout<<direction_ghost<<endl;
					ghost_spot = ghost_spot - 1;
					}
				else
					ghost_spot = ghost_spot + 1;
		}

		else{

				peek = ghost.at(ghost_spot);
				arr_maze[peek.y][peek.x] = 6;
				arr_maze[peek.y+1][peek.x] = 5;
				if(arr_maze[peek.x][peek.y-1]==1){
					direction_ghost = 1;
										cout<<direction_ghost<<endl;

					ghost_spot = ghost_spot + 1;
					}
				else
					ghost_spot = ghost_spot - 1;

		}




		//if(arr_maze[pstarty][pstartx])



		if( inloop.x!=1 && !visited[inloop.y][inloop.x-1]){

			if(arr_maze[inloop.y][inloop.x-1]==0 || arr_maze[inloop.y][inloop.x-1]==5){

				node up;


				up.x = inloop.x-1;
				up.y = inloop.y;
				up.pathcost = inloop.pathcost + 1;

				up.hfunc = abs(up.x-a)+(up.y-b) + up.pathcost;


								visited[up.y][up.x] = true;

				greedy.Insert(up);
				//size = size + 1;

				path[up.y][up.x].y = inloop.y;
				path[up.y][up.x].x = inloop.x;


			}

			if(arr_maze[inloop.y][inloop.x-1]==3){
				w = inloop.y;
				u = inloop.x;

				break;
			}

		}


		if( inloop.x!=(i-1) && !visited[inloop.y][inloop.x+1]){

			if(arr_maze[inloop.y][inloop.x+1]==0){
				node up;
				up.x = inloop.x+1;
				up.y = inloop.y;
				up.pathcost = inloop.pathcost + 1;

				up.hfunc = abs(up.x-a)+(up.y-b) + up.pathcost;

								visited[up.y][up.x] = true;


				greedy.Insert(up);
				//size = size + 1;

				path[up.y][up.x].y = inloop.y;
				path[up.y][up.x].x = inloop.x;

			}

			if(arr_maze[inloop.y][inloop.x+1]==3){
				w = inloop.y;
				u = inloop.x;

				break;
			}

		}


		if( inloop.y!=1 && !visited[inloop.y-1][inloop.x]){

			if(arr_maze[inloop.y-1][inloop.x]==0){
				node up;
				up.x = inloop.x;
				up.y = inloop.y-1;
				up.pathcost = inloop.pathcost + 1;

				up.hfunc = abs(up.x-a)+(up.y-b) + up.pathcost;

												visited[up.y][up.x] = true;


				greedy.Insert(up);
				//size = size + 1;

				path[up.y][up.x].y = inloop.y;
				path[up.y][up.x].x = inloop.x;

			}



			if(arr_maze[inloop.y-1][inloop.x]==3){
				w = inloop.y;
				u = inloop.x;

				break;
				}
		}


		if( inloop.y!=(j-2) && !visited[inloop.y+1][inloop.x]){

			if(arr_maze[inloop.y+1][inloop.x]==0){
				node up;
				up.x = inloop.x;
				up.y = inloop.y+1;
				up.pathcost = inloop.pathcost + 1;

				up.hfunc = abs(up.x-a)+(up.y-b) + up.pathcost;

				visited[up.y][up.x] = true;


				greedy.Insert(up);
				//size = size + 1;

				path[up.y][up.x].y = inloop.y;
				path[up.y][up.x].x = inloop.x;

			}

			if(arr_maze[inloop.y+1][inloop.x]==3){
				w = inloop.y;
				u = inloop.x;

				break;
			}

		}

	}




	//cout<<inloop.pathcost<<endl;	
	//cout<<size<<endl;

	//cout<<w<<" "<<u<<" "<<endl;
	//cout<<path[w][u].y<<" "<<path[w][u].x<<" "<<endl;
 	
 	cout<<w<<" "<<u<<" "<<"hey"<<endl;


	int d;
	while(1){


			arr_maze[w][u] = 3;

			d = inloop.y;
			w = path[w][u].y;
			u = path[d][u].x;
			

			if(path[w][u].y==-1)
				break;

		
	}

		//arr_maze[35][34] = 3;
		//arr_maze[m][n]=2;

	for(int x = 0; x < i; x++){
		for(int y = 0; y < j; y++){

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

			if(arr_maze[y][x]==5){
				cout<<"g";

			}

			if(arr_maze[y][x]==6){
				cout<<"G";

			}

			
		}

	}

	





}





