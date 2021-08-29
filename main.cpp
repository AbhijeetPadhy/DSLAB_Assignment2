#include<iostream>

using namespace std;

class AVL_Node{
	private:
		int key;
		int bf; //balance factor bf = height(left subtree) - height(right subtree)
		AVL_Node *LChild, *RChild;
	friend class AVL_Tree;
};

class AVL_Tree{
	private:
		AVL_Node *root;
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

int main(){
	return 0;
}
