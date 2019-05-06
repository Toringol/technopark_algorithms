/*
* Binary MSD для long long.
* Дан массив неотрицательных целых 64-разрядных чисел. 
* Количество чисел не больше 106. Отсортировать массив методом MSD по битам (бинарный QuickSort).
*/

#include <iostream>

#define NUMBEROFBITS 63

void swap(unsigned long long &first, unsigned long long &second) {
	unsigned long long temp = first;
	first = second;
	second = temp;
}

bool digit(unsigned long long number, int index) {
	return (number >> index) & 1;
}

void quicksortMSD(unsigned long long *data, int left, int right, int wBit) {
	int i = left;
	int j = right;
	if (right <= left || wBit < 0)
		return;
	while (j != i) {
		while (!digit(data[i], wBit) && (i < j))
			++i;
		while (digit(data[j], wBit) && (j > i))
			--j;
		swap(data[i], data[j]);
	}
	if (!digit(data[right], wBit))
		++j;
	quicksortMSD(data, left, j - 1, wBit - 1);
	quicksortMSD(data, j, right, wBit - 1);
}

int main() {
	int size;
	std::cin >> size;
	if (size < 0)
		return 0;

	unsigned long long *numbers = new unsigned long long[size];
	for (int i = 0; i < size; ++i) {
		std::cin >> numbers[i];
	}

	quicksortMSD(numbers, 0, size - 1, NUMBEROFBITS);

	for (int i = 0; i < size; ++i) {
		std::cout << numbers[i] << " ";
	}
	
	delete[] numbers;

	return 0;
}
