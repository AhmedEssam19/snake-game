#include "Snake.h"

Snake::Snake(const sf::Texture& whole_snake, unsigned int length):
    whole_snake {whole_snake}, length{length}
{
    // setting snake head
    p_snake[0].setTexture(whole_snake);
    p_snake[0].setTextureRect(sf::IntRect(4 * width, 0 * height, width, height));

    // setting snake body
    size_t len = p_snake.size();
    for (int i = 1; i < len - 1; i++)
    {
        p_snake[i].setTexture(whole_snake);
        p_snake[i].setTextureRect(sf::IntRect(1 * width, 0 * height, width, height));
    }

    // setting snake tail
    p_snake[len - 1].setTexture(whole_snake);
    p_snake[len - 1].setTextureRect(sf::IntRect(4 * width, 2 * height, width, height));

    // setting the apple
    apple.setTexture(whole_snake);
    apple.setTextureRect(sf::IntRect(0 * width, 3 * height, width, height));
}


void Snake::start()
{
    // setting the orientation of the snake in the beginning
    size_t len = p_snake.size();
    for (int i = 0; i < len - 1; i++)
        p_snake[i].setPosition(sf::Vector2f(width * (len - i - 1), 0));
    
    // setting The position of the apple randomly
    apple.setPosition(sf::Vector2f((rand() % 30) * 64, (rand() % 15) * 64));
}

void Snake::draw(sf::RenderWindow& window)
{
    // draw the snake and the apple
    size_t len = p_snake.size();
    for (int i = 0; i < len; i++)
        window.draw(p_snake[i]);

    window.draw(apple);
}

void Snake::move(float x, float y)
{
    // moving snake parts. we move head first then we move next part to head last position and so on
    if (x != 0 || y != 0)
    {
        size_t len = p_snake.size();
        for (size_t i = len - 1; i > 0; i--)
        {
            p_snake[i].setPosition(p_snake[i - 1].getPosition());
        }
        p_snake[0].setPosition(sf::Vector2f((int)(p_snake[0].getPosition().x + x + 1920) % 1920, (int)(p_snake[0].getPosition().y + y + 1088) % 1088));
    }
}

void Snake::move_right()
{
    // rotating the snake part that comes afterhead to the right depending on last state
    if (p_snake[0].getTextureRect() == sf::IntRect(3 * width, 0 * height, width, height))
        p_snake[1].setTextureRect(sf::IntRect(0 * width, 0 * height, width, height));
    else if(p_snake[0].getTextureRect() == sf::IntRect(4 * width, 1 * height, width, height))
        p_snake[1].setTextureRect(sf::IntRect(0 * width, 1 * height, width, height));

    // rotating the snake head the right
    p_snake[0].setTextureRect(sf::IntRect(4 * width, 0 * height, width, height));
}

void Snake::move_left()
{
    // rotating the snake part that comes afterhead to the left depending on last state
    if (p_snake[0].getTextureRect() == sf::IntRect(3 * width, 0 * height, width, height))
        p_snake[1].setTextureRect(sf::IntRect(2 * width, 0 * height, width, height));
    else if (p_snake[0].getTextureRect() == sf::IntRect(4 * width, 1 * height, width, height))
        p_snake[1].setTextureRect(sf::IntRect(2 * width, 2 * height, width, height));

    // rotating the snake head the left
    p_snake[0].setTextureRect(sf::IntRect(3 * width, 1 * height, width, height));
}

void Snake::move_up()
{
    // rotating the snake part that comes afterhead to the north depending on last state
    if (p_snake[0].getTextureRect() == sf::IntRect(4 * width, 0 * height, width, height))
        p_snake[1].setTextureRect(sf::IntRect(2 * width, 2 * height, width, height));
    else if (p_snake[0].getTextureRect() == sf::IntRect(3 * width, 1 * height, width, height))
        p_snake[1].setTextureRect(sf::IntRect(0 * width, 1 * height, width, height));

    // rotating the snake head the north
    p_snake[0].setTextureRect(sf::IntRect(3 * width, 0 * height, width, height));
}

