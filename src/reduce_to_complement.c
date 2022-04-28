#include "../include/runner.h"
#include "../include/ddmin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <time.h>

char *
reduce_to_complement(char * executeFile_path, char * input_file_path, int n, int * len, double p2) {

	struct stat st;
	stat(input_file_path, &st);
	char * complement = (char *) malloc (21);
	
	char ans[3][15] ;
	memset(ans[0], 0, 15) ;
    	memset(ans[1], 0, 15) ;
    	memset(ans[2], 0, 15) ;
	strcpy(ans[0], "jsondump.c:33") ;
	strcpy(ans[1], "jsondump.c:44") ;
	strcpy(ans[2], "jsondump.c:120") ;
	
	int file_index = 0 ;

	for (int i = 0 ; i < n ; i ++) {
		int total = 0 ;
		sprintf(complement, "complement");
		FILE * read_file = fopen(input_file_path, "r");
		remove(complement) ;
		FILE * write_file = fopen(complement, "w+");
		for (int j = 0 ; j < n ; j ++) {
			for (int k = 0 ; k < len[j] ; k ++) {
				unsigned char buf ;
				if(fread(&buf, 1, 1, read_file) != 1) {
					break ;
				}
				if (i == j) {
					continue ;
				}
				fwrite(&buf, 1, 1, write_file);
				total ++ ;
			}
		}
		fclose(write_file);
		fclose(read_file) ;
		
		if (total == st.st_size)
			continue ;

		EXITCODE rt = runner(executeFile_path, complement, "output/ddmin_output.txt");
		if (rt.code_num != 1) {
			remove("stderr") ;
			continue ;
		}

		FILE * stderr_ptr = fopen("stderr", "r") ;
		char temp[200] ;
	        char std[3][60] ;
	        memset(std[0], 0, 60) ;
	        memset(std[1], 0, 60) ;
       		memset(std[2], 0, 60) ;
	        fgets(temp, 200, stderr_ptr) ;
	        fgets(temp, 200, stderr_ptr) ;
	        fgets(temp, 200, stderr_ptr) ;
	        fgets(std[0], 60, stderr_ptr) ;
	        fgets(std[1], 60, stderr_ptr) ;
	        fgets(std[2], 60, stderr_ptr) ;
		fclose(stderr_ptr) ;
		remove("stderr") ;
		if (strstr(std[0], "33") != NULL && strstr(std[1], "44") != NULL && strstr(std[2], "120") != NULL) {	
                        // store
                       	 
                        char save_complement[20] ;
                        memset(save_complement, 0, 20) ;
                        sprintf(save_complement, "complement%d", file_index) ;
                        file_index ++ ;

                        if (access(save_complement, F_OK) == 0) {
                                remove(save_complement) ;
                        }
                        FILE * file_candidate = fopen(save_complement, "w+") ;
                        FILE * result_file = fopen(complement, "r") ;
                        unsigned char buf ;
                        while (fread(&buf, 1, 1, result_file)) {
                                fwrite(&buf, 1, 1, file_candidate) ;
                        }
                        fclose(result_file) ;
                        fclose(file_candidate) ;
                        
			//
			/*
			remove("temp") ;
			FILE * new_temp = fopen("temp", "w+") ;
			FILE * result_file = fopen(complement, "r") ;
			unsigned char buf ;
			while (fread(&buf, 1, 1, result_file) == 1) {
				fwrite(&buf, 1, 1, new_temp) ;
			}
			fclose(result_file) ;
			fclose(new_temp) ;
			return complement;
			*/

		}
	}
        // random select
        
        if (file_index != 0) {
		fprintf(stderr, "complement: %d\n", file_index) ;
                srand(time(NULL)) ;
                int rand_num = rand() % file_index ;
                sprintf(complement, "complement%d", rand_num) ;
                // change temp
                remove("temp") ;
                FILE * new_temp = fopen("temp", "w+") ;
                FILE * result_file = fopen(complement, "r") ;
                unsigned char buf ;

                while (fread(&buf, 1, 1, result_file)) {
                        fwrite(&buf, 1, 1, new_temp);
                }
                fclose(result_file);
                fclose(new_temp);

                return complement ;
        }
        
	//
	free(complement);
	return input_file_path;
}
