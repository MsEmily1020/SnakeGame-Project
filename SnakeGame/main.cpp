#include <SFML/Graphics.hpp>
#include <stdlib.h>			// srand(), read()
#include <time.h>			// time()
#include <stdio.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_RIGHT	2
#define DIR_LEFT	3

using namespace sf;

class Snake {
public:
	int dir_;
	int x_;
	int y_;
	RectangleShape sprite_;	// �׷���
};

class Apple {
public:
	int x_;
	int y_;
	RectangleShape sprite_;
};


int main() {
	const int WIDTH = 1000;
	const int HEIGHT = 800;

	int block = 40; // �� ĭ�� 40 ����
	const int w = WIDTH / block;
	const int h = HEIGHT / block;
	
	RenderWindow  window(VideoMode(WIDTH, HEIGHT), "Snake Game");
	// 1�ʿ� 30���� �۾��� �̷�� ������ frame ����
	// ��ǻ�� ����� �޶� �Ȱ��� �ൿ ��
	window.setFramerateLimit(15);
	
	srand(time(NULL));

	Snake snake;
	snake.dir_ = DIR_DOWN;
	snake.x_ = 3;
	snake.y_ = 3;
	snake.sprite_.setPosition(snake.x_ * block, snake.y_ * block);
	snake.sprite_.setSize(Vector2f(block, block));
	snake.sprite_.setFillColor(Color::Green);

	Apple apple;
	apple.x_ = rand() % w;
	apple.y_ = rand() % h;
	apple.sprite_.setPosition(apple.x_ * block, apple.y_ * block);
	apple.sprite_.setSize(Vector2f(block, block));
	apple.sprite_.setFillColor(Color::Red);

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			// �������� x�� ������ �� â�� �ݾ�������
			if (e.type == Event::Closed)
				window.close();
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			snake.dir_ = DIR_UP;
		}
		
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			snake.dir_ = DIR_DOWN;
		}
		
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			snake.dir_ = DIR_LEFT;
		}
		
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			snake.dir_ = DIR_RIGHT;
		}
		
		// update
		
		// �� �̵�
		if (snake.dir_ == DIR_UP) {
			snake.y_--;
		}
		
		else if (snake.dir_ == DIR_DOWN) {
			snake.y_++;
		}
		
		else if (snake.dir_ == DIR_LEFT) {
			snake.x_--;
		}
		
		else if (snake.dir_ == DIR_RIGHT) {
			snake.x_++;
		}

		if (snake.x_ < 0) snake.x_ = 0;
		if (snake.x_ >= w) snake.x_ = w - 1;
		if (snake.y_ < 0) snake.y_ = 0;
		if (snake.y_ >= h) snake.y_ = h - 1;

		snake.sprite_.setPosition(snake.x_ * block, snake.y_ * block);

		// ���� ����� �Ծ��� ��
		if (snake.x_ == apple.x_ && snake.y_ == apple.y_)
		{
			apple.x_ = rand() % w;
			apple.y_ = rand() % h;
			apple.sprite_.setPosition(apple.x_ * block, apple.y_ * block);
		}

		// render
		window.clear();

		window.draw(snake.sprite_);
		window.draw(apple.sprite_);	// ��� ����� ��ĥ��� ����� ���� ����

		window.display();
	}

	return 0;
}