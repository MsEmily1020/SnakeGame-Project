#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
	RenderWindow  window(VideoMode(640, 480), "Snake Game");		RenderWindow  window(VideoMode(640, 480), "Snake Game");


	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			// �������� x�� ������ �� â�� �ݾ�������
			if (e.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}
	return 0;
}