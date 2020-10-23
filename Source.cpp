#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include <ctime>
#include "Snake.h"

int main()
{
	srand(time(NULL));
	const float moving_distance{ 64 };
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "My First Game");
	sf::Texture snake_texture, background;
	snake_texture.setSmooth(true);
	background.setSmooth(true);
	sf::Clock clock;
	float speed{};
	float x{}, y{};
	enum driections { left, up, right, down };
	int direction = right;
	bool key_pressed{ false };

	if (!snake_texture.loadFromFile("snake-graphics.png"))
	{
		std::cout << "Loading Error" << std::endl;
		return 1;
	}

	if (!background.loadFromFile("images.jpg"))
	{
		std::cout << "Loading Error" << std::endl;
		return 1;
	}

	// set the back ground 
	sf::Sprite Pbackground(background);

	// scale the background to fill the screen
	Pbackground.setScale(sf::Vector2f((float) 1920 / Pbackground.getTextureRect().width, 
						(float) 1080 / Pbackground.getTextureRect().height));

	// declaring snake and setting its initial orientaion
	Snake snake(snake_texture);
	snake.start();

	while (window.isOpen())
	{
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// close window
			if (Event.type == sf::Event::Closed)
				window.close();

			if (Event.type == sf::Event::KeyPressed)
			{
				// moving left
				if (Event.key.code == sf::Keyboard::Left)
				{
					// ensure not to rotate 180 degrees
					// key_pressed prevent double press before moving the snake
					if (direction != right && !key_pressed)
					{
						key_pressed = true;
						snake.move_left();
						x = -moving_distance; y = 0;
						direction = left;
					}
				}

				// moving down
				else if (Event.key.code == sf::Keyboard::Down)
				{
					if (direction != up && !key_pressed)
					{
						key_pressed = true;
						snake.move_down();
						x = 0; y = moving_distance;
						direction = down;
					}
				}

				// moving right
				else if (Event.key.code == sf::Keyboard::Right)
				{
					if (direction != left && !key_pressed)
					{
						key_pressed = true;
						snake.move_right();
						x = moving_distance; y = 0;
						direction = right;
					}
				}

				// moving up
				else if (Event.key.code == sf::Keyboard::Up)
				{
					if (direction != down && !key_pressed)
					{
						key_pressed = true;
						snake.move_up();
						x = 0; y = -moving_distance;
						direction = up;
					}
				}

				else
				{
					x = 0; y = 0;
				}
			}
		}

			speed += clock.restart().asSeconds() * 100;
			if (speed > 20)
			{
				window.draw(Pbackground);
				key_pressed = false;
				speed = 0;
				snake.move(x, y);
				snake.apple_eaten();
				snake.snake_crash(window);
				snake.draw(window);

				// rotate the snake after drawing it
				snake.rotate();
				window.display();
				window.clear();
			}
	}
}

