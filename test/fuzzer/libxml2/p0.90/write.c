#include <stdio.h>
#include <string.h>

int
main (int argc, char * argv[]) {
	
	FILE * test_script = fopen("test2.sh", "w+") ;
	char command[] = "ASAN_OPTIONS=detect_leaks=0 ../../../../bin/main ../../../../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../../../../fuzzer-test-suite/libxml2-v2.9.2/crash-d8960e21ca40ea5dc60ad655000842376d4178a1 0.90 1.0 5.0\n" ; 
/*
	for (int i = 0 ; i < 300 ; i ++) {
		if (i < 10) {
			char move[20] ;
			sprintf(move, "mv temp sigma5.0/%d\n", i) ;
			fwrite(command, 1, sizeof(command)-1, test_script) ;
			fwrite(move, 1, sizeof(move)-1, test_script) ;	
		}
		else if (i < 100) {
			char move[21] ;
			sprintf(move, "mv temp sigma5.0/%d\n", i) ;
			fwrite(command, 1, sizeof(command)-1, test_script) ;
			fwrite(move, 1, sizeof(move)-1, test_script) ;	

		}
		else{
			char move[22] ;
			sprintf(move, "mv temp sigma5.0/%d\n", i) ;
			fwrite(command, 1, sizeof(command)-1, test_script) ;
			fwrite(move, 1, sizeof(move)-1, test_script) ;	
		}
	}
*/
	char command2[] = "ASAN_OPTIONS=detect_leaks=0 ../../../../bin/main ../../../../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../../../../fuzzer-test-suite/libxml2-v2.9.2/crash-d8960e21ca40ea5dc60ad655000842376d4178a1 0.90 1.0 10.0\n" ; 

	for (int i = 0 ; i < 30 ; i ++) {
		if (i < 10) {
			char move[21] ;
			sprintf(move, "mv temp sigma10.0/%d\n", i) ;
			fwrite(command2, 1, sizeof(command2)-1, test_script) ;
			fwrite(move, 1, sizeof(move)-1, test_script) ;	
		}
		else if (i < 100) {
			char move[22] ;
			sprintf(move, "mv temp sigma10.0/%d\n", i) ;
			fwrite(command2, 1, sizeof(command2)-1, test_script) ;
			fwrite(move, 1, sizeof(move)-1, test_script) ;	

		}
		else{
			char move[23] ;
			sprintf(move, "mv temp sigma10.0/%d\n", i) ;
			fwrite(command2, 1, sizeof(command2)-1, test_script) ;
			fwrite(move, 1, sizeof(move)-1, test_script) ;	
		}
	}

	char command3[] = "ASAN_OPTIONS=detect_leaks=0 ../../../../bin/main ../../../../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../../../../fuzzer-test-suite/libxml2-v2.9.2/crash-d8960e21ca40ea5dc60ad655000842376d4178a1 0.90 1.0 15.0\n" ; 

	for (int i = 0 ; i < 30 ; i ++) {
		if (i < 10) {
			char move[21] ;
			sprintf(move, "mv temp sigma15.0/%d\n", i) ;
			fwrite(command3, 1, sizeof(command3)-1, test_script) ;
			fwrite(move, 1, sizeof(move)-1, test_script) ;	
		}
		else if (i < 100) {
			char move[22] ;
			sprintf(move, "mv temp sigma15.0/%d\n", i) ;
			fwrite(command3, 1, sizeof(command3)-1, test_script) ;
			fwrite(move, 1, sizeof(move)-1, test_script) ;	

		}
		else{
			char move[23] ;
			sprintf(move, "mv temp sigma15.0/%d\n", i) ;
			fwrite(command3, 1, sizeof(command3)-1, test_script) ;
			fwrite(move, 1, sizeof(move)-1, test_script) ;	
		}
	}

	char command4[] = "ASAN_OPTIONS=detect_leaks=0 ../../../../bin/main ../../../../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../../../../fuzzer-test-suite/libxml2-v2.9.2/crash-d8960e21ca40ea5dc60ad655000842376d4178a1 0.90 1.0 20.0\n" ; 

	for (int i = 0 ; i < 30 ; i ++) {
		if (i < 10) {
			char move[21] ;
			sprintf(move, "mv temp sigma20.0/%d\n", i) ;
			fwrite(command4, 1, sizeof(command4)-1, test_script) ;
			fwrite(move, 1, sizeof(move)-1, test_script) ;	
		}
		else if (i < 100) {
			char move[22] ;
			sprintf(move, "mv temp sigma20.0/%d\n", i) ;
			fwrite(command4, 1, sizeof(command4)-1, test_script) ;
			fwrite(move, 1, sizeof(move)-1, test_script) ;	

		}
		else{
			char move[23] ;
			sprintf(move, "mv temp sigma20.0/%d\n", i) ;
			fwrite(command4, 1, sizeof(command4)-1, test_script) ;
			fwrite(move, 1, sizeof(move)-1, test_script) ;	
		}
	}

	fclose(test_script) ;
}
