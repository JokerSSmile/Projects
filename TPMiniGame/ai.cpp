#include "constants.h"
#include "ai.h"

void FirstPcTurn(int field[FIELD_CELLS][FIELD_CELLS], bool& isPlayersTurn)
{
	field[1][1] = 1;
	isPlayersTurn = false;
}

void SecondPcTurn(int field[FIELD_CELLS][FIELD_CELLS], bool& isPlayersTurn)
{
	if (field[0][0] == 0 && field[0][2] == 0 && field[2][0] == 0 && field[2][2] == 0)
	{
		if (field[0][2] == 0)
		{
			field[0][2] = 1;
			isPlayersTurn = false;
		}
		else
		{
			field[0][0] = 1;
			isPlayersTurn = false;
		}
	}
	else if ((field[0][1] == 0 && field[1][0] == 0 && field[2][1] == 0 && field[1][2] == 0))
	{

		if (field[2][0] == 0)
		{
			field[2][0] = 1;
			isPlayersTurn = false;
		}
		else
		{
			field[0][2] = 1;
			isPlayersTurn = false;
		}
	}
}

void ThirdPcTurn(int field[FIELD_CELLS][FIELD_CELLS], bool& isPlayersTurn)
{
	if (field[0][2] == 1 && field[1][1] == 1 && field[2][0] == 0)
	{
		field[2][0] = 1;
		isPlayersTurn = false;
	}
	else if (field[1][0] == 2 && field[2][0] == 2 && field[0][0] == 0)
	{
		field[0][0] = 1;
		isPlayersTurn = false;
	}
	else if (field[0][2] == 1 && field[2][0] == 2)
	{
		if (field[2][2] == 0)
		{
			if (field[1][2] == 0)
			{
				field[2][2] = 1;
				isPlayersTurn = false;
			}
			else if (field[1][2] == 2)
			{
				field[0][0] = 1;
				isPlayersTurn = false;
			}
		}
		else if (field[2][2] == 2)
		{
			field[2][1] = 1;
			isPlayersTurn = false;
		}
	}
	else if (field[0][2] == 2)
	{
		if (field[0][0] == 2)
		{
			field[0][1] = 1;
			isPlayersTurn = false;
		}
		else if (field[0][1] == 2)
		{
			field[0][0] = 1;
			isPlayersTurn = false;
		}
		else if (field[1][0] == 2)
		{
			field[2][1] = 1;
			isPlayersTurn = false;
		}
		else if (field[1][2] == 2)
		{
			field[2][2] = 1;
			isPlayersTurn = false;
		}
		else if (field[2][1] == 2)
		{
			field[1][0] = 1;
			isPlayersTurn = false;
		}
		else if (field[2][2] == 2)
		{
			field[1][2] = 1;
			isPlayersTurn = false;
		}
	}
	else if (field[0][2] == 0)
	{
		field[0][2] = 1;
		isPlayersTurn = false;
	}
}

