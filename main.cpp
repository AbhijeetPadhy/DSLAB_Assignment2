#include<iostream>

using namespace std;

class AVL_Node{
	private:
		int key;
		int bf; //balance factor bf = height(left subtree) - height(right subtree)
		AVL_Node *LChild, *RChild;
	public:
		AVL_Node(int k){
			key = k;
			bf = 0;
			LChild = NULL;
			RChild = NULL;
		}
	friend class AVL_Tree;
};

class AVL_Tree{
	private:
		AVL_Node *root;
		AVL_Node * insert(AVL_Node *root, int k);
		int printTreeUtil(AVL_Node* node, FILE *fptr);
	public:
		AVL_Tree();
		AVL_Tree(const AVL_Tree &T);
		AVL_Tree &operator=(const AVL_Tree &T);
		void AVL_Insert(int k);
		void AVL_Delete(int k);
		bool AVL_Search(int k);
		void AVL_Print(const char *filename);
		~AVL_Tree();
};

AVL_Tree::AVL_Tree(){
	root = NULL;
}

AVL_Tree::AVL_Tree(const AVL_Tree &T){
	
}
AVL_Tree & AVL_Tree::operator=(const AVL_Tree &T){
	
}

AVL_Node * AVL_Tree::insert(AVL_Node *root, int k){
	if(root == NULL)
		return new AVL_Node(k);
	if(k < root->key)
		root->LChild = insert(root->LChild,k);
	if(k > root->key)
		root->RChild = insert(root->RChild,k);
	return root;
}

void AVL_Tree::AVL_Insert(int k){
	if(root == NULL)
		root = new AVL_Node(k);
	else
		root = insert(root,k);
}
void AVL_Tree::AVL_Delete(int k){
	
}
bool AVL_Tree::AVL_Search(int k){
	
}

int AVL_Tree::printTreeUtil(AVL_Node* node, FILE *fptr){
	fprintf(fptr,"node%d [label = \"<f0> | <f1> %d | <f2>\"];\n",node->key,node->key);
	if(node->LChild != NULL){
		printTreeUtil(node->LChild, fptr);
		fprintf(fptr,"\"node%d\":f0 -> \"node%d\":f1;\n",node->key,node->LChild->key);
	}
		
	if(node->RChild != NULL){
		printTreeUtil(node->RChild, fptr);
		fprintf(fptr,"\"node%d\":f2 -> \"node%d\":f1;\n",node->key,node->RChild->key);
	}
	
	return node->key;
}

void AVL_Tree::AVL_Print(const char *filename){
	FILE *fptr;
	fptr = fopen(filename,"w");
	fprintf(fptr,"digraph G {\n");
	fprintf(fptr,"node [shape = record,height=.1];\n");
	printTreeUtil(root, fptr);
	fprintf(fptr,"}");
	fclose(fptr);
}
AVL_Tree::~AVL_Tree(){
	
}

int main(){
	int choice = -1;
	int element = -1, element2=-1;
	char str[] = "graph.gv";
	AVL_Tree *tree = new AVL_Tree();
	do{
		cout<<"\nThis is an implementation of AVL Tree"<<endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"1. Insert an element"<<endl;
		cout<<"2. Delete an element"<<endl;
		cout<<"3. Search for an element"<<endl;
		cout<<"4. Print an image of the tree"<<endl;
		cout<<"5. Insert a series of elements"<<endl;
		cout<<"\nPress 0 to quit.";
		cout<<"\nEnter Your Choice: ";
		cin>>choice;
		cout<<"\n------------------OPERATION-------------------"<<endl;
		switch(choice){
			case 0:
				break;
			case 1:
				cout<<"Please enter the element you want to insert: ";
				cin>>element;
				tree->AVL_Insert(element);
				break;
			case 2:
				cout<<"Please enter the element you want to delete: ";
				cin>>element;
				tree->AVL_Delete(element);
				break;
			case 3:
				cout<<"Please enter the element you want to search: ";
				cin>>element;
				if(tree->AVL_Search(element))
					cout<<"The searched element is found!"<<endl;
				else
					cout<<"The searched element is not found!"<<endl;
				break;
			case 4: 
				cout<<"An image of the tree can be produced by using the following command: "<<endl;
				cout<<"dot -Tpng graph.gv -o graph.png"<<endl;
				cout<<"The image will be named graph.png and will be present in the same path"<<endl;
				tree->AVL_Print(str);
				break;
			case 5:
				cout<<"Enter the number of elements you want to insert: ";
				cin>>element;
				cout<<"Insert all the elements:"<<endl;
				for(int i=0;i<element;i++){
					cin>>element2;
					tree->AVL_Insert(element2);
				}
				break;
			default:
				cout<<"Incorrect Choice!"<<endl;
				break;
		}
	}while(choice != 0);
	return 0;
}
