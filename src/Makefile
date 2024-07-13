CXX = g++
CC = gcc

VERSION = 0.0.69
BRANCH = develop

EXEC = s21_matrix_oop.a

SOURCE = $(wildcard s21_*.cpp)
HEADER = $(wildcard s21_*.h)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCE))

GTEST = $(wildcard testfiles/*.cpp)

CXXFLAGS = -std=c++17 -pthread -Wall -Werror -Wextra 

LIBFLAGS = -std=c++17 -lgtest_main -lgtest -lgmock 

VALGRIND = valgrind --tool=memcheck --leak-check=yes

CLANG = clang-format -style=Google

all: clean $(EXEC)

clean: clean_test clean_report
	rm -rf *.o $(PRE_EXEC) $(EXEC)

$(EXEC): $(OBJECTS)
	ar rc $@ $^
	ranlib $@
	rm -rf $^
	
%.o: %.cpp
	$(CC) -c $< -o $@ $(CXXFLAGS) 

test: $(EXEC)
	$(CXX) $(GTEST) $^ -o $@ $(LIBFLAGS) 
	./test

clean_test:
	rm -rf test

test_valgrind: test
	$(VALGRIND) ./test

gcov_report: $(SOURCE) clean_test clean_report
	$(CXX) --coverage $(GTEST) $< -o $@ $(LIBFLAGS) -o test
	./test
	gcovr -r . --html-details -o gcov_report.html
	# ~/.local/bin/gcovr -r . --html-details -o gcov_report.html
	mkdir GCOVRreport
	mv *.html *.css GCOVRreport
	rm -rf *.gcno *.gcda

lcov_report: $(SOURCE) clean_test clean_report
	$(CXX) -fprofile-arcs -ftest-coverage $(GTEST) $< -o $@ $(LIBFLAGS) -o test
	./test
	lcov --capture --directory . --output-file coverage.info --ignore-errors inconsistent
	genhtml coverage.info --output-directory coverage_report
	# ~/.local/bin/lcov -r . --html-details -o gcov_report.html
	rm -rf *.gcno *.gcda
	
open_report_l:
	firefox coverage_report/index.html

open_report:
	firefox GCOVRreport/gcov_report.html

clean_report:
	rm -rf *.gcno *.gcda *.html *.css GCOVRreport *.info coverage_report

format:
	$(CLANG) -n $(SOURCE) $(HEADER)

setformat:
	$(CLANG) -i $(SOURCE) $(HEADER)

commit:
	git add -A
	git commit -m "$(EXEC)_$(VERSION) - $(shell date +'%Y-%m-%d %H:%M')"
	git push origin $(BRANCH)