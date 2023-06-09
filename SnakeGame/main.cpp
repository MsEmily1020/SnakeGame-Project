#include <SFML/Graphics.hpp>
#include <stdlib.h>			// srand(), read()
#include <time.h>			// time()

using namespace sf;

int main() {
	RenderWindow  window(VideoMode(640, 480), "Snake Game");
	// 1�ʿ� 60���� �۾��� �̷�� ������ frame ����
	// ��ǻ�� ����� �޶� �Ȱ��� �ൿ ��
	window.setFramerateLimit(60);

	srand(time(NULL));

	int block = 40;

	RectangleShape snake;
	snake.setPosition(200, 300);
	snake.setSize(Vector2f(block, block));
	snake.setFillColor(Color::Green);

	RectangleShape apple;
	apple.setPosition(rand() % 640 - block, rand() % 480 - block);
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
			snake.move(0, -5);
		
		else if (Keyboard::isKeyPressed(Keyboard::Down))
			snake.move(0, 5);
		
		else if (Keyboard::isKeyPressed(Keyboard::Left))
			snake.move(-5, 0);
		
		else if (Keyboard::isKeyPressed(Keyboard::Right))
			snake.move(5, 0);
		
		// update
		
		// ���� ����� �Ծ��� ��
		if (snake.getGlobalBounds().intersects(apple.getGlobalBounds()))
		{
			apple.setPosition(rand() % 640 - block, rand() % 480 - block);
		}

		// render
		window.clear();
		
		window.draw(snake);
		
		window.draw(apple);	// ��� ����� ��ĥ��� ����� ���� ����
		
		window.display();
	}

	return 0;
}