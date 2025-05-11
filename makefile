# Compiler and options
CC = gcc
CFLAGS = -Wall -Wextra -g

# Executable name
TARGET = cy_fighters

# List of source files
SRCS = main.c utils.c fighters.c team.c combat.c
OBJS = $(SRCS:.c=.o)
DEPS = cy_fighters.h

# Default rule
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Generic rule to compile source files
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

# Rule to completely rebuild the project
remake: clean all

# Prevents Make from confusing filenames with targets
.PHONY: all clean run remake