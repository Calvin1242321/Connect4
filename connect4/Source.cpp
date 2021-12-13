// The connect four game, Version 1.0, April 19, 2021
// Written by:
//     Calvin Cheng(zxc1242321@gmail.com)
// Taiwan Tech,Spring 2021

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace std;
using namespace sf;

const int WIDTH = 7;
const int HEIGHT = 6;

int board[HEIGHT][WIDTH];
int columnMax[WIDTH];
int counter;
int j = 0;
int k = 0;
bool yelloSide = true;


void draw();

//	initial the game
void reset();
//	end the game, if someone is win or draw
void check();
void yelloPlay(Vector2i a);
void redPlay(Vector2i a);
bool gameContinue();
bool firstTime;


Texture Board;
Texture red_checker;
Texture yellow_checker;

Sprite main_board;
Sprite red[21];
Sprite yellow[21];

int main()
{

	RenderWindow window(sf::VideoMode(700, 600), "Connect 4! (space to restart)");
	reset();



	while (window.isOpen())
	{
		Vector2i pos;
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			////move back//////
			draw();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
					reset();
				}
			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{

					pos = Mouse::getPosition(window);
					firstTime = false;
					pos.x /= 100;
					pos.y /= 100;
					pos.x++;
					pos.y++;
					//cout << pos.x << " " << pos.y;
					if (yelloSide)
					{
						yelloPlay(pos);
						yelloSide = false;
					}
					else
					{
						redPlay(pos);
						yelloSide = true;
					}
				}
			}
		}
		
		window.clear();
		window.draw(main_board);
		for (int i = 0;i < 21;i++)
		{
			window.draw(red[i]);
			window.draw(yellow[i]);
		}
		window.display();
		if (!gameContinue())
		{
			system("pause");
			reset();
		}
	}
	return 0;
}

void reset()
{
	Board.loadFromFile("images/board.png");
	red_checker.loadFromFile("images/red.png");
	yellow_checker.loadFromFile("images/yellow.png");
	main_board.setTexture(Board);
	for (int i = 0;i < 21;i++)
	{
		red[i].setTexture(red_checker);
		red[i].setPosition(800, 700);
		yellow[i].setTexture(yellow_checker);
		yellow[i].setPosition(800, 700);
	}
	yelloSide = true;
	firstTime = true;
	counter = 0;
	for (int i = 0;i < HEIGHT;i++)
	{
		for (int j = 0;j < WIDTH;j++)
		{
			board[i][j] = 0;
		}
	}
	for (int i = 0;i < WIDTH;i++)
	{
		columnMax[i] = 0;
	}
}

void draw()
{
	system("CLS");
	if (firstTime)
	{
		if (yelloSide)
		{
			cout << "Yellow's Turn\n";
		}
		else
		{
			cout << "Red's Turn\n";
		}
	}

	else
	{
		firstTime = true;
	}

}

bool gameContinue()
{
	//	row
	for (int i = 0;i < HEIGHT;i++)
	{
		for (int j = 0;j < WIDTH - 3;j++)
		{
			if (board[i][j] == 1 && board[i][j + 1] == 1 && board[i][j + 2] == 1 && board[i][j + 3] == 1)
			{
				cout << "Yellow won!\n";
				//system("pause");
				return false;
			}
			else if (board[i][j] == 2 && board[i][j + 1] == 2 && board[i][j + 2] == 2 && board[i][j + 3] == 2)
			{
				cout << "Red won!\n";
				//system("pause");
				return false;
			}
		}
	}
	//	column

	for (int i = 0;i < HEIGHT - 3;i++)
	{
		for (int j = 0;j < WIDTH;j++)
		{
			if (board[i][j] == 1 && board[i + 1][j] == 1 && board[i + 2][j] == 1 && board[i + 3][j] == 1)
			{
				cout << "Yellow won!\n";
				//system("pause");
				return false;
			}
			else if (board[i][j] == 2 && board[i + 1][j] == 2 && board[i + 2][j] == 2 && board[i + 3][j] == 2)
			{
				cout << "Red won!\n";
				//system("pause");
				return false;
			}
		}
	}
	//	diag

	for (int i = 0;i < HEIGHT - 3;i++)
	{
		for (int j = 0;j < WIDTH - 3;j++)
		{
			if (board[i][j] == 1 && board[i + 1][j + 1] == 1 && board[i + 2][j + 2] == 1 && board[i + 3][j + 3] == 1)
			{
				cout << "Yellow won!\n";
				system("pause");
				return false;
			}
			else if (board[i][j] == 2 && board[i + 1][j + 1] == 2 && board[i + 2][j + 2] == 2 && board[i + 3][j + 3] == 2)
			{
				cout << "Red won!\n";
				system("pause");
				return false;
			}
		}
	}

	for (int i = 0;i < HEIGHT - 3;i++)
	{
		for (int j = WIDTH - 1;j >= 3;j--)
		{
			if (board[i][j] == 1 && board[i + 1][j - 1] == 1 && board[i + 2][j - 2] == 1 && board[i + 3][j - 3] == 1)
			{
				cout << "Yellow won!\n";
				//system("pause");
				return false;
			}
			else if (board[i][j] == 2 && board[i + 1][j - 1] == 2 && board[i + 2][j - 2] == 2 && board[i + 3][j - 3] == 2)
			{
				cout << "Red won!\n";
				//system("pause");
				return false;
			}
		}
	}

	//	draw
	if (counter == 42)
	{
		cout << "Draw\n";
		system("pause");
		return false;
	}

	return true;
}

void yelloPlay(Vector2i a)
{
	int line;
	line = a.x;

	columnMax[line - 1]++;
	if (columnMax[line - 1] > HEIGHT)
	{
		columnMax[line - 1]--;
	}

	for (int i = WIDTH - 1;i >= 0;i--)
	{
		if (board[i][line - 1] == 0)
		{
			board[i][line - 1] = 1;

			if (j != 21)
			{
				yellow[j].setPosition((line - 1) * 100, i * 100);
			}
			j++;
			break;
		}
	}
}
void redPlay(Vector2i a)
{

	int line;
	line = a.x;

	columnMax[line - 1]++;
	if (columnMax[line - 1] > HEIGHT)
	{
		columnMax[line - 1]--;
	}

	for (int i = WIDTH - 1;i >= 0;i--)
	{
		if (board[i][line - 1] == 0)
		{
			board[i][line - 1] = 2;

			if (k != 21)
			{
				red[k].setPosition((line - 1) * 100, i * 100);
			}
			k++;
			break;
		}
	}
}

