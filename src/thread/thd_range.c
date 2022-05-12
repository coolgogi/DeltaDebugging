#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include "../../include/runner.h"
#include "../../include/ddmin.h"
#include <sys/stat.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/param.h>

int answer_index = 0 ;
sem_t mutex ;

struct input {
	
	int begin ;
	int end ;
	int file_size ;
	char executeFile_path[100] ;
	char ans[100] ;
} ;

void* thread (void * arg) {
	sem_wait(&mutex) ;
	int * arr = (int *) arg ;
	int begin = arr[0] ;
	int end = arr[1] ;
	int file_size = arr[2] ;
	char * ans = (char *) malloc (100) ;
	sprintf(ans, "jsondump.c:44") ;
	int t_num = begin % 8 ;
	
	char * complement_path = (char *) malloc (15) ;
	sprintf(complement_path, "complement%d", t_num) ;
	char * stderr_path = (char *) malloc (10) ;
	sprintf(stderr_path, "stderr%d", t_num) ;

	FILE * read_file = fopen("temp", "r") ;
	FILE * write_file = fopen(complement_path, "w+") ;
	fseek(read_file, 0, SEEK_SET) ;	
	if (begin != 0) {
		int num = begin ;
		unsigned char * buf = (unsigned char *) malloc (num) ;
		memset(buf, 0, num) ;
		fread(buf, num, 1, read_file) ;
		fwrite(buf, num, 1, write_file) ;
		free(buf) ;
	}
	fseek(read_file, end, SEEK_SET) ;
	if (end != file_size) {
		int num = file_size - end ;
		unsigned char * buf = (unsigned char *) malloc (num) ;
		memset(buf, 0, num) ;
		fread(buf, num, 1, read_file) ;
		fwrite(buf, num, 1, write_file) ;
		free(buf) ;
	}
	fclose(write_file) ;
	fclose(read_file) ;
	
	EXITCODE rt = thd_runner("../jsmn/jsondump", complement_path, stderr_path) ;
	FILE * stderr_ptr = fopen(stderr_path, "r") ;
        char output[300] ;
        memset(output, 0, 300) ;
       	while (!feof(stderr_ptr)) {
        	fgets(output, 300, stderr_ptr) ;
		if (strstr(output, ans) != NULL) {
			break ;
      		}  
	}
	fclose(stderr_ptr) ;
	remove(stderr_path) ;

	if (strstr(output, ans) != NULL) {
		char * newTemp_path = (char *) malloc (10) ;
		sprintf(newTemp_path, "temp%d", answer_index) ;
		answer_index ++ ;
		FILE * new_temp = fopen(newTemp_path, "w+") ;
		FILE * result_file = fopen(complement_path, "r") ;
		unsigned char buf ;
		while (fread(&buf, 1, 1, result_file)) {
			fwrite(&buf, 1, 1, new_temp) ;
		}
		fclose(result_file) ;
		fclose(new_temp) ;
		free(newTemp_path) ;
	}	
	free(stderr_path) ;
	free(complement_path) ;	
	free(ans) ;
	free(arr) ;
	sem_post(&mutex) ;
	void * p = NULL ;
	return p ;
}

void
thd_range (char * executeFile_path, char * input_file_path, char * ans) {
	
	struct stat st ;
	stat(input_file_path, &st) ;
	char * complement ;
	complement = (char *) malloc (30) ;
	sprintf(complement, "complement") ;
	int file_size = st.st_size ;
	
	//
	sem_init(&mutex, 0, 1) ;
	pthread_t t[8] ;
	//
	int begin = 0 ;
	for (int range_size = file_size - 1 ; range_size > 0 ; range_size --) {
		fprintf(stderr, "range size: %d %d\n", range_size, file_size) ;
		for ( ; begin <= file_size - range_size ; begin ++) {
			fprintf(stderr, "%d, ", begin) ;
			int mutex_num = begin % 8 ; 
			
			if (begin > 7) {
				pthread_join(t[mutex_num], NULL) ;
			}
			int end = begin + range_size ;
			int * arr = (int *) malloc (sizeof(int) * 3) ;
			arr[0] = begin ;
			arr[1] = end ;
			arr[2] = file_size ;
			pthread_create(&t[mutex_num], NULL, thread, (void *) arr) ;
		}
		fprintf(stderr, "\n") ;
		for (int i = 0 ; i < MIN(8, begin) ; i ++) {
			pthread_join(t[i], NULL) ;
		}
		begin = 0 ;
		if (answer_index > 0) {
			srand(time(NULL)) ;
			int rnum = rand() % answer_index ;
			char * selected_path = (char *) malloc (10) ;
			sprintf(selected_path, "temp%d", rnum) ;
			FILE * selected_file = fopen(selected_path, "r") ;
			FILE * temp_file = fopen("temp", "w+") ;
			unsigned char buf ;
			file_size = 0 ;
			while (fread(&buf, 1, 1, selected_file)) {
				fwrite(&buf, 1, 1, temp_file) ;
				file_size ++ ;
			}
			answer_index = 0 ;
			fprintf(stderr, "file size: %d\n", file_size) ;
			range_size = MIN(file_size, range_size) ;
			fclose(temp_file) ;
			fclose(selected_file) ;	
			free(selected_path) ;
		}

	}
	free(complement) ;
}

