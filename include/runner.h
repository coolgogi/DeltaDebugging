enum Code {
	PASS = 0,
	FAIL = 1,
	KILL = 9,
	SEGV = 11,
	STOP = 19
};

enum Valid {

	UNRESOLVED = -1,
	VALID = 0,
	INVALID = 1,
};

enum file_descriptor {
	BCOV_FILENO = 3,
	TOTAL_FILENO = 4,	
};

typedef struct exitcode {

	int code_num;
	int valid;
	int child_pid;

} EXITCODE;

EXITCODE runner (char *, char *, char *);
EXITCODE o_runner (char *, char *, char *);
EXITCODE r_runner (char *, char *, char *);
EXITCODE t_runner (char *, char *, char *);
EXITCODE thd_runner (char *, char *, char *);
EXITCODE pcs_runner (char *, char *, char *);
