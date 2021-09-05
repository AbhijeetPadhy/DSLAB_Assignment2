
#include<iostream>
#include <stack>

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

class Stack_Node{
	public:
		AVL_Node *node;
		int a;
	Stack_Node(){
		node = NULL;
		a = 0;
	}
	Stack_Node(AVL_Node *P, int n){
		node = P;
		a = n;
	}
};

class AVL_Tree{
	private:
		AVL_Node *root;
		int printTreeUtil(AVL_Node* node, FILE *fptr);
		bool AVL_Search_util(AVL_Node *node, int k);
		AVL_Node* AVL_Clone(AVL_Node *node);
		void AVL_ClearTree(AVL_Node *node);
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

AVL_Node* AVL_Tree::AVL_Clone(AVL_Node *node){
	if(node == NULL)
		return NULL;
	AVL_Node *new_node = new AVL_Node(node->key);
	new_node->bf = node->bf;
	new_node->LChild = AVL_Clone(node->LChild);
	new_node->RChild = AVL_Clone(node->RChild);
	
	return new_node;
}

// copy constructor
AVL_Tree::AVL_Tree(const AVL_Tree &T){
	root = NULL;
	root = AVL_Clone(T.root);
}

AVL_Tree & AVL_Tree::operator=(const AVL_Tree &T){
	cout<<"Equal to operator overloading!!"<<endl;
	if(this != &T){
		cout<<"Different trees!"<<endl;
		AVL_ClearTree(root);
		root = NULL;
		root = AVL_Clone(T.root);
	}
	return *this;
}

void AVL_Tree::AVL_Insert(int k){
	if(root == NULL){
		root = new AVL_Node(k);
		return;
	}
	AVL_Node *P,*S,*Q, *R;
	AVL_Node *T = new AVL_Node(-1);
	AVL_Node *dummy = T;
	T->RChild = root;
	S = P = root;
	bool flag = false;
	int a;
	while(k != P->key){
		if(k < P->key){
			Q = P->LChild;
			if(Q == NULL){
				Q = new AVL_Node(k);
				P->LChild = Q;
				flag = true;
				break;
			}else if(Q->bf != 0){
				T = P;
				S = Q;
			}
			P = Q;
		}else if(k > P->key){
			Q = P->RChild;
			if(Q == NULL){
				Q = new AVL_Node(k);
				P->RChild = Q;
				flag = true;
				break;
			}else if(Q->bf != 0){
				T = P;
				S = Q;
			}
			P = Q;
		}	
	}
	if(flag == false){
		delete(dummy);
		throw "Element Already Exists Exception!";
	}
	if(k < S->key){
		R = P = S->LChild;
		a = -1;
	}else{
		R = P = S->RChild;
		a = 1;
	}
	while(P != Q){
		if(k < P->key){
			P->bf = 1;
			P = P->LChild;
		}else if(k > P->key){
			P->bf = -1;
			P = P->RChild;
		}
	}
	if(S->bf == 0){
		S->bf = -a;
		delete(dummy);
		return;
	}
	else if(S->bf == a){
		S->bf = 0;
		delete(dummy);
		return;
	}else if(S->bf == -a){
		if(R->bf == -a){
			//A8
			P = R;
			if(a == -1){
				S->LChild = R->RChild;
				R->RChild = S;
			}else if(a == 1){
				S->RChild = R->LChild;
				R->LChild = S;
			}
			S->bf = R->bf = 0;
		}else if(R->bf == a){
			//A9
			if(a == -1){
				P = R->RChild;
				R->RChild = P->LChild;
				P->LChild = R;
				S->LChild = P->RChild;
				P->RChild = S;
			}else if(a == 1){
				P = R->LChild;
				R->LChild = P->RChild;
				P->RChild = R;
				S->RChild = P->LChild;
				P->LChild = S;
			}
			if(P->bf == -a){
				S->bf = a;
				R->bf = 0;
			}else if(P->bf == 0){
				S->bf = 0;
				R->bf = 0;
			}else if(a == 1){
				S->bf = 0;
				R->bf = -a;
			}
			P->bf = 0;
		}
	}
	if(S == T->RChild)
		T->RChild = P;
	else
		T->LChild = P;
	root = dummy->RChild;
	delete(dummy);
}

