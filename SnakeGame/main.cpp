#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	RenderWindow  window(VideoMode(640, 480), "Snake Game");
	// 1�ʿ� 60���� �۾��� �̷�� ������ frame ����
	// ��ǻ�� ����� �޶� �Ȱ��� �ൿ ��
	window.setFramerateLimit(60);

	RectangleShape snake;
	snake.setPosition(200, 300);
	snake.setSize(Vector2f(30, 30));
	snake.setFillColor(Color::Green);

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
		
		window.clear();
		
		window.draw(snake);
		
		window.display();
	}
	return 0;
}