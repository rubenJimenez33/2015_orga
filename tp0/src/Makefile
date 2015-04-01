CC=gcc -g -O0
CFLAGS=-c -Wall
LDFLAGS=
OBJ_DIR=/
SOURCES=main.c

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=tp0

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
