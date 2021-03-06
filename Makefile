CC=clang
INCLDIR = include
BINDIR = bin
SRCDIR = src
CFLAGS = -g -O0 -fsanitize=address 

OBJS = runner ddmin reduce_to_substring reduce_to_complement trace-pc-guard split
BINS = $(addsuffix .o, $(OBJS))
BINFILES = $(addprefix bin/, $(BINS))
SRCS = $(addsuffix .c, $(OBJS))
SRCFILES = $(addprefix src/, $(SRCS))
VPATH = src
TARGET = main
SPLIT = split_main

O_OBJS = o_runner o_ddmin o_substring o_complement o_split
O_BINS = $(addsuffix .o, $(O_OBJS))
O_BINFILES = $(addprefix bin/, $(O_BINS))
O_SRCS = $(addsuffix, .c, $(O_OBJS))
O_SRCFILES = $(addprefix src/, $(O_SRCS))
O_TARGET = o_main

R_OBJS = r_runner range 
R_BINS = $(addsuffix .o, $(R_OBJS))
R_BINFILES = $(addprefix bin/, $(R_BINS))
R_SRCS = $(addsuffix, .c, $(R_OBJS))
R_SRCFILES = $(addprefix src/, $(R_SRCS))
R_TARGET = r_main

T_OBJS = t_runner t_range
T_BINS = $(addsuffix .o, $(T_OBJS))
T_BINFILES = $(addprefix bin/, $(T_BINS))
T_SRCS = $(addsuffix, .c, $(T_OBJS))
T_SRCFILES = $(addprefix src/, $(T_SRCS))
T_TARGET = t_main

THD_OBJS = thd_runner thd_range
THD_BINS = $(addsuffix .o, $(THD_OBJS))
THD_BINFILES = $(addprefix bin/thread/, $(THD_BINS))
THD_SRCS = $(addsuffx, .c (THD_OBJS))
THD_SRCFILES = $(addprefix src/thread/, $(THD_SRCFILES)) 
THD_TARGET = thd_main

PCS_OBJS = pcs_runner pcs_range
PCS_BINS = $(addsuffix .o, $(PCS_OBJS))
PCS_BINFILES = $(addprefix bin/process/, $(PCS_BINS))
PCS_SRCS = $(addsuffx, .c (PCS_OBJS))
PCS_SRCFILES = $(addprefix src/process/, $(PCS_SRCFILES)) 
PCS_TARGET = pcs_main

all: $(OBJS)
	$(CC) $(CFLAGS) -L/usr/local/lib $(SRCDIR)/$(TARGET).c -lgsl -lgslcblas $(BINFILES) -lm -o $(BINDIR)/$(TARGET) 

$(OBJS) : | $(BINDIR)
	$(CC) -c -Wall -I/usr/include $(CFLAGS) $(SRCDIR)/$@.c -o $(BINDIR)/$@.o

$(SPLIT) : split
	$(CC) $(CFLAGS) -L/usr/local/lib $(SRCDIR)/$(SPLIT).c -lgsl -lgslcblas $(BINDIR)/split.o -lm -o $(BINDIR)/$(SPLIT)

$(BINDIR):
	mkdir $(BINDIR)

origin: $(O_OBJS)
	$(CC) $(CFLAGS) $(SRCDIR)/$(O_TARGET).c $(O_BINFILES) -o $(BINDIR)/$(O_TARGET)

r: $(R_OBJS)
	$(CC) $(CFLAGS) $(SRCDIR)/$(R_TARGET).c $(R_BINFILES) -o $(BINDIR)/$(R_TARGET)

token: $(T_OBJS)
	$(CC) $(CFLAGS) $(SRCDIR)/$(T_TARGET).c $(T_BINFILES) -o $(BINDIR)/$(T_TARGET)

thread: $(THD_OBJS)
	$(CC) $(CFLAGS) $(SRCDIR)/thread/$(THD_TARGET).c $(THD_BINFILES) -pthread -o $(BINDIR)/thread/$(THD_TARGET)

process: $(PCS_OBJS)
	$(CC) $(CFLAGS) $(SRCDIR)/process/$(PCS_TARGET).c $(PCS_BINFILES) -pthread -o $(BINDIR)/process/$(PCS_TARGET)

$(O_OBJS): | $(BINDIR)
	$(CC) -c $(CFLAGS) $(SRCDIR)/$@.c -o $(BINDIR)/$@.o

$(R_OBJS): | $(BINDIR)
	$(CC) -c $(CFLAGS) $(SRCDIR)/$@.c -o $(BINDIR)/$@.o

$(T_OBJS): | $(BINDIR)
	$(CC) -c $(CFLAGS) $(SRCDIR)/$@.c -o $(BINDIR)/$@.o

$(THD_OBJS): | $(BINDIR)
	$(CC) -c $(CFLAGS) $(SRCDIR)/thread/$@.c -o $(BINDIR)/thread/$@.o

$(PCS_OBJS): | $(BINDIR)
	$(CC) -c $(CFLAGS) $(SRCDIR)/process/$@.c -o $(BINDIR)/process/$@.o

clean:
	rm $(BINFILES) $(BINDIR)/$(TARGET)
	rm $(O_BINFILES) $(BINDIR)/$(O_TARGET)
	rm $(R_BINFILES) $(BINDIR)/$(R_TARGET)

split_clean:
	rm $(BINDIR)/$(SPLIT)
	rm test/result2
	rm test/result4
	rm test/result8
	rm test/result16
	rm test/result32
	rm test/result64
	rm test/result128
	rm test/result256
	rm test/result377
