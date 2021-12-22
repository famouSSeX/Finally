#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Sound.hpp>
#include <time.h>
#include "Menu.hpp"
#include <windows.h>
#include <iostream>
using namespace sf;

int main()
{
	//генератор случайных чисел
	srand(time(0));

	RenderWindow app(VideoMode(400, 400), "Sapper");

	sf::Image icon;
	if (!icon.loadFromFile("images/images.png"))
	{
		return false;
	}
	app.setIcon(32, 32, icon.getPixelsPtr());

	ko::Menu(app);
	if (ko::Menu(app) == false)
		return false;


	// удача
	SoundBuffer kolokol;//создаём буфер для звука
	kolokol.loadFromFile("audio/kolokol.ogg");//загружаем в него звук
	Sound lucky(kolokol);//создаем звук и загружаем в него звук из буфера
	// взрыв
	SoundBuffer boom;//создаём буфер для звука
	boom.loadFromFile("audio/boom.ogg");//загружаем в него звук
	Sound boom4(boom);//создаем звук и загружаем в него звук из буфера

	// ширина клетки
	int w = 32;
	int gridLogic[12][12];
	int gridView[12][12];

	// загрузка текстуры
	Texture Pole;
	Pole.loadFromFile("images/background.png");
	Sprite pole(Pole);

	Texture t;
	t.loadFromFile("images/tiles.jpg");
	Sprite s(t);

	//расстановка бомб
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			gridView[i][j] = 10;
			if (rand() % 7 == 0) 
				gridLogic[i][j] = 9;
			else gridLogic[i][j] = 0;
		}

	//цифры вокруг бомб
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			int n = 0;
			if (gridLogic[i][j] == 9) continue;
			if (gridLogic[i + 1][j] == 9) n++;
			if (gridLogic[i][j + 1] == 9) n++;
			if (gridLogic[i - 1][j] == 9) n++;
			if (gridLogic[i][j - 1] == 9) n++;
			if (gridLogic[i + 1][j + 1] == 9) n++;
			if (gridLogic[i - 1][j - 1] == 9) n++;
			if (gridLogic[i - 1][j + 1] == 9) n++;
			if (gridLogic[i + 1][j - 1] == 9) n++;
			gridLogic[i][j] = n;
		}

	while (app.isOpen())
	{
		//получаем координаты мышки
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / w;
		int y = pos.y / w;

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed)

				if (e.key.code == Mouse::Left)
					gridView[x][y] = gridLogic[x][y];

					if ((gridView[x][y] != 9) && (gridView[x][y] != 10) && (gridView[x][y] != 11) && (e.type == Event::MouseButtonPressed))
						lucky.play();

					if ((gridView[x][y] == 9) && (e.type == Event::MouseButtonPressed))
						boom4.play();

				else if ((e.key.code == Mouse::Right) && (gridView[x][y] != gridLogic[x][y]))
					gridView[x][y] = 11 ;
		}

		app.clear();
		pole.setTexture(Pole);
		app.draw(pole);
		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
			{
				if (gridView[x][y] == 9) gridView[i][j] = gridLogic[i][j];

				//вырезаем из спрайта нужный нам квадратик текстуры
				s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));

				//устанавливаем его заданную позицию…
				s.setPosition(i * w, j * w);

				app.draw(s);
			}
		app.display();
	}

	return 0;
}