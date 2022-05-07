#include <stdio.h>
#include <stdlib.h>

int
main (int argc, char * argv[]) {

	int n = atoi(argv[1]) ;
	int total = 0 ;
	for (int i = 2 ; i < n ; i ++) {
		for (int j = 2 ; j <= i ; j ++ ) {
			total = total + 1 ;  
		}
	}
	printf("total: %d\n", total) ;
	return 0 ;

}
