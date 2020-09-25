
default: testsim runsim

clear:
	rm runsim testsim

testsim: testsim.c
	gcc -Wall -ggdb -Werror -o testsim testsim.c

runsim: runsim.c
	gcc -Wall -ggdb -Werror -o runsim runsim.c
