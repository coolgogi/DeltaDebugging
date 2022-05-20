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

atomic_int answer_index = 0;
atomic_int begin = 0;

struct input {
        int range_size;
        int index;
        char * execute_file_path;
        char * ans;
};

int
find_answer_string (char * stderr_path, char * ans) {
	char buffer[1025];
	memset(buffer, 0, 1025);
	FILE * stderr_file_ptr = fopen(stderr_path, "r");	
	struct stat st;
	stat(stderr_path, &st);
	
	int div = st.st_size / 1024;
	int mod = st.st_size % 1024;
	for (int i = 0; i < div; i++) {
		if (fread(buffer, 1024, 1, stderr_file_ptr) == 1) {
			if (strstr(buffer, ans) != NULL) {
				fclose(stderr_file_ptr);
				return 1;
			}
		}		
	}
	if (fread(buffer, mod, 1, stderr_file_ptr) == 1) {
		if (strstr(buffer, ans) != NULL) {
			fclose(stderr_file_ptr);
			return 1;
		}
	}
	for (int i = 0; i < div; i++) {
		int offset = 1024 * (i + 1);
		fseek(stderr_file_ptr, offset - strlen(ans), SEEK_SET);
		int len = MIN(strlen(ans) * 2, strlen(ans) + mod);
		if (fread(buffer, len, 1, stderr_file_ptr) == 1) {
			if (strstr(buffer, ans) != NULL) {
				fclose(stderr_file_ptr);
				return 1;
			}
		}
	}
	fclose(stderr_file_ptr);
	return 0;
}

void *
thread (void * arg) {
	struct input * ip = (struct input *) arg;
	char complement_path[15] ;
	char stderr_path[10] ;
	sprintf(complement_path, "complement%d", ip->index) ;
	sprintf(stderr_path, "stderr%d", ip->index) ;

        FILE * read_file_ptr = fopen("temp", "r");
	struct stat st;
	stat("temp", &st); 

        while (1) {
		if (begin > st.st_size - ip->range_size) {
			break;
		}
		int start = atomic_fetch_add(&begin, 1);

		int end = start + ip->range_size;

                FILE * write_file_ptr = fopen(complement_path, "w+");
                write_file(read_file_ptr, write_file_ptr, 0, start);
                write_file(read_file_ptr, write_file_ptr, end, st.st_size);
                fclose(write_file_ptr);
                
		remove(stderr_path);
                EXITCODE rt = pcs_runner(ip->execute_file_path, complement_path, stderr_path);
		if (find_answer_string(stderr_path, ip->ans) == 1) {
			int index = atomic_fetch_add(&answer_index, 1);
                        char temp_file_path[10];
                        sprintf(temp_file_path, "temp%d", index);
		      	copy_file(complement_path, temp_file_path);
		} 
        }
        fclose(read_file_ptr);
        void * p = NULL;
        return p;	
}

void
pcs_range (char * execute_file_path, char * answer, int process_num) {
        srand(time(NULL));

        struct input * ip[process_num];
        for (int i = 0; i < process_num; i++) {
                ip[i] = (struct input *) malloc(sizeof(struct input));
                ip[i]->index = i;
		ip[i]->execute_file_path = execute_file_path;
		ip[i]->ans = answer;
        }
        pthread_t t[process_num];
	
	struct stat st;
        stat("temp", &st);
	int start_size = st.st_size - 1;
	int current_size = 0;
	do {
		answer_index = 0;
		for (int range_size = start_size; range_size > 0; range_size--) {
			begin = 0;
	                for (int i = 0; i < process_num; i++) {
	                        ip[i]->range_size = range_size;
	                        pthread_create(&t[i], NULL, thread, (void *) ip[i]);
	                }
	                for (int i = 0; i < process_num; i++) {
	                        pthread_join(t[i], NULL);
	                }

	                if (answer_index > 0) {
				current_size = range_size ;
				break ; 
	                }
	        }
		if (answer_index > 0) {
			int rnum = rand() % answer_index;
		 	char selected_path[10];
	 		sprintf(selected_path, "temp%d", rnum);
			copy_file(selected_path, "temp");
			stat("temp", &st);
			start_size = MIN(current_size, st.st_size - 1) ;
		}
	} while (answer_index != 0) ;

        for (int i = 0; i < process_num; i++) {
                free(ip[i]);
        }

}

