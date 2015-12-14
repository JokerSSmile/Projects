#include "tree.h"


//Patrushev Oleg PS-21
/*
23. Теннисный  турнир  проходит  по  олимпийской  системе с
выбываниями.  Известен  рейтинг  каждого  игрока.   Результаты
турнира  записаны  с  помощью  дерева.  Первоначально задается
только список участников, которым соответствуют листья дерева.
Требуется  предложить  принцип  проведения  турнира (выбор пар
участников,  организация предварительных туров,  распределение
или  посев сильнейших игроков так,  чтобы они не встречались в
начале турнира и  т.п.),  показать  в  наглядном  виде  дерево
проведенного  турнира,  выдать список сенсаций турнира,  когда
побеждал  игрок   с   низшим   рейтингом.   Определить   самый
сенсационный  результат по максимальной разнице рейтингов(14).
*/

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
	while (num > 2)
	{
		num = num / 2;
		maxNum += num;
	}
	return maxNum;
}

void GetQualifyingData()
{
	if (isNumDegreeOfTwo(size(PlayersData)) == false)
	{
		sort(PlayersData.begin(), PlayersData.end(), compare);
		int playersToQualify = (size(PlayersData) - GetNearestGrade(size(PlayersData))) * 2;

		for (vector<Player>::iterator it = PlayersData.begin(); it != PlayersData.end(); ++it)
		{
			if (size(Qualifying) < playersToQualify)
			{
				Qualifying.push_back(*it);
			}
			else
			{
				Playoff.push_back(*it);
			}
		}
	}
	else
	{
		for (vector<Player>::iterator it = PlayersData.begin(); it != PlayersData.end(); ++it)
		{
			Playoff.push_back(*it);
		}
	}
}

void SetPlayoffData()
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
			if (Qualifying.front().rating < Qualifying.back().rating)
			{
				Sensations.push_back(Qualifying.front());
				Sensations.push_back(Qualifying.back());
			}
		}
		else if (result == 2)
		{
			Playoff.push_back(Qualifying.back());
			if (Qualifying.front().rating > Qualifying.back().rating)
			{
				Sensations.push_back(*Qualifying.end());
				Sensations.push_back(Qualifying.back());
			}
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

void SetCorrectSeeding()
{
	int counter = 0;
	while (counter != int(sqrt(GetNearestGrade(size(Playoff)))))
	{
		
		Playoff.push_back(*Playoff.begin());
		Playoff.erase(Playoff.begin());
		counter++;
	}
}

void DetermineWinners(int counter, int startPos)
{
	vector<Player> Copy = Playoff;
	unsigned int s = size(Copy);
	for (int i = 0; i < startPos; i++)
	{
		Copy.erase(Copy.begin());
	}
	while (size(Playoff) < (counter))
	{
		unsigned int result = 0;
		cout << "Who wins the round" << endl;
		cout << " 1 if " << Copy.at(0).name << Copy.at(0).rating << endl;
		cout << " 2 if " << Copy.at(1).name << Copy.at(1).rating << endl;
		cin >> result;
		if (result == 1)
		{
			Playoff.push_back(Copy.at(0));
			if (Copy.at(0).rating < Copy.at(1).rating)
			{
				Sensations.push_back(Copy.at(0));
				Sensations.push_back(Copy.at(1));
			}
		}
		else if (result == 2)
		{
			Playoff.push_back(Copy.at(1));
			if (Copy.at(0).rating > Copy.at(1).rating)
			{
				Sensations.push_back(Copy.at(1));
				Sensations.push_back(Copy.at(0));
			}
		}
		Copy.erase(Copy.begin());
		Copy.erase(Copy.begin());
	}
}

void ShowVector(vector<Player>& myVector)
{
	for (vector<Player>::iterator it = myVector.begin(); it != myVector.end(); ++it)
	{
		cout << it->name << " ";
		cout << it->rating << endl;
	}
}

void GetSemiFinals()
{
	int counter = size(Playoff) + size(Playoff) / 2;
	int startSize = size(Playoff) / 2;
	int startPos = 0;
	int startSizeTemp = size(Playoff);
	int borderToDetermineFinalist = GetMaxNumber(size(Playoff));

	int round = 1;
	while (size(Playoff) < borderToDetermineFinalist)//here fix
	{
		cout << "     " << round << " - round" << endl;
		startSizeTemp = size(Playoff);
		DetermineWinners(counter, startPos);
		counter += startSize / 2;
		startPos = startSizeTemp;
		startSize = startSize / 2;
		round++;
	}
}

void AddToTree(Node*& Tree)
{
	for (vector<Player>::reverse_iterator it = Playoff.rbegin(); it != Playoff.rend(); ++it)
	{
		Final.push_back(*it);
	}

	for (vector<Player>::iterator it = Final.begin(); it != Final.end(); ++it)
	{
		TreeAdd(it, Tree);

	}
}

void OutputTree(Node*& Tree, int& startPlayoffSize, ofstream& out)
{
	out << "----1----" << endl;
	int level = 0;
	int counterT = 0;
	Show(Tree, out, level, counterT, startPlayoffSize);
}

void GetBestSensations()
{
	int maxDifference = 0;
	vector<Player> Copy = Sensations;
	while (size(Copy) > 0)
	{
		if (abs(Copy.at(0).rating - Copy.at(1).rating) > maxDifference)
		{
			MaxSensation.clear();
			MaxSensation.push_back(Copy.at(0));
			MaxSensation.push_back(Copy.at(1));
			maxDifference = abs(Copy.at(0).rating - Copy.at(1).rating);
		}
		Copy.erase(Copy.begin());
		Copy.erase(Copy.begin());
	}
}

void OutputSensations(ofstream& out)
{
	int count = 0;
	for (vector<Player>::iterator it = Sensations.begin(); it != Sensations.end(); ++it)
	{
		count++;
		out << it->name << "  " << it->rating << "  ";
		if (count % 2 == 0)
		{
			out << endl;
		}
	}
	out << endl;
	out << "----THE BIGGEST SENSATION----" << endl;
	out << MaxSensation[0].name << "  " << MaxSensation[0].rating << endl;
	out << MaxSensation[1].name << "  " << MaxSensation[1].rating << endl;
	out << "----WITH RATING DIFFERENCE----" << endl;
	out << abs(MaxSensation[0].rating - MaxSensation[1].rating);
}

int main()
{
	setlocale(LC_ALL, "RUS");
	GetInputData();
	Node* Tree = NULL;

	GetQualifyingData();

	cout << "----Here are all players----" << endl;
	ShowVector(PlayersData);

	cout << "----Here are plyers who need qualifying----" << endl;
	ShowVector(Qualifying);

	cout << "----Choose winning of qualifying----" << endl;
	SetPlayoffData();

	cout << "----Here are plyers who are in playoff----" << endl;
	sort(Playoff.begin(), Playoff.end(), compare);
	ShowVector(Playoff);
	int startPlayoffSize = size(Playoff) / 2;

	cout << "----Seeding playoff players----" << endl;

	Seeding();
	SetCorrectSeeding();

	GetSemiFinals();

	cout << "----GRAND FINAL----" << endl;

	DetermineWinners(size(Playoff) + 1, size(Playoff) - 2);

	AddToTree(Tree);

	ofstream out;
	out.open("output.txt");

	OutputTree(Tree, startPlayoffSize, out);

	GetBestSensations();

	OutputSensations(out);

	out.close();

	system("pause");
    return 0;
}
