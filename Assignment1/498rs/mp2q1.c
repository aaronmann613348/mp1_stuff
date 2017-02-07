#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int queueLength;
    int jobBeingServiced;
} Server;

int main(){
	//initialize servers
	int N = 20;
    int numServers = 20;
    Server serverArr[numServers];
    for(int i = 0; i < numServers; i++){
    	serverArr[i].queueLength = 0;
    	serverArr[i].jobBeingServiced = 0;
    	//printf("server %d queue length: %d\n", i, serverArr[i].queueLength);
    }

    //initalize variables
	double lambda;
	int queueLength = 0;
	int jobBeingServiced = 0;

	double mu = .5;

	double queueLengthSum = 0.0;
	double queueLengthAvg = 0.0;
	int count = 0;
	double waitTime = 0.0;

	double lambdaArr[90];
	double waitTimeArr[90];

	srand(time(NULL));

	int histogram [250];

	for(int i = 0; i <250; i++){
		histogram[i] = 0;
	}

	//lamba loop
	for(lambda = .2; lambda < .35; lambda += .01){
		//time slot loop
		for(int i = 1; i < 10000; i++){
			//Arrivals with parameter N and lambda
			for(int i = 0; i < N; i++){
				int randnum = rand() % 100;
				if(randnum <= (int)(lambda*100)){
					//find shortest queue;
					int shortest = 0;
					for(int i = 0; i < numServers; i++){
					 	if(serverArr[i].queueLength < serverArr[shortest].queueLength){
					 		shortest = i;
					 	}
					}
					//update queue length of shortest
					serverArr[shortest].queueLength++;
				}
			}	
			
			//calculate departures or start servicing a job for each server
			for(int i = 0; i < numServers; i++){
				//check if server is idle, if it is start servicing a job
				if(serverArr[i].jobBeingServiced == 0 && serverArr[i].queueLength >= 1){
					serverArr[i].jobBeingServiced = 1;
					serverArr[i].queueLength -= 1;
				}
				//else check if there is a departure in that server
				else if(serverArr[i].jobBeingServiced == 1){
					int randnum = rand() % 100;
					if(randnum <= (int)(mu*100)){
						serverArr[i].jobBeingServiced = 0;
					}
				}
			}


			for(int i = 0; i < numServers; i++){
				if(serverArr[i].queueLength<250)
				histogram[serverArr[i].queueLength] = histogram[serverArr[i].queueLength] + 1;
			}


			for(int i = 0; i < numServers; i++){
				queueLengthSum += serverArr[i].queueLength;
				queueLengthSum /= numServers;
				queueLengthAvg = queueLengthSum/i;
			}

			waitTime = queueLengthAvg/lambda;
		}

		FILE *fp2;
		fp2=fopen("mp2q2.csv","w+");
		fprintf(fp,"delay, delayfraction");

		for(int i = 0; i < 250; i++){
			fprintf(fp,"\n%f,%f",i,histogram[i]);
		}

		fclose(fp2);
		printf("file created\n");



		lambdaArr[count] = lambda;
		waitTimeArr[count] = waitTime;
		count++;
	}

	/*for(int k = 0; k < 90; k++){
		printf("--------------------------------------------\n");
		printf("index: %d\n", k);
		printf("lambda: %f\n", lambdaArr[k]);
		printf("Average Wait Time: %f\n", waitTimeArr[k]);
	}*/

		
	FILE *fp;
	fp=fopen("mp2q1.csv","w+");
	fprintf(fp,"lambda, waitTime");

	for(int i = 0; i < 90; i++){
		fprintf(fp,"\n%f,%f",lambdaArr[i],waitTimeArr[i]);
	}

	fclose(fp);
	printf("file created\n");

	return 0;
}
