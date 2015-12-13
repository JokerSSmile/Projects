#include "tree.h"

struct Cmp
{
	bool operator()(const Player &a, const Player &b)
	{
		return a.rating < b.rating;
	}
} compare;

void GetInputData()
{
	string line;
	string name;
	ifstream input("temp.txt");
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

int GetMaxNumber(int num)
{
	int maxNum = num;
	while (num != 2)
	{
		num = num / 2;
		maxNum += num;
	}
	return maxNum;
}

void GetQualifyingData()
{
	sort(PlayersData.begin(), PlayersData.end(), compare);
	for (vector<Player>::iterator it = PlayersData.begin(); it != PlayersData.end(); ++it)
	{
		if (size(Qualifying) < GetNearestGrade(size(PlayersData)))
		{
			Qualifying.push_back(*it);
		}
		else
		{
			Playoff.push_back(*it);
		}
	}
}

void SetPlayoffData(vector<Player>& Difference, int& ratingDifference)
{
	while (size(Qualifying) != 0)
	{
		unsigned int result = 0;
		cout << "Who wins the round" << endl;
		cout << " 1 if " << Qualifying.front().name << Qualifying.front().rating << endl;
		cout << " 2 if " << Qualifying.back().name << Qualifying.back().rating << endl;
		cin >> result;
		if (result == 1)
		{
			Playoff.push_back(*Qualifying.begin());
		}
		else if (result == 2)
		{
			Playoff.push_back(Qualifying.back());
		}

		if (abs(Qualifying.begin()->rating - Qualifying.back().rating) > ratingDifference)
		{
			Difference.clear();
			Difference.push_back(*Qualifying.begin());
			Difference.push_back(Qualifying.back());
			ratingDifference = abs(Qualifying.begin()->rating - Qualifying.back().rating);
		}

		Qualifying.erase(Qualifying.begin());
		Qualifying.pop_back();
	}
}

void Seeding()
{
	vector<Player> Copy = Playoff;
	sort(Copy.begin(), Copy.end(), compare);
	Playoff.clear();
	int s = size(Copy);

	while (size(Playoff) < s)
	{
		Playoff.push_back(*Copy.begin());
		Copy.erase(Copy.begin());
		Playoff.push_back(Copy.back());
		Copy.pop_back();
		Playoff.push_back(*Copy.begin());
		Copy.erase(Copy.begin());
		Playoff.push_back(*Copy.begin());
		Copy.erase(Copy.begin());
	}
}

void DetermineWinners(int num, int startPos)
{
	vector<Player> Copy = Playoff;
	unsigned int s = size(Copy);
	for (int i = 0; i < startPos; i++)
	{
		Copy.erase(Copy.begin());
	}

	while (size(Playoff) < (s + num))
	{
		unsigned int result = 0;
		cout << "Who wins the round" << endl;
		cout << " 1 if " << Copy.at(0).name << Copy.at(0).rating << endl;
		cout << " 2 if " << Copy.at(1).name << Copy.at(1).rating << endl;
		cin >> result;
		if (result == 1)
		{
			Playoff.push_back(Copy.at(0));
		}
		else if (result == 2)
		{
			Playoff.push_back(Copy.at(1));
		}
		Copy.erase(Copy.begin());
		Copy.erase(Copy.begin());
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");
	GetInputData();
	Node* Tree = NULL;

	vector<Player> Difference;
	int ratingDifference = 0;
	int counter = 4;
	int startPos = 0;

	GetQualifyingData();

	for (vector<Player>::iterator it = PlayersData.begin(); it != PlayersData.end(); ++it)
	{
		cout << it->rating << endl;
	}

	cout << "----Qualifying----" << endl;

	for (vector<Player>::iterator it = Qualifying.begin(); it != Qualifying.end(); ++it)
	{
		cout << it->rating << endl;
	}

	cout << "----Choose----" << endl;

	SetPlayoffData(Difference, ratingDifference);

	cout << "----Playoff----" << endl;
	sort(Playoff.begin(), Playoff.end(), compare);
	for (vector<Player>::iterator it = Playoff.begin(); it != Playoff.end(); ++it)
	{
		cout << it->name;
		cout << it->rating << endl;
	}

	cout << "----Difference----" << endl;

	cout << Difference.front().rating << Difference.front().name << endl;
	cout << Difference.back().rating << Difference.back().name << endl;
	cout << ratingDifference << endl;

	cout << "----Seeding----" << endl;

	Seeding();

	cout << "----Seeded--Playoff----" << endl;

	for (vector<Player>::iterator it = Playoff.begin(); it != Playoff.end(); ++it)
	{
		cout << it->name;
		cout << it->rating << endl;
	}

	cout << "----Determiners ----" << endl;

	DetermineWinners(counter, startPos);
	while (size(Playoff) < GetMaxNumber(size(Playoff)))//here fix
	{
		startPos += size(Playoff);
		DetermineWinners(counter, startPos);
		counter = counter / 2;
		cout << "--------" << counter << " " << startPos << endl;
	}
	
	//DetermineWinners(counter, startPos);
	//counter = counter / 2;
	//startPos += size(Playoff);
	//DetermineWinners(counter, startPos);

	cout << "----Result 1 round----" << endl;

	for (vector<Player>::iterator it = Playoff.begin(); it != Playoff.end(); ++it)
	{
		cout << it->name;
		cout << it->rating << endl;
	}

	system("pause");
    return 0;
}
