#include <SFML/Graphics.hpp>
#include <stdlib.h>			// srand(), read()
#include <time.h>			// time()

#include <stdio.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_RIGHT	2
#define DIR_LEFT	3

using namespace sf;

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


	RectangleShape snake;
	int snake_dir = DIR_DOWN;
	int snake_x = 3;
	int snake_y = 3;
	snake.setPosition(snake_x * block, snake_y * block);
	snake.setSize(Vector2f(block, block));
	snake.setFillColor(Color::Green);
	
	RectangleShape apple;
	int apple_x = rand() % w;
	int apple_y = rand() % h;
	apple.setPosition(apple_x * block, apple_y * block);
	apple.setSize(Vector2f(block, block));
	apple.setFillColor(Color::Red);
	
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
			snake_dir = DIR_UP;
		}

		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			snake_dir = DIR_DOWN;
		}

		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			snake_dir = DIR_LEFT;
		}

		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			snake_dir = DIR_RIGHT;
		}

		// update

		if (snake_dir == DIR_UP) {
			snake_y--;
		}

		else if (snake_dir == DIR_DOWN) {
			snake_y++;
		}

		else if (snake_dir == DIR_LEFT) {
			snake_x--;
		}

		else if (snake_dir == DIR_RIGHT) {
			snake_x++;
		}

		snake.setPosition(snake_x * block, snake_y * block);

		// 뱀이 사과를 먹었을 때
		if (snake.getGlobalBounds().intersects(apple.getGlobalBounds()))
		{
			apple_x = rand() % w;
			apple_y = rand() % h;
			apple.setPosition(apple_x * block, apple_y * block);
		}
		
		// render
		
		window.clear();
		
		window.draw(snake);
		
		window.draw(apple);	// 뱀과 사과가 겹칠경우 사과가 위에 나옴
		
		window.display();
	}

	return 0;
}