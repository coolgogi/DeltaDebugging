CC=clang
INCLDIR = include
BINDIR = bin
SRCDIR = src
CFLAGS = -g -O0 -fsanitize=address 
OBJS = runner ddmin reduce reduce_to_substring reduce_to_complement trace-pc-guard split
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

$(O_OBJS): | $(BINDIR)
	$(CC) -c $(CFLAGS) $(SRCDIR)/$@.c -o $(BINDIR)/$@.o

clean:
	rm $(BINFILES) $(BINDIR)/$(TARGET)

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
