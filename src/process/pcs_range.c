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
#include <errno.h>

#define WAITING -1

atomic_int answer_index = 0 ;
sem_t sem ;

int * begin_arr ;
int range_size ;

struct input {
        int index ;
        char * execute_file_path ;
        char * ans ;
} ;
  
FILE * read_file_ptr ;


int
find_answer_string (char * stderr_path, char * ans) {
	char buffer[1025] ;
	memset(buffer, 0, 1025) ;
	FILE * stderr_file_ptr = fopen(stderr_path, "r") ;	
	struct stat st ;
	stat(stderr_path, &st) ;
	
	int div = st.st_size / 1024 ;
	int mod = st.st_size % 1024 ;
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

//        FILE * read_file_ptr = fopen("temp", "r") ;
	struct stat st ;
	stat("temp", &st) ; 
	int current_rs = range_size ;
        while (1) {
		
		int start ;
		if (range_size == 0) {
			break ;	
		}

		if (begin_arr[ip->index] == WAITING) {
			sem_wait(&sem) ;
		}
		while (1) {
			if (begin_arr[ip->index] != WAITING) {
				start = begin_arr[ip->index] ;
				begin_arr[ip->index] = WAITING ;
				sem_post(&sem) ;
				break ;
			}
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
        fclose(read_file_ptr) ;
        void * p = NULL ;
        return p ;	
}

void
pcs_range (char * execute_file_path, char * answer, int process_num) {

	begin_arr = (int *) malloc(sizeof(int) * process_num) ;
	sem_init(&sem, 0, process_num) ;
	read_file_ptr = fopen("temp", "r") ;

        struct input * ip[process_num] ;
        pthread_t t[process_num] ;
        for (int i = 0 ; i < process_num ; i++) {
                ip[i] = (struct input *) malloc(sizeof(struct input)) ;
                ip[i]->index = i ;
		ip[i]->execute_file_path = execute_file_path ;
		ip[i]->ans = answer ;

		begin_arr[i] = -1 ;	
		pthread_create(&t[i], NULL, thread, (void *) ip[i]) ;
        }
	
	struct stat st ;
        stat("temp", &st) ;
	int start_size = st.st_size - 1 ;
	int current_size = 0 ;

	while (1) {
		for (range_size = start_size ; range_size > 0 ; range_size--) {
			for (int begin = 0 ; begin <= st.st_size - range_size ; begin++) {
				int arr_i = 0 ;
				while (1) {
					if (begin_arr[arr_i] == WAITING) {
						begin_arr[arr_i] = begin ;
						arr_i = (arr_i + 1) % process_num ;
						break ;
					}
					fprintf(stderr, "arr_i: %d, begin: %d\n", arr_i, begin) ;
					arr_i = (arr_i + 1) % process_num ;
				}
			}
			//waiting thread
			while (1) {
				int flag = 1 ;
				for (int i = 0 ; i < process_num ; i ++) {
					if (begin_arr[i] != -1) {
						flag = 0 ;
					}
				}
				if (flag == 1) {
					break ;
				}
			}
			//
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
			stat("temp", &st) ;
			start_size = MIN(current_size, st.st_size - 1) ;
			answer_index = 0 ;
			fclose(read_file_ptr) ;
			read_file_ptr = fopen("temp", "r") ;
		}
	}
	range_size = 0 ;

	for (int i = 0 ; i < process_num ; i++) {
		pthread_join(t[i], NULL) ;
                free(ip[i]) ;
	}

	free(begin_arr) ;
	fclose(read_file_ptr) ;
}
