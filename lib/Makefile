##
## FTP SERVER
##
## Makefile of the string_parser static library
##

# Paths
STRING_PARSER_DIRECTORY		=	./string_parser
STRING_PARSER_LIB_NAME		=	libstring_parser.a
STRING_PARSER_TEST_NAME		=	string_parser_test

# Rules
all:
	make -C $(STRING_PARSER_DIRECTORY) ; cp $(STRING_PARSER_DIRECTORY)/$(STRING_PARSER_LIB_NAME) .

tests_run: tests_compile
	./$(STRING_PARSER_TEST_NAME) -j1

tests_compile:
	make tests_compile -C $(STRING_PARSER_DIRECTORY) ; cp $(STRING_PARSER_DIRECTORY)/$(STRING_PARSER_TEST_NAME) .

clean:
	make clean -C $(STRING_PARSER_DIRECTORY)

fclean: clean
	make fclean -C $(STRING_PARSER_DIRECTORY)
	rm -f $(STRING_PARSER_LIB_NAME) $(STRING_PARSER_TEST_NAME)

re: fclean all