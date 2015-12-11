#include "tree.h"

struct Cmp
{
	bool operator()(const Player &a, const Player &b)
	{
		return a.rating > b.rating;
	}
} compare;

void GetInputData(vector<Player>& PlayersData)
{
	string line;
	string name;
	ifstream input("input.txt");
	while (input.good())
	{
		getline(input, line);
		name = line;
		name.erase(remove_if(name.begin(), name.end(), isdigit), name.end());
		Player *player = new Player;
		player->name = name;
		player->rating = stoi(line.erase(0, name.size()));
		PlayersData.push_back(*player);
	}
}

int GetNearestGrade(int num)
{
	int i = 2;
	while (i <= num)
	{
		i *= 2;
	}
	return i / 2;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	GetInputData(PlayersData);

	Node* Tree = NULL;



	sort(PlayersData.begin(), PlayersData.end(), compare);
	for (vector<Player>::iterator it = PlayersData.begin(); it != PlayersData.end(); ++it)
	{
		TreeAdd(it, Tree);
	}

	//Show(Tree);
	cout << "------------------------" << endl;
	Show1(Tree);
	cout << "------------------------" << endl;
	//Show2(Tree);


	GetNearestGrade(size(PlayersData));

	system("pause");
    return 0;
}
