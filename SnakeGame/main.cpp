#include <SFML/Graphics.hpp>
#include <stdlib.h>			// srand(), read()
#include <time.h>			// time()

#include <stdio.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_RIGHT	2
#define DIR_LEFT	3
#define BODY_MAX	20	// 뱀의 최대 길이

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

	int block = 40; // 한 칸을 40 으로
	const int w = WIDTH / block;
	const int h = HEIGHT / block;

	RenderWindow  window(VideoMode(WIDTH, HEIGHT), "Snake Game");
	// 1초에 30번의 작업이 이루어 지도록 frame 조절
	// 컴퓨터 사양이 달라도 똑같이 행동 함
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
			// 윈도우의 x를 눌렀을 때 창이 닫아지도록
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

		// 몸통에 대한 이동
		for (int i = snake.length_ - 1; i > 0; i--) {
			snake.body_[i].x_ = snake.body_[i - 1].x_;
			snake.body_[i].y_ = snake.body_[i - 1].y_;
		}

		// 머리에 대한 이동
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

		// 뱀이 사과를 먹었을 때 몸통 길어짐
		// TODO : 길이가 1일 때 두 번 먹어야 길어지는 버그 고치기
		if (snake.body_[0].x_ == apple.x_ && snake.body_[0].y_ == apple.y_)
		{
			apple.x_ = rand() % w;
			apple.y_ = rand() % h;
			apple.sprite_.setPosition(apple.x_ * block, apple.y_ * block);
			if (snake.length_ < BODY_MAX)
				snake.length_++;
		}

		if (snake.body_[0].x_ < 0) snake.body_[0].x_ = 0;
		if (snake.body_[0].x_ >= w) snake.body_[0].x_ = w - 1;
		if (snake.body_[0].y_ < 0) snake.body_[0].y_ = 0;
		if (snake.body_[0].y_ >= h) snake.body_[0].y_ = h - 1;

		for (int i = 0; i < snake.length_; i++) {
			snake.body_[i].sprite_.setPosition(snake.body_[i].x_ * block, snake.body_[i].y_ * block);
		}

		// render
		window.clear();

		for (int i = 0; i < BODY_MAX; i++) {
			window.draw(snake.body_[i].sprite_);
		}

		window.draw(apple.sprite_);	// 뱀과 사과가 겹칠경우 사과가 위에 나옴

		window.display();
	}
	
	return 0;
}