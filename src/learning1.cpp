#include <iostream>
#include <string>
#include "Log.h"

//#define LogInt(x) std::cout << x << std::endl;
//使用常量表达式constexpr代替宏macro，好处是没有额外的开销
template<typename T>
constexpr void LogInt(T x)
{
	std::cout << x << std::endl;
}

void Example1()   ///Loop & Control Flow
{
	int i = 0;
	bool condition = true;
	for (; condition;)
	{
		i++;
		if (i % 2 == 0)
			continue;
		Log("Hello World!");
		std::cout << i << std::endl;
		if (!(i < 4))
			condition = false;
	}

	for (int a = 0; a < 5; a++)
	{
		if ((a + 1) % 2 == 0)
			break;
		Log("Hello!");
		std::cout << a << std::endl;
	}

	Log("===============");

	int j = 0;
	while (j < 5)
	{
		Log("Hello World!");
		j++;
	}

	do {
		Log("Happy");
	} while (false);
}

void Example2()  ///Pointer
{
	int var = 26;
	int* ptr = &var;
	*ptr = 10;
	std::cout << var << std::endl;

	char* buffer = new char[8];
	memset(buffer, 'c', 8);
	buffer[7] = 0;
	std::cout << buffer << std::endl;
	char** ptrb = &buffer;

	delete[] buffer;

}

void Example3()    //Reference
{
	int a = 5;
	Increment1(&a);
	Increment2(a);
	int& ref = a;

	LogInt(ref);

}

class Player
{
public:
	int x = 2;
	int y = 3;
	int speed = 5;

	void Move(int xa, int ya)
	{
		x += xa * speed;
		y += ya * speed;
	}
};

void Example4()   ///Class
{
	Player player;
	player.Move(1, -1);
}

enum MyEnum : unsigned char/* 默认是int类型，不能改成float，因为enum就是一个integer*/
{
	A = 5, B, C
};

class MyLog
{
public:
	enum class Level
	{
		LevelError = 0, LevelWarning = 1, LevelInfo = 3
	};

private:
	Level m_LogLevel = Level::LevelInfo;

public:
	void SetLevel(Level level)
	{
		m_LogLevel = level;
	}

	void Error(const char* message)
	{
		if (m_LogLevel >= Level::LevelError)
			std::cout << "[Error]: " << message << std::endl;
	}

	void Warn(const char* message)
	{
		if (m_LogLevel >= Level::LevelWarning)
			std::cout << "[warning]: " << message << std::endl;
	}

	void Info(const char* message)
	{
		if (m_LogLevel >= Level::LevelInfo)
			std::cout << "[Info]: " << message << std::endl;
	}
};

void Example5()   ///Enum
{
	MyLog log;
	log.SetLevel(MyLog::Level::LevelInfo);
	log.Warn("Hello!");
	log.Error("Hello!");
	log.Info("Hello!");
}

struct Entity
{
	static int x, y;

	void Print()
	{
		std::cout << x << ", " << y << std::endl;
	}
};

int Entity::x = 0;
int Entity::y = 0;

void Example6()   ///Static For Class&Struct
{
	Entity e1;
	Entity e2;
	e1.x = 2;
	e2.x = 6;
	std::cout << e1.x << std::endl;
}

//静态成员函数可以访问静态成员函数或者变量，但不能访问非静态成员函数或变量，非静态函数可以访问静态成员变量或函数
class Singleton1
{
private:
	static Singleton1* s_Instance;
public:
	static Singleton1& get() { return *s_Instance; }

	void Hello() { std::cout << "Hello!" << std::endl; }
};

Singleton1* Singleton1::s_Instance = nullptr;

class Singleton2
{
public:
	static Singleton2& get()
	{
		static Singleton2 instance;
		return instance;
	}

	void Hello() { std::cout << "Hello!" << std::endl; }
};

void Example7()   ///Static for Class&Struct
{
	Singleton1::get().Hello();
	Singleton2::get().Hello();
}

void Function()
{
	static int i = 0;
	i++;
	std::cout << i << std::endl;
}
void Example8()   ///Local Static
{
	Function();
	Function();
	Function();
 }

class Entity2
{
public:
	float x, y;

	Entity2(float X, float Y)
	{
		x = X;
		y = Y;
		std::cout << "Created Entity2!" << std::endl;
	}

	~Entity2()
	{
		std::cout << "Destroyed Entity2!" << std::endl;
	}

	void Print()
	{
		std::cout << x << ", " << y << std::endl;
	}
};

class Deentity
{
public:
	/*Deentity() = delete;*/

private:
	/*Deentity();*/
};

void Example9()   ///Constuctor&Destructor
{
	Entity2 e(0.0f, 2.3f);
	e.Print();
	Deentity de; //可以通过Deentity类中的方式来让无法创建一个类的一个实例
}

class Log2
{
public:
	static void Write()
	{
		std::cout << "Just do it!" << std::endl;
	}
};

void Example10()  ///Static
{
	Log2::Write();
	Log2 love;
}

class Entity3
{
public:
	float X, Y;

	void Move(float xa, float ya)
	{
		X += xa;
		Y += ya;
	}
};

class Player3 : public Entity3
{
public:
	const char* Name;

	void Print()
	{
		std::cout << Name << std::endl;
	}
};

void Example11()   ///Inheritance
{
	Player3 playera;
	playera.Name = "zhoushenshen";
	playera.Print();
	playera.Move(2.0, 3.0);
	std::cout << playera.X << ", " << playera.Y << std::endl;
}

class  Printable
{
public:
	virtual std::string GetClassName() = 0;
};

class Entity4 : public Printable
{
public:
	virtual std::string GetName() { return "Entity"; }
	std::string GetClassName() override { return "Entity"; }
};

class Player4 : public Entity4
{
private:
	std::string m_Name;
public:
	Player4(const std::string& name)
		: m_Name(name) {}
	std::string GetName() override { return m_Name; }
	std::string GetClassName() override { return "Player"; }
};

void PrintName(Entity4* entity)
{
	std::cout << entity->GetName() << std::endl;
}

class AA : public Printable
{
public:
	std::string GetClassName() override { return "AA"; }
};

void Print(Printable* obj)
{
	std::cout << obj->GetClassName() << std::endl;
}

void Example12()    ///Virtual Function & Pure Virtual Function(interface)
{
	Entity4* e = new Entity4();
	std::cout << e->GetName() << std::endl;
	PrintName(e);

	Player4* p = new Player4("zhoushenshen");
	std::cout << p->GetName() << std::endl;
	PrintName(p);

	Print(e);
	Print(p);
	Print(new AA());
}
