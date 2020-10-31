#include <iostream>
#include <memory>
#include <chrono>
#include <array>

//Pre-compiled Header
//#include "pch.h"

struct Entity39
{
	int x, y;

	int* GetPositons()
	{
		return &x;
	}
};

void Example39()    ////Type Punning
{
	int a = 50;
	char& value = *(char*)&a;   ///直接用value=a和这种对比，为什么打印的结果不是50，深入理解
	std::cout << value << std::endl;

	Entity39 e = { 5,8 };
	int* positon = (int*)&e;
	std::cout << positon[0] << ", " << positon[1] << std::endl;
	int y = *(int*)((char*)&e + 4);
	std::cout << y << std::endl;

	int* positon1 = e.GetPositons();
	std::cout << positon1[0] << ", " << positon1[1] << std::endl;
}

struct Vector402
{
	float x, y;
};

struct  Vector404
{
	/*float x, y, z, w;

	Vector402& GetA()
	{
		return *(Vector402*)&x;
	}*/

	union
	{
		struct
		{
			float x, y, z, w;
		};

		struct
		{
			Vector402 a, b;
		};
	};
};

void PrintVector402(const Vector402& vector)
{
	std::cout << vector.x << ", " << vector.y << std::endl;
}

void Example40()   ////Unions
{
	Vector404 vector = { 1.0f,2.0f,3.0f,4.0f };
	PrintVector402(vector.a);
	PrintVector402(vector.b);
	std::cout << "---------------------------" << std::endl;
	vector.z = 500.0f;
	PrintVector402(vector.a);
	PrintVector402(vector.b);

}

class Base
{
public:
	Base() { std::cout << "Base Constructer\n"; }
	virtual ~Base() { std::cout << "Base Destructor\n"; }
};

class Derived : public Base
{
public:
	Derived() { m_array = new int[5]; std::cout << "Derived Constructer\n"; }
	~Derived() { delete m_array; std::cout << "Derived Destructor\n"; }

private:
	int* m_array;
};

void Example41()    ////Virtual Destructor
{
	Base* base = new Base;
	delete base;
	std::cout << "------------------------------\n";

	Derived* derived = new Derived;
	delete derived;
	std::cout << "------------------------------\n";

	Base* poly = new Derived;
	delete poly;   ///如果不在Base中使用virtual destructor 那么delete时只会调用base的destructor，不会调用derived的destructor
}

class AnotherClass : public Base
{
public:
	AnotherClass() {}
	~AnotherClass() {}
};

void Example42()   ////Casting in C/C++
{
	double value = 5.25;
	/*double a = value + 5.3;*/
	/*double a = (int)(value + 5.3);*/
	double a = (int)value + 5.3;
	std::cout << a << std::endl;

	double s = static_cast<int>(value) + 5.3;
	std::cout << s << std::endl;

	Derived* derive = new Derived();
	Base* base = derive;
	/*AnotherClass* ac = static_cast<AnotherClass*>(base);*/
	/*AnotherClass* ac = dynamic_cast<AnotherClass*>(base);*/
	Derived* ac = dynamic_cast<Derived*>(base);
	if (ac)
	{
		std::cout << "Successfully Conversion" << std::endl;
	}
	else
	{
		std::cout << "Failed to Conversion!" << std::endl;
	}

}

class Entity43
{
public:
	virtual void PrintName() {}
};

class Player43 : public Entity43
{
public:

};

class Enemy43 : public Entity43
{
public:

};

void Example43()   ////Dynamic cast
{
	Player43* player = new Player43();
	Entity43* actuallyEnemy = new Enemy43();

	Entity43* actuallyPlayer = player;

	Player43* p0 = dynamic_cast<Player43*>(actuallyEnemy);
	if (p0)
	{
		std::cout << "P0 Type conversion successful" << "\n";
	}
	else
	{
		std::cout << "P0 Type conversion failed" << "\n";
	}

	Player43* p1 = dynamic_cast<Player43*>(actuallyPlayer);
	if (p1)
	{
		std::cout << "P1 Type conversion successful" << "\n";
	}
	else
	{
		std::cout << "P1 Type conversion failed" << "\n";
	}
}

class Timer44
{
public:
	Timer44()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer44()
	{
		Stop();
	}

	void Stop()
	{
		auto EndTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimepoint).time_since_epoch();

		auto duration = end - start;
		std::chrono::duration<float> duration1 = EndTimepoint - m_StartTimepoint;
		double ms = duration.count() * 0.001;

		std::cout << duration.count() << "us (" << ms << "ms )\n";
		std::cout << duration1.count() << "s\n";
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;

};

void Example44()  ////Benchmarking in C++
{
	int value = 0;
	{
		Timer44 timer;
		for (int i = 0; i < 100; i++)
			value += 2;
	}

	std::cout << value << std::endl;

	struct Vector2
	{
		float x, y;
	};

	std::cout << "Make Shared\n";
	{
		std::array<std::shared_ptr<Vector2>, 100> sharedPts;
		Timer44 timer;
		for (unsigned int i = 0; i < sharedPts.size(); i++)
			sharedPts[i] = std::make_shared<Vector2>();
	}

	std::cout << "New Shared\n";
	{
		std::array<std::shared_ptr<Vector2>, 100> sharedPts;
		Timer44 timer;
		for (unsigned int i = 0; i < sharedPts.size(); i++)
			sharedPts[i] = std::shared_ptr<Vector2>(new Vector2());
	}

	std::cout << "Make Unique\n";
	{
		std::array<std::unique_ptr<Vector2>, 100> sharedPts;
		Timer44 timer;
		for (unsigned int i = 0; i < sharedPts.size(); i++)
			sharedPts[i] = std::make_unique<Vector2>();
	}

	__debugbreak();   //MSVC自带的内在函数，可以用代码的方法插入一个断点

}
