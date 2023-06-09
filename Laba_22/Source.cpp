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

stats heapify(std::vector<int>& mas, int n, int i, bool f)
{
	stats obj;
	obj.comparison_count = 0;
	obj.copy_count = 0;
	int largest = i;
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

	if ((l < n && mas[l] > mas[largest] && f == true) || (l < n && mas[l] < mas[largest] && f == false))
	{
		largest = l;
		obj.comparison_count++;
	}

	if ((r < n && mas[r] > mas[largest] && f == true) || (r < n && mas[r] < mas[largest] && f == false))
	{
		largest = r;
		obj.comparison_count++;
	}

	if (largest != i)
	{
		int k = mas[i];
		mas[i] = mas[largest];
		mas[largest] = k;
		obj.copy_count++;
		stats temp = heapify(mas, n, largest, f);
		obj.comparison_count += temp.comparison_count;
		obj.copy_count += temp.copy_count;
	}
	return obj;
}

stats sort_pyramid(std::vector<int>& mas, bool f)
{
	stats obj;
	obj.comparison_count = 0;
	obj.copy_count = 0;

	for (int i = mas.size() / 2 - 1; i >= 0; i--)
	{
		stats temp = heapify(mas, mas.size(), i, f);
		obj.comparison_count += temp.comparison_count;
		obj.copy_count += temp.copy_count;
	}

	for (int i = mas.size() - 1; i >= 0; i--)
	{
		int k = mas[0];
		mas[0] = mas[i];
		mas[i] = k;
		obj.copy_count++;
		stats temp = heapify(mas, i, 0, f);
		obj.comparison_count += temp.comparison_count;
		obj.copy_count += temp.copy_count;
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

void test_sort_pyramid(std::vector<int>& mas, bool f)
{
	stats obj = sort_pyramid(mas, f);

	std::cout << "comparison_count: " << obj.comparison_count << "\ncopy_count: " << obj.copy_count << std::endl;
}

void test_of_sorts()
{
	int arr[13] = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000 };
	for (int i = 0; i < 13; i++)
	{
		std::cout << "Sorting an array with " << arr[i] << " elements\n";
		stats obj;	
		std::vector<int> mas;
		for (int j = 0; j < arr[i]; j++)
		{
			mas.push_back(lcg());
		}
		sort_bubble(mas, false);
		obj = sort_bubble(mas, true);
		std::cout << "comparison_count: " << obj.comparison_count << "\ncopy_count: " << obj.copy_count << std::endl;
	}
}

int main()
{
	std::vector<int> mas;
	while (true)
	{
		system("cls");
		std::cout << "1 - Sort bubble" << std::endl;
		std::cout << "2 - Sort shell" << std::endl;
		std::cout << "3 - Sort pyramid" << std::endl;
		std::cout << "4 - Create massive" << std::endl;
		std::cout << "5 - Create random massive" << std::endl;
		std::cout << "6 - Print massive" << std::endl;
		std::cout << "7 - Exit" << std::endl;
		int z = getch();
		system("cls");

		if (z == '1')
		{
			test_sort_bubble(mas, true);
			if (getch()) z = '0';
		}

		if (z == '2')
		{
			test_sort_shell(mas, true);
			if (getch()) z = '0';
		}

		if (z == '3')
		{
			test_sort_pyramid(mas, true);
			if (getch()) z = '0';
		}

		if (z == '4') mas = fill();

		if (z == '5') mas = random_fill();

		if (z == '6')
		{
			print(mas);
			if (getch()) z = '0';
		}

		if (z == '7') return 0;
	}
}