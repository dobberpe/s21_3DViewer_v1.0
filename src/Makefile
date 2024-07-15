#================================== COMPILER ==================================#
CC = gcc
CPP = g++
#==============================================================================#

#==================================== FLAGS ===================================#
CFLAGS = -Wall -Wextra -Werror -g --std=c11
CPPFLAGS = -Wall -Wextra -Werror -g --std=c++17
UNAME := $(shell uname)
# ifeq ($(UNAME), Linux)
# 	GFLAGS = -lncurses -lgtest -lstdc++
# endif

# ifeq ($(UNAME), Darwin)
# 	GFLAGS =  -I/opt/homebrew/include -L/opt/homebrew/lib -lncurses -lgtest
# endif
#==============================================================================#

#================================ TARGET NAMES ================================#
CLANG_FILE = ../materials/linters/.clang-format
PARSER = main
#==============================================================================#

#=============================== DIRECTORY NAMES ==============================#
PARSER_DIR = parser
TRANSFORM_DIR = transformations
COMMON_DIR = common
#==============================================================================#

#====================== LIST OF FILE AND DIRS IN MODULES ======================#
SOURCE_PARSER = $(wildcard $(PARSER_DIR)/*.c)
SOURCE_TRANSFORM= $(wildcard $(TRANSFORM_DIR)/*.c)
#==============================================================================#

#================================= MAIN TARGETS ===============================#
.PHONY: all install uninstall cli desktop launch_cli test gcov_report clang_i clang_n cppcheck valgrind_cli valgrind_test rebuild clean dvi dist

all: install

install:
	$(CC) $(CFLAGS) main.c $(SOURCE_PARSER) $(SOURCE_TRANSFORM) -o $(PARSER)

uninstall:

test:

gcov_report:

clang_i:
	@cp $(CLANG_FILE) .
	@clang-format -i $(PARSER_DIR)/*.c \
									$(PARSER_DIR)/*.h \
									$(TRANSFORM_DIR)/*.c \
									$(TRANSFORM_DIR)/*.h \
									$(COMMON_DIR)/*.h \
									*.c
	@rm .clang-format
	@echo "formatting..."

clang_n:
	@cp $(CLANG_FILE) .
	@clang-format -n $(PARSER_DIR)/*.c \
									$(PARSER_DIR)/*.h \
									$(TRANSFORM_DIR)/*.c \
									$(TRANSFORM_DIR)/*.h \
									$(COMMON_DIR)/*.h \
									*.c
	@rm .clang-format
	@echo "checking format..."

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --check-level=exhaustive $(PARSER_DIR)/* $(TRANSFORM_DIR)/* $(COMMON_DIR)/*

valgrind:
	valgrind -s -q --tool=memcheck --leak-check=yes --track-origins=yes --show-leak-kinds=all --verbose --log-file=valgrind_out.txt ./$(PARSER)
	@cat valgrind_out.txt
	@rm valgrind_out.txt

valgrind_test:

rebuild: uninstall install

clean:
	@rm -rf *.gcno *.gcda *.info report $(PARSER) main.dSYM dist
	@echo "cleaning..."

dvi:

dist:
	
#==============================================================================#

#============================== CREATE DIRECTORIES ============================#

#==============================================================================#