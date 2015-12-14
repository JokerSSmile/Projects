#pragma once

#include <iomanip>

#define _USE_MATH_DEFINES

#include <clocale>  
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <math.h>

using namespace std;

struct Player
{
	int rating;
	string name;
};

vector<Player> PlayersData;
vector<Player> Qualifying;
vector<Player> Playoff;
vector<Player> PlayoffSeeding;
vector<Player> Final;

vector<Player> Sensations;
vector<Player> MaxSensation;

bool isNumDegreeOfTwo(int num)
{
	for (unsigned int i = 2; i < 1000; i = i * 2)
	{
		if (num == i)
		{
			return true;
		}
	}
	return false;
}

int cnt_digits(int num) { return (num /= 10) ? 1 + cnt_digits(num) : 1; }

struct Node
{
	Player player;
	Node* left;
	Node* right;
};

void TreeAdd(vector<Player>::iterator p, Node *&tree)
{
	if (NULL == tree) //если ничего нет
	{
		tree = new Node;
		tree->left = NULL;
		tree->right = NULL;
		tree->player = *p;
	}
	else if (NULL == tree->left)
	{
		TreeAdd(p, tree->left);
	}
	else
	{
		TreeAdd(p, tree->right);
	}
}

void Show(Node*& tree, ofstream& out, int& level, int& counter, int& degree)
{
	if (NULL == tree)    return;    //≈сли дерева нет, выходим
	counter++;

	int strLength = size(tree->player.name) + cnt_digits(tree->player.rating);

	if (isNumDegreeOfTwo(counter))
	{
		level++;
		degree--;
		out << endl;
	}
	for (int i = 0; i < degree; i++)
	{
		char star = '  ';
		out << string((strLength * degree) / 8, star);
	}
	out << tree->player.rating << " ";
	out << tree->player.name;
	Show(tree->left, out, level, counter, degree);  
	Show(tree->right, out, level, counter, degree); 
}