void Snake::move_down()
{
    // rotating the snake part that comes afterhead to the south depending on last state
    if (p_snake[0].getTextureRect() == sf::IntRect(4 * width, 0 * height, width, height))
        p_snake[1].setTextureRect(sf::IntRect(2 * width, 0 * height, width, height));
    else if (p_snake[0].getTextureRect() == sf::IntRect(3 * width, 1 * height, width, height))
        p_snake[1].setTextureRect(sf::IntRect(0 * width, 0 * height, width, height));
    
    // rotating the snake head the south
    p_snake[0].setTextureRect(sf::IntRect(4 * width, 1 * height, width, height));
}

void Snake::rotate()
{
    int counter{ 0 };
    size_t len = p_snake.size();
    // changing tail orientation and turning part depending on turning part
    if (p_snake[len - 1].getTextureRect() == sf::IntRect(4 * width, 2 * height, width, height))
    {
        if (p_snake[len - 2].getTextureRect() == sf::IntRect(2 * width, 0 * height, width, height))
        {
            p_snake[len - 2].setTextureRect(sf::IntRect(2 * width, 1 * height, width, height));
            p_snake[len - 1].setTextureRect(sf::IntRect(4 * width, 3 * height, width, height));
        }
        else if (p_snake[len - 2].getTextureRect() == sf::IntRect(2 * width, 2 * height, width, height))
        {
            p_snake[len - 1].setTextureRect(sf::IntRect(3 * width, 2 * height, width, height));
            p_snake[len - 2].setTextureRect(sf::IntRect(2 * width, 1 * height, width, height));
        }
    }
    else if (p_snake[len - 1].getTextureRect() == sf::IntRect(3 * width, 2 * height, width, height))
    {
        if (p_snake[len - 2].getTextureRect() == sf::IntRect(2 * width, 0 * height, width, height))
        {
            p_snake[len - 2].setTextureRect(sf::IntRect(1 * width, 0 * height, width, height));
            p_snake[len - 1].setTextureRect(sf::IntRect(3 * width, 3 * height, width, height));
        }
        else if (p_snake[len - 2].getTextureRect() == sf::IntRect(0 * width, 0 * height, width, height))
        {
            p_snake[len - 1].setTextureRect(sf::IntRect(4 * width, 2 * height, width, height));
            p_snake[len - 2].setTextureRect(sf::IntRect(1 * width, 0 * height, width, height));
        }
    }

    else if (p_snake[len - 1].getTextureRect() == sf::IntRect(4 * width, 3 * height, width, height))
    {
        if (p_snake[len - 2].getTextureRect() == sf::IntRect(0 * width, 1 * height, width, height))
        {
            p_snake[len - 1].setTextureRect(sf::IntRect(4 * width, 2 * height, width, height));
            p_snake[len - 2].setTextureRect(sf::IntRect(1 * width, 0 * height, width, height));
        }

        else if (p_snake[len - 2].getTextureRect() == sf::IntRect(2 * width, 2 * height, width, height))
        {
            p_snake[len - 1].setTextureRect(sf::IntRect(3 * width, 3 * height, width, height));
            p_snake[len - 2].setTextureRect(sf::IntRect(1 * width, 0 * height, width, height));
            p_snake[len - 2].setTextureRect(sf::IntRect(1 * width, 0 * height, width, height));
        }
    }

    else
    {
        if (p_snake[len - 2].getTextureRect() == sf::IntRect(0 * width, 1 * height, width, height))
        {
            p_snake[len - 1].setTextureRect(sf::IntRect(3 * width, 2 * height, width, height));
            p_snake[len - 2].setTextureRect(sf::IntRect(2 * width, 1 * height, width, height));
        }

        else if (p_snake[len - 2].getTextureRect() == sf::IntRect(0 * width, 0 * height, width, height))
        {
            p_snake[len - 1].setTextureRect(sf::IntRect(4 * width, 3 * height, width, height));
            p_snake[len - 2].setTextureRect(sf::IntRect(2 * width, 1 * height, width, height));
        }
    }

    // changing the spirit after turning part
    for (size_t i = 1; i < len - 1; i++)
    {

        // counnting number of turning parts
        if (p_snake[i].getTextureRect() == sf::IntRect(2 * width, 0 * height, width, height) ||
            p_snake[i].getTextureRect() == sf::IntRect(0 * width, 0 * height, width, height) ||
            p_snake[i].getTextureRect() == sf::IntRect(2 * width, 2 * height, width, height) ||
            p_snake[i].getTextureRect() == sf::IntRect(0 * width, 1 * height, width, height))
   
            counter++;

        else if (counter > 0)
        {
            sf::IntRect temp = p_snake[i].getTextureRect();

            // shifting each spirit to the next one
            for (int j = i; j > i - counter; j--)
            {
                p_snake[j].setTextureRect(p_snake[j - 1].getTextureRect());
            }

            // if number of turning parts is odd we alternating snake body part
            if (counter % 2 != 0)
            {
                if (temp == sf::IntRect(2 * width, 1 * height, width, height))
                {
                    p_snake[i - counter].setTextureRect(sf::IntRect(1 * width, 0 * height, width, height));
                }
                else if (temp == sf::IntRect(1 * width, 0 * height, width, height))
                {
                    p_snake[i - counter].setTextureRect(sf::IntRect(2 * width, 1 * height, width, height));
                }
            }

            // if number of turning parts is even we change nothing
            else
                p_snake[i - counter].setTextureRect(temp);

            counter = 0;
        }
    }
}

