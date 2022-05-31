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
#include <stdatomic.h>

#define BUFFER_SIZE 100

atomic_int answer_index = 0 ;
atomic_int total_cnt = 0 ;
int range_size ;
struct stat st ;

sem_t full ;
sem_t empty ;
pthread_mutex_t mutex ;

int begin_queue[BUFFER_SIZE] ;
int front = 0 ;
int rear = 0 ;

FILE ** read_file_ptr ;

int count = 0 ;

struct input {
        int index ;
        char * execute_file_path ;
        char * ans ;
} ;

void
queue_push(int element) {
	begin_queue[rear] = element ;
	rear = (rear + 1) % BUFFER_SIZE ;
	return ;
}

int
queue_pop() {
	int rt = begin_queue[front] ;
	front = (front + 1) % BUFFER_SIZE ;
	return rt ;
}

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

void *
thread (void * arg) {
	struct input * ip = (struct input *) arg ;
	char complement_path[15] ;
	char stderr_path[10] ;
	sprintf(complement_path, "complement%d", ip->index) ;
	sprintf(stderr_path, "stderr%d", ip->index) ;
	int cnt = 0 ;
        while (1) {
		int start ; 
		sem_wait(&full) ;
		pthread_mutex_lock(&mutex) ;
		start = queue_pop() ;
		pthread_mutex_unlock(&mutex) ;
		sem_post(&empty) ;
		if (start == -1) {
			if (cnt != 0) {
				atomic_fetch_add(&total_cnt, cnt) ;
				cnt = 0 ;
			}
			continue ;
		}
		if (start == -2) {
			break ;
		}
		int end = start + range_size ;

                FILE * write_file_ptr = fopen(complement_path, "w+") ;
                write_file(read_file_ptr[ip->index], write_file_ptr, 0, start) ;
                write_file(read_file_ptr[ip->index], write_file_ptr, end, st.st_size) ;
                fclose(write_file_ptr) ;
                
		remove(stderr_path) ;
                EXITCODE rt = pcs_runner(ip->execute_file_path, complement_path, stderr_path) ;
		cnt++ ;
		if (find_answer_string(stderr_path, ip->ans) == 1) {
			int index = atomic_fetch_add(&answer_index, 1) ;
                        char temp_file_path[10] ;
                        sprintf(temp_file_path, "temp%d", index) ;
		      	copy_file(complement_path, temp_file_path) ;
		}
        }
        return NULL ;
}

void
pcs_range (char * execute_file_path, char * answer, int process_num) {
	pthread_mutex_init(&mutex, NULL) ;
	sem_init(&empty, 0, BUFFER_SIZE) ;
	sem_init(&full, 0, 0) ;

	read_file_ptr = (FILE **) malloc(sizeof(FILE *) * process_num) ;

        stat("temp", &st) ;
	int start_size = st.st_size - 1 ;
	int current_size = 0 ;
	range_size = start_size ;

        pthread_t t[process_num] ;
        struct input * ip[process_num] ;
        for (int i = 0 ; i < process_num ; i++) {
                ip[i] = (struct input *) malloc(sizeof(struct input)) ;
                ip[i]->index = i ;
		ip[i]->execute_file_path = execute_file_path ;
		ip[i]->ans = answer ;
        	read_file_ptr[i] = fopen("temp", "r") ;
		pthread_create(&t[i], NULL, thread, (void *) ip[i]) ;
        }
	

	while (1) {
		for (range_size = start_size ; range_size > 0 ; range_size--) {
			for (int begin = 0 ; begin <= st.st_size - range_size ; begin++) {
				sem_wait(&empty) ;
				queue_push(begin) ;
				sem_post(&full) ;
			}
			while (total_cnt != st.st_size - range_size + 1) {
				sem_wait(&empty) ;
				queue_push(-1) ;
				sem_post(&full) ;
			}
			total_cnt = 0 ;
			if (answer_index > 0) {
				current_size = range_size ;
				break ;
	                }
	        }
		if (answer_index == 0) {
			break ;
		}
		if (answer_index > 0) {
			int rnum = rand() % answer_index ;
		 	char selected_path[10] ;
	 		sprintf(selected_path, "temp%d", rnum) ;
			copy_file(selected_path, "temp") ;
			for (int i = 0 ; i < process_num ; i++) {
				fclose(read_file_ptr[i]) ;
				read_file_ptr[i] = fopen("temp", "r") ;
			}

			stat("temp", &st) ;
			start_size = MIN(current_size, st.st_size - 1) ;
			answer_index = 0 ;
		}
	}
	for (int i = 0 ; i < process_num ; i++) {
		sem_wait(&empty) ;
		queue_push(-2) ;
		sem_post(&full) ;
	}
        for (int i = 0 ; i < process_num ; i++) {
		pthread_join(t[i], NULL) ;
                free(ip[i]) ;
		fclose(read_file_ptr[i]) ;
        }
	free(read_file_ptr) ;
	pthread_mutex_destroy(&mutex) ;
}

