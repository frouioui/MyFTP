##
## FTP SERVER
##
## Makefile of the string_parser static library
##

# Compilation
CC		=	gcc
CFLAGS	=	-W -Werror -Wextra -Wall -I$(INCLUDE_DIRECTORY) 				\
									-I$(LIBRARY_STRING_PARSER_INCLUDE)		\
									-I$(LIBRARY_SOCKET_INCLUDE)				\
									-I$(LIBRARY_MSG_QUEUE_INCLUDE)			\

# FTP server
BINARY_NAME							=	myftp
TEST_BINARY_NAME					=	myftp_test

# String parsing library
LIBRARY_STRING_PARSER_NAME			=	string_parser.a
LIBRARY_STRING_PARSER_TEST_NAME		=	string_parser_test

# Socket library
LIBRARY_SOCKET_NAME					=	socket.a
LIBRARY_SOCKET_TEST_NAME			=	socket_test

# Message queue library
LIBRARY_MSG_QUEUE_NAME				=	msg_queue.a
LIBRARY_MSG_QUEUE_TEST_NAME			=	msg_queue_test

# Object files
OBJS		=	$(SRC:.c=.o)
MAIN_OBJ	=	$(MAIN_SRC:.c=.o)
TEST_OBJS	=	$(TEST_SRC:.c=.o)

# Criterion flags
CRITERION	=	-lcriterion -lgcov --coverage

# Static library flags
STATIC_LIB_FLAG		=	-L$(LIBRARY_PATH) -lstring_parser -lsocket -lmsg_queue

# Paths
SRC_DIRECTORY					=	./src
TEST_DIRECTORY					=	./tests
INCLUDE_DIRECTORY				=	./include
LIBRARY_PATH					=	./lib

# Include path static libraries
LIBRARY_STRING_PARSER_INCLUDE	=	$(LIBRARY_PATH)/string_parser/include
LIBRARY_SOCKET_INCLUDE			=	$(LIBRARY_PATH)/socket/include
LIBRARY_MSG_QUEUE_INCLUDE		=	$(LIBRARY_PATH)/msg_queue/include

# Source files
SRC			=	$(SRC_DIRECTORY)/argument/parser.c					\
				$(SRC_DIRECTORY)/helper/helper.c					\
				$(SRC_DIRECTORY)/server/init_server.c				\
				$(SRC_DIRECTORY)/server/init_server_connection.c	\
				$(SRC_DIRECTORY)/server/server_error.c				\
				$(SRC_DIRECTORY)/server/server.c					\

# Main file
MAIN_SRC	=	$(SRC_DIRECTORY)/main.c								\

# Test files
TEST_SRC	=	$(TEST_DIRECTORY)/argument/parser_test.c			\
				$(TEST_DIRECTORY)/server/init_server_test.c			\

# Rules
all: $(BINARY_NAME)

$(BINARY_NAME): compile_library $(OBJS) $(MAIN_OBJ)
	$(CC) $(OBJS) $(MAIN_OBJ) -o $(BINARY_NAME) $(STATIC_LIB_FLAG)

debug: compile_library_debug
	$(CC) -g3 $(SRC) $(MAIN_SRC) -o $(BINARY_NAME) $(STATIC_LIB_FLAG) -I$(INCLUDE_DIRECTORY) -I$(LIBRARY_STRING_PARSER_INCLUDE) -I$(LIBRARY_SOCKET_INCLUDE) -I$(LIBRARY_MSG_QUEUE_INCLUDE)


compile_library:
	make -C $(LIBRARY_PATH)

compile_library_debug:
	make -C $(LIBRARY_PATH)

tests_run: tests_compile
	./$(TEST_BINARY_NAME) -j1
	./$(LIBRARY_PATH)/$(LIBRARY_STRING_PARSER_TEST_NAME) -j1
	./$(LIBRARY_PATH)/$(LIBRARY_MSG_QUEUE_TEST_NAME) -j1
	./$(LIBRARY_PATH)/$(LIBRARY_SOCKET_TEST_NAME) -j1

tests_compile: compile_library
	make tests_compile -C $(LIBRARY_PATH) ; cp $(LIBRARY_PATH)/$(LIBRARY_STRING_PARSER_TEST_NAME) .
	make tests_compile -C $(LIBRARY_PATH) ; cp $(LIBRARY_PATH)/$(LIBRARY_SOCKET_TEST_NAME) .
	make tests_compile -C $(LIBRARY_PATH) ; cp $(LIBRARY_PATH)/$(LIBRARY_MSG_QUEUE_TEST_NAME) .
	$(CC) $(SRC) $(TEST_SRC) -o $(TEST_BINARY_NAME) $(STATIC_LIB_FLAG) $(CRITERION) -I$(INCLUDE_DIRECTORY) -I$(LIBRARY_STRING_PARSER_INCLUDE) -I$(LIBRARY_SOCKET_INCLUDE) -I$(LIBRARY_MSG_QUEUE_INCLUDE)

clean:
	make clean -C $(LIBRARY_PATH)
	rm -f $(OBJS) $(MAIN_OBJ) $(TEST_OBJS)
	rm -f *.gcda
	rm -f *.gcno

fclean: clean
	make fclean -C $(LIBRARY_PATH)
	rm -f $(TEST_BINARY_NAME) $(BINARY_NAME) $(LIBRARY_STRING_PARSER_TEST_NAME) $(LIBRARY_MSG_QUEUE_TEST_NAME) $(LIBRARY_SOCKET_TEST_NAME)

re: fclean all