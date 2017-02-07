#include <iostream>
#include <fstream>
#include "minheap.cpp"
#include <queue>
#include "node.h"
#include <cmath>

using namespace std;

int main(){

	std::cout<<"Yo World!"<<std::endl;

	ifstream maze;

	maze.open ("bigmaze.txt");


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
	maze1.open ("bigmaze.txt");

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

	char single;

	for(int x = 0; x < i; x++){
		for(int y = 0; y < j; y++){

			maze1.get(single);
			if(x==(i-1) && y==(j-1))
				single = '\n';
			cout<<single;
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

		}


	}



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
	int w;
	int u;
	start.x=m;
	start.y=n;
	start.pathcost = 0;

	int size = 0;

	start.hfunc = abs(start.x-a) + abs(start.y-b); //hfunc same as greedy for beginning because there has been no expansion
	greedy.Insert(start);



	while(greedy._vector.empty()!=1){

		inloop = greedy.GetMin();
		greedy.DeleteMin();

		size = size + 1;

		visited[inloop.y][inloop.x] = true;



		if( inloop.x!=1 && !visited[inloop.y][inloop.x-1]){		//if not wall or visited

			if(arr_maze[inloop.y][inloop.x-1]==0){

				node up;		//new node


				up.x = inloop.x-1;		
				up.y = inloop.y;
				up.pathcost = inloop.pathcost + 1;	//increase pathcost

				up.hfunc = abs(up.x-a)+(up.y-b) + up.pathcost;		//calculate hfunc by adding hueristic and pathcost for new node


								visited[up.y][up.x] = true;		//set as visited

				greedy.Insert(up);		//add to minheap
				//size = size + 1;

				path[up.y][up.x].y = inloop.y;
				path[up.y][up.x].x = inloop.x;


			}

			if(arr_maze[inloop.y][inloop.x-1]==3){		//if end then save and break
				w = inloop.y;	
				u = inloop.x;

				break;
			}

		}


		if( inloop.x!=(i-1) && !visited[inloop.y][inloop.x+1]){ //same as above but for node 1 below

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


		if( inloop.y!=1 && !visited[inloop.y-1][inloop.x]){			//same as above but for node to the left

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


		if( inloop.y!=(j-2) && !visited[inloop.y+1][inloop.x]){		//same as above but for node 1 to the right

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



	//cout<<w<<" "<<u<<" "<<endl;
	//cout<<path[w][u].y<<" "<<path[w][u].x<<" "<<endl;

	int d;
	while(1){
		
			arr_maze[w][u] = 3;					//set node before end node as a 3
			//cout<<arr_maze[w][u]<<endl;

			d = w;				//follow solution path recorded in the node array path to backtrace solution
			w = path[w][u].y;
			u = path[d][u].x;
			

			if(path[w][u].y==-1)			//when path==-1 beginning is found and backtracing in complete and break from loop
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





