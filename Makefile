CC = gcc
# -Wall: Enable all warnings
# -Werror: Treat warnings as errors
CFLAGS = -Wall 

# Check if DEBUG is defined and set to 1
ifeq ($(DEBUG), 1)
    CFLAGS += -DDEBUG=1
endif

# Get a list of all .c files in the current directory
# SRCS = $(wildcard *.c)
SRCS = main.c parser.c assembler.c

# Generate a list of corresponding .o files
OBJS = $(SRCS:.c=.o)

# Specify the name of the final executable
TARGET = hackassembler

# Default target, builds the final executable
all: $(TARGET)

# Rule to build the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile each .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up object files and the final executable
clean:
	rm -f $(OBJS) $(TARGET)