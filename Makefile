##
## FTP SERVER
##
## Makefile of the string_parser static library
##

# Compilation
CC		=	gcc
CFLAGS	=	-W -Werror -Wextra -Wall -I$(INCLUDE_DIRECTORY) 			\
									-I$(LIBRARY_STRING_PARSER_INCLUDE) 	\

BINARY_NAME							=	myftp
TEST_BINARY_NAME					=	myftp_test

LIBRARY_STRING_PARSER_NAME			=	string_parser.a
LIBRARY_STRING_PARSER_TEST_NAME		=	string_parser_test

OBJS		=	$(SRC:.c=.o)
MAIN_OBJ	=	$(MAIN_SRC:.c=.o)
TEST_OBJS	=	$(TEST_SRC:.c=.o)

CRITERION	=	-lcriterion -lgcov --coverage

STATIC_LIB_FLAG		=	-L$(LIBRARY_PATH) -lstring_parser

# Paths
SRC_DIRECTORY					=	./src
TEST_DIRECTORY					=	./tests
INCLUDE_DIRECTORY				=	./include
LIBRARY_PATH					=	./lib
LIBRARY_STRING_PARSER_INCLUDE	=	$(LIBRARY_PATH)/string_parser/include

# Source files
SRC			=	$(SRC_DIRECTORY)/argument/parser.c		\

# Main file
MAIN_SRC	=	$(SRC_DIRECTORY)/main.c					\

# Test files
TEST_SRC	=	$(TEST_DIRECTORY)/test.c				\

# Rules
all: $(BINARY_NAME)

$(BINARY_NAME): compile_library $(OBJS) $(MAIN_OBJ)
	$(CC) $(OBJS) $(MAIN_OBJ) -o $(BINARY_NAME) $(STATIC_LIB_FLAG)

compile_library:
	make -C $(LIBRARY_PATH)

tests_run: tests_compile
	./$(TEST_BINARY_NAME) -j1
	./$(LIBRARY_STRING_PARSER_TEST_NAME) -j1

tests_compile: compile_library $(OBJS) $(TEST_OBJS)
	make tests_compile -C $(LIBRARY_PATH) ; cp $(LIBRARY_PATH)/$(LIBRARY_STRING_PARSER_TEST_NAME) .
	$(CC) $(OBJS) $(TEST_OBJS) -o $(TEST_BINARY_NAME) $(STATIC_LIB_FLAG) $(CRITERION)

clean:
	make clean -C $(LIBRARY_PATH)
	rm -f $(OBJS) $(MAIN_OBJ) $(TEST_OBJS)

fclean: clean
	make fclean -C $(LIBRARY_PATH)
	rm -f $(TEST_BINARY_NAME) $(BINARY_NAME) $(LIBRARY_STRING_PARSER_TEST_NAME)

re: fclean all