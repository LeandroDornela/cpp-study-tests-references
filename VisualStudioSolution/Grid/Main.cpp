#include <iostream>
#include "Grid.h"
#include <chrono>
#include <thread>

#define START_BENCHMARK std::cout << "Starting benchmark." << std::endl; auto start = std::chrono::high_resolution_clock::now();
#define FINISH_BENCHMARK auto end = std::chrono::high_resolution_clock::now(); std::cout << "Done. Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
#define WAIT(t) std::this_thread::sleep_for(std::chrono::seconds(t));

struct MyStruct
{
	int _a = 0;
	int _b = 0;
	int _c = 0;

	MyStruct() {};
	MyStruct(int a, int b, int c) : _a(a), _b(b), _c(c) { /*std::cout << "-";*/ }
};

const MyStruct globalDefStruct = MyStruct(1, 1, 1);

void PrintCell(const int& value)
{
	std::cout << value;
}

void PrintCell(const MyStruct& value)
{
	std::cout << value._a;
}

inline void SumValues(MyStruct& value)
{
	value._a = value._a + value._b + value._c;
}

inline void SetDefault(MyStruct& value) // inline não faz effeito nessa situação.
{
	// value = MyStruct(1, 2, 3); // Vai criar uma nova struct a cada celula
	value = globalDefStruct;
}


void CreateAndSum(MyStruct defStruct)
{
	Grid<MyStruct> testGrid_struct(100, 100, defStruct);
	testGrid_struct.TEMP_ForEachCell(SumValues);

	//std::cout << testGrid_struct.GetCell(0, 0)->_a << std::endl;
}

inline void JustSum(Grid<MyStruct>& testGrid_struct)
{
	testGrid_struct.TEMP_ForEachCell(SumValues);
}

void CreateAndSet(Grid<MyStruct>& testGrid_struct)
{
	//testGrid_struct.TEST_ForEachSetDef(MyStruct(1, 2, 3));
	testGrid_struct.TEST_ForEachSetDef(globalDefStruct);
}

inline void CreateAndSetFuncPointer(Grid<MyStruct>& testGrid_struct)
{
	testGrid_struct.TEMP_ForEachCell(SetDefault);
}


int main()
{
	/*
	{
		Grid<int> testGrid_int(10000, 10000, 0);
	}

	int a, b, c;
	std::cin >> a >> b >> c;
	MyStruct defStruct = MyStruct(a, b, c);
	*/

	/*
	{
		Grid<MyStruct> testGrid_struct(10000, 10000, defStruct);
		testGrid_struct.TEMP_ForEachCell(SumValues);
		//testGrid_struct.ForEachCell(PrintCell);
	}
	*/
	std::cin.get();

	int it = 1000;
	float m = 0;
	for (int j = 0; j < it; j++)
	{
		std::cout << "Starting benchmark." << std::endl;
		
		// START BENCHMARK
		auto start = std::chrono::high_resolution_clock::now();

		MyStruct defStruct = MyStruct(1, 2, 3);
		Grid<MyStruct> testGrid_struct(50, 50, globalDefStruct);
		//for (int i = 0; i < 200; i++) CreateAndSum(defStruct);
		for (int i = 0; i < 10000; i++) JustSum(testGrid_struct);
		//for (int i = 0; i < 1000; i++) CreateAndSet(testGrid_struct); // 28ms
		//for (int i = 0; i < 1000; i++) CreateAndSetFuncPointer(testGrid_struct); // 45ms

		// END BENCHMARK
		auto end = std::chrono::high_resolution_clock::now();

		auto duration = end - start;
		m += std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
		std::cout << "Done. Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << std::endl;
	}
	std::cout << "========================" << std::endl;
	std::cout << "Average: " << m / it << std::endl;
	

	std::cin.get();
}