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
#include <signal.h> 

#define BUFFER_SIZE 100

int * candidate ;
atomic_int answer_index = 0 ;
atomic_int total_cnt = 0 ;
int range_size ;
struct stat st ;
int p_num ;

sem_t buf ;
sem_t executing_thread ;

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
	char complement_path[20] ;
	char stderr_path[10] ;
	int cur_index = ip->index ;
	sprintf(complement_path, "complement%d", cur_index) ;
	sprintf(stderr_path, "stderr%d", ip->index) ;
        read_file_ptr[ip->index] = fopen("temp", "r") ;

        while (1) {
		int start ; 
		sem_wait(&buf) ;
		sem_post(&executing_thread) ;
		pthread_mutex_lock(&mutex) ;
		start = queue_pop() ;
		pthread_mutex_unlock(&mutex) ;

		int end = start + range_size ;
                FILE * write_file_ptr = fopen(complement_path, "w+") ;
                write_file(read_file_ptr[ip->index], write_file_ptr, 0, start) ;
                write_file(read_file_ptr[ip->index], write_file_ptr, end, st.st_size) ;
                fclose(write_file_ptr) ;
                
		remove(stderr_path) ;
                EXITCODE rt = pcs_runner(ip->execute_file_path, complement_path, stderr_path) ;
		if (find_answer_string(stderr_path, ip->ans) == 1) {
			int index = atomic_fetch_add(&answer_index, 1) ;
			candidate[index] = cur_index ;
			cur_index = cur_index + p_num ;
			sprintf(complement_path, "complement%d", cur_index) ;
		}
		sem_wait(&executing_thread) ;
        }
        pthread_exit(0) ;
}

void
pcs_range (char * execute_file_path, char * answer, int process_num) {
	pthread_mutex_init(&mutex, NULL) ;
	sem_init(&buf, 0, 0) ;
	sem_init(&executing_thread, 0, 0) ;

	p_num = process_num ;

	read_file_ptr = (FILE **) malloc(sizeof(FILE *) * process_num) ;

        stat("temp", &st) ;
	int start_size = st.st_size - 1 ;
	int current_size = 0 ;
	range_size = start_size ;

	candidate = (int *) malloc(sizeof(int) * 100) ;

        pthread_t t[process_num] ;
        struct input * ip[process_num] ;
        for (int i = 0 ; i < process_num ; i++) {
                ip[i] = (struct input *) malloc(sizeof(struct input)) ;
                ip[i]->index = i ;
		ip[i]->execute_file_path = execute_file_path ;
		ip[i]->ans = answer ;
		pthread_create(&t[i], NULL, thread, (void *) ip[i]) ;
        }
	

	while (1) {
		for (range_size = start_size ; range_size > 0 ; range_size--) {
			for (int begin = 0 ; begin <= st.st_size - range_size ; begin++) {
				queue_push(begin) ;
				sem_post(&buf) ;
			}
			int buf_size ;
			int thread_num ;
			do {
				sem_getvalue(&buf, &buf_size) ;
				sem_getvalue(&executing_thread, &thread_num) ;
			} while (buf_size != 0 && thread_num != 0) ;

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
			answer_index = 0 ;
			int new_index = candidate[rnum] ;
		 	char selected_path[20] ;
	 		sprintf(selected_path, "complement%d", new_index) ;
			for (int i = 0 ; i < process_num ; i++) {
				fclose(read_file_ptr[i]) ;
				read_file_ptr[i] = fopen(selected_path, "r") ;
			}
			stat(selected_path, &st) ;
			start_size = MIN(current_size, st.st_size - 1) ;
			fprintf(stderr, "%s\n", selected_path) ;
		}
	}

  	for (int i = 0 ; i < process_num ; i++) {
		pthread_cancel(t[i]) ;
		fclose(read_file_ptr[i]) ;
		free(ip[i]) ;
		pthread_join(t[i], NULL) ;
        }
	free(candidate) ;
	free(read_file_ptr) ;
	pthread_mutex_destroy(&mutex) ;
	sem_close(&buf) ;
	sem_close(&executing_thread) ;
}

