#include "Snake.h"

const sf::IntRect Snake::UP_HEAD {3 * width, 0 * height, width, height};
const sf::IntRect Snake::DOWN_HEAD {4 * width, 1 * height, width, height};
const sf::IntRect Snake::LEFT_HEAD {3 * width, 1 * height, width, height};
const sf::IntRect Snake::RIGHT_HEAD {4 * width, 0 * height, width, height};

const sf::IntRect Snake::UP_TAIL {4 * width, 3 * height, width, height};
const sf::IntRect Snake::DOWN_TAIL {3 * width, 2 * height, width, height};
const sf::IntRect Snake::RIGHT_TAIL {3 * width, 3 * height, width, height};
const sf::IntRect Snake::LEFT_TAIL {4 * width, 2 * height, width, height};

const sf::IntRect Snake::HORIZONTAL_MID {1 * width, 0 * height, width, height};
const sf::IntRect Snake::VERTICAL_MID {2 * width, 1 * height, width, height};

const sf::IntRect Snake::FIRST_QUARTER {2 * width, 0 * height, width, height};
const sf::IntRect Snake::SECOND_QUARTER {0 * width, 0 * height, width, height};
const sf::IntRect Snake::THIRD_QUARTER {0 * width, 1 * height, width, height};
const sf::IntRect Snake::FORTH_QUARTER {2 * width, 2 * height, width, height};

Snake::Snake(const sf::Texture& snake_image, unsigned int length):
    snake_image {snake_image}, length{length}
{
    // setting snake head
    p_snake[0].setTexture(snake_image);
    p_snake[0].setTextureRect(RIGHT_HEAD);

    // setting snake body
    size_t len = p_snake.size();
    for (int i = 1; i < len - 1; i++)
    {
        p_snake[i].setTexture(snake_image);
        p_snake[i].setTextureRect(HORIZONTAL_MID);
    }

    // setting snake tail
    p_snake[len - 1].setTexture(snake_image);
    p_snake[len - 1].setTextureRect(LEFT_TAIL);

    // setting the apple
    apple.setTexture(snake_image);
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
    if (p_snake[0].getTextureRect() == UP_HEAD)
        p_snake[1].setTextureRect(SECOND_QUARTER);
    else if(p_snake[0].getTextureRect() == DOWN_HEAD)
        p_snake[1].setTextureRect(THIRD_QUARTER);

    // rotating the snake head the right
    p_snake[0].setTextureRect(RIGHT_HEAD);
}

void Snake::move_left()
{
    // rotating the snake part that comes afterhead to the left depending on last state
    if (p_snake[0].getTextureRect() == UP_HEAD)
        p_snake[1].setTextureRect(FIRST_QUARTER);
    else if (p_snake[0].getTextureRect() == DOWN_HEAD)
        p_snake[1].setTextureRect(FORTH_QUARTER);

    // rotating the snake head the left
    p_snake[0].setTextureRect(LEFT_HEAD);
}

void Snake::move_up()
{
    // rotating the snake part that comes afterhead to the north depending on last state
    if (p_snake[0].getTextureRect() == RIGHT_HEAD)
        p_snake[1].setTextureRect(FORTH_QUARTER);
    else if (p_snake[0].getTextureRect() == LEFT_HEAD)
        p_snake[1].setTextureRect(THIRD_QUARTER);

    // rotating the snake head the north
    p_snake[0].setTextureRect(UP_HEAD);
}

void Snake::move_down()
{
    // rotating the snake part that comes afterhead to the south depending on last state
    if (p_snake[0].getTextureRect() == RIGHT_HEAD)
        p_snake[1].setTextureRect(FIRST_QUARTER);
    else if (p_snake[0].getTextureRect() == LEFT_HEAD)
        p_snake[1].setTextureRect(SECOND_QUARTER);
    
    // rotating the snake head the south
    p_snake[0].setTextureRect(DOWN_HEAD);
}

