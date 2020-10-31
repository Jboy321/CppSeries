#include <iostream>
#include <string>
#include <array>
#include <stdlib.h>
#include <memory>
#include <vector>

struct Vector2
{
	float x, y;

	Vector2(float x, float y)
		: x(x), y(y) {}

	Vector2 Add(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator+(const Vector2& other) const
	{
		return Add(other);
	}

	Vector2 Mutiply(const Vector2& other) const
	{
		return Vector2(x * other.x, y * other.y);
	}

	Vector2 operator*(const Vector2& other) const
	{
		return Mutiply(other);
	}

	bool operator==(const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2& other) const
	{
		return !(*this == other);
	}
};

std::ostream& operator<<(std::ostream& stream, const Vector2& other)
{
	stream << other.x << "," << other.y;
	return stream;
}

void Example23()   ///Operator Overloading
{
	Vector2 position(4.0f, 4.0f);
	Vector2 speed(0.5f, 1.5f);
	Vector2 powerup(1.1f, 1.1f);

	Vector2 result1 = position.Add(speed.Mutiply(powerup));///Java里就只能这样写，但C++可以运算符重载
	Vector2 result2 = position + speed * powerup;

	std::cout << result2 << std::endl;

	if (result1 == result2)
	{

	}

}


class Entity7     ///This Keyword
{
public:
	int x, y;

	Entity7(int x, int y)
	{

		this->x = x;  ///如果写成x = x，是给形参赋值，而不是给成员变量赋值
		this->y = y;

	}

	int Get() const
	{
		const Entity7* et1 = this;
		return x, y;
	}
};

class Entity8
{
public:
	Entity8()
	{
		std::cout << "Created Entity8" << std::endl;
	}

	~Entity8()
	{
		std::cout << "Destroyed Entity8" << std::endl;
	}

	void Printptr() {}
};

int* CreatArray(int* array)
{
	return array;
}

class ScopedPtr
{
private:
	Entity8* m_Ptr;
public:
	ScopedPtr(Entity8* ptr)
		: m_Ptr(ptr)
	{

	}

	~ScopedPtr()
	{
		delete m_Ptr;
	}
};

void Example24()   ///Stack Scope Lifetime
{
	{
		/*Entity8* escop = new Entity8();*/
		ScopedPtr esptr = new Entity8();  ///通过这种方法来实现heap上创建的变量的自动删除；很巧妙
		//Unique_Ptr:Smater Pointer中的一种

	}

	int array[50];
	CreatArray(array);

}

void Example25()
{
	std::shared_ptr<Entity8> sp0;
	{
		std::unique_ptr<Entity8> eu = std::make_unique<Entity8>();///(new Entity8())
		eu->Printptr();
		//std::unique_ptr<Entity8> eu1 = eu; //unique pointer不能copy，因为假设有两个unique poniter的话
		/////一个scope结束后delete和free memory，另外一个就指向free memory，所以说禁止copy。

		std::shared_ptr<Entity8> es = std::make_shared<Entity8>();  //control block
		sp0 = es;

		std::weak_ptr<Entity8> wp = es;///weak_ptr和share_ptr的区别，首先我们知道unique_pt
		//是禁止copy的，而share_ptr是可以copy的，share_ptr会创建一个reference count,
		//当计数为0的时候就会delete。而weak_ptr相当于不带reference count的share_ptr.

	}
}

class String
{
private:
	char* m_Buffer;
	unsigned int m_Size;
public:
	String(const char* string)
	{
		m_Size = strlen(string);
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, string, m_Size);
		m_Buffer[m_Size] = 0;
		//m_Buffer = string;
	}

	///Copy Constructor和构造函数等类似，不写也默认自带，只是默认自带的是浅拷贝模式
	String(const String& other)
		: m_Size(other.m_Size)
	{
		/*memcpy(this, &other, sizeof(String));*/
		std::cout << "Copy" << std::endl;
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
		/*_ASSERTE(_CrtCheckMemory());*/   ///这一行代码可以用来检查内存泄露
	}

	~String()
	{
		std::cout << "Destroyed!" << std::endl;
		delete[] m_Buffer;
	}

	char& operator[](unsigned int index)
	{
		return m_Buffer[index];
	}

	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.m_Buffer;
	return stream;
}

void Example26()   ///Copying and Copy Constructor
{
	String string("Zhoushenshen");
	String second = string;

	second[2] = 'a';

	std::cout << string << std::endl;
	std::cout << second << std::endl;
}

class Entity9
{
public:
	int x;

public:
	Entity9(int gx)
		: x(gx)
	{

	}

	~Entity9()
	{

	}

	void Print() const { std::cout << "Hello!" << std::endl; }
};

class ScopedPtr2
{
private:
	Entity9* m_Obj;
public:
	ScopedPtr2(Entity9* entity)
		: m_Obj(entity)
	{

	}

	~ScopedPtr2()
	{
		delete m_Obj;
	}

	Entity9* GetObject() const { return m_Obj; }

	const Entity9* operator->() const
	{
		return m_Obj;
	}
};

struct Vector3
{
	float x, y, z;
};

void Example27()   ///Arrow Operator
{
	Entity9 e(2);
	e.Print();

	Entity9* ptr = &e;
	(*ptr).Print();

	ptr->Print();
	ptr->x;

	const ScopedPtr2 spentity = new Entity9(2);
	spentity.GetObject()->Print();

	spentity->Print();

	int offset1 = (int)&((Vector3*)nullptr)->x;
	int offset2 = (int)&((Vector3*)nullptr)->y;
	int offset3 = (int)&((Vector3*)nullptr)->z;
	std::cout << offset1 << "," << offset2 << "," << offset3 << std::endl;

}

struct Vertex
{
	float x, y, z;

	Vertex(float x, float y, float z)
		: x(x), y(y), z(z)
	{

	}

	Vertex(const Vertex& other)
		: x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Copied" << std::endl;
	}
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex)
{
	stream << vertex.x << "," << vertex.y << "," << vertex.z;
	return stream;
}

void Example28()   ///Dynamic Array/Vector///Optimization the usage of stdvector
{
	//Dynamic Array
	//std::vector<Vertex> vertices;
	//vertices.push_back({ 1,2,3 });
	//vertices.push_back({ 4,5,6 });

	//for (int i = 0; i < vertices.size(); i++)
	//	std::cout << vertices[i] << std::endl;

	//for (Vertex v : vertices)
	//	std::cout << v << std::endl;

	///*vertices.clear();*/   //resize to 0

	//vertices.erase(vertices.begin() + 1);

	//for (Vertex& v : vertices)
	//	std::cout << v << std::endl;

	///Optimization the usage of stdvector

	std::vector<Vertex> vertices;
	vertices.reserve(3);   ///分配能够储存3个Vertex的memory,没有这个分配的下面会copy6次。。。。
	//vertices.push_back(Vertex(1, 2, 3));
	vertices.emplace_back(1, 2, 3);//这样写就直接在vector里初始化一个Vertex，没有从main到vector的copy过程
	//vertices.push_back(Vertex(4, 5, 6));
	vertices.emplace_back(4, 5, 6);
	//vertices.push_back(Vertex(7, 8, 9));
	vertices.emplace_back(4, 5, 6);


}