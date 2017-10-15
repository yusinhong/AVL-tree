#pragma once
#include<iostream>
template<class T>
class CNode
{
public:
	CNode(){
		m_Left = NULL;
		m_Right = NULL;
		m_Father = NULL;
	};
	~CNode(){};
	T m_Value;
	CNode<T>*m_Left;
	CNode<T>*m_Right;
	CNode<T>*m_Father;
};