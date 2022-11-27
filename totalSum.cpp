#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>


int main(){

	int fd[2];
	int N;
	int M;
	std::cout<<"inpute N ";
	std::cin>>N;
	std::vector<int>vec(N);

	for(int i = 0; i < N; i++){

            vec[i] = (rand() % 10) + 1;
            std::cout<<vec[i]<<" ";
 
	}

	std::cout<<"Number of parallel workers ";
	std::cin>>M;
	std::vector<pid_t> pids(M);

	if(pipe(fd) == -1){
		std::cout<<"ERROR";
	}

	for(int i = 0; i < M; i++){
  
	   pids[i] = fork();
	   if(pids[i] == 0){
	if ( close(fd[0]) == -1){
		
		std::cout<<"ERROR";
	}
		   int subTotalValueOfChild = 0;


	   for(int j = i * N/M; j < (i) * N/M; j++){


		   subTotalValueOfChild += vec[j];

	   }

	   std::cout<<"Sub-total value of child "  <<  subTotalValueOfChild << std::endl;
	   write(fd[1], &subTotalValueOfChild, sizeof(subTotalValueOfChild));
	   if(close(fd[1]) == -1){
		   std::cout<<"ERROR";
	   }
		   exit(0);


	   }
	}


	
	int totalSummary = 0;
	for(int i = 0; i < M; i++){
		int status;
		wait(&status);
		int num;
		read(fd[0], &num, sizeof(num));
		totalSummary += num;
	}

        

	std::cout<<"Total summary is"<< totalSummary <<std::endl;

}




