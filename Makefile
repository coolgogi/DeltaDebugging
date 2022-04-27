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

all: $(OBJS)
	$(CC) $(CFLAGS) -L/usr/local/lib $(SRCDIR)/$(TARGET).c -lgsl -lgslcblas $(BINFILES) -lm -o $(BINDIR)/$(TARGET) 

$(OBJS) : | $(BINDIR)
	$(CC) -c -Wall -I/usr/include $(CFLAGS) $(SRCDIR)/$@.c -o $(BINDIR)/$@.o

$(SPLIT) : split
	$(CC) $(CFLAGS) -L/usr/local/lib $(SRCDIR)/$(SPLIT).c -lgsl -lgslcblas $(BINDIR)/split.o -lm -o $(BINDIR)/$(SPLIT)

$(BINDIR):
	mkdir $(BINDIR)

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
