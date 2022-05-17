#include <stdio.h>

int * split (int file_size, int n, double stddev);
char * reduce_to_substring (char * path, char * s, int n, int * len, double p2, char * ans);
char * reduce_to_complement (char * path, char * s, int n, int * len, double p2, char * ans);
char * ddmin (char * execute_file_path, char * input_file_path, double p, double p2, double sigma, char * ans);

char * o_ddmin (char * execute_file_path, char * input_file_path, char * ans) ;
int * o_split (int file_size, int n);
char * o_substring (char * execute_path, char * input_path, int n, int * len, char * ans);
char * o_complement (char * execute_path, char * input_path, int n, int * len, char * ans);

char * r_ddmin (char * path, char * inputFile_path, char * ans, double p) ;
int * r_split (int file_size, int n);
char * r_substring (char * execute_path, char * input_path, int n, int * len, char * ans);
char * r_complement (char * execute_path, char * input_path, int n, int * len, char * ans);
void range (char * execute_file_path, char * input_file_path, char * ans) ;

int t_ddmin (char * executeFile_path, char * inputFile_path, char * ans, char * offsetFile_path) ;
int * t_split (int file_size, int n, char * offset_path) ;
char * t_substring (char * execute_path, char * input_path, int n, int * len, char * ans);
char * t_complement (char * execute_path, char * input_path, int n, int * len, char * ans);

void thd_ddmin (char * path, char * inputFile_path, char * ans) ;
void thd_range (char * execute_file_path, char * input_file_path, char * ans) ;
void writeFile (FILE * read, FILE * write, int len, unsigned char * buf) ;
void pcs_ddmin (char * path, char * inputFile_path, char * ans) ;
void pcs_range (char * execute_file_path, char * input_file_path, char * ans) ;
