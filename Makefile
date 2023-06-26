# A simple Makefile for compiling small SDL projects

# set the compiler
CC := gcc

# set the compiler flags  `sdl2-config --libs --cflags`  -lm
# CFLAGS := -Wall -lSDL2 -lSDL2_ttf -ldl

# add source files here
SRCS := main.c lexer/lexer.c parser/parser.c stree/stree.c

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := main

# recipe for building the final executable
$(EXEC): $(OBJS) Makefile
	$(CC) -o $@ $(OBJS)

# recipe for building object files
#$(OBJS): $(@:.o=.c) $(HDRS) Makefile
#    $(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(OBJS)