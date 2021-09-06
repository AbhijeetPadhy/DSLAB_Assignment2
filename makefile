CC = g++
CFLAGS = -Wall
OBJFILES = AVL_Tree.o main.o
TARGET = avl_tree_main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
