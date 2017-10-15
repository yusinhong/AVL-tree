#include "stdafx.h"
#include"AVL_Tree.h"
using namespace std;
int main()
{
	int i;
	int a[8] = { 30, 50, 70, 20, 10, 40, 45, 43 };
	CAVL_Tree<int>avlTree;
	for (i = 0; i < 8; i++)
	{
		avlTree.Insert(a[i]);
	}
	avlTree.inOrder(avlTree.GetRoot());
	cout << "\n";
	avlTree.PreOrder(avlTree.GetRoot());
	cout << "\n";
	avlTree.PostOrder(avlTree.GetRoot());
	cout << "\n";
	avlTree.Remove(70);
	avlTree.inOrder(avlTree.GetRoot());
	cout << "\n";
	avlTree.PreOrder(avlTree.GetRoot());
	cout << "\n";
	avlTree.PostOrder(avlTree.GetRoot());
	cout << "\n";
	return 0;
}

