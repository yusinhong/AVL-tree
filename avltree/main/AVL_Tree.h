#pragma once
#include"Node.h"
using namespace std;
template<class T>
class CAVL_Tree
{
public:
	CAVL_Tree(){ m_Root = NULL; };
	~CAVL_Tree(){ Delete(m_Root); };
	void Insert(T value)
	{
		cout << "Insert:" << value << "\n";
		if (!m_Root)
		{
			m_Root = new CNode < T > ;
			m_Root->m_Value = value;
		}
		else
		{
			CNode<T>*now = m_Root;
			do{
				if (value == now->m_Value)
					return;
				else if (value < now->m_Value)
				{
					if (!now->m_Left)
					{
						now->m_Left = new CNode < T > ;
						now->m_Left->m_Father = now;
						now->m_Left->m_Value = value;
						now = now->m_Left;
						break;
					}
					now = now->m_Left;
				}
				else if (value > now->m_Value)
				{
					if (!now->m_Right)
					{
						now->m_Right = new CNode < T > ;
						now->m_Right->m_Father = now;
						now->m_Right->m_Value = value;
						now = now->m_Right;
						break;
					}
					now = now->m_Right;
				}
			} while (1);
			int balenceFactor;
			while (now){
				balenceFactor = GetBalenceFactor(now);
				if (abs(balenceFactor) >= 2)
					break;
				now = now->m_Father;
			}
			TreeRotation(now, balenceFactor);
		}
	};
	void TreeRotation(CNode<T>*node, int balenceFactor)
	{
		CNode<T>*A = node;
		if (node == NULL&&abs(balenceFactor) < 2)
			return;
		else if (balenceFactor < 0 && GetBalenceFactor(node->m_Right)>0)
		{
			//RL
			std::cout << "Run RL" << std::endl;
			CNode<T>* B = A->m_Right;
			CNode<T>* C = B->m_Left;
			if (!A->m_Father) m_Root = C;
			else if (A->m_Father->m_Left == A)
				A->m_Father->m_Left = C;
			else if (A->m_Father->m_Right == A)
				A->m_Father->m_Right = C;
			CNode<T>* CL = C->m_Left;
			CNode<T>* CR = C->m_Right;
			C->m_Left = A;
			C->m_Right = B;
			A->m_Right = CL;
			B->m_Left = CR;
			//////////
			C->m_Father = A->m_Father;
			A->m_Father = C;
			B->m_Father = C;
			if (CL) CL->m_Father = A;
			if (CR) CR->m_Father = B;
		}
		else if (balenceFactor > 0 && GetBalenceFactor(node->m_Left) < 0) {	//LR
			std::cout << "Run LR" << std::endl;
			CNode<T>* B = A->m_Left;
			CNode<T>* C = B->m_Right;
			if (!A->m_Father) m_Root = C;
			else if (A->m_Father->m_Left == A)
				A->m_Father->m_Left = C;
			else if (A->m_Father->m_Right == A)
				A->m_Father->m_Right = C;
			CNode<T>* CL = C->m_Left;
			CNode<T>* CR = C->m_Right;
			C->m_Right = A;
			C->m_Left = B;
			A->m_Left = CR;
			B->m_Right = CL;
			//////////
			C->m_Father = A->m_Father;
			A->m_Father = C;
			B->m_Father = C;
			if (CR) CR->m_Father = A;
			if (CL) CL->m_Father = B;
		}
		else if (balenceFactor < 0 && GetBalenceFactor(node->m_Right) <= 0) { //RR
			std::cout << "Run RR" << std::endl;
			CNode<T>* B = A->m_Right;
			if (!A->m_Father) m_Root = B;
			else if (A->m_Father->m_Left == A)
				A->m_Father->m_Left = B;
			else if (A->m_Father->m_Right == A)
				A->m_Father->m_Right = B;
			CNode<T>* reg = B->m_Left;
			B->m_Left = A;
			A->m_Right = reg;
			//////////
			B->m_Father = A->m_Father;
			A->m_Father = B;
			if (reg) reg->m_Father = A;
		}
		else if (balenceFactor > 0 && GetBalenceFactor(node->m_Left) >= 0) { //LL
			std::cout << "Run LL" << std::endl;
			CNode<T>* B = A->m_Left;
			//CNode<T>* C = B->m_Right;
			if (!A->m_Father) m_Root = B;
			else if (A->m_Father->m_Left == A)
				A->m_Father->m_Left = B;
			else if (A->m_Father->m_Right == A)
				A->m_Father->m_Right = B;
			CNode<T>* reg = B->m_Right;
			B->m_Right = A;
			A->m_Left = reg;
			//////////
			B->m_Father = A->m_Father;
			A->m_Father = B;
			if (reg) reg->m_Father = A;
		}
	};
	int GetBalenceFactor(CNode<T>* node) {
		if (!node) return 0;
		return GetTreeHeight(node->m_Left) - GetTreeHeight(node->m_Right);
	};

