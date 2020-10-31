#include <iostream>

#include <string>
#include <tuple>

#include <fstream>
#include <optional>
#include <vector>

#include <variant>

#include <any>

#include <cmath>
#include <chrono>
#include <algorithm>
#include <thread>

extern void Example10();

std::tuple<std::string, int> CreatePerson()
{
	return { "Zhoushenshen", 30 };
}

void Example45()    ////Structured Bindings
{
	auto person = CreatePerson();
	std::string& name1 = std::get<0>(person);
	int age1 = std::get<1>(person);
	std::cout << name1 << ", " << age1 << std::endl;

	std::string name2;
	int age2;
	std::tie(name2, age2) = CreatePerson();
	std::cout << name2 << ", " << age2 << std::endl;   //这两种写法都没有直接创建1个struct来做函数返回值方便

	auto [name3, age3] = CreatePerson();
	std::cout << name3 << ", " << age3 << std::endl;  //必须是C++17以上才支持Structured Bindings,C++11和14都不支持

}

std::optional<std::vector<std::string>> ReadFileAsString(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::vector<std::string> lines;
	if (stream)
	{
		std::string line;
		while (std::getline(stream, line))
		{
			if (line.empty())
				continue; ///跳过空行

			lines.push_back(line);
		}

		stream.close();
		return lines;
	}

	return {};
}

void Example46()  ////How to deal with Optional Data in C++
{
	std::optional < std::vector < std::string >> data = ReadFileAsString("C:/git/readme.txt");

	if (data.has_value())   ///也可以直接用if(data)
	{
		std::cout << "File read successfully\n";
		for (std::string& str : data.value())
			std::cout << str << std::endl;
	}
	else
	{
		std::cout << "File could not be opened\n";
	}

	std::vector<std::string> np;
	np.push_back("Not present");
	auto value = data.value_or(np);
	for (std::string& str : value)
		std::cout << str << std::endl;

	std::optional<int> count;
	int c = count.value_or(100);
	std::cout << c << std::endl;
}

enum class ErrorCode
{
	None = 0, NotFound = 1, NoAccess = 3
};

std::variant<std::string, ErrorCode> ReadFileAsString()
{
	return {};
}

void Example47()   ////std::variant   本质是Union
{
	std::variant<std::string, int> data;

	std::cout << sizeof(std::string) << "\n";
	std::cout << sizeof(int) << "\n";
	std::cout << sizeof(data) << "\n";

	data = "Peter";
	std::cout << std::get<std::string>(data) << "\n";
	std::cout << data.index() << "\n";

	data = 2;
	std::cout << std::get<int>(data) << "\n";
	std::cout << data.index() << "\n";

	if (auto value = std::get_if<std::string>(&data))
	{
		std::string& v1 = *value;
	}
	else
	{
		
	}

}

void Example48()   ////std::any
{
	std::any data;
	data = 2;
	data = "Peter";
	data = std::string("Peter");
	std::string string =  std::any_cast<std::string>(data);
	//small_storage时any和variant类似都是基于Union做的处理，但对于Big_storage时any使用动态分配内存，不是很好，不推荐使用any
}

struct ProfileResult
{
	std::string Name;
	long long Start, End;
	uint32_t ThreadID;
};

struct  InstrumentationSession
{
	std::string Name;

};

class Instrumentor
{
private:
	InstrumentationSession* m_CurrentSession;
	std::ofstream m_OutputStream;
	int m_ProfileCount;

public:
	Instrumentor()
		: m_CurrentSession(nullptr), m_ProfileCount(0)
	{

	}

	void BeginSession(const std::string& name, const std::string& filepath = "results.json")
	{
		m_OutputStream.open(filepath);
		WriteHeader();
		m_CurrentSession = new InstrumentationSession{ name };
	}

	void EndSession()
	{
		WriteFooter();
		m_OutputStream.close();
		delete m_CurrentSession;
		m_CurrentSession = nullptr;
		m_ProfileCount = 0;

	}

	void WriteProfile(const ProfileResult& result)
	{
		if (m_ProfileCount++ > 0)
			m_OutputStream << ",";

		std::string name = result.Name;
		std::replace(name.begin(), name.end(), '"', '\'');

		m_OutputStream << "{";
		m_OutputStream << "\"cat\":\"function\",";
		m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
		m_OutputStream << "\"name\":\"" << name << "\",";
		m_OutputStream << "\"ph\":\"X\",";
		m_OutputStream << "\"pid\":0,";
		m_OutputStream << "\"tid\":" << result.ThreadID << ",";
		m_OutputStream << "\"ts\":" << result.Start;
		m_OutputStream << "}";

		m_OutputStream.flush();

	}

	void WriteHeader()
	{
		m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
		m_OutputStream.flush();
	}

	void WriteFooter()
	{
		m_OutputStream << "]}";
		m_OutputStream.flush();
	}

	static Instrumentor& Get()
	{
		static Instrumentor* instance = new Instrumentor();
		return *instance;
	}

};

class InstrumentationTimer
{
private:
	std::string m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint; //high_resolution_clock是steady_clock的高精度版
	bool m_Stopped;

public:
	InstrumentationTimer(std::string name)
		: m_Name(name), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~InstrumentationTimer()
	{
		if (!m_Stopped)
			Stopped();
	}

	void Stopped()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		std::cout << m_Name << ": " << (end - start) << "us\n";

		uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
		Instrumentor::Get().WriteProfile({ m_Name, start, end ,threadID});

		m_Stopped = true;
	}

};

#define PROFILING 1
#if PROFILING
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name)
//#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define PROFILE_SCOPE(name)
#endif

void Function1()
{
	PROFILE_FUNCTION();
	
	for (int i = 0; i < 1000; i++)
		/*std::cout << "Hello World #" << i << std::endl;*/
		i++;
}

void Function2()
{
	PROFILE_FUNCTION();

	for (int i = 0; i < 1000; i++)
		/*std::cout << "Hello World #" << sqrt(i) << std::endl;*/
		sqrt(i);
}

void RunBenchmarks()
{
	PROFILE_FUNCTION();

	std::cout << "RunBenchmarks...\n";
	Function1();
	Function2();

}

void Example49()
{
	Instrumentor::Get().BeginSession("Profile");
	RunBenchmarks();
	Instrumentor::Get().EndSession();
}

int main()
{		
	Example10();

	std::cin.get();

}