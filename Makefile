CC=clang
INCLDIR = include
BINDIR = bin
SRCDIR = src
CFLAGS = -g -O0 -fsanitize=address 
OBJS = runner ddmin reduce reduce_to_substring reduce_to_complement trace-pc-guard
BINS = $(addsuffix .o, $(OBJS))
BINFILES = $(addprefix bin/, $(BINS))
SRCS = $(addsuffix .c, $(OBJS))
SRCFILES = $(addprefix src/, $(SRCS))
VPATH=src
TARGET = main

all: $(OBJS)
	$(CC) $(CFLAGS) $(SRCDIR)/$(TARGET).c $(BINFILES) -o $(BINDIR)/$(TARGET)

$(OBJS) : | $(BINDIR)
	$(CC) -c $(CFLAGS) $(SRCDIR)/$@.c -o $(BINDIR)/$@.o


$(BINDIR):
	mkdir $(BINDIR)

clean:
	rm $(BINFILES) $(BINDIR)/$(TARGET)
