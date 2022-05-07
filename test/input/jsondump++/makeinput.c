#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


int
main (int argc, char * argv[]) {
	
	FILE * origin_file = fopen(argv[1], "r") ;
	struct stat st ;
	stat(argv[1], &st) ;
	int n = st.st_size ; 


	for (int i = 0 ; i < n ; i ++ ) {
		char * file_name = (char *) malloc (10) ;
		sprintf(file_name, "%03d", i) ;
		FILE * write_file = fopen(file_name , "w+") ;
		
		fseek(origin_file, 0, SEEK_SET) ;
		unsigned char * buf = (unsigned char *) malloc (i+2) ;
		fread(buf, i+1, 1, origin_file) ;
		fwrite(buf, i+1, 1, write_file) ;
		fclose(write_file) ;
	}
	fclose(origin_file) ;
	return 0 ;
}
