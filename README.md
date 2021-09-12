# -DSLAB_Assignment2
AVL Tree

System Requirements
======================
1. Windows  
	i. GNU make  
		https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download  
	ii. GNU GCC compiler  
	iii. Graphwiz  
		https://graphviz.org/download/
	Please remember to add path to environemt variable during installation for each of the above mentioned tools.
	
2. Linux  
	i. Graphwiz  
	https://graphviz.org/download/
	
	
Build Instructions  
==================
run the following command in terminal in the same directory as source code:  
	make  

This is expected to produce the executable binary which goes by the name "avl_tree_main.exe" in windows and "avl_tree_main" in linux.

Execution instructions
====================
1. Windows : In Command Prompt type
	avl_tree_main.exe  
2. Linux  : In terminal type
	./avl_tree_main  

Program Instructions
====================

You are first shown the menu which looks like this:

	This is an implementation of AVL Tree
	--------------------------------------------------------
	1. Insert an element
	2. Delete an element
	3. Search for an element
	4. Print an image of the tree
	5. Insert a series of elements
	6. Clone a tree and print it.

	Press 0 to quit.
	Enter Your Choice: 

Enter the required option and follow the steps shown in terminal. Examples of each of them are shown below:

1. Insert an element

	Enter Your Choice: 1

	------------------OPERATION-------------------
	Please enter the element you want to insert: 12

2. Delete an element

Enter Your Choice: 2

------------------OPERATION-------------------
Please enter the element you want to delete: 12
Element 12 has been successfully deleted!

3. Search for an element

Enter Your Choice: 3

------------------OPERATION-------------------
Please enter the element you want to search: 12
The searched element is found!

4. Print an image of the tree

Enter Your Choice: 4

------------------OPERATION-------------------
An image of the tree can be produced by using the following command:
dot -Tpng graph.gv -o graph.png
The image will be named graph.png and will be present in the same path

5. Insert a series of elements

Enter Your Choice: 5

------------------OPERATION-------------------
Enter the number of elements you want to insert: 5
Insert all the elements:
3 2 4 1 5

6. Clone a tree and print it.

Enter Your Choice: 6

------------------OPERATION-------------------
Cloning the tree...
Printing the tree. Check the filename cloned_graph.gv
Operation Successful. Please check the file cloned_graph.gv

7. Quit
Enter Your Choice: 0

Clean Instructions  
==================
run the following command in terminal in the same directory as source code:  
	make clean

This is supposed to delete all files created during build process.
