/* 
* “Считалочка”. В круг выстроено N человек, пронумерованных числами от 1 до N. 
* Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек. 
* (Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й, 
* затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.) 
* Необходимо определить номер уцелевшего. N, k ≤ 10000.
*/

#include <iostream>

size_t whoIsLast(size_t numberOfPeople, size_t offset) {
	size_t res = 0;
	for (size_t i = 1; i <= numberOfPeople; ++i) {
		res = (res + offset) % i;
	}
	return res + 1;
}

int main() {
	size_t numberOfPeople = 0, offset = 0;
	std::cin >> numberOfPeople >> offset;
	if (numberOfPeople > 0 && offset > 0) {
		std::cout << whoIsLast(numberOfPeople, offset);
	}
	return 0;
}
