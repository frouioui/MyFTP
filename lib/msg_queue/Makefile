##
## FTP SERVER
##
## Makefile of the msg_queue static library
##

# Compilation
CC		=	gcc
CFLAGS	=	-W -Werror -Wextra -Wall -I$(INCLUDE_DIRECTORY)

LIBRARY_NAME	=	libmsg_queue.a
TEST_NAME		=	msg_queue_test
DEBUG_NAME		=	msg_queue

OBJS		=	$(SRC:.c=.o)
TEST_OBJS	=	$(TEST_SRC:.c=.o)

CRITERION	=	-lcriterion -lgcov --coverage

# Paths
SRC_DIRECTORY		=	./src
TEST_DIRECTORY		=	./tests
INCLUDE_DIRECTORY	=	./include

# Source files
SRC				=	$(SRC_DIRECTORY)/append_new_message.c						\
					$(SRC_DIRECTORY)/create_msg_queue.c							\
					$(SRC_DIRECTORY)/is_message_done.c							\
					$(SRC_DIRECTORY)/destroy_msg_queue.c						\
					$(SRC_DIRECTORY)/read_and_trim_last_message.c				\

# Main file
SRC_MAIN		=	$(SRC_DIRECTORY)/main.c										\

# Test files
TEST_SRC		=	$(TEST_DIRECTORY)/create_msg_queue_tests.c					\
					$(TEST_DIRECTORY)/is_message_done_tests.c					\
					$(TEST_DIRECTORY)/append_new_message_tests.c				\
					$(TEST_DIRECTORY)/read_and_trim_last_message_tests.c		\

# Rules
all: $(LIBRARY_NAME)

$(LIBRARY_NAME): $(OBJS)
	ar rc $(LIBRARY_NAME) $(OBJS)
	ar t $(LIBRARY_NAME)

debug:
	gcc -g3 $(SRC) $(SRC_MAIN) -o msg_queue -I$(INCLUDE_DIRECTORY)

tests_compile:
	$(CC) $(SRC) $(TEST_SRC) -o $(TEST_NAME) $(CRITERION) -I$(INCLUDE_DIRECTORY)

clean:
	rm -f $(OBJS) $(TEST_OBJS)
	rm -f *.gcda
	rm -f *.gcno
	
fclean: clean
	rm -f $(LIBRARY_NAME) $(TEST_NAME) $(DEBUG_NAME)

re: fclean all