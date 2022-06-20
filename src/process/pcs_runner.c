#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/param.h>
#include "../../include/runner.h"

#define BUFFER_SIZE 4096

int
find_answer_string (char * stderr_path, char * ans) {
        char buffer[BUFFER_SIZE + 1] ;
        memset(buffer, 0, BUFFER_SIZE + 1) ;
        FILE * stderr_file_ptr = fopen(stderr_path, "r") ;
        struct stat stderr_st ;
        stat(stderr_path, &stderr_st) ;

        int div = stderr_st.st_size / BUFFER_SIZE ;
        int mod = stderr_st.st_size % BUFFER_SIZE ;
        for (int i = 0 ; i < div ; i++) {
                if (fread(buffer, BUFFER_SIZE, 1, stderr_file_ptr) == 1) {
                        if (strstr(buffer, ans) != NULL) {
                                fclose(stderr_file_ptr) ;
                                return 1 ;
                        }
                }
        }
        if (fread(buffer, mod, 1, stderr_file_ptr) == 1) {
                if (strstr(buffer, ans) != NULL) {
                        fclose(stderr_file_ptr) ;
                        return 1 ;
                }
        }
        for (int i = 0 ; i < div ; i++) {
                int offset = BUFFER_SIZE * (i + 1) ;
                fseek(stderr_file_ptr, offset - strlen(ans), SEEK_SET) ;
                int len = MIN(strlen(ans) * 2, strlen(ans) + mod) ;
                if (fread(buffer, len, 1, stderr_file_ptr) == 1) {
                        if (strstr(buffer, ans) != NULL) {
                                fclose(stderr_file_ptr) ;
                                return 1 ;
                        }
                }
        }
        fclose(stderr_file_ptr) ;
        return 0 ;
}

int
pcs_runner (char * exec, char * input, char * stderr_path, char * ans) {

	pid_t child_pid;
    	EXITCODE rt;

    	rt.valid = UNRESOLVED;

   	child_pid = fork();
	
    	if (child_pid < 0) {
        	rt.code_num = errno;
    	}
    	else if (child_pid == 0) {
		int fp[3];
		mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
		fp[0] = open(input, O_RDONLY);
		fp[1] = open("stdout_file", O_WRONLY | O_CREAT, mode);
		fp[2] = open(stderr_path, O_WRONLY | O_CREAT, mode);
		if (dup2(fp[0], STDIN_FILENO) == -1) {
			fprintf(stderr, "STDIN dup2 error in runner\n");
   	      		rt.code_num = errno;	
	    		exit(errno);
       		}
		
		if (dup2(fp[1], STDOUT_FILENO) == -1 ) {
			fprintf(stderr, "STDOUT dup2 error in runner\n");
 	      		rt.code_num = errno;	
	    		exit(errno);
		}
			
		if (dup2(fp[2], STDERR_FILENO) == -1) {
            		fprintf(stderr, "STDERR dup2 error in runner\n");
            		rt.code_num = errno;
       			exit(errno);
       		}

		if (execl(exec, exec, input, 0x0) == -1) {	        
			perror("runner : ");
	      		rt.code_num = errno;  
		        exit(errno);  
		}
		close(fp[2]);
		close(fp[1]);	
        	close(fp[0]);

	}
    	else {
        	pid_t w;
        	int status;
        	time_t cur, start;
        	cur = time(0);
       		start = time(0);

       		while (cur - start < 10) {
			w = waitpid(child_pid, &status, WNOHANG);
			if (w != 0)
				break;
			cur = time(0);
	        }
	        if (cur - start >= 10) {
			kill(child_pid, SIGKILL);
	    	    	w = waitpid(child_pid, &status, 0);
			rt.code_num = SIGKILL;
			return 0 ;
		}
       
        	if (w == -1) {
           		perror("runner.c waitpid: ");
           		return 0 ;
        	}
    	}
	if (find_answer_string(stderr_path, ans) == 1) {
		return 1 ;
	}
	return 0 ;
}
