#include <iostream>
#include <string>
#include <array>
#include <stdlib.h>

class Entity
{
public:

	static const int size = 5;
	int* array1 = new int[size];

	std::array<int, 5> array2; ///C11标准

	Entity()
	{
		for (int i = 0; i < size; i++)
		{
			array1[i] = 2;
		}

		for (unsigned int j = 0; j < array2.size(); j++)
		{
			array2[j] = 2;
		}
	}
};

void Example13()    ////Array
{
	int example[5];  //create on the stack

	for (int i = 0; i < 5; i++)
	{
		example[i] = 2;
	}

	int* ptr = example;
	example[2] = 5;
	*(int*)((char*)ptr + 8) = 6;
	std::cout << example[2] << std::endl;

	int* another = new int[5]; //create on the heap
	delete[] another;

	Entity e;
}

void PrintString(const std::string& string)
{
	std::cout << string << std::endl;
}

void Example14()   ///String
{
	const char* name = "ZhouShenShen";  ///按照C标准方式定义string
	char name2[5] = { 'Z', 'h', 'o', 'u', 0 }; // 空字符代表结束，对应ASCII码0，也可以写成'\0'
	std::cout << name << std::endl;
	std::cout << name2 << std::endl;

	std::string name3 = std::string("XuWei") + "Love"; ///C++标准定义string
	name3 += "ZhouShenShen";
	bool contains = name3.find("oh") != std::string::npos;  ///npos是一个常数，用来表示不存在的位置
	std::cout << name3 << std::endl;
	std::cout << contains << std::endl;

	PrintString("zhoushenshen");
}

void Example15()    //String Literal
{
	const char name[8] = "Zhou\0ss";
	std::cout << strlen(name) << std::endl;
	const wchar_t* name2 = L"zhoushenshen";
	const char16_t* name3 = u"zhoushenshen";  //utf-16,2bytes,char是utf-8，1byte
	const char32_t* name4 = U"zhoushenshen";  //utf-32,4bytes

	using namespace std::string_literals;
	std::string name0 = "zhoushenshen"s + "Hello";
	std::wstring name01 = L"zhoushenshen"s + L"Hello";
	std::u16string name02 = u"zhoushenshen"s + u"Hello";
	std::u32string name03 = U"zhoushenshen"s + U"Hello";

	const char* example = R"(line1
line2
line3)";

	const char* ex = "line1\n"
		"line2\n"
		"line3\n";

	std::cout << example << std::endl;
	std::cout << ex << std::endl;
}

class Entity1
{
private:
	int m_X, m_Y;
	mutable int var;
public:
	int GetX() const
	{
		var = 2;
		return m_X;
	}
	//const放在后面表示这个method是只读不会改变class

};

void Example16()    ///Const
{
	const int MAX_AGE = 90;
	int* a = new int; //const int*/int const */int* const


	*a = 2; //注意上一行添加上const的位置，结果不一样
	a = (int*)&MAX_AGE; //用这个来说明可以强制改变const，但那一般不会改变const，const是promise

	std::cout << *a << std::endl;

	Entity1 e1;
}

void PrintEntity(const Entity1& ee)
{
	std::cout << ee.GetX() << std::endl;
}

class Entity2
{
private:
	std::string m_Name;
	mutable int m_DebugCount = 0;
public:
	const std::string& GetName() const
	{
		m_DebugCount++;
		return m_Name;
	}

	int GetDebugCount() const
	{
		return m_DebugCount;
	}
};

void Example17()    //Mutable
{
	const Entity2 e;
	e.GetName();
	e.GetName();
	e.GetName();

	std::cout << e.GetDebugCount() << std::endl;

	int x = 8;
	auto f = [=]() mutable
	{
		x++;
		std::cout << x << std::endl;
	};

	f();
}

class Entity3
{
private:
	std::string m_Name;
public:
	Entity3()
	{
		m_Name = "Unkown";
	}

	Entity3(const std::string& name)
	{
		m_Name = name;
	}

	const std::string& Getname() const { return m_Name; }
};

class Entity5
{
private:
	std::string m_Name;
	int m_Score;
public:
	Entity5()
		: m_Name("Unkown"), m_Score(0)
	{
	}

	Entity5(const std::string& name, int score)
		: m_Name(name), m_Score(score)   ///这里的顺序必须对应前面的成员顺序
	{
	}

	const std::string& Getname() const { return m_Name; }
	int Getscore() const { return m_Score; }
};
///第二种方式的好处就是只用初始化一次，第一种方式会初始化两次，
///因为默认的constructor先进行初始化再调用自己写的constructor初始化第二次

void Example18()   ///Member Initializer List
{
	const Entity3 e0;
	std::cout << e0.Getname() << std::endl;

	const Entity3 e1("Zhoushenshen");
	std::cout << e1.Getname() << std::endl;

	const Entity5 e2;
	std::cout << e2.Getname() << std::endl;
	std::cout << e2.Getscore() << std::endl;

	const Entity5 e3("Zhoushenshen", 88);
	std::cout << e3.Getname() << std::endl;
	std::cout << e3.Getscore() << std::endl;


}

static int s_Level = 1;
static int s_Speed = 2;

void Example19()   ///Ternary Operator(Conditional Assignment)
{
	if (s_Level > 5)
		s_Speed = 10;
	else
		s_Speed = 5;

	s_Speed = s_Level > 5 ? 10 : 5;
	std::cout << s_Speed << std::endl;
	s_Level = 8;
	s_Speed = s_Level > 5 ? s_Level > 10 ? 15 : 10 : 5;
	std::cout << s_Speed << std::endl;
	s_Speed = s_Level > 5 && s_Level < 100 ? s_Level > 10 ? 15 : 10 : 5;
	std::cout << s_Speed << std::endl;
	///&&称为短路运算符，与&的区别是，第一次判断无论真假&都会判断第二次，
	///而&&只有当第一次为真才会进行第二次判断

	std::string rank = s_Level > 10 ? "Master" : "Beginner";
	std::cout << rank << std::endl;
}

void Example20()  ///How to instantiate objects, create on stack or heap
{
	Entity5* e;
	{
		Entity5 entity("Zhoushenshen", 65);
		e = &entity;
		std::cout << entity.Getname() << std::endl;

		Entity5* ep = new Entity5("zhoushenshen", 65);
		delete ep;

	}


}

void Example21()    ///New keyword
{
	int a = 2;
	int* b = new int;

	Entity5* ne0 = new Entity5[50];
	Entity5* ne1 = new Entity5();//这样写不仅allocate memory，同时也进行初始化

	delete b;
	delete[] ne0;   //array相应的delete也得带[]
	delete ne1;

}

class Entity6
{
private:
	std::string m_Name;
	int m_Age;
public:
	/*explicit*/ Entity6(const std::string& name)
		: m_Name(name), m_Age(-1) {}
	/*explicit*/ Entity6(int age)
		: m_Name("Unkown"), m_Age(age) {}
};

void PrintEntity6(const Entity6& ep6)
{
	///Print
}

void Example22()    ///Implicit Conversion Explicit Keyword
{
	PrintEntity6(std::string("Zhoushenshen"));
	PrintEntity6(22);

	Entity6 a = std::string("Zhoushenshen");  ///Entity6 a(std::string("Zhoushenshen"))
	Entity6 b = 22;  ///Entity6 b(22)

}