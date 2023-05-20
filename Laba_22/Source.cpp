#include <cstdio>
#include <iostream>
#include <conio.h>
#include <vector>

struct stats 
{
	size_t comparison_count = 0;
	size_t copy_count = 0;
};


size_t lcg()
{
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

bool test_int(char* b)
{
	if (*b == '-') b++;
	if (*b == 0) return false;
	if (*b == '0' && *(b + 1) != 0) return false;
	while (*b)
	{
		if (*b < '0' || *b>'9') return false;
		b++;
	}
	return true;
}

int scan()
{
	while (true)
	{
		char* str = new char[256];
		std::cin.getline(str, 256);
		if (test_int(str))
		{
			int x = atoi(str);
			delete[] str;
			return x;
		}
		else puts("Wrong data");
		delete[]str;
	}
}

void print(std::vector<int> mas)
{
	for (int i = 0; i < mas.size(); i++)
	{
		std::cout << mas[i] << " ";
	}
	std::cout << std::endl;
}

std::vector<int> fill()
{
	int n = 0;
	std::cout << "Enter the size of the array: ";
	while (true)
	{
		n = scan();
		if (n > 0) break;
		else puts("Wrong data");
	}
	std::vector<int> mas;
	for (int i = 0; i < n; i++)
	{
		std::cout << "mas[" << i + 1 << "]: ";
		mas.push_back(scan());
	}
	return mas;
}

std::vector<int> random_fill()
{
	int n = 0;
	std::cout << "Enter the size of the array: ";
	while (true)
	{
		n = scan();
		if (n > 0) break;
		else puts("Wrong data");
	}
	std::vector<int> mas;
	for (int i = 0; i < n; i++)
	{
		mas.push_back(lcg());
	}
	return mas;
}

stats sort_bubble(std::vector<int>& mas, bool f)
{
	stats obj;
	obj.comparison_count = 0;
	obj.copy_count = 0;
	for (int i = 0; i < mas.size(); i++)
	{
		for (int j = 0; j < mas.size() - 1 - i; j++)
		{
			if ((mas[j] > mas[j + 1] && f == true) || (mas[j] < mas[j + 1] && f == false))
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

stats sort_shell(std::vector<int>& mas, bool f)
{
	stats obj;
	obj.comparison_count = 0;
	obj.copy_count = 0;
	for (int d = mas.size() / 2; d > 0; d=d/2)
	{
		for (int i = d; i < mas.size(); ++i)
		{
			for (int j = i - d; j >= 0; j -= d) 
			{
				if ((mas[j] > mas[j + d] && f == true) || (mas[j] < mas[j + d] && f == false))
				{
					int k = mas[j];
					mas[j] = mas[j + d];
					mas[j+ d] = k;
					obj.copy_count++;
					obj.comparison_count++;
				}
				else
				{
					obj.comparison_count++;
					break;
				}
			}
		}
	}
	return obj;
}

void test_sort_bubble(std::vector<int>& mas, bool f)
{
	stats obj = sort_bubble(mas, f);

	std::cout << "comparison_count: " << obj.comparison_count << "\ncopy_count: " << obj.copy_count << std::endl;
}

void test_sort_shell(std::vector<int>& mas, bool f)
{
	stats obj = sort_shell(mas, f);

	std::cout << "comparison_count: " << obj.comparison_count << "\ncopy_count: " << obj.copy_count << std::endl;
}

int main()
{
	std::vector<int> mas;
	mas = random_fill();
	print(mas);
	test_sort_shell(mas, true);
	print(mas);
}