void Snake::apple_eaten()
{
    // check if snake head touched the apple
    if (!(p_snake[0].getPosition().x >= apple.getPosition().x + width ||
        p_snake[0].getPosition().x + width <= apple.getPosition().x ||
        p_snake[0].getPosition().y + height <= apple.getPosition().y ||
        p_snake[0].getPosition().y >= apple.getPosition().y + height))
    {
        // changing position of the apple randomly
        apple.setPosition(sf::Vector2f((rand() % 30) * 64, (rand() % 15) * 64));
        
        // inserting the new body part after snake head directly depending on the head orientation
        sf::Sprite temp(whole_snake);
        if (p_snake[0].getTextureRect() == sf::IntRect(3 * width, 0 * height, width, height))
        {
            temp.setTextureRect(sf::IntRect(2 * width, 1 * height, width, height));
          
            // setting position of new part to head position
            temp.setPosition(p_snake[0].getPosition());
            p_snake[0].move(0, -64);
        }

        else if (p_snake[0].getTextureRect() == sf::IntRect(4 * width, 0 * height, width, height))
        {
            temp.setTextureRect(sf::IntRect(1 * width, 0 * height, width, height));
            temp.setPosition(p_snake[0].getPosition());
            p_snake[0].move(64, 0);
        }

        else if (p_snake[0].getTextureRect() == sf::IntRect(4 * width, 1 * height, width, height))
        {
            temp.setTextureRect(sf::IntRect(2 * width, 1 * height, width, height));
            temp.setPosition(p_snake[0].getPosition());
            p_snake[0].move(0, 64);
        }

        else
        {
            temp.setTextureRect(sf::IntRect(1 * width, 0 * height, width, height));
            temp.setPosition(p_snake[0].getPosition());
            p_snake[0].move(-64, 0);
        }

        // ensure that snake move from end of a side to start of the other side
        p_snake[0].setPosition(sf::Vector2f((int)(p_snake[0].getPosition().x + 1920) % 1920, (int)(p_snake[0].getPosition().y + 1088) % 1088));
        //increasing the length of the body
        length++;
        p_snake.insert(p_snake.begin() + 1, temp);
    }
}

void Snake::snake_crash(sf::RenderWindow& window)
{
    // check if snake head touched any part of snake body
    size_t len = p_snake.size();
    for (size_t i = 1; i < len; i++)
    {
        if (!(p_snake[0].getPosition().x >= p_snake[i].getPosition().x + width ||
            p_snake[0].getPosition().x + width <= p_snake[i].getPosition().x ||
            p_snake[0].getPosition().y + height <= p_snake[i].getPosition().y ||
            p_snake[0].getPosition().y >= p_snake[i].getPosition().y + height))

            window.close();
    }
}
