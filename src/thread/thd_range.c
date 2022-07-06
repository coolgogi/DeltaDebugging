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

int
find_answer_string (char * stderr_path, char * ans) {
	char buffer[1025] ;
	memset(buffer, 0, 1025) ;
	FILE * stderr_file_ptr = fopen(stderr_path, "r") ;	
	struct stat stderr_st ;
	stat(stderr_path, &stderr_st) ;
	
	int div = stderr_st.st_size / 1024 ;
	int mod = stderr_st.st_size % 1024 ;
	for (int i = 0 ; i < div ; i++) {
		if (fread(buffer, 1024, 1, stderr_file_ptr) == 1) {
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
		int offset = 1024 * (i + 1) ;
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


void* 
thread (void * arg) {

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
	
	FILE * read_file_ptr = fopen(ip->inputFile_path, "r") ;
	char stderr_output[300] ;
	for (int i = mod ; i <= file_size - range_size ; i = i + 8) {
		int begin = i ;
		int end = i + range_size ;

		FILE * write_file_ptr = fopen(complement, "w+") ;
		write_file(read_file_ptr, write_file_ptr, 0, begin) ;
		write_file(read_file_ptr, write_file_ptr, end, file_size) ;
		fclose(write_file_ptr) ;

		remove(stderr_path) ;
		EXITCODE rt = thd_runner(exec, complement, stderr_path) ;
 		if (find_answer_string(stderr_path, ans) == 1) {
                                char temp_path[10] ;
                                sem_wait(&mutex) ;
                                sprintf(temp_path, "temp%d", answer_index) ;
                                answer_index ++ ;
                                sem_post(&mutex) ;
                                FILE * temp_file = fopen(temp_path, "w+") ;
                                FILE * result_file = fopen(complement, "r") ;
                                struct stat st ;
                                stat(complement, &st) ;
                                write_file(result_file, temp_file, 0, st.st_size) ;
                                fclose(result_file) ;
                                fclose(temp_file) ;
		}
	}	
	fclose(read_file_ptr) ;
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
			write_file(selected_file, temp_file, 0, file_size) ;
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