	int GetTreeHeight(CNode<T>* node) {
		if (node == NULL) return 0;
		int leftTreeHeight = GetTreeHeight(node->m_Left);
		int rightTreeHeight = GetTreeHeight(node->m_Right);
		if (leftTreeHeight >= rightTreeHeight)
			return leftTreeHeight + 1;
		else return rightTreeHeight + 1;
	};

	void Delete(CNode<T>* deleteItem) {
		if (!deleteItem) return;
		Delete(deleteItem->m_Left);
		Delete(deleteItem->m_Right);
		delete deleteItem;
	}
	void inOrder(CNode<T>* root) {
		if (!root) return;
		if (root->m_Left) inOrder(root->m_Left);
		std::cout << root->m_Value << ", ";
		if (root->m_Right) inOrder(root->m_Right);
	};
	void PreOrder(CNode<T>* root) {
		if (!root) return;
		std::cout << root->m_Value << ", ";
		if (root->m_Left) PreOrder(root->m_Left);
		if (root->m_Right) PreOrder(root->m_Right);
	};
	void PostOrder(CNode<T>* root) {
		if (!root) return;
		if (root->m_Left) PostOrder(root->m_Left);
		if (root->m_Right) PostOrder(root->m_Right);
		std::cout << root->m_Value << ", ";
	};

	CNode<T>* GetRoot() {
		return m_Root;
	};

	bool Remove(T value) {
		CNode<T>* now = m_Root;
		while (now->m_Left || now->m_Right) {
			if (now->m_Value == value) break;
			else if (now->m_Value < value)
				now = now->m_Right;
			else if (now->m_Value > value)
				now = now->m_Left;
		}
		if (now->m_Value != value) return false;
		if (!now->m_Left && !now->m_Right) {
			if (now->m_Father->m_Left == now)
				now->m_Father->m_Left = NULL;
			else if (now->m_Father->m_Right == now)
				now->m_Father->m_Right = NULL;
			delete now;
		}
		else if (now->m_Left && !now->m_Right) {
			if (now->m_Father->m_Left == now)
				now->m_Father->m_Left = now->m_Left;
			else if (now->m_Father->m_Right == now)
				now->m_Father->m_Right = now->m_Left;
			now->m_Left->m_Father = now->m_Father;
			delete now;
		}
		else if (!now->m_Left && now->m_Right) {
			if (now->m_Father->m_Left == now)
				now->m_Father->m_Left = now->m_Right;
			else if (now->m_Father->m_Right == now)
				now->m_Father->m_Right = now->m_Right;
			now->m_Right->m_Father = now->m_Father;
			delete now;
		}
		else {
			CNode<T>* replaceItem = now;
			replaceItem = replaceItem->m_Left;
			while (replaceItem->m_Right)
				replaceItem = replaceItem->m_Right;
			int n = replaceItem->m_Value;
			if (Remove(replaceItem->m_Value))
				now->m_Value = n;
		}
		CNode<T>* unbalenceNode = GetUnbalenceNode(m_Root);
		TreeRotation(unbalenceNode, GetBalenceFactor(unbalenceNode));
		return true;
	};

	CNode<T>* GetUnbalenceNode(CNode<T>* root) {
		if (!root) return NULL;
		int balenceFactor = GetBalenceFactor(root);
		if (abs(balenceFactor) >= 2) return root;
		CNode<T>* subTree;
		subTree = GetUnbalenceNode(root->m_Left);
		if (subTree) return subTree;
		subTree = GetUnbalenceNode(root->m_Right);
		if (subTree) return subTree;
		return NULL;
	};

private:
	CNode<T>* m_Root;
};
