project: bubble_sort.o merge_sort.o insertion_sort.o selection_sort.o project.o graphics_funcs.o Makefile
	cc bubble_sort.o merge_sort.o insertion_sort.o selection_sort.o project.o graphics_funcs.o -o project -lncurses
bubble_sort.o: bubble_sort.c project.h graphics_funcs.h
	cc -Wall -c bubble_sort.c
merge_sort.o: merge_sort.c project.h graphics_funcs.h
	cc -Wall -c merge_sort.c 
insertion_sort.o: insertion_sort.c project.h graphics_funcs.h
	cc -Wall -c insertion_sort.c 
selection_sort.o: selection_sort.c project.h graphics_funcs.h
	cc -Wall -c selection_sort.c 
project.o: project.c project.h graphics_funcs.h
	cc -Wall -c project.c 
graphics_funcs.o: graphics_funcs.c project.h graphics_funcs.h
	cc -Wall -c graphics_funcs.c 
clean:
	rm *.o project
