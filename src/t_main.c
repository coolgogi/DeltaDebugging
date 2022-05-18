#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/ddmin.h"
#include <unistd.h> 
#include <errno.h>

int
main (int argc, char * argv[]) {
	if (argc != 5) {
		fprintf(stderr, "invalid arguments\n") ;
		exit(EXIT_FAILURE) ;
	}
	
	if (access(argv[1], X_OK) == -1) {
                perror("main.c argv[1]: ");
                exit(errno);
	}

	if (access(argv[2], R_OK) == -1) {
                perror("main.c argv[2]: ");
                exit(errno);
        }
		
	if (access(argv[3], R_OK) == -1) {
                perror("main.c argv[3]: ");
                exit(errno);
        }

	time_t begin = time(NULL) ;
	int cnt = t_range(argv[1], argv[2], argv[3], argv[4]) ;
	time_t end = time(NULL) ;
	fprintf(stderr, "executing time: %ld\ncnt: %d\n", end - begin, cnt) ;
	return 0 ;

}