void Snake::rotate()
{
    int counter{ 0 };
    size_t len = p_snake.size();
    // changing tail orientation and turning RIGHT depending on turning part
    if (p_snake[len - 1].getTextureRect() == LEFT_TAIL)
    {
        if (p_snake[len - 2].getTextureRect() == FIRST_QUARTER)
        {
            p_snake[len - 2].setTextureRect(VERTICAL_MID);
            p_snake[len - 1].setTextureRect(UP_TAIL);
        }
        else if (p_snake[len - 2].getTextureRect() == FORTH_QUARTER)
        {
            p_snake[len - 1].setTextureRect(DOWN_TAIL);
            p_snake[len - 2].setTextureRect(VERTICAL_MID);
        }
    }
    else if (p_snake[len - 1].getTextureRect() == DOWN_TAIL)
    {
        if (p_snake[len - 2].getTextureRect() == FIRST_QUARTER)
        {
            p_snake[len - 2].setTextureRect(HORIZONTAL_MID);
            p_snake[len - 1].setTextureRect(RIGHT_TAIL);
        }
        else if (p_snake[len - 2].getTextureRect() == SECOND_QUARTER)
        {
            p_snake[len - 1].setTextureRect(LEFT_TAIL);
            p_snake[len - 2].setTextureRect(HORIZONTAL_MID);
        }
    }

    else if (p_snake[len - 1].getTextureRect() == UP_TAIL)
    {
        if (p_snake[len - 2].getTextureRect() == THIRD_QUARTER)
        {
            p_snake[len - 1].setTextureRect(LEFT_TAIL);
            p_snake[len - 2].setTextureRect(HORIZONTAL_MID);
        }

        else if (p_snake[len - 2].getTextureRect() == FORTH_QUARTER)
        {
            p_snake[len - 1].setTextureRect(RIGHT_TAIL);
            p_snake[len - 2].setTextureRect(HORIZONTAL_MID);
            p_snake[len - 2].setTextureRect(HORIZONTAL_MID);
        }
    }

    else
    {
        if (p_snake[len - 2].getTextureRect() == THIRD_QUARTER)
        {
            p_snake[len - 1].setTextureRect(DOWN_TAIL);
            p_snake[len - 2].setTextureRect(VERTICAL_MID);
        }

        else if (p_snake[len - 2].getTextureRect() == SECOND_QUARTER)
        {
            p_snake[len - 1].setTextureRect(UP_TAIL);
            p_snake[len - 2].setTextureRect(VERTICAL_MID);
        }
    }

    // changing the spirit after turning part
    for (size_t i = 1; i < len - 1; i++)
    {

        // counnting number of turning parts
        if (p_snake[i].getTextureRect() == FIRST_QUARTER || p_snake[i].getTextureRect() == SECOND_QUARTER ||
            p_snake[i].getTextureRect() == FORTH_QUARTER || p_snake[i].getTextureRect() == THIRD_QUARTER)
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
                if (temp == VERTICAL_MID)
                {
                    p_snake[i - counter].setTextureRect(HORIZONTAL_MID);
                }
                else if (temp == HORIZONTAL_MID)
                {
                    p_snake[i - counter].setTextureRect(VERTICAL_MID);
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
        sf::Sprite temp(snake_image);
        if (p_snake[0].getTextureRect() == UP_HEAD)
        {
            temp.setTextureRect(VERTICAL_MID);
          
            // setting position of new part to head position
            temp.setPosition(p_snake[0].getPosition());
            p_snake[0].move(0, -64);
        }

        else if (p_snake[0].getTextureRect() == RIGHT_HEAD)
        {
            temp.setTextureRect(HORIZONTAL_MID);
            temp.setPosition(p_snake[0].getPosition());
            p_snake[0].move(64, 0);
        }

        else if (p_snake[0].getTextureRect() == DOWN_HEAD)
        {
            temp.setTextureRect(VERTICAL_MID);
            temp.setPosition(p_snake[0].getPosition());
            p_snake[0].move(0, 64);
        }

        else
        {
            temp.setTextureRect(HORIZONTAL_MID);
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
