#include <cstdio>
#include <iostream>
#include <conio.h>
#include <vector>

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};


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

std::vector<int> random_fill(int n)
{
	std::vector<int> mas;
	for (int i = 0; i < n; i++)
	{
		mas.push_back(lcg());
	}
	return mas;
}

stats sort_bubble(std::vector<int>& mas)
{
	stats obj;
	obj.comparison_count = 0;
	obj.copy_count = 0;
	for (int i = 0; i < mas.size(); i++)
	{
		for (int j = 0; j < mas.size() - 1 - i; j++)
		{
			if (mas[j] > mas[j + 1])
			{
				int k = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = k;
				obj.copy_count++;
			}
			obj.comparison_count++;
		}
	}
	return obj;
}

void test_sort_bubble(std::vector<int>& mas)
{
	stats obj = sort_bubble(mas);

	std::cout << "comparison_count: " << obj.comparison_count << "\ncopy_count: " << obj.copy_count << std::endl;
}

int main()
{
	std::vector<int> mas;
	mas = random_fill(100);
	print(mas);
	test_sort_bubble(mas);
	print(mas);
}