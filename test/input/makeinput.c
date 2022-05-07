#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


int
main (int argc, char * argv[]) {
	
	FILE * origin_file = fopen(argv[1], "r") ;
	char * path ;
	if (argc > 2) {
		path = argv[2] ;
	}
	else {
		fprintf(stderr, "invalid input\n") ;
	}
	struct stat st ;
	stat(argv[1], &st) ;
	int n = st.st_size ; 
	char * file_name = (char *) malloc (100) ;
	
	for (int i = 0 ; i < n ; i ++ ) {
		sprintf(file_name, "%s%d", path, i) ;
		FILE * write_file = fopen(file_name , "w+") ;
		
		fseek(origin_file, 0, SEEK_SET) ;
		unsigned char * buf = (unsigned char *) malloc (i+2) ;
		fread(buf, i+1, 1, origin_file) ;
		fwrite(buf, i+1, 1, write_file) ;
		fclose(write_file) ;
	}
	free(path) ;
	free(file_name) ;
	fclose(origin_file) ;
	return 0 ;
}
