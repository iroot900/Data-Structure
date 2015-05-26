#include <iostream>
#include <algorithm>
using namespace std;

class TreeNode
{
public:
	TreeNode(int val) :m_val(val), m_left(NULL), m_right(NULL), m_height(0){}
	int m_val;
	int m_height;
	TreeNode *m_left;
	TreeNode *m_right;
};

void leftRotate(TreeNode*& root)
{
	auto temp = root->m_left;
	root->m_left = temp->m_right;
	temp->m_right = root;
	root = temp;

	root->m_right->m_height = max(root->m_right->m_left == NULL ? 0 : root->m_right->m_left->m_height, root->m_right->m_right == NULL ? 0 : root->m_right->m_right->m_height) + 1;
	root->m_height = max(root->m_left == NULL ? 0 : root->m_left->m_height, root->m_right == NULL ? 0 : root->m_right->m_height) + 1;
}

void rightRotate(TreeNode*& root)
{
	auto temp = root->m_right;
	root->m_right = temp->m_left;
	temp->m_left = root;
	root = temp;
	root->m_left->m_height = max(root->m_left->m_left == NULL ? 0 : root->m_left->m_left->m_height, root->m_left->m_right == NULL ? 0 : root->m_left->m_right->m_height) + 1;
	root->m_height = max(root->m_left == NULL ? 0 : root->m_left->m_height, root->m_right == NULL ? 0 : root->m_right->m_height) + 1;
}

void addNode(TreeNode* &root, int val)
{
	if (root == NULL) root = new TreeNode(val);
	else if (root->m_val>val){ addNode(root->m_left, val); }
	else { addNode(root->m_right, val); }
	//	root->m_height=max(root->m_left==NULL?0:root->m_left->m_height,root->m_right==NULL?0:root->m_right->m_height)+1;

	int balance = (root->m_left == NULL ? 0 : root->m_left->m_height) - (root->m_right == NULL ? 0 : root->m_right->m_height);

	if (balance>1)
	{
		if (val>root->m_left->m_val)
			rightRotate(root->m_left);
		leftRotate(root);
	}
	else if (balance<-1)
	{
		if (val<root->m_right->m_val)
			leftRotate(root->m_right);
		rightRotate(root);
	}
	root->m_height = max(root->m_left == NULL ? 0 : root->m_left->m_height, root->m_right == NULL ? 0 : root->m_right->m_height) + 1;

	//addNode(root,new TreeNode(val));
}

void inorder(TreeNode* root)
{
	if (root == NULL) return;
	inorder(root->m_left);
	cout << root->m_val << " " << "(" << root->m_height << "L)" << " ,";
	inorder(root->m_right);
}

TreeNode* & find(TreeNode* &root, int val)
{
	if (root == NULL) return root;
	if (root->m_val == val) return root;
	else if (root->m_val>val)  return find(root->m_left, val);
	else return find(root->m_right, val);
}

TreeNode* & minFind(TreeNode* &root)
{
	if (root->m_left != NULL) return minFind(root->m_left);
	else return root;
}

void removeNode(TreeNode*& root, int val)
{
	// TreeNode* & it=find(root,val);
	// find something deltetee it..
	// not only. copy val.. then delete it.
	if (root == NULL) return;
	if (root->m_val == val) {
		TreeNode*& it = root;
		if (it->m_left != NULL&&it->m_right != NULL)
		{
			// copy the next min...to cur.
			TreeNode* &minp = minFind(it->m_right);
			it->m_val = minp->m_val;

			// delete the next min..
			removeNode(it->m_right, minp->m_val);

		}
		else if (it->m_left != NULL)
		{
			auto temp = it;
			it = it->m_left;
			delete temp;
		}

		else {
			auto temp = it;
			it = it->m_right;
			delete temp;
		}
	}
	else if (root->m_val>val)
		removeNode(root->m_left, val);
	else if (root->m_val<val)
		removeNode(root->m_right, val);
	// detelte is easy. current point to next..
	// get the min . put min value hear, detel min.

	if (root == NULL) return;

	int balance = (root->m_left == NULL ? 0 : root->m_left->m_height) - (root->m_right == NULL ? 0 : root->m_right->m_height);

	if (balance>1)
	{
		if (val>root->m_left->m_val)
			rightRotate(root->m_left);
		leftRotate(root);
	}
	else if (balance<-1)
	{
		if (val<root->m_right->m_val)
			leftRotate(root->m_right);
		rightRotate(root);
	}

	root->m_height = max(root->m_left == NULL ? 0 : root->m_left->m_height, root->m_right == NULL ? 0 : root->m_right->m_height) + 1;
}

void clear(TreeNode* &root)
{
	if (root == NULL) return;
	clear(root->m_left);
	clear(root->m_right);
	delete root;
	root = NULL;
}

int height(TreeNode* root)
{
	if (root == NULL) return 0;
	int hl = height(root->m_left);
	int hr = height(root->m_right);
	return (hl>hr ? hl : hr) + 1;
}

int main() {

	TreeNode* root = NULL;
	addNode(root, 3); addNode(root, 5); addNode(root, 0); addNode(root, 7); addNode(root, 4); addNode(root, 8); addNode(root, 3);
	addNode(root, 9);
	/*auto itt=minFind(root); cout<<"min: "<<itt->m_val<<endl;
	itt=find(root,0); cout<<"find: "<<itt->m_val<<endl;
	inorder(root);
	cout<<endl;
	cout<<"---"<<endl;
	removeNode(root,3);
	inorder(root);
	cout<<endl;
	removeNode(root,0);
	inorder(root);
	cout<<endl;
	removeNode(root,5);
	inorder(root);
	cout<<endl;
	removeNode(root,7);
	inorder(root);
	cout<<endl;
	removeNode(root,4);
	inorder(root);
	cout<<endl;
	removeNode(root,11);
	inorder(root);
	cout<<endl;
	auto it=find(root,3);
	if(it!=NULL) cout<<it->m_val<<endl;
	else cout<<"None!"<<endl;
	it=find(root,6);
	if(it!=NULL) cout<<it->m_val<<endl;
	else cout<<"None!"<<endl;
	it=find(root,5);
	if(it!=NULL) cout<<it->m_val<<endl;
	else cout<<"None!"<<endl;
	it=find(root,11);
	if(it!=NULL) cout<<it->m_val<<endl;
	else cout<<"None!"<<endl;
	cout<<height(root)<<"___height___"<<endl;
	clear(root);

	cout<<height(root)<<"___height___"<<endl;
	it=find(root,6);
	if(it!=NULL) cout<<it->m_val<<endl;
	else cout<<"None!"<<endl;
	it=find(root,5);
	if(it!=NULL) cout<<it->m_val<<endl;
	else cout<<"None!"<<endl;
	it=find(root,4);
	if(it!=NULL) cout<<it->m_val<<endl;
	else cout<<"None!"<<endl;
	return 0;*/

	for (int i = 10; i<16; i++)
		addNode(root, i);
	inorder(root);
	cout << endl;
	removeNode(root, 3);
	inorder(root);
	cout << endl;
	removeNode(root, 0);
	inorder(root);
	cout << endl;
	removeNode(root, 2);
	inorder(root);
	cout << endl;
	removeNode(root, 7);
	inorder(root);
	cout << endl;
}
