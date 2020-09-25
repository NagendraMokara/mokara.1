# Compile automatically with make
$ make
gcc -Wall -ggdb -Werror -o testsim testsim.c
gcc -Wall -ggdb -Werror -o runsim runsim.c

# Run the program
$ ./runsim 2 < testing.data