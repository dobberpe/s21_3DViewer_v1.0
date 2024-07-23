#================================== COMPILER ==================================#
CC = gcc
CPP = g++
#==============================================================================#

#==================================== FLAGS ===================================#
CFLAGS = -Wall -Wextra -Werror -g --std=c11
CPPFLAGS = -Wall -Wextra -Werror -g --std=c++17
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	GFLAGS = -lm -lcheck -lsubunit
endif

ifeq ($(UNAME), Darwin)
	GFLAGS =  -lcheck
endif
#==============================================================================#

#================================ TARGET NAMES ================================#
CLANG_FILE = ../materials/linters/.clang-format
PARSER = main
TEST = test_laucnher
ARG ?= $(PARSER)
#==============================================================================#

#=============================== DIRECTORY NAMES ==============================#
PARSER_DIR = parser
TRANSFORM_DIR = transformations
COMMON_DIR = common
TEST_DIR = tests
#==============================================================================#

#====================== LIST OF FILE AND DIRS IN MODULES ======================#
SOURCE_PARSER = $(wildcard $(PARSER_DIR)/*.c)
SOURCE_TRANSFORM= $(wildcard $(TRANSFORM_DIR)/*.c)
SOURCE_TEST = $(wildcard $(TEST_DIR)/*.c)
#==============================================================================#

#================================= MAIN TARGETS ===============================#
.PHONY: all install uninstall cli desktop launch_cli test gcov_report clang_i clang_n cppcheck valgrind_cli valgrind_test rebuild clean dvi dist

all: install

install:

uninstall:

test: clean
	$(CC) $(CFLAGS) $(SOURCE_TEST) $(SOURCE_PARSER) $(SOURCE_TRANSFORM) -o $(TEST) $(GFLAGS)
	@echo "\nrunning tests..."
	@./$(TEST)
	@echo "\ndeleting test launcher..."
	@rm -rf $(TEST)

gcov_report: clean
	$(CC) $(CFLAGS) $(SOURCE_TEST) $(SOURCE_PARSER) $(SOURCE_TRANSFORM) -o $(TEST) $(GFLAGS) --coverage
	@./$(TEST)
	@lcov -t "tests" -o tests.info -c -d . -rc lcov_branch_coverage=1 --exclude "$(PWD)/tests/*"
	@genhtml -o report tests.info -rc lcov_branch_coverage=1
	@rm -rf *.gcno *.gcda *.gcov


format:
	@cp $(CLANG_FILE) .
	@find . -name '*.c' -o -name '*.h' -o -name '*.cpp' -o -name '*.hpp' 2>/dev/null | xargs -r clang-format -i
	@rm .clang-format
	@echo "formatting..."

format_check:
	@cp $(CLANG_FILE) .
	@find . -name '*.c' -o -name '*.h' -o -name '*.cpp' -o -name '*.hpp' 2>/dev/null | xargs -r clang-format -n
	@rm .clang-format
	@echo "checking format..."

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --check-level=exhaustive $(PARSER_DIR)/* $(TRANSFORM_DIR)/* $(COMMON_DIR)/* $(TEST_DIR)/*

valgrind:
	valgrind -s -q --tool=memcheck --leak-check=yes --track-origins=yes --show-leak-kinds=all --verbose --log-file=valgrind_out.txt ./$(ARG)
	@cat valgrind_out.txt
	@rm valgrind_out.txt

valgrind_tests: clean
	$(CC) $(CFLAGS) $(SOURCE_TEST) $(SOURCE_PARSER) $(SOURCE_TRANSFORM) -o $(TEST) $(GFLAGS)
	@echo "\nstarting valgrind on tests...\n"
	valgrind -s -q --tool=memcheck --leak-check=yes --track-origins=yes --show-leak-kinds=all --verbose --log-file=valgrind_out.txt ./$(TEST)
	@cat valgrind_out.txt
	@rm valgrind_out.txt

rebuild: uninstall install

clean:
	@rm -rf *.gcno *.gcda *.info report $(PARSER) $(TEST) *.dSYM dist a.out
	@echo "cleaning...\n"

dvi:

dist:
	
#==============================================================================#

#============================== CREATE DIRECTORIES ============================#

#==============================================================================#