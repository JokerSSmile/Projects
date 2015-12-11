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

void TreeAdd(vector<Player>::iterator p, Node *&tree) //В функцию принимается записываемый элемент и указатель на ссылку на структуру.
{
	if (NULL == tree) //если ничего нет
	{
		tree = new Node; //выделяем память (как на огороде грядку вскопали почти)
		tree->left = tree->right = NULL; //очищаем участки для роста
		tree->name = p->name; //записали в звено данные
		tree->rating = p->rating;
	}
	else if (NULL == tree->left)
	{
		TreeAdd(p, tree->left); //если слева участок не занят, создаем там подзвено
	}
	else
	{
		TreeAdd(p, tree->right); //если занят, создаем подзвено справа
	}
}

/*СИММЕТРИЧНЫЙ ОБХОД*/
void Show(Node *&tree)
{
	if (NULL == tree)    return;    //Если дерева нет, выходим

	Show(tree->left); //Обошли левое поддерево 
	cout << tree->name; //Посетили узел
	cout << tree->rating << endl;
	Show(tree->right); //Обошли правое поддерево   
}

/*ОБХОД В ПРЯМОМ ПОРЯДКЕ*/
void Show1(Node *&tree)
{
	if (NULL == tree)    return;    //Если дерева нет, выходим
	cout << tree->name; //Посетили узел
	cout << tree->rating << endl;
	Show(tree->left); //Обошли левое поддерево   
	Show(tree->right); //Обошли правое поддерево   
}

/*ОБРАТНЫЙ ОБХОД*/
void Show2(Node *&tree)
{
	if (NULL == tree)    return;    //Если дерева нет, выходим

	Show(tree->left); //Обошли левое поддерево 
	Show(tree->right); //Обошли правое поддерево  
	cout << tree->name; //Посетили узел
	cout << tree->rating << endl;
}
