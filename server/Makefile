OUTPUTS = server
CC = gcc

all: $(OUTPUTS)

clean:
	rm -f $(OUTPUTS)
	rm -f *.o
	
.PHONY: all clean

%.o: %.c %.h
	$(CC) -c -o $@ $<

server: main.c connection.c matrix.c matrixOperation.c
	gcc -std=c99  $^ -o $@ 
	
                


