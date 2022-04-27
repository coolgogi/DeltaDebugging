#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "../include/ddmin.h"
#include <time.h>

int
main (int argc, char * argv[]) {

    if (argc != 4) {
	fprintf(stderr, "invalid arguments\n") ;
	exit(EXIT_FAILURE) ;
    }

    int file_size = atoi(argv[1]) ;
    int n = atoi(argv[2]) ;
    double stddev = atof(argv[3]) ;

    srand(time(NULL)) ;
    double rand_num = (double) rand() / (double) RAND_MAX ;
    fprintf(stderr, "%lf\n", rand_num) ;

    int * len = split(file_size, n, stddev);
    int total = 0 ;
    for (int i = 0 ; i < n ; i ++) {
	printf("len[%d]: %d\n", i, len[i]) ;
    	total = total + len[i] ;
    }
    if (total == file_size) {
	printf("size correct\n") ;
    }
    printf("\n") ;
    free(len) ;

    return 0;

}
