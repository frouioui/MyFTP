##
## FTP SERVER
##
## Makefile of the string_parser static library
##

# Compilation
CC		=	gcc
CFLAGS	=	-W -Werror -Wextra -Wall -I$(INCLUDE_DIRECTORY)

LIBRARY_NAME	=	libstring_parser.a
TEST_NAME		=	string_parser_test

OBJS		=	$(SRC:.c=.o)
TEST_OBJS	=	$(TEST_SRC:.c=.o)

CRITERION	=	-lcriterion -lgcov --coverage

# Paths
SRC_DIRECTORY		=	./src
TEST_DIRECTORY		=	./tests
INCLUDE_DIRECTORY	=	./include

# Source files
SRC				=	$(SRC_DIRECTORY)/is_number.c			\

# Test files
TEST_SRC		=	$(TEST_DIRECTORY)/is_number_test.c		\

# Rules
all: $(LIBRARY_NAME)

$(LIBRARY_NAME): $(OBJS)
	ar rc $(LIBRARY_NAME) $(OBJS)
	ar t $(LIBRARY_NAME)

tests_compile:
	$(CC) $(SRC) $(TEST_SRC) -o $(TEST_NAME) $(CRITERION) -I$(INCLUDE_DIRECTORY)

clean:
	rm -f $(OBJS) $(TEST_OBJS)
	rm -f *.gcda
	rm -f *.gcno
	
fclean: clean
	rm -f $(LIBRARY_NAME) $(TEST_NAME)

re: fclean all