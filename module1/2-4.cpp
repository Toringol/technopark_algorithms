/*
* Дан отсортированный массив различных целых чисел A[0..n-1] 
* и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i] 
* найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i]. 
* Время работы поиска для каждого элемента B[i]: O(log(k)). n ≤ 110000, m ≤ 1000.
*/

#include <iostream>

void searchFirstSpaceToBinarySearch(const int* arr, int sizeOfArray, int element, int* leftBoundary, int* rightBoundary) {
	*rightBoundary = *leftBoundary + 1;
	while ((*rightBoundary < sizeOfArray - 1) && arr[*rightBoundary] < element) {
		*rightBoundary *= 2;
	}
	if (*rightBoundary > sizeOfArray - 1)
		*rightBoundary = sizeOfArray - 1;
}

int findInsertionPoint(const int* arr, int sizeOfArray,
	int element, int leftBoundary, int rightBoundary) {
	if (element < arr[0])
		return 0;
	if (element > arr[sizeOfArray - 1])
		return sizeOfArray - 1;
	int startPosition = leftBoundary;
	int endPosition = rightBoundary;
	while (startPosition < endPosition) {
		int middlePosition = (startPosition + endPosition) / 2;
		if (arr[middlePosition] < element)
			startPosition = middlePosition + 1;
		else
			endPosition = middlePosition;
	}
	if (startPosition == endPosition && startPosition > 0)
		startPosition--;
	return (element - arr[startPosition] <= arr[endPosition] - element) ? startPosition : endPosition;
}

int main() {

	int sizeOfFirstArray;
	std::cin >> sizeOfFirstArray;
	int* firstArray = new int[sizeOfFirstArray];
	if (firstArray == NULL)
		return 0;
	for (int i = 0; i < sizeOfFirstArray; i++) {
		std::cin >> firstArray[i];
	}

	int sizeOfSecondArray;
	std::cin >> sizeOfSecondArray;
	int* secondArray = new int[sizeOfSecondArray];
	if (secondArray == NULL)
		return 0;
	for (int i = 0; i < sizeOfSecondArray; i++) {
		std::cin >> secondArray[i];
	}

	int leftBoundary, rightBoundary;

	for (int i = 0; i < sizeOfSecondArray; i++) {
		leftBoundary = 0;
		rightBoundary = sizeOfFirstArray - 1;
		searchFirstSpaceToBinarySearch(firstArray, sizeOfFirstArray,
			secondArray[i], &leftBoundary, &rightBoundary);
		std::cout << findInsertionPoint(firstArray, sizeOfFirstArray,
			secondArray[i], leftBoundary, rightBoundary) << " ";
	}

	delete[] firstArray;
	delete[] secondArray;

	return 0;
}
