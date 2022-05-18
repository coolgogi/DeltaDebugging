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
	int file_size ;
	int range_size ;
	int mod ;
	char * executeFile_path ;
	char * inputFile_path ;
	char * ans ;
	unsigned char * buf ;
	char * stderr_path ;
	char * complement_path ;
} ;

void* thread (void * arg) {

	struct input * ip = (struct input *) arg ;
	int file_size = ip->file_size ;
	int range_size = ip->range_size ;
	int loop = file_size - range_size ;
	int mod = ip->mod ;
	char * exec = ip->executeFile_path ;
	char * ans = ip->ans ;
	unsigned char * buf = ip->buf ; 
	char * stderr_path = ip->stderr_path ;
	char * complement = ip->complement_path ;
	
	FILE * read_file = fopen(ip->inputFile_path, "r") ;
	char stderr_output[300] ;
	for (int i = mod ; i <= file_size - range_size ; i = i + 8) {
		int begin = i ;
		int end = i + range_size ;

		FILE * write_file = fopen(complement, "w+") ;
		fseek(read_file, 0, SEEK_SET) ;		
		if (begin != 0) {
			writeFile(read_file, write_file, begin, buf) ;
		}
		fseek(read_file, end, SEEK_SET) ;
		if (end != file_size) {
			writeFile(read_file, write_file, file_size - end, buf) ;
		}
		fclose(write_file) ;

		remove(stderr_path) ;
		EXITCODE rt = thd_runner(exec, complement, stderr_path) ;
		FILE * stderr_file = fopen(stderr_path, "r") ;	
		while (!feof(stderr_file)) {
			memset(stderr_output, 0, 300) ;
			fgets(stderr_output, 300, stderr_file) ;
			if (strstr(stderr_output, ans) != NULL) {
				sem_wait(&mutex) ;
				char * temp_path = (char *) malloc(10) ;
				sprintf(temp_path, "temp%d", answer_index) ;
				FILE * temp_file = fopen(temp_path, "w+") ;
				FILE * result_file = fopen(complement, "r") ;
				struct stat st ;
				stat(complement, &st) ;
				writeFile(result_file, temp_file, st.st_size, buf) ;
				fclose(result_file) ;
				fclose(temp_file) ;	
				free(temp_path) ;
				answer_index ++ ;
				sem_post(&mutex) ;	
				break ;
			}
		}
		fclose(stderr_file) ;
	}	
	fclose(read_file) ;
	void * p = NULL ;
	return p ;
}

void
thd_range (char * executeFile_path, char * inputFile_path, char * answer) {
	
	struct stat st ;
	stat(inputFile_path, &st) ;
	int file_size = st.st_size ;

	char * complement[8] ;
	unsigned char * buf[8] ;
	char * stderr_path[8] ;
	struct input * ip[8] ;
	for (int i = 0 ; i < 8 ; i ++) {
		complement[i] = (char *) malloc(15) ;
		buf[i] = (unsigned char *) malloc(1024) ;
		stderr_path[i] = (char *) malloc(10) ;
		sprintf(complement[i], "complement%d", i) ;
		memset(buf[i], 0, 1024) ;	
		sprintf(stderr_path[i], "stderr%d", i) ;
		ip[i] = (struct input *) malloc(sizeof(struct input)) ;
	}
	unsigned char * range_buf = (unsigned char *) malloc(1024) ;
	memset(range_buf, 0, 1024) ;	
	//
	sem_init(&mutex, 0, 1) ;
	pthread_t t[8] ;
	//

	for (int range_size = file_size - 1 ; range_size > 0 ; range_size --) {
		for (int i = 0 ; i < 8 ; i ++) {
			ip[i]->file_size = file_size;
			ip[i]->range_size = range_size;
			ip[i]->mod = i;
			ip[i]->executeFile_path = executeFile_path ;
			ip[i]->inputFile_path = inputFile_path ;
			ip[i]->ans = answer ;
			ip[i]->buf = buf[i] ;
			ip[i]->stderr_path = stderr_path[i] ;
			ip[i]->complement_path = complement[i] ;

			pthread_create(&t[i], NULL, thread, (void *) ip[i]) ;
		}
		for (int i = 0 ; i < 8 ; i ++) {
			pthread_join(t[i], NULL) ;
		}
	
		if (answer_index > 0) {
			srand(time(NULL)) ;
			int rnum = rand() % answer_index ;
			char * selected_path = (char *) malloc(10) ;
			sprintf(selected_path, "temp%d", rnum) ;
			FILE * selected_file = fopen(selected_path, "r") ;
			FILE * temp_file = fopen("temp", "w+") ;
			stat(selected_path, &st) ;
			file_size = st.st_size ;
			writeFile(selected_file, temp_file, file_size, range_buf) ;
			answer_index = 0 ;
			range_size = MIN(file_size, range_size + 1) ;
			fclose(temp_file) ;
			fclose(selected_file) ;	
			free(selected_path) ;
		}
	}
	for (int i = 0 ; i < 8 ; i ++) {
		free(complement[i]) ;
		free(buf[i]) ;
		free(stderr_path[i]) ;
		free(ip[i]) ;
	}
	free(range_buf) ;
}
