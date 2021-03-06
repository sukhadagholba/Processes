// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write 
// the three messages to the parent and have the parent print out 
// the messages. 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MSGSIZE 16

char* msg1 = "hello world #1";
char* msg2 = "hello world #2";
char* msg3 = "hello world #3";

int main(void)
{
    // Your code here
    // solution1
    /*char buffer[MSGSIZE];    
    int p[2]; 
    int pipe_var = pipe(p);

    int f = fork();    

    if (pipe_var < 0) {
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    if(f<0){
    	fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if(f==0){
   	write(p[1], msg1, MSGSIZE);
    	write(p[1], msg2, MSGSIZE);
    	write(p[1], msg3, MSGSIZE);
    }
    else{

    	for (int i = 0; i < 3; i++) {
        	read(p[0], buffer, MSGSIZE);
        	printf("%s\n", buffer);
    	}	    
    }
    return 0;*/

    //solution2
    int fd[2];
    char buffer[16];
    int p = pipe(fd);

    int pid = fork(); 
     
    if(p == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if(pid == -1){
      perror("fork");
      exit(EXIT_FAILURE);
    }
    else if(pid == 0){
      printf("Child writing messages to parent\n");
      write(fd[1], msg1, MSGSIZE);
      write(fd[1], msg2, MSGSIZE);
      write(fd[1], msg3, MSGSIZE);
    }
    else{

      for(int i=0; i<3; i++){
        read(fd[0], buffer, MSGSIZE);
        printf("%s\n", buffer);
      }

    }
    return 0;
}	
