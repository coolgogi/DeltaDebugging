#include <stdio.h>
#include <stdlib.h>
#include "../include/runner.h"
#include "../include/ddmin.h"
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <sys/param.h>

int
t_range (char * executeFile_path, char * inputFile_path, char * offsetFile_path, char * ans) {
	//size
	struct stat st ;
	stat(inputFile_path, &st) ;
	int size = st.st_size ;
	char * data = (char *) calloc (sizeof(char), size) ;
	char * answer = (char *) calloc (sizeof(char), size) ;
	
	//data
	FILE * inputFile = fopen(inputFile_path, "r") ;
	fread(data, size, 1, inputFile) ;
	fread(answer, size, 1, inputFile) ;
	fclose(inputFile) ;
	
	//offset
	FILE * offsetFile = fopen(offsetFile_path, "r") ;
	int * offset = (int *) calloc (sizeof(int), size) ;
	char offset_temp[20] ;
	memset(offset, 0, sizeof(int) * size) ;
	memset(offset_temp, 0, 20) ;
	offset[0] = 1 ;
	while (!feof(offsetFile)) {
		fgets(offset_temp, 20, offsetFile) ;
		int index = atoi(offset_temp) ;
		offset[index] = 1 ;
	}

	//number of offset
	int num_of_offset = 0 ;
	for (int i = 0 ; i < size ; i ++) {
		if (offset[i] == 1) {
			if (i + 1 < size) {
				if (offset[i + 1] == 0) {
					num_of_offset ++ ;
				}
			}
			num_of_offset ++ ;
		}
	}

	int token_len[num_of_offset] ;
	int token_len_index = 0 ; 
	int total = 0 ;
	for (int i = 0 ; i < size ; i ++) {
		int temp = 0 ;
		if (offset[i] == 1) {
			token_len[token_len_index] = 1 ;
			total = total + 1 ;
		}
		else { 
			temp ++ ;
			if (i < size - 1) {
				while(offset[i+1] == 0) {
					temp ++ ;
					i ++ ;
					if (i == size - 1)
						break ;
				}
			}
			token_len[token_len_index] = temp ;
			total = total + temp ;
		}
		token_len_index ++ ;
	}

	//token
	char * token[num_of_offset] ;
	int d_index = 0 ; 
	for (int i = 0 ; i < num_of_offset ; i ++) {
		token[i] = (char *) calloc (sizeof(char), token_len[i] + 1) ;
		for (int j = 0 ; j < token_len[i] ; j ++) {
			token[i][j] = data[d_index] ;
			d_index ++ ;
		}
	}
	
	//range
	int token_size = sizeof(token) / sizeof(token[0]) ;

	int cnt = 0 ;
	int flag = 0 ;
	int min_index = -1 ;
	int min_size = size ;

	for (int rs = token_size - 1 ; rs > 0 ; rs --) {
		for (int begin = 0 ; begin <= token_size - rs ; begin ++) {
			if (flag == 1) {
				begin = min_index ; 
			}
			//temp_token
			char * temp_token[token_size - rs] ;
			int temp_index = 0 ;
			int end = begin + rs ; 
			int inputArrayLength = 0 ;

			if (begin != 0) {
				for (int i = 0 ; i < begin ; i ++ ) {
					inputArrayLength = inputArrayLength + strlen(token[i]) ;
					temp_token[temp_index] = (char *) calloc (sizeof(char), strlen(token[i]) + 1) ;	
					for (int j = 0 ; j < strlen(token[i]) ; j ++ ) {
						temp_token[temp_index][j] = token[i][j] ; 
					}
					temp_index ++ ; 
				}
			}	
			if (end != token_size) {
				for (int i = end ; i < token_size ; i ++) {
					inputArrayLength = inputArrayLength + strlen(token[i]) ;
					temp_token[temp_index] = (char *) calloc (sizeof(char), strlen(token[i]) + 1) ;
					for (int j = 0 ; j < strlen(token[i]) ; j ++ ) {
						temp_token[temp_index][j] = token[i][j] ; 
					}
					temp_index ++ ; 
				}
			}
			
			char * target_input = (char *) calloc (sizeof(char), inputArrayLength + 1) ;
			int t_index = 0 ;
			for (int i = 0 ; i < temp_index ; i ++) {
				for (int j = 0 ; j < strlen(temp_token[i]) ; j ++) {
					target_input[t_index] = temp_token[i][j] ; 
					t_index ++ ; 
				}
			}
			target_input[inputArrayLength] = '\0' ;
			FILE * complement = fopen("complement", "w+") ;
			fwrite(target_input, strlen(target_input), 1, complement) ;
			fclose(complement) ;
	
			EXITCODE rt = t_runner(executeFile_path, "complement", "ddmin_stdout") ;
			cnt ++ ;

			FILE * stderr_ptr = fopen("stderr", "r") ;
			if (stderr_ptr == NULL) {
				continue ; 
			}
			char output[300] ;
			memset(output, 0, 300) ;

			while (!feof(stderr_ptr)) {
				fgets(output, 300, stderr_ptr) ;
				if (strstr(output, ans) != NULL) {
					break ;
				}
			}
			fclose(stderr_ptr) ;
			remove("stderr") ;

			if (strstr(output, ans) != NULL) {
				if (min_size > strlen(target_input)) {
					min_size = strlen(target_input) ;
					min_index = begin ;
				}
				if (flag == 1) {	
					strcpy(answer, target_input) ;
					int temp_num = sizeof(temp_token) / sizeof(temp_token[0]) ;
					FILE * answer_temp = fopen("answer_temp", "w+") ;
					fwrite(answer, strlen(answer), 1, answer_temp) ;
					fclose(answer_temp) ;
					for (int i = 0 ; i < temp_index ; i ++ ) {
						token[i] = (char *) realloc (token[i], strlen(temp_token[i]) + 1) ;
						for (int j = 0 ; j < strlen(temp_token[i]) ; j ++ ) {
							token[i][j] = temp_token[i][j] ; 
						}
						token[i][strlen(temp_token[i])] = '\0' ; 
					}		
					min_index = -1 ;
					flag = 0 ;
					token_size = token_size - rs ;
					begin = MAX(-1, begin - rs);
				}
			}
			for (int i = 0 ; i < temp_index ; i ++) {
				free(temp_token[i]) ; 
			}
			free(target_input) ;
		}
		if (min_index != -1) {
			rs ++ ;
			flag = 1 ;
		}
		
	}	
	
	FILE * output = fopen("token_range_result", "w+") ;
	fwrite(answer, strlen(answer), 1, output) ;
	fclose(output);

	//free
	for (int i = 0 ; i < sizeof(token) / sizeof(token[0]) ; i ++) {
		free(token[i]) ;
	}
	free(answer) ;
	free(offset) ;
	free(data) ;
	return cnt ;	
}

