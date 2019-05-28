a.exe : main.o core_functions.o
	gcc main.o core_functions.o -lm
core_functions.o : core_functions.c core_functions.h
	gcc -c core_functions.c
main.o : main.c core_functions.h
	gcc -c main.c