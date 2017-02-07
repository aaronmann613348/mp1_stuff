#include <iostream>
#include <fstream>
#include "minheap1.cpp"
#include <queue>
#include "node.h"
#include <cmath>

using namespace std;

int main(){

	std::cout<<"Yo World!"<<std::endl;

	ifstream maze;

	maze.open ("bigmaze2.txt");


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
	maze1.open ("bigmaze2.txt");

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
	int d;
	int size = 0;
	start.x=m;
	start.y=n;
	start.pathcost = 0;
	start.node = 0;

	start.hfunc = abs(start.x-a) + abs(start.y-b);
	greedy.Insert(start);

	while(greedy._vector.empty()!=1){

		inloop = greedy.GetMin();
		greedy.DeleteMin();

		size = size + 1;



		visited[inloop.y][inloop.x] = true;

	if( inloop.x!=(i-1) && !visited[inloop.y][inloop.x+1]){

			if(arr_maze[inloop.y][inloop.x+1]==0){
				node up;
				up.x = inloop.x+1;
				up.y = inloop.y;
				up.pathcost = inloop.pathcost + 1;
				up.node = inloop.node + 1;


				up.hfunc = abs(up.x-a)+abs(up.y-b) + up.pathcost;

				if(arr_maze[up.y][up.x+1]==1)			//checks for a wall and adds appropriate value
					up.hfunc = up.hfunc + 1;

				/*if(arr_maze[up.y+1][up.x]==1)
					up.hfunc = up.hfunc + 2;

				if(arr_maze[up.y-1][up.x]==1)
					up.hfunc = up.hfunc + 2;*/


				if(inloop.direction == 3)			//if the direction is same add 1 to the pathcost
					up.pathcost = up.pathcost + 1;

				up.direction = 3;				//set direction

				visited[up.y][up.x] = true;

				greedy.Insert(up);

				path[up.y][up.x].y = inloop.y;
				path[up.y][up.x].x = inloop.x;

			}

			if(arr_maze[inloop.y][inloop.x+1]==3){
				w = inloop.y;
				u = inloop.x;

				break;
			}

		}


		if( inloop.x!=1 && !visited[inloop.y][inloop.x-1]){

			if(arr_maze[inloop.y][inloop.x-1]==0){

				node up;


				up.x = inloop.x-1;
				up.y = inloop.y;
				up.pathcost = inloop.pathcost + 1;
				up.node = inloop.node + 1;

				

				up.direction = 1;			//set direction

				up.hfunc = abs(up.x-a)+abs(up.y-b) + up.pathcost;

				if(arr_maze[up.y][up.x-1]==1)		//checks for a wall and adds appropriate value
					up.hfunc = up.hfunc + 1;

				/*if(arr_maze[up.y+1][up.x]==1)
					up.hfunc = up.hfunc + 2;

				if(arr_maze[up.y-1][up.x]==1)
					up.hfunc = up.hfunc + 2;*/



				if(inloop.direction == 1)		//if the direction is same add 1 to the pathcost	
					up.pathcost = up.pathcost + 1;

				/*if(inloop.x==35 && inloop.y==35){

					cout<<up.y<<" "<<up.x<<" "<<endl;

				}*/

				visited[up.y][up.x] = true;

				greedy.Insert(up);

				path[up.y][up.x].y = inloop.y;
				path[up.y][up.x].x = inloop.x;


			}

			if(arr_maze[inloop.y][inloop.x-1]==3){
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
				up.node = inloop.node + 1;


				up.hfunc = abs(up.x-a)+abs(up.y-b) + up.pathcost;

				/*if(arr_maze[up.y][up.x-1]==1)
					up.hfunc = up.hfunc + 2;

				if(arr_maze[up.y][up.x+1]==1)
					up.hfunc = up.hfunc + 2;*/

				if(arr_maze[up.y-1][up.x]==1)			//checks for a wall and adds appropriate value
					up.hfunc = up.hfunc + 1;


				if(inloop.direction == 4)			//if the direction is same add 1 to the pathcost
					up.pathcost = up.pathcost + 1;

				up.direction = 4;			//set direction

				greedy.Insert(up);

				visited[up.y][up.x] = true;

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
				up.node = inloop.node + 1;


				if(inloop.direction == 2)			//if the direction is same add 1 to the pathcost
					up.pathcost = up.pathcost + 1;

				up.direction = 2;					//set direction

				up.hfunc = abs(up.x-a)+abs(up.y-b) + up.pathcost;

				//if(arr_maze[up.y][up.x-1]==1)
					//up.hfunc = up.hfunc + 2;

				if(arr_maze[up.y+1][up.x]==1)				//checks for a wall and adds appropriate value		
					up.hfunc = up.hfunc + 1;

				//if(arr_maze[up.y][up.x+1]==1)
					//up.hfunc = up.hfunc + 2;


				visited[up.y][up.x] = true;

				greedy.Insert(up);

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

	cout<<inloop.pathcost<<endl;	
	cout<<size<<endl;

	

	//cout<<w<<" "<<u<<" "<<endl;
	//cout<<path[w][u].y<<" "<<path[w][u].x<<" "<<endl;

	while(1){
		
			arr_maze[w][u] = 3;
			//cout<<arr_maze[w][u]<<endl;

			d = w;
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



			
		}

	}

	





}





