##
## FTP SERVER
##
## Makefile of the string_parser static library
##

# Paths
STRING_PARSER_DIRECTORY		=	./string_parser
STRING_PARSER_LIB_NAME		=	libstring_parser.a
STRING_PARSER_TEST_NAME		=	string_parser_test

SOCKET_DIRECTORY			=	./socket
SOCKET_LIB_NAME				=	libsocket.a
SOCKET_TEST_NAME			=	socket_test

# Rules
all:
	make -C $(STRING_PARSER_DIRECTORY) ; cp $(STRING_PARSER_DIRECTORY)/$(STRING_PARSER_LIB_NAME) .
	make -C $(SOCKET_DIRECTORY) ; cp $(SOCKET_DIRECTORY)/$(SOCKET_LIB_NAME) .

debug:
	make CC="gcc -g3" -C $(STRING_PARSER_DIRECTORY) ; cp $(STRING_PARSER_DIRECTORY)/$(STRING_PARSER_LIB_NAME) .
	make CC="gcc -g3" -C $(SOCKET_DIRECTORY) ; cp $(SOCKET_DIRECTORY)/$(SOCKET_LIB_NAME) .

tests_run: tests_compile
	./$(STRING_PARSER_TEST_NAME) -j1
	./$(SOCKET_TEST_NAME) -j1

tests_compile:
	make tests_compile -C $(STRING_PARSER_DIRECTORY) ; cp $(STRING_PARSER_DIRECTORY)/$(STRING_PARSER_TEST_NAME) .
	make tests_compile -C $(SOCKET_DIRECTORY) ; cp $(SOCKET_DIRECTORY)/$(SOCKET_TEST_NAME) .

clean:
	make clean -C $(STRING_PARSER_DIRECTORY)
	make clean -C $(SOCKET_DIRECTORY)

fclean: clean
	make fclean -C $(STRING_PARSER_DIRECTORY)
	make fclean -C $(SOCKET_DIRECTORY)
	rm -f $(STRING_PARSER_LIB_NAME) $(STRING_PARSER_TEST_NAME) $(SOCKET_LIB_NAME) $(SOCKET_TEST_NAME)

re: fclean all