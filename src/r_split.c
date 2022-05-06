#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

int *
o_split (int file_size, int n) {
	
	int * len = (int *) malloc(sizeof(int) * n) ;
	memset(len, 0, sizeof(int) * n) ;
	
	int mean = (int) ceil(((double) file_size - (double) n) / (double) n) ;
	int sum_len = 0 ;
	for (int i = 0 ; i < n - 1 ; i ++) {
		int allot = mean ;
		if (allot + sum_len > file_size - n) {
			if (sum_len == file_size - n) {
				allot = 0 ;
			}
			else {
				allot = file_size - n - sum_len ; 
			}
		}
		len[i] = 1 + allot ;
		sum_len = sum_len + allot ;
	}
	len[n - 1] = (file_size - n) - sum_len + 1 ;
	return len ;
}
