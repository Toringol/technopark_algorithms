/*
* Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. 
* Требуется найти k-ю порядковую статистику. т.е. напечатать число, 
* которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм.
* Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
* Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. 
* Описание для случая прохода от начала массива к концу:
* Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
* Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. 
* Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. 
* Последним элементом лежит опорный.
* Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
* Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
* Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
* Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
* В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

* Реализуйте стратегию выбора опорного элемента “медиана трёх”. 
* Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
*/

#include <iostream>

void swap(size_t &first, size_t &second) {
	size_t temp = first;
	first = second;
	second = temp;
}

size_t selectPivot(size_t *data, size_t left, size_t right) {
	size_t middle = (left + right) / 2;
	if (data[left] > data[right])
		if (data[right] > data[middle])
			return right;
		else
			return middle;
	else if (data[left] > data[middle])
		return left;
	else
		return middle;
}


size_t partition(size_t *data, size_t left, size_t right) {
	swap(data[left], data[selectPivot(data, left, right)]);
	size_t j = right;
	for (size_t i = right; i > left; i--) {
		if (data[i] > data[left]) {
			swap(data[i], data[j]);
			--j;
		}
	}
	swap(data[left], data[j]);
	return j;
}


size_t findKStatistics(size_t *data, size_t n, size_t k) {
	size_t left = 0;
	size_t right = n - 1;
	while (lastPivotPos != k) {
		lastPivotPos = partition(data, left, right);
		if (k < lastPivotPos)
			right = lastPivotPos - 1;
		else
			left = lastPivotPos + 1;
	}
	return data[lastPivotPos];
}

int main() {
	size_t numberOfElem = 0, kStat = 0;
	std::cin >> numberOfElem >> kStat;

	size_t *numbers = new size_t[numberOfElem];
	for (size_t i = 0; i < numberOfElem; i++) {
		std::cin >> numbers[i];
	}

	std::cout << findKStatistics(numbers, numberOfElem, kStat);

	delete[] numbers;
	
	return 0;
}
