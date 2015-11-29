#include <iostream>
#include "program.h"

using namespace sf;
using namespace std;

void ProcessEvents(RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void DrawWindow(RenderWindow& window, vector<Block>& blocks)
{
	window.clear(Color(200, 200, 200));
	for (int i = 0; i < BLOCKS_COUNT; i++)
	{
		window.draw(blocks[i].figure);
	}
	window.display();
}

void InitializeProgram(vector<Block>& blocks)
{
	for (int i = 0; i < BLOCKS_COUNT; i++)
	{
		Block newBlock(START_POSITION.x, START_POSITION.y + i * SPACE_BETWEEN_BLOCKS);
		newBlock.figure.setPosition(newBlock.position.x, newBlock.position.y);
		newBlock.figure.setSize(Vector2f(BLOCK_START_SIZE));
		newBlock.figure.setFillColor(Color(255, 255, 255));
		blocks.push_back(newBlock);
	}
}

void FirstStep(vector<Block>& blocks, int& animationStep)
{
	for (int i = 0; i < BLOCKS_COUNT; i++)
	{
		if (START_POSITION.x + FIRST_STEP_SHIFT > blocks[i].position.x)
		{
			blocks[i].position.x += BLOCK_SPEED;
			blocks[i].figure.move(BLOCK_SPEED, 0);
		}
		else
		{
			animationStep = 2;
		}
	}
}

void SecondStep(vector<Block>& blocks, int& animationStep)
{
	for (int i = 0; i < BLOCKS_COUNT; i++)
	{
		if (blocks[0].figure.getPosition().y != blocks[i].figure.getPosition().y)
		{
			blocks[i].figure.move(BLOCK_SPEED / 2, -BLOCK_SPEED / 2);
			blocks[i].position.x = blocks[i].figure.getPosition().x;
			blocks[i].position.y = blocks[i].figure.getPosition().y;
		}
		else if (blocks[0].figure.getPosition().y == blocks[BLOCKS_COUNT - 1].figure.getPosition().y)
		{
			animationStep = 3;
		}
	}
}

void ThirdStep(vector<Block>& blocks, int& animationStep)
{
	for (int i = 0; i < BLOCKS_COUNT; i++)
	{
		if (static_cast<int>(blocks[i].figure.getFillColor().b) > 0)
		{
			int blue = static_cast<int>(blocks[i].figure.getFillColor().b) - BLOCK_COLOR_CHANGE_SPEED;
			blocks[i].figure.setFillColor(Color(255, 255, blue));
		}
		else
		{
			animationStep = 4;
		}
	}
}

void ForthStep(vector<Block>& blocks, int& animationStep)
{
	for (int i = 0; i < BLOCKS_COUNT; i++)
	{
		if (blocks[i].position.y != blocks[i].startPosition.y)
		{
			blocks[i].position.y += BLOCK_SPEED;
			blocks[i].figure.move(0, BLOCK_SPEED);
		}
		else if (blocks[BLOCKS_COUNT - 1].position.y == blocks[BLOCKS_COUNT - 1].startPosition.y)
		{
			animationStep = 5;
		}
	}
}

void FifthStep(vector<Block>& blocks, int& animationStep)
{
	for (int i = 0; i < BLOCKS_COUNT; i++)
	{
		if (blocks[i].position.x != blocks[i].startPosition.x)
		{
			blocks[i].position.x -= BLOCK_SPEED;
			blocks[i].figure.move(-BLOCK_SPEED, 0);
		}
		else if (blocks[BLOCKS_COUNT - 1].position.x == blocks[BLOCKS_COUNT - 1].startPosition.x)
		{
			animationStep = 6;
		}
	}
}

void SixthStep(vector<Block>& blocks, int& animationStep)
{
	for (int i = 0; i < BLOCKS_COUNT; i++)
	{
		if (static_cast<int>(blocks[i].figure.getFillColor().b) != 255)
		{
			int blue = static_cast<int>(blocks[i].figure.getFillColor().b) + BLOCK_COLOR_CHANGE_SPEED;
			blocks[i].figure.setFillColor(Color(255, 255, blue));
		}
		else
		{
			animationStep = 1;
		}
	}
}

void Update(vector<Block>& blocks, int& animationStep)
{
	switch (animationStep)
	{
	case 1: FirstStep(blocks, animationStep); break;
	case 2: SecondStep(blocks, animationStep); break;
	case 3: ThirdStep(blocks, animationStep); break;
	case 4: ForthStep(blocks, animationStep); break;
	case 5: FifthStep(blocks, animationStep); break;
	case 6: SixthStep(blocks, animationStep); break;
	}
}

int main()
{
	vector<Block> blocks;
	vector<Block> Sblocks;

	int animationStep = 1;

	RenderWindow window(VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Lab 7.2");
	
	InitializeProgram(blocks);

	Clock clock;
	Time updateTime = Time::Zero;

	while (window.isOpen())
	{
		updateTime += clock.restart();
		while (updateTime > FPS_LIMIT)
		{
			updateTime -= FPS_LIMIT;
			ProcessEvents(window);
			Update(blocks, animationStep);
		}
		DrawWindow(window, blocks);
	}
	return 0;
}