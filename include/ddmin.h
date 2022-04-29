int * split (int file_size, int n, double stddev);
char * reduce_to_substring (char * path, char * s, int n, int * len, double p2, char * ans);
char * reduce_to_complement (char * path, char * s, int n, int * len, double p2, char * ans);
char * reduce (char * path, char * s, int n);
char * ddmin (char * execute_file_path, char * input_file_path, double p, double p2, double sigma, char * ans);

char * o_ddmin (char * execute_file_path, char * input_file_path, char * ans) ;
int * o_split (int file_size, int n);
char * o_substring (char * execute_path, char * input_path, int n, int * len, char * ans);
char * o_complement (char * execute_path, char * input_path, int n, int * len, char * ans);
