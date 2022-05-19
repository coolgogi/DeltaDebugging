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

int answer_index = 0;
int begin = 0;

pthread_mutex_t answer_mutex;
pthread_mutex_t begin_mutex;

struct input {
        int file_size;
        int range_size;
        int index;
        char * execute_file_path;
        char * input_file_path;
        char * ans;
        char * stderr_path;
        char * complement_path;
};

void *
thread (void * arg) {
	struct input * ip = (struct input *) arg;

        FILE * read_file_ptr = fopen(ip->input_file_path, "r");
        char stderr_output[300];

        while (1) {
		pthread_mutex_lock(&begin_mutex);
		if (begin > ip->file_size - ip->range_size) {
			pthread_mutex_unlock(&begin_mutex);
			break;
		}
		int start = begin;
		begin++;
		pthread_mutex_unlock(&begin_mutex);

		int end = start + ip->range_size;

                FILE * write_file_ptr = fopen(ip->complement_path, "w+");
                write_file(read_file_ptr, write_file_ptr, 0, start);
                write_file(read_file_ptr, write_file_ptr, end, ip->file_size);
                fclose(write_file_ptr);
                
		remove(ip->stderr_path);
                EXITCODE rt = pcs_runner(ip->execute_file_path, ip->complement_path, ip->stderr_path);
                FILE * stderr_file_ptr = fopen(ip->stderr_path, "r");
		if (stderr_file_ptr == NULL) {
			fclose(stderr_file_ptr);
			continue;
		}
                while (!feof(stderr_file_ptr)) {
                	memset(stderr_output, 0, 300);
                        fgets(stderr_output, 300, stderr_file_ptr);
                        if (strstr(stderr_output, ip->ans) != NULL) {
                                pthread_mutex_lock(&answer_mutex);
                                int index = answer_index;
				answer_index++;
                                pthread_mutex_unlock(&answer_mutex);

                                char temp_file_path[10];
                                sprintf(temp_file_path, "temp%d", index);
				copy_file(ip->complement_path, temp_file_path);
                                break;
                        }
                }
                fclose(stderr_file_ptr);
        }
        fclose(read_file_ptr);
        void * p = NULL;
        return p;	
}

void
pcs_range (char * execute_file_path, char * input_file_path, char * answer) {
        char * complement[8];
        char * stderr_path[8];
        struct input * ip[8];
        for (int i = 0; i < 8; i++) {
                stderr_path[i] = (char *) malloc(10);
                sprintf(stderr_path[i], "stderr%d", i);
                complement[i] = (char *) malloc(15);
                sprintf(complement[i], "complement%d", i);

                ip[i] = (struct input *) malloc(sizeof(struct input));

                ip[i]->index = i;
		ip[i]->execute_file_path = execute_file_path;
		ip[i]->input_file_path = input_file_path;
		ip[i]->ans = answer;
		ip[i]->stderr_path = stderr_path[i];
		ip[i]->complement_path = complement[i];
        }
      	pthread_mutex_init(&answer_mutex, NULL);
       	pthread_mutex_init(&begin_mutex, NULL);	
        pthread_t t[8];
	
	struct stat st;
        stat(input_file_path, &st);
        int file_size = st.st_size;
	for (int range_size = file_size - 1; range_size > 0; range_size--) {
		begin = 0;
                for (int i = 0; i < 8; i++) {
                        ip[i]->file_size = file_size;
                        ip[i]->range_size = range_size;

                        pthread_create(&t[i], NULL, thread, (void *) ip[i]);
                }
                for (int i = 0; i < 8; i++) {
                        pthread_join(t[i], NULL);
                }

                if (answer_index > 0) {
                        srand(time(NULL));
                        int rnum = rand() % answer_index;
                        char selected_path[10];
                        sprintf(selected_path, "temp%d", rnum);

			copy_file(selected_path, "temp"); 

                        answer_index = 0;
			stat("temp", &st);
			file_size = st.st_size; 
                        range_size = MIN(file_size, range_size + 1);
                }
        }
        for (int i = 0; i < 8; i++) {
                free(complement[i]);
                free(stderr_path[i]);
                free(ip[i]);
        }

}

