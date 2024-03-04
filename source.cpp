#include <Windows.h>
#include <iostream>
#include <random>
#include <list>

using std::cout;
using std::endl;

class Window {
public:
	int x() {
		CONSOLE_SCREEN_BUFFER_INFO i;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &i);

		return (i.srWindow.Right - i.srWindow.Left + 1);
	};

	int y()
	{
		CONSOLE_SCREEN_BUFFER_INFO i;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &i);

		return (i.srWindow.Bottom - i.srWindow.Top + 1);
	}

	void move(const int& x, const int& y) {
		cout << "\033[" << y << ";" << x << "H";
	};

	void print(const std::string& text)
	{
		cout << text;
	}

	int random(const int& min, const int& max)
	{
		return rand() % (max + 1 - min) + min;
	}

	void clear()
	{
		print("\033c\n");
		move(0, 0);
	}
};

class Point {
public:
	int x;
	int y;
	Point(int x, int y) : x(x), y(y) { };

};

int main() { 
	Window console{};
	std::list<Point> stars{};


	while (1)
	{
		int desiredstars = console.x() * console.y() / 2;
		if (stars.size() < desiredstars)
			stars.push_back(Point{ console.random(2, console.x() - 2), 0 });

		for (Point& star : stars)
		{
			star.y++;

			if (star.y > 0)
			{
				console.move(star.x, star.y);
				console.print("x");
			}

			if (star.y > console.y())
			{
				star.x = console.random(2, console.x() - 2);
				star.y = -console.random(0, 5);
			}
		}
		Sleep(1000 / 60);

		console.clear();
	}
}