	// 1. Delete node only from leaf or if it has a single child, kind of using successor
	// 2. Store the path in stack
	// 3. Manage the bf as you move up the stack
	// 4. Rebalancing might be required in a particular case which will be same as in insertion.

void AVL_Tree::AVL_Delete(int k){
	stack<Stack_Node*> stack;
	AVL_Node *P = root, *Q = NULL;
	AVL_Node* dummy = new AVL_Node(0);
	dummy->RChild = P;
	Q = dummy;
	stack.push(new Stack_Node(Q,+1));
	while(P != NULL){
		if(k < P->key){
			// Visit left subtree
			stack.push(new Stack_Node(P,-1));
			cout<<"Pushing element: "<<P->key<<endl;
			Q = P;
			P = P->LChild;
			
		}else if(k > P->key){
			// Visit right subtre
			cout<<"Pushing element: "<<P->key<<endl;
			stack.push(new Stack_Node(P,+1));
			Q = P;
			P = P->RChild;
		}else{
			// This is the node to be deleted
			//case1: Leaf Node
			if(P->LChild == NULL && P->RChild == NULL){
				cout<<"Leaf Node!"<<Q->key;
				// If root node is to be deleted
				if(P == root){
					root = NULL;
					Q->RChild = root;
				}
				else if(k < Q->key){
					Q->LChild = NULL;
				}else{
					Q->RChild = NULL;
				}
				delete(P);
				P = NULL;
			}
			//case2: Node to be deleted has only one child
			else if(P->LChild == NULL || P->RChild == NULL){
				// If P has only right child
				if(P->RChild != NULL){
					// If root node is to be deleted
					if(P == root){
						//If P points to root, Q points to dummy. The right child of dummy should point to the new root.
						root = P->RChild;
						Q->RChild = root;
					}
					// If P is left child of Q
					else if(P->key < Q->key){
						Q->LChild = P->RChild;
					}
					// If P is right child of Q
					else{
						Q->RChild = P->RChild;
					}
				}
				// If P has only left child
				else{
					// If root node is to be deleted
					if(P == root){
						root = P->LChild;
						Q->RChild = root;
					}
					// If P is left child of Q
					else if(P->key < Q->key){
						Q->LChild = P->LChild;
					}
					// If P is right child of Q
					else{
						Q->RChild = P->LChild;
					}
				}
				delete(P);
				P = NULL;
			}
			//case3: Node to be deleted has two children
			else{
				// find successor
				AVL_Node *cur = P->RChild;
				cout<<"Starting from "<<cur->key<<endl;
				while(cur->LChild != NULL)
					cur = cur->LChild;
				int a = cur->key;
				AVL_Delete(cur->key);
				P->key = a;
				P = NULL;
				return; // balancing is done once when  we deleted the successor. We arent deleting any more elements.
			}
		}
	}
	Stack_Node *temp;
	while (!stack.empty()) {
    	temp = stack.top();
    	cout<<"element: "<<temp->node->key<<endl;
    	stack.pop();
    	if(temp->node == dummy)
    		break;
    	if(temp->node->bf == -temp->a){
    		temp->node->bf = 0;
		}else if(temp->node->bf == 0){
			temp->node->bf = temp->a;
			break;
		}else if(temp->node->bf == temp->a){
			// Rebalancing is required!
			Stack_Node *parent = stack.top();
			if(temp->node->bf == -1 ){ // This means deletion occured on left sub tree and right sub tree has a higher length now
				//temp = A
				AVL_Node *right_child = temp->node->RChild;
				// case 1a and case 3a: Single Left Rotation 
				if(right_child->bf <= 0){ 
					temp->node->RChild = right_child->LChild;
					right_child->LChild = temp->node;
					
					if(parent->a == +1)
						parent->node->RChild = right_child;
					else if(parent->a == -1)
						parent->node->LChild = right_child;
					else
						parent->node->RChild = right_child; // when parent is dummy!
					// case 1a:
					if(right_child->bf == -1){
						temp->node->bf = 0;
						right_child->bf = 0;
					}
					// case 3a: It is a part of case 1a with a slight modification in balance factors
					else if(right_child->bf == 0){
						temp->node->bf = -1;
						right_child->bf = +1;
						break;
					}
				}
				// case 2a: Right-Left Rotation
				else{
					//asigning names
					AVL_Node * A = temp->node;
					AVL_Node * B = temp->node->RChild;
					AVL_Node * X = B->LChild;
					AVL_Node * alpha = A->LChild;
					AVL_Node * beta = X->LChild;
					AVL_Node * gamma = X->RChild;
					AVL_Node * delta = B->RChild;
					
					// rotating and handling links
					X->LChild = A;
					X->RChild = B;
					
					A->LChild = alpha;
					A->RChild = beta;
					
					B->LChild = gamma;
					B->RChild = delta;
					
					if(parent->a == +1)
						parent->node->RChild = X;
					else if(parent->a == -1)
						parent->node->LChild = X;
					else
						parent->node->RChild = X; // when parent is dummy!
					
					// Correcting BF
					if(X->bf == -1){
						// alpha = h, beta = h-1, gamma = h, delta = h
						A->bf = +1;
						B->bf = 0;
					}else if(X->bf == 0){
						// alpha = h, beta = h, gamma = h, delta = h
						A->bf = 0;
						B->bf = 0;
					}else if(X->bf == 1){
						// alpha = h, beta = h, gamma = h-1, delta = h
						A->bf = 0;
						B->bf = -1;
					}
					X->bf = 0;	
				}	
			}else{
				//temp = A
				AVL_Node *left_child = temp->node->LChild;
				// case 1b and 3b:
				if(left_child->bf >= 0){ 
					temp->node->LChild = left_child->RChild;
					left_child->RChild = temp->node;
					
					if(parent->a == +1)
						parent->node->RChild = left_child;
					else if(parent->a == -1)
						parent->node->LChild = left_child;
					else
						parent->node->RChild = left_child;
					// case 1b:
					if(left_child->bf == +1){
						temp->node->bf = 0;
						left_child->bf = 0;
					}
					// case 3b: It is a part of case 1b with a slight modification in balance factors
					else if(left_child->bf == 0){
						temp->node->bf = +1;
						left_child->bf = -1;
						break;
					}
				}
				// case 2b:
				else{
					//asigning names
					AVL_Node * A = temp->node;
					AVL_Node * B = A->LChild;
					AVL_Node * X = B->RChild;
					AVL_Node * alpha = A->RChild;
					AVL_Node * beta = X->RChild;
					AVL_Node * gamma = X->LChild;
					AVL_Node * delta = B->LChild;
					
					// rotating and handling links
					X->LChild = B;
					X->RChild = A;
					
					A->LChild = beta;
					A->RChild = alpha;
					
					B->LChild = delta;
					B->RChild = gamma;
					
					if(parent->a == +1)
						parent->node->RChild = X;
					else if(parent->a == -1)
						parent->node->LChild = X;
					else
						parent->node->RChild = X; // when parent is dummy!
					
					// Correcting BF
					if(X->bf == -1){
						// alpha = h, beta = h, gamma = h-1, delta = h
						A->bf = 0;
						B->bf = +1;
					}else if(X->bf == 0){
						// alpha = h, beta = h, gamma = h, delta = h
						A->bf = 0;
						B->bf = 0;
					}else if(X->bf == +1){
						// alpha = h, beta = h-1, gamma = h, delta = h
						A->bf = -1;
						B->bf = 0;
					}
					X->bf = 0;	
				}
			}
		}
    }
    root = dummy->RChild;
    delete(dummy);
}

bool AVL_Tree::AVL_Search_util(AVL_Node *node, int k){
	if(node == NULL)
		return false;
	if(node->key == k)
		return true;
	if(k < node->key)
		return AVL_Search_util(node->LChild, k);
	return AVL_Search_util(node->RChild, k);
}

bool AVL_Tree::AVL_Search(int k){
	return AVL_Search_util(root,k);
}

int AVL_Tree::printTreeUtil(AVL_Node* node, FILE *fptr){
	fprintf(fptr,"%d [label = \"<f0> | <f1> %d / %d | <f2>\"];\n",node->key,node->key, node->bf);
	if(node->LChild != NULL){
		printTreeUtil(node->LChild, fptr);
		fprintf(fptr,"\"%d\":f0 -> \"%d\":f1;\n",node->key,node->LChild->key);
	}
		
	if(node->RChild != NULL){
		printTreeUtil(node->RChild, fptr);
		fprintf(fptr,"\"%d\":f2 -> \"%d\":f1;\n",node->key,node->RChild->key);
	}
	
	return node->key;
}

void AVL_Tree::AVL_Print(const char *filename){
	if(root == NULL){
		cout<<"The Tree is empty, so nothing will be generated!\n";
		return;
	}
	FILE *fptr;
	fptr = fopen(filename,"w");
	fprintf(fptr,"digraph G {\n");
	fprintf(fptr,"node [shape = record,height=.1];\n");
	printTreeUtil(root, fptr);
	fprintf(fptr,"}");
	fclose(fptr);
}

void AVL_Tree::AVL_ClearTree(AVL_Node *node){
	if(node == NULL)
		return;
	AVL_ClearTree(node->LChild);
	AVL_ClearTree(node->RChild);
	delete(node);
	return;
}

AVL_Tree::~AVL_Tree(){
	cout<<"Destructing object..."<<endl;
	AVL_ClearTree(root);
	root = NULL;
}

int main(){
	int choice = -1;
	int element = -1, element2=-1;
	char str[] = "graph.gv";
	AVL_Tree *clone = NULL;
	AVL_Tree *tree = new AVL_Tree();
	do{
		cout<<"\nThis is an implementation of AVL Tree"<<endl;
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"1. Insert an element"<<endl;
		cout<<"2. Delete an element"<<endl;
		cout<<"3. Search for an element"<<endl;
		cout<<"4. Print an image of the tree"<<endl;
		cout<<"5. Insert a series of elements"<<endl;
		cout<<"6. Clone a tree and print it."<<endl;
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
			case 6:
				cout<<"Cloning the tree..."<<endl;
				clone = new AVL_Tree(*tree);
				cout<<"Printing the tree. Check the filename cloned_graph.gv"<<endl;
				clone->AVL_Print("cloned_graph.gv");
				cout<<"Operation Successful. Please check the file cloned_graph.gv"<<endl;
				break;
			default:
				cout<<"Incorrect Choice!"<<endl;
				break;
		}
	}while(choice != 0);
	
	delete(tree);
	delete(clone);
	return 0;
}
