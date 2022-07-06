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

#define QUEUE_SIZE 200

int * candidate ;

atomic_int answer_index = 0 ;
atomic_int number_of_done_task = 0 ;
atomic_int q_index = 0 ;
int number_of_total_task = 0 ;

int range_size ;
struct stat st ;
int p_num ;

sem_t buf ;
pthread_mutex_t queue_mutex ;
pthread_mutex_t cond_mutex ;
pthread_mutex_t empty_mutex ;
pthread_cond_t task_done ;
pthread_cond_t empty ;

int begin_queue[QUEUE_SIZE] ;
int front = 0 ;
int rear = 0 ;

FILE ** read_file_ptr ;

struct input {
        int index ;
        char * execute_file_path ;
        char * ans ;
} ;

void
queue_push(int element) {
	if (rear - front == QUEUE_SIZE) {
		pthread_cond_wait(&empty, &empty_mutex) ;
	}
	int temp = rear % QUEUE_SIZE ;
	begin_queue[temp] = element ;
	rear++ ;
	return ;
}

int
queue_pop() {
	pthread_mutex_lock(&queue_mutex) ;
	int temp = front ;
	front++ ;
	pthread_mutex_unlock(&queue_mutex) ;
	if (rear == front) {
		pthread_cond_signal(&empty) ;	
	}
	temp = temp % QUEUE_SIZE ;
	int rt = begin_queue[temp] ;
	return rt ;
}

void *
thread (void * arg) {
	struct input * ip = (struct input *) arg ;
	char complement_path[50] ;
	char stderr_path[20] ;
	int cur_index = ip->index ;
	char temp_file_path[20] ;

	sprintf(complement_path, "complement%d", cur_index) ;
	sprintf(stderr_path, "stderr%d", ip->index) ;
        sprintf(temp_file_path, "temp%d", ip->index) ;
	read_file_ptr[ip->index] = fopen(temp_file_path, "r") ;

        while (1) {
		int start ; 
		sem_wait(&buf) ;
		start = queue_pop() ;
		
		int end = start + range_size ;
                FILE * write_file_ptr = fopen(complement_path, "w+") ;
		fseek(read_file_ptr[ip->index], 0L, SEEK_SET) ;
                write_file(read_file_ptr[ip->index], write_file_ptr, 0, start) ;
		read_file(read_file_ptr[ip->index], start, end) ;
                write_file(read_file_ptr[ip->index], write_file_ptr, end, st.st_size) ;
                fclose(write_file_ptr) ;
                
		remove(stderr_path) ;
                if (pcs_runner(ip->execute_file_path, complement_path, stderr_path, ip->ans) == 1) {
			int answer_cur_index = atomic_fetch_add(&answer_index, 1) ;
			candidate[answer_cur_index] = cur_index ;
			cur_index = cur_index + p_num ;
			sprintf(complement_path, "complement%d", cur_index) ;
		}
		atomic_fetch_add(&number_of_done_task, 1) ;
		if (number_of_done_task == number_of_total_task) {
			pthread_cond_signal(&task_done) ;
		}
        }
}

void
pcs_range (char * execute_file_path, char * answer, int process_num) {
	pthread_mutex_init(&queue_mutex, NULL) ;
	pthread_mutex_init(&cond_mutex, NULL) ;
	pthread_mutex_init(&empty_mutex, NULL) ;
	pthread_cond_init(&task_done, NULL) ;
	pthread_cond_init(&empty, NULL) ;
	sem_init(&buf, 0, 0) ;

	p_num = process_num ;

	read_file_ptr = (FILE **) malloc(sizeof(FILE *) * process_num) ;

        stat("temp0", &st) ;
	int current_size ;
	int start_size = st.st_size - 1 ;

	candidate = (int *) malloc(sizeof(int) * st.st_size) ;

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
			number_of_total_task = number_of_total_task + st.st_size - range_size + 1 ;
			for (int begin = 0 ; begin <= st.st_size - range_size ; begin++) {
				queue_push(begin) ;
				sem_post(&buf) ;
			}

			pthread_cond_wait(&task_done, &cond_mutex) ;

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
		 	char selected_path[50] ;
	 		sprintf(selected_path, "complement%d", new_index) ;
			for (int i = 0 ; i < process_num ; i++) {
				char temp_file_path[20] ;
				sprintf(temp_file_path, "temp%d", i) ;
				copy_file(selected_path, temp_file_path) ;
				fclose(read_file_ptr[i]) ;
				read_file_ptr[i] = fopen(temp_file_path, "r") ;
			}
			stat(selected_path, &st) ;
			start_size = MIN(current_size, st.st_size - 1) ;
			fprintf(stderr, "%s\n", selected_path) ;
		}
	}

	for (int i = 0 ; i < process_num ; i++) {
		free(ip[i]) ;
		fclose(read_file_ptr[i]) ;
		pthread_cancel(t[i]) ;	
		pthread_join(t[i], NULL) ;
        }
	free(candidate) ;
	free(read_file_ptr) ;
	sem_close(&buf) ;
	pthread_mutex_destroy(&queue_mutex) ;
	pthread_mutex_destroy(&cond_mutex) ;
	pthread_cond_destroy(&task_done) ;
}
