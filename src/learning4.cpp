#include <iostream>
#include <GLFW/glfw3.h>
//extern "C" int glfwInit();

#include <string>
#include <vector>
#include <unordered_map>
#include <array>

#include <functional>

#include <thread>

#include <algorithm>

///Macros
//#if 0
#if PR_DEBUG == 1
#define Log(x) std::cout << x << std::endl
#elif defined(PR_RELEASE)
#define Log(x)
#endif
//#endif
///Macro中用\可以换行，不然都是同一行
#define MAIN int main()\
{\
	std::cin.get();\
}

void Example29()   /// Libraries(Static linking)&Dynamic Libraries
{
	int a = glfwInit();
	std::cout << a << std::endl;
}

template<typename T>
void Printtp(T value)
{
	std::cout << value << std::endl;
}

template<typename T, int N, int member>
class Array
{
private:
	T m_Array[N];
public:
	Array()
	{
		for (int i = 0; i < N; i++)
			m_Array[i] = member;
	}

	int GetSize() const { return N; }

};

void Example30()    ///Template,Compiling的时候Compiler根据后面传入的参数类型自动创建该参数类型的函数或Class等等
{
	Printtp<int>(5); ///Printtp(5),也可直接这样写，会自动分析类型
	Printtp<std::string>("Hello");
	Printtp<float>(5.5f);

	Array<int, 5, 1> array1;
	std::cout << array1.GetSize() << std::endl;

}

void Example31()    ///Macros
{
	Log("Hello!");
}

std::string Getname()
{
	return "Zhoushenshen";
}

class Device
{

};

class DeviceManager
{
private:
	std::unordered_map<std::string, std::vector<Device*>> m_Devices;
public:
	const std::unordered_map<std::string, std::vector<Device*>>& GetDevices() const
	{
		return m_Devices;
	}
};

void Example32()   ///Auto Keyword
{
	auto a = 5;  ///"xu",'a',5.5f

	auto name = Getname();   ///不建议这样使用，还是得明确类型，后面两个例子可以使用

	std::vector<std::string> strings;
	strings.push_back("Apple");
	strings.push_back("Orange");

	/*for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); it++)*/
	for (auto it = strings.begin(); it != strings.end(); it++)//代码更简洁
	{
		std::cout << *it << std::endl;
	}

	using DeviceMap = std::unordered_map<std::string, std::vector<Device*>>;
	/*typedef std::unordered_map<std::string, std::vector<Device*>> DeviceMap;*/

	DeviceManager dm;
	const DeviceMap& device1 = dm.GetDevices();
	const auto& device2 = dm.GetDevices();


}

void HelloWord(int a)
{
	std::cout << "Hello World! Value: " << a << std::endl;
}

void PrintValue(int value)
{
	std::cout << "Value: " << value << std::endl;
}

void ForEach(const std::vector<int>& values, void(*func)(int))
{
	for (int value : values)
		func(value);
}

void ForEach2(const std::vector<int>& values, const std::function<void(int)>& func)
{
	for (int value : values)
		func(value);
}

void Example33()   ///Function Pointer && Lambda
{
	auto function1 = HelloWord;///其实是&HelloWorld,隐式转换

	function1(3);

	typedef void(*HWF)(int);

	HWF function2 = HelloWord;
	function2(10);

	std::vector<int> values = { 1, 5, 4,3,2 };
	ForEach(values, PrintValue);

	std::vector<int> values2 = { 1,5,2,4,3 };

	int a = 2;

	auto lambda = [=](int value) mutable { a = 5;  std::cout << "Values2: " << a << std::endl; };

	ForEach2(values2, lambda);

	auto it = std::find_if(values2.begin(), values2.end(), [](int value) {return value > 3; });
	std::cout << *it << std::endl;

}

namespace apple {
	void print(const std::string& text)
	{
		std::cout << text << std::endl;
	}
	namespace function {
		void print_again()
		{
			std::cout << "Again!" << std::endl;
		}
	}
}

namespace orange {
	void print(const char* text)
	{
		std::string temp = text;
		std::reverse(temp.begin(), temp.end());
		std::cout << temp << std::endl;
	}
}

void Example34()   ////Namespace
{
	/*using namespace apple;
	using namespace orange;*/

	apple::print("Hello!");
	orange::print("Hello!");

	namespace a = apple;
	a::print("Hello!");

	using namespace apple::function;
	print_again();
}

static bool s_Finished = false;
void DoWork()
{
	using namespace std::literals::chrono_literals;
	std::cout << "Started thread id = " << std::this_thread::get_id() << std::endl;
	while (!s_Finished)
	{
		std::cout << "working...\n";
		std::this_thread::sleep_for(1s);
	}
}

void Example35()   ////Thread
{
	std::thread worker(DoWork);

	std::cin.get();
	s_Finished = true;


	worker.join();   ///等待worker线程任务结束或者退出才继续执行主线程

	std::cout << "Finished." << std::endl;
	std::cout << "Started thread id = " << std::this_thread::get_id() << std::endl;

}

struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = end - start;

		float ms = duration.count() * 1000.0f;
		std::cout << "Timer took " << ms << "ms " << std::endl;
	}
};

void Funtime()
{
	Timer timer;

	for (int i = 0; i < 100; i++)
	{
		std::cout << "Hello" << std::endl;
	}
}

void Example36()   ////Timing
{
	using namespace std::literals::chrono_literals;

	auto start = std::chrono::high_resolution_clock::now();

	std::this_thread::sleep_for(1s);

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> duration = end - start;

	std::cout << duration.count() << "s" << std::endl;

	Funtime();

}

void Example37()   ///Multidimensional Array
{
	int* array = new int[5];
	int** a2d = new int* [5];  //这两行实质上差不多，都只是做了一件事，分配了200Bytes的内存

	for (int i = 0; i < 5; i++)
	{
		a2d[i] = new int[5];
	}

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			a2d[x][y] = 2;
		}
	}

	for (int i = 0; i < 5; i++)
		delete[] a2d[i];
	delete[] a2d;

	int* array2 = new int[5 * 5];
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			array2[x + y * 5] = 2;
		}
	}
	delete[] array2;

	int*** a3d = new int** [5];
	for (int i = 0; i < 5; i++)
	{
		a3d[i] = new int* [5];
		for (int j = 0; j < 5; j++)
		{
			int** ptr = a3d[i];
			ptr[j] = new int[5];
			/*a3d[i][j] = new int[5];*/
		}
	}
	a3d[0][0][0] = 1;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			delete[] a3d[i][j];
		}
		delete[] a3d[i];
	}
	delete[] a3d;
}

void Example38()   ////Sort
{
	std::vector<int> values = { 3, 5, 1, 4, 2 };
	/*std::sort(values.begin(), values.end());*/
	/*std::sort(values.begin(), values.end(), std::greater<int>());*/
	std::sort(values.begin(), values.end(), [](int a, int b)
		{
			if (a == 1)
				return false;
			if (b == 1)
				return true;
			return a < b;
		});

	for (int& value : values)
		std::cout << value << std::endl;
}

//MAIN