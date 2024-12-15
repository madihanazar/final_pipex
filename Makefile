# Compiler
CC = cc

# Compiler Flags
CFLAGS = -Wall -Wextra -Werror

# Source files for the main program
SRC = error.c helper.c pipex.c paths.c string_utils.c string_utils1.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

# Source files for the bonus version
BONUS_SRC = error.c helper_bonus.c pipex_bonus.c paths.c string_utils.c string_utils1.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

# Object files (replace .c with .o)
OBJ = $(SRC:.c=.o)

# Object files for the bonus version (replace .c with .o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

# Header file
HEADERS = pipex.h

# Output executables
EXEC = pipex
BONUS_EXEC = pipex_bonus

# Default target to build the executable
all: $(EXEC)

# Rule to build the main executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Rule to build the bonus executable
$(BONUS_EXEC): $(BONUS_OBJ)
	$(CC) $(BONUS_OBJ) -o $(BONUS_EXEC)

# Rule to create object files from source files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the main executable
clean:
	rm -f $(OBJ) $(BONUS_OBJ)

# Remove all generated files (object files and executables)
fclean: clean
	rm -f $(EXEC) $(BONUS_EXEC)

# Rebuild the project (clean and then build)
re: fclean all

# Rule to build the bonus version (run this with `make bonus`)
bonus: $(BONUS_EXEC)

# Rule to check for the headers (useful for debugging)
.PHONY: all clean fclean re bonus
