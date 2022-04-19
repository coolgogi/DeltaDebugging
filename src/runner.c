#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include "../include/runner.h"


EXITCODE
runner (char * exec, char * input, char * output) {

	pid_t child_pid;
    	EXITCODE rt;

    	rt.valid = UNRESOLVED;

   	child_pid = fork();
	
    	if (child_pid < 0) {
        	rt.code_num = errno;
    	}
    	else if (child_pid == 0) {
		
	
		int fp[3] ;
		mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH ;
        	fp[0] = open(input, O_RDONLY);
		
		if (dup2(fp[0], STDIN_FILENO) == -1) {
			fprintf(stderr, "STDIN dup2 error in runner\n");
     		    	rt.code_num = errno;	
		    	exit(errno);
        	} 
		
		if (execl(exec, exec, input, 0x0) == -1) {	        
			perror("runner : ");
       		     	rt.code_num = errno;  
	            	exit(errno);  
		}
			
        	close(fp[0]);

	}
    	else {
        	pid_t w;
        	int status ;
        	time_t cur, start ;
        	cur = time(0);
       		start = time(0);

       		while (cur - start < 10) {
			w = waitpid(child_pid, &status, WNOHANG) ;
			if (w != 0)
				break ;
			cur = time(0) ;
	        }
	        if (cur - start >= 10) {
			kill(child_pid, SIGKILL);
        		w = waitpid(child_pid, &status, 0);
			rt.code_num = 9 ;
			return rt ;
		}
       
        	if (w == -1) {
            		perror("runner.c waitpid: ");
            		rt.code_num = errno;
            		return rt;
        	}

        	rt.code_num = WEXITSTATUS(status);
        	if (rt.code_num == EACCES) {
            		rt.valid = UNRESOLVED;
        	}
        	else if (rt.code_num == EBADF) {
            		rt.valid = UNRESOLVED;
        	}
        	else if (WIFEXITED(status)) {
            		rt.valid = VALID;
        	}
        	else {
            		rt.valid = INVALID;
        	}
		
    	}
	rt.child_pid = child_pid ;

    	return rt;
}
