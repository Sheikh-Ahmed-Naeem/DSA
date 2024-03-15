#include<iostream>
using namespace std;
class node
{
	public:
		int data;
		node* right;
		node* left;
		node(int val)
		{
			data = val;
			right = NULL;
			left = NULL;
		}
};
void insert(node* &root, int val)
{
	if (root==NULL)
	{
	    root= new node(val);
	    return;
	}
	else if (val>root->data)
	{
		insert(root->right,val);
	}
	else if (val<root->data)
	{
		insert(root->left,val);
	}
	else
	    return;
}
void search(node* root,int key)
{
	if (root==NULL)
	{
		cout<<"Tree is NULL"<<endl;
		return;
    }
    else
    if(key==root->data)
    {
    	cout<<"Found the element "<<endl;
    	return;
	}
	else if (key<root->data)
	{
		search(root->left,key);
	}
	else if (key>root->data)
	{
		search(root->right,key);
	}
}
node* minnode(node* root)
{
	if (root==NULL)
	{
		return 0;
	}
	while(root->left!=NULL)
	{
		root=root->left;
	}
	return root;
}
node* deletenode(node* root,int val)
{
	if(root==NULL)
	{
		cout<<"No tree"<<endl;
		return 0;
	}
	else 
	{
		if (val<root->data)
		{
			root->left = deletenode(root->left,val);
		}
		else if (val>root->data)
		{
			root->right = deletenode(root->right,val);
		}
		else
		{
		if (root->left==NULL)
		{
		   node* temp = root->right;
		   delete root;
		   return temp;	
		}	
		else if (root->right ==NULL)
		{
			node* temp = root->left;
			delete root;
			return temp;
		}
		node* temp = minnode(root->right);
		root->data = temp->data;
		root->right = deletenode(root->right,temp->data);
		}
	   return root;
	}
	
}
void inorder(node* root)
{
	if (root == NULL)
	{
		return;
	}
	inorder(root->left);
	cout<<root->data<<" ";
	inorder(root->right);
}
int main()
{
	node* root = new node(6);
	root->left = new node(4);
	root->right = new node(8);
	root->left->right = new node(5);
	root->right->left= new node(7);
	cout<<"Your tree is "<<endl;
	inorder(root);
	insert(root,10);
	cout<<"Your tree after inserting is"<<endl;
	inorder(root);
	cout<<endl;
	search(root,8);
	cout<<"New node is "<<endl;
    root = deletenode(root,8);
	inorder(root);
	}
