#pragma once

#include <clocale>  
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;

struct Player
{
	int rating;
	string name;
};

vector<Player> PlayersData;
vector<Player>::iterator it;

struct Node
{
	int level = 0;
	string name;
	int rating;
	Node* left;
	Node* right;
};

void TreeAdd(vector<Player>::iterator p, Node *&tree) //� ������� ����������� ������������ ������� � ��������� �� ������ �� ���������.
{
	if (NULL == tree) //���� ������ ���
	{
		tree = new Node; //�������� ������ (��� �� ������� ������ �������� �����)
		tree->left = tree->right = NULL; //������� ������� ��� �����
		tree->name = p->name; //�������� � ����� ������
		tree->rating = p->rating;
	}
	else if (NULL == tree->left)
	{
		TreeAdd(p, tree->left); //���� ����� ������� �� �����, ������� ��� ��������
	}
	else
	{
		TreeAdd(p, tree->right); //���� �����, ������� �������� ������
	}
}

/*������������ �����*/
void Show(Node *&tree)
{
	if (NULL == tree)    return;    //���� ������ ���, �������

	Show(tree->left); //������ ����� ��������� 
	cout << tree->name; //�������� ����
	cout << tree->rating << endl;
	Show(tree->right); //������ ������ ���������   
}

/*����� � ������ �������*/
void Show1(Node *&tree)
{
	if (NULL == tree)    return;    //���� ������ ���, �������
	cout << tree->name; //�������� ����
	cout << tree->rating << endl;
	Show(tree->left); //������ ����� ���������   
	Show(tree->right); //������ ������ ���������   
}

/*�������� �����*/
void Show2(Node *&tree)
{
	if (NULL == tree)    return;    //���� ������ ���, �������

	Show(tree->left); //������ ����� ��������� 
	Show(tree->right); //������ ������ ���������  
	cout << tree->name; //�������� ����
	cout << tree->rating << endl;
}
