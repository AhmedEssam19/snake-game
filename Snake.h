#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class Snake
{
private:
	const sf::Texture whole_snake;
	unsigned int length;
	std::vector<sf::Sprite> p_snake{2 + length};
	sf::Sprite apple;
	const unsigned int width{ 64 };
	const unsigned int height{ 64 };


public:
	Snake(const sf::Texture& whole_snake, unsigned int length = 1);
	void start();
	void draw(sf::RenderWindow& window);
	void move(float x, float y);
	void move_right();
	void move_left();
	void move_up();
	void move_down();
	void rotate();
	void apple_eaten();
	void snake_crash(sf::RenderWindow& window);
};

