#include <SFML/Graphics.hpp>
#include <stdlib.h>			// srand(), read()
#include <time.h>			// time()
#include <stdio.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_RIGHT	2
#define DIR_LEFT	3
#define BODY_MAX	20	// ���� �ִ� ����

using namespace sf;

class Object {
public:
	int x_;
	int y_;
	RectangleShape sprite_;
};

class Snake {
public:
	int dir_;
	int length_;
	Object body_[BODY_MAX];
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
	snake.length_ = 1;
	for (int i = 0; i < BODY_MAX; i++) {
		snake.body_[i].x_ = -100;
		snake.body_[i].y_ = -100;
		snake.body_[i].sprite_.setPosition(snake.body_[i].x_ * block, snake.body_[i].y_ * block);
		snake.body_[i].sprite_.setSize(Vector2f(block, block));
		snake.body_[i].sprite_.setFillColor(Color::Green);

	}
	snake.body_[0].x_ = 3;
	snake.body_[0].y_ = 3;
	
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
			snake.body_[0].y_--;
		}
		
		else if (snake.dir_ == DIR_DOWN) {
			snake.body_[0].y_++;
		}
		
		else if (snake.dir_ == DIR_LEFT) {
			snake.body_[0].x_--;
		}
		
		else if (snake.dir_ == DIR_RIGHT) {
			snake.body_[0].x_++;
		}

		// ���뿡 ���� �̵�
		for (int i = snake.length_ - 1; i > 0; i--) {
			snake.body_[i].x_ = snake.body_[i - 1].x_;
			snake.body_[i].y_ = snake.body_[i - 1].y_;
			snake.body_[i].sprite_.setPosition(snake.body_[i].x_ * block, snake.body_[i].y_ * block);

		}

		if (snake.body_[0].x_ < 0) snake.body_[0].x_ = 0;
		if (snake.body_[0].x_ >= w) snake.body_[0].x_ = w - 1;
		if (snake.body_[0].y_ < 0) snake.body_[0].y_ = 0;
		if (snake.body_[0].y_ >= h) snake.body_[0].y_ = h - 1;
		
		for (int i = 0; i < BODY_MAX; i++) {
			snake.body_[i].sprite_.setPosition(snake.body_[i].x_ * block, snake.body_[i].y_ * block);
		}

		// ���� ����� �Ծ��� �� ���� �����
		// TODO : ���̰� 1�� �� �� �� �Ծ�� ������� ���� ��ġ��
		if (snake.body_[0].x_ == apple.x_ && snake.body_[0].y_ == apple.y_)
		{
			apple.x_ = rand() % w;
			apple.y_ = rand() % h;
			apple.sprite_.setPosition(apple.x_ * block, apple.y_ * block);
			snake.length_++;
		}

		// render
		window.clear();
		
		for (int i = 0; i < BODY_MAX; i++) {
			window.draw(snake.body_[i].sprite_);
		}

		window.draw(apple.sprite_);	// ��� ����� ��ĥ��� ����� ���� ����
		
		window.display();
	}

	return 0;
}