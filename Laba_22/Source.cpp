#include <cstdio>
#include <iostream>
#include <conio.h>
#include <vector>

size_t lcg()
{
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

void print(std::vector<int> mas)
{
	for (int i = 0; i < mas.size(); i++)
	{
		std::cout << mas[i] << " ";
	}
	std::cout << std::endl;
}

std::vector<int> fill(std::vector<int> mas, int n)
{
	for (int i = 0; i < n; i++)
	{
		mas.push_back(lcg());
	}
	return mas;
}

int main()
{
	std::vector<int> mas;
	mas = fill(mas, 100);
	print(mas);
}