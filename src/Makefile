OS = $(shell uname)

SOURCES = 'Cube v2.0'/affine.c 'Cube v2.0'/parser.c
CFLAGS= -std=c11 -Wall -Wextra -Werror -g #-O0 
CHECKFLAGS=$(shell pkg-config --libs check)
GCOVFLAGS=-fprofile-arcs -ftest-coverage
LFLAGS=-lgcov --coverage
CC= gcc


ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
	UNTPATH = 'Cube v2.0'/ogltest1.app
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lcheck_pic -lrt -lm
	UNTPATH = 'Cube v2.0'/ogltest1
endif

all: install

.PHONY: all, install, uninstall, clean, dvi, dist, tests, gcov_report

install: 
	make uninstall && make clean
	cd ../ && mkdir build
	cd 'Cube v2.0' && qmake6 && make && make clean && cd ../ && mv $(UNTPATH) ../build/

dvi:
	open dvi.md

uninstall:
	rm -rf ../build*

dist: 
	rm -rf Archive_3D_Viewer_v1.0
	mkdir Archive_3D_Viewer_v1.0
	cp -a ../build/* Archive_3D_Viewer_v1.0
	tar -cvzf Archive_3D_Viewer_v1.0.tar.gz Archive_3D_Viewer_v1.0

test:
	checkmk tests.check > tests.c
	gcc tests.c $(SOURCES) $(TEST_LIBS) -o tests #-fsanitize=address
	clang-format -i tests.c
	./tests 

gcov_report: 
	make test
	gcc tests.c $(SOURCES) $(TEST_LIBS) --coverage -o ./gcov
	./gcov
	lcov -t "./gcov" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html
	rm -rf *.gcno *gcda *.gcov

format:
	clang-format -i -style=google *.c *.h
	clang-format -n -style=google *.c *.h

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css calc *.dSYM tests *.info s21_viewer_tests s21_viewer_tests.c report/ .DS_Store ../.DS_Store .clang-format 
	rm -rf Archive_3D_Viewer_v1.0 gcov
	rm -rf *gz
