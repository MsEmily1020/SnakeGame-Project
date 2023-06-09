#include <SFML/Graphics.hpp>
#include <stdlib.h>			// srand(), read()
#include <time.h>			// time()

using namespace sf;

int main() {
	const int WIDTH = 1000;
	const int HEIGHT = 800;

	RenderWindow  window(VideoMode(WIDTH, HEIGHT), "Snake Game");
	// 1초에 60번의 작업이 이루어 지도록 frame 조절
	// 컴퓨터 사양이 달라도 똑같이 행동 함
	window.setFramerateLimit(60);

	srand(time(NULL));


	// 한 칸을 40 으로
	int block = 40;

	RectangleShape snake;
	snake.setPosition(200, 300);
	snake.setSize(Vector2f(block, block));
	snake.setFillColor(Color::Green);

	RectangleShape apple;
	apple.setPosition(rand() % WIDTH - block, rand() % HEIGHT - block);
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
			snake.move(0, -5);

		else if (Keyboard::isKeyPressed(Keyboard::Down))
			snake.move(0, 5);

		else if (Keyboard::isKeyPressed(Keyboard::Left))
			snake.move(-5, 0);

		else if (Keyboard::isKeyPressed(Keyboard::Right))
			snake.move(5, 0);

		// update

		// 뱀이 사과를 먹었을 때
		if (snake.getGlobalBounds().intersects(apple.getGlobalBounds()))
		{
			apple.setPosition(rand() % WIDTH - block, rand() % HEIGHT - block);
		}

		// render	
		window.clear();

		window.draw(snake);

		window.draw(apple);	// 뱀과 사과가 겹칠경우 사과가 위에 나옴

		window.display();
	}

	return 0;
}