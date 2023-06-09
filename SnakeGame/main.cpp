#include <SFML/Graphics.hpp>
#include <stdlib.h>			// srand(), read()
#include <time.h>			// time()

using namespace sf;

int main() {
	const int WIDTH = 1000;
	const int HEIGHT = 800;

	int block = 40; // �� ĭ�� 40 ����
	const int w = WIDTH / block;
	const int h = HEIGHT / block;

	RenderWindow  window(VideoMode(WIDTH, HEIGHT), "Snake Game");
	// 1�ʿ� 30���� �۾��� �̷�� ������ frame ����
	// ��ǻ�� ����� �޶� �Ȱ��� �ൿ ��
	window.setFramerateLimit(30);

	srand(time(NULL));

	RectangleShape snake;
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
			// �������� x�� ������ �� â�� �ݾ�������
			if (e.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			snake_y--;
			snake.move(0, -block);
		}

		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			snake_y++;
			snake.move(0, block);
		}

		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			snake_x--;
			snake.move(-block, 0);
		}

		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			snake_x++;
			snake.move(block, 0);
		}

		// update

		// ���� ����� �Ծ��� ��
		if (snake.getGlobalBounds().intersects(apple.getGlobalBounds()))
		{
			apple_x = rand() % w;
			apple_y = rand() % h;
			apple.setPosition(apple_x * block, apple_y * block);
		}

		// render
		window.clear();
		
		window.draw(snake);
		
		window.draw(apple);	// ��� ����� ��ĥ��� ����� ���� ����
		
		window.display();
	}

	return 0;
}