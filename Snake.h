#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class Snake
{
private:
	const sf::Texture snake_image;
	unsigned int length;
	std::vector<sf::Sprite> p_snake{length};
	sf::Sprite apple;

	// width and height of snake parts in pixels
	static const unsigned int width{ 64 };
	static const unsigned int height{ 64 };


	// set different snake parts rectangles
	static const sf::IntRect UP_HEAD;
	static const sf::IntRect DOWN_HEAD;
	static const sf::IntRect LEFT_HEAD;
	static const sf::IntRect RIGHT_HEAD;

	static const sf::IntRect UP_TAIL;
	static const sf::IntRect DOWN_TAIL;
	static const sf::IntRect LEFT_TAIL;
	static const sf::IntRect RIGHT_TAIL;

	static const sf::IntRect HORIZONTAL_MID;
	static const sf::IntRect VERTICAL_MID;

	static const sf::IntRect FIRST_QUARTER;
	static const sf::IntRect SECOND_QUARTER;
	static const sf::IntRect THIRD_QUARTER;
	static const sf::IntRect FORTH_QUARTER;

public:
	Snake(const sf::Texture& snake_image, unsigned int length = 1);
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

