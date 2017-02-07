#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <iostream>
#include <fstream>
int main(){

for(int i = 0; i<10; i++){

	double k = rand()%10;
				k = k/10;

	std::cout<<k<<std::endl;

	}
}