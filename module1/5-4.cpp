/*
* Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием. 
* Общее время работы алгоритма O(n log n).
* Закраска прямой 2.
* На числовой прямой окрасили N отрезков. 
* Известны координаты левого и правого концов каждого отрезка (Li и Ri). 
* Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
*/

#include <iostream>
#include <cstring>

struct Point {
	int x;
	char c;
	Point() : x(0), c('-') {};
	Point(int x, char c) : x(x), c(c) {};
};

int is_less(Point a, Point b) {
	return a.x < b.x;
}

void merge(Point* array1, int len1, Point* array2, int len2, Point* result) {
	int i = 0, j = 0, k = 0;
	while (i < len1 && j < len2) {
		if (is_less(array1[i], array2[j])) {
			result[k] = array1[i++];
		}
		else {
			result[k] = array2[j++];
		}
		k++;
	}

	if (i >= len1) {
		for (int index = k; index < len1 + len2; index++) {
			result[index] = array2[j++];
		}
	}
	else if (j >= len2) {
		for (int index = k; index < len1 + len2; index++) {
			result[index] = array1[i++];
		}
	}
}

void mergeSort(Point* array, int length) {
	if (length <= 1) {
		return;
	}

	int firstLength = length / 2;
	int secondLength = length - firstLength;

	mergeSort(array, firstLength);
	mergeSort(array + firstLength, secondLength);

	Point* result = new Point[length];

	merge(array, firstLength, array + firstLength, secondLength, result);
	memcpy(array, result, sizeof(Point) * length);

	delete[] result;
}



int main() {

	int n, x, y;
	int depth, len;
	std::cin >> n;

	n *= 2;

	Point *points = new Point[n];

	for (int i = 0; i < n; i += 2) {
		std::cin >> x >> y;
		points[i] = Point(x, 's');
		points[i + 1] = Point(y, 'e');
	}

	mergeSort(points, n);

	depth = len = 0;

	for (int i = 0; i < n - 1; i++) {
		if (points[i].c == 's') depth++;
		if (points[i].c == 'e') depth--;
		if (depth == 1) len += points[i + 1].x - points[i].x;
	}

	std::cout << len << std::endl;

	delete[] points;
	return 0;
}
