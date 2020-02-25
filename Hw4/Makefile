CC = gcc
CFLAGS =  -Wall -g

default: command_executor

command_executor: command_executor.o 
	$(CC) $^ -o $@

command_executor.o: command_executor.c solution.c
	$(CC) -c $(CFLAGS) -o $@ command_executor.c

clean:
	/bin/rm -f command_executor.o command_executor



#### USED FOR TESTING ######################### IGNORE PLZ
# run: 
# 	./command_executor

# all: command_executor

############### -D is to add flag called CHAD :)
# CFLAGS =  -Wall -g -D CHAD