void ForthPcTurn(int field[FIELD_CELLS][FIELD_CELLS], bool& isPlayersTurn)
{
	if (field[0][2] == 1 && field[2][0] == 2)
	{
		if (field[2][2] == 1)
		{
			if (field[1][2] == 0)
			{
				field[1][2] = 1;
				isPlayersTurn = false;
			}

			else if (field[1][2] == 2 && field[0][0] == 0)
			{
				field[0][0] = 1;
				isPlayersTurn = false;
			}
			else if (field[0][0] == 2 && field[1][2] == 2 && field)
			{
				field[1][0] = 1;
				isPlayersTurn = false;
			}
		}
		else if (field[2][2] == 2)
		{
			if (field[1][2] == 2 && field[0][1] == 0 && field[2][1] == 1)
			{
				if (field[0][1] == 0)
				{
					field[0][1] = 1;
				}
			}
			else if (field[1][2] == 2 && field[2][2] == 2 && field[1][1] == 1)
			{
				if (field[0][1] == 0)
				{
					field[0][1] = 1;
					isPlayersTurn = false;
				}
			}
			else if (field[0][1] == 2 && field[2][1] == 1)
			{
				if (field[1][0] == 0)
				{
					field[1][0] = 1;
					isPlayersTurn = false;
				}
			}
			else if (field[0][0] == 1 && field[1][0] == 2 && field[2][0] == 2)
			{
				if (field[0][1] == 0)
				{
					field[0][1] = 1;
					isPlayersTurn = false;
				}
			}
		}
		else if (field[2][2] == 0)
		{
			if (field[0][0] == 1 && field[1][2] == 2)
			{
				if (field[2][1] == 2)
				{
					if (field[0][1] == 0)
					{
						field[0][1] = 0;
						isPlayersTurn = false;
					}
				}
				else if (field[0][1] == 2)
				{
					if (field[2][2] == 0)
					{
						field[2][2] = 1;
						isPlayersTurn = false;
					}
				}
				else if (field[0][1] == 0 && field[1][0] == 2 && field[2][0] == 2)
				{
					field[0][1] = 1;
					isPlayersTurn = false;
				}
			}
			else if (field[0][0] == 1 && field[1][0] == 2 && field[2][0] == 2)
			{
				if (field[2][2] == 0)
				{
					field[2][2] = 1;
					isPlayersTurn = false;
				}
				else
				{
					field[0][1] = 1;
					isPlayersTurn = false;
				}
			}
		}
	}
	else if (field[0][2] == 2)
	{
		if (field[0][0] == 2)
		{
			if (field[2][1] == 0)
			{
				field[2][1] = 1;
				isPlayersTurn = false;
			}
			else if (field[2][1] == 2)
			{
				field[1][2] = 1;
				isPlayersTurn = false;
			}
		}
		else if (field[0][1] == 2 && field[0][0] == 1)
		{
			if (field[1][0] == 0)
			{
				field[1][0] = 1;
				isPlayersTurn = false;
			}
			else field[2][2] = 1;
		}
		else if (field[1][0] == 2 && field[2][1] == 1)
		{
			if (field[2][2] == 0)
			{
				field[2][2] = 1;
				isPlayersTurn = false;
			}
			else field[0][1] = 1;
			isPlayersTurn = false;
		}
		else if (field[1][2] == 2 && field[2][2] == 1)
		{
			if (field[2][1] == 0)
				field[2][1] = 1;
			else
			{
				field[0][0] = 1;
			}
		}
		else if (field[2][2] == 2 && field[1][2] == 1)
		{
			if (field[1][0] == 0)
				field[1][0] = 1;
			else field[0][1] = 1;
		}
		else if (field[2][1] == 2)
		{
			if (field[1][2] == 0)
				field[1][2] = 1;
			else field[0][0] = 1;
		}
	}
	else if (field[2][2] == 2 && field[1][2] == 2 && field[0][1] == 0 && field[2][1] == 1)
	{
		field[0][1] = 1;
		isPlayersTurn = false;
	}
}

void FifthPcTurn(int field[FIELD_CELLS][FIELD_CELLS], bool& isPlayersTurn)
{
	if (field[0][1] == 0)
		field[0][1] = 1;
	else if (field[2][1] == 0)
		field[2][1] = 1;
	else if (field[1][0] == 1 && field[2][1] == 1)
	{
		if (field[0][0] == 0)
			field[0][0] = 1;
		else if (field[1][2] == 0)
			field[1][2] = 1;
	}
	else if (field[0][0] == 2 && field[0][2] == 2 && field[1][2] == 1)
	{
		if (field[1][0] == 0)
		{
			field[1][0] = 1;
			isPlayersTurn = false;
		}
		else field[2][2] = 1;
	}
	else if (field[0][1] == 1 && field[1][2] == 1 && field[0][2] == 2)
	{
		if (field[2][1] == 0)
			field[2][1] = 1;
		else field[0][0] = 1;
	}
}

void PcTurn(sf::RenderWindow& window, int& turnCounter, int field[FIELD_CELLS][FIELD_CELLS], bool& isPlayersTurn)
{
	if (turnCounter == 0)
	{
		FirstPcTurn(field, isPlayersTurn);
	}
	else if (turnCounter == 2)
	{
		SecondPcTurn(field, isPlayersTurn);
	}
	else if (turnCounter == 4)
	{
		ThirdPcTurn(field, isPlayersTurn);
	}
	else if (turnCounter == 6)
	{
		ForthPcTurn(field, isPlayersTurn);
	}
	else if (turnCounter == 8)
	{
		FifthPcTurn(field, isPlayersTurn);
	}
}
