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

atomic_int answer_index = 0 ;
int range_size ;
struct stat st ;
FILE * read_file_ptr ;

int * begin_queue ;
int queue_index = 0 ;

pthread_mutex_t mutex ;

struct input {
        int index ;
        char * execute_file_path ;
        char * ans ;
} ;

int
queue_push (int num, int process_num) {
	if (queue_index < process_num) {
		pthread_mutex_lock(&mutex) ;
		begin_queue[queue_index] = num ;
		queue_index++ ;
		pthread_mutex_unlock(&mutex) ;
		return 0 ;
	}
	return -1 ;
}

int
queue_pop () {
	if (queue_index > 0) {
		pthread_mutex_lock(&mutex) ;
		int rt = begin_queue[0] ;
		queue_index-- ;
		for (int i = 0 ; i < queue_index ; i++) {
			begin_queue[i] = begin_queue[i + 1] ;
		}
		pthread_mutex_unlock(&mutex) ;
		return rt ;
	}
	return -1 ;
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

        while (1) {
		int start ;
		while (1) {
			start = queue_pop() ;
			fprintf(stderr, "index: %d, start: %d, queue_index: %d\n", ip->index, start, queue_index) ;
			if (start != -1) {
				break ;
			}
			if (range_size == 0) {
				break ;
			}
		}
		if (range_size == 0) {
			break ;
		}

		int end = start + range_size ;

                FILE * write_file_ptr = fopen(complement_path, "w+") ;
                write_file(read_file_ptr, write_file_ptr, 0, start) ;
                write_file(read_file_ptr, write_file_ptr, end, st.st_size) ;
                fclose(write_file_ptr) ;
                
		remove(stderr_path) ;
                EXITCODE rt = pcs_runner(ip->execute_file_path, complement_path, stderr_path) ;
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
	begin_queue = (int *) malloc(sizeof(int) * process_num) ;

        read_file_ptr = fopen("temp", "r") ;
        pthread_t t[process_num] ;
        struct input * ip[process_num] ;
        for (int i = 0 ; i < process_num ; i++) {
                ip[i] = (struct input *) malloc(sizeof(struct input)) ;
                ip[i]->index = i ;
		ip[i]->execute_file_path = execute_file_path ;
		ip[i]->ans = answer ;
        }
	
        stat("temp", &st) ;
	int start_size = st.st_size - 1 ;
	int current_size = 0 ;

        for (int i = 0 ; i < process_num ; i++) {
		pthread_create(&t[i], NULL, thread, (void *) ip[i]) ;
	}
	while (1) {
		for (range_size = start_size ; range_size > 0 ; range_size--) {
			fprintf(stderr, "range_size: %d\n", range_size) ;
			for (int begin = 0 ; begin <= st.st_size - range_size ; begin++) {
				int rt ;
				while (1) {
					if (queue_push(begin, process_num) != -1) {
						break ;
					}
				}	
			}

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
			fclose(read_file_ptr) ;
			read_file_ptr = fopen("temp", "r") ;

			stat("temp", &st) ;
			start_size = MIN(current_size, st.st_size - 1) ;
			answer_index = 0 ;
		}
	}
	range_size = 0 ;
        for (int i = 0 ; i < process_num ; i++) {
		pthread_join(t[i], NULL) ;
                free(ip[i]) ;
        }
	fclose(read_file_ptr) ;
	free(begin_queue) ;
	pthread_mutex_destroy(&mutex) ;
}

