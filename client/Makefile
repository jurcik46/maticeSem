OUTPUTS = client
CC = gcc

all: $(OUTPUTS)

clean:
	rm -f $(OUTPUTS)
	rm -f *.o
	
.PHONY: all clean

%.o: %.c %.h
	$(CC) -c -o $@ $<

client: main.c connection.c matrix.c
	gcc -std=c99  $^ -o $@ 
	
                


