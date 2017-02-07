
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <iostream>
#include <fstream>
#include <thread>
#include <unistd.h>


int main(){

srand(time(NULL));

double mean_q = 0;










for(double j = 1; j<25; j++){


	double lambda = j/100;
		double Queue = 1;

	for(int i = 1; i < 10000 ; i++){


		bool leave = true;

			while(leave){


				double s = rand()%10;
				s = s/10;

				double p = rand()%10;
				p = p/100;

				s = s + p;

				//std::cout<<s<<"BYE"<<std::endl;

				if(lambda>s){
					Queue++;

					leave = false;
				}

				double k = rand()%10;
				k = k/10;

				double q = rand()%10;
				q = q/100;

				double mu = k+q;

				//std::cout<<mu<<"HI"<<std::endl;


				if(.25>mu){
					if(Queue>0){
						Queue--;
					}
				}

				

			}



				
			mean_q = (mean_q*(i-1) + Queue)/i;


		}

		//std::cout<<m<<std::endl;

		std::cout<<mean_q/lambda<<std::endl;

		mean_q = 0;
	}

}