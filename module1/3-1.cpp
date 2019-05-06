/*
* Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
* Формат входных данных.
* В первой строке количество команд n. n ≤ 1000000.
* Каждая команда задаётся как 2 целых числа: a b.
* a = 1 - push front
* a = 2 - pop front
* a = 3 - push back
* a = 4 - pop back
* Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
* Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
* Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”. 
* Формат выходных данных.
* Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
*
* Реализовать очередь с динамическим зацикленным буфером.
*/

#include <iostream>

class CQueue {

public:
	CQueue();
	CQueue(const CQueue&q) = delete;
	CQueue(CQueue&& q) = delete;

	~CQueue();

	CQueue& operator= (const CQueue&) = delete;
	CQueue& operator= (CQueue&&) = delete;
	
	void Enqueue(int data);
	int Dequeue();
	bool IsEmpty() const { return head == 0 && tail == head; }

private:
	int* buffer;
	int bufferSize;
	int head; 
	int tail;

	void ExpandMemory() {
		int newBufferSize = (bufferSize > 0) ? bufferSize * 2 : 50;
		int* newBuffer = new int[newBufferSize];
		if (head != tail) {
			int counter = 0;
			for (int i = head; i < bufferSize; i++) {
				if (i == tail)
					break;
				newBuffer[counter++] = buffer[i];
				if (i == bufferSize - 1)
					i = -1;
			}
			head = 0;
			tail = counter;
		}
		if (buffer != NULL)
			delete[] buffer;
		buffer = newBuffer;
		bufferSize = newBufferSize;
	}

};

CQueue::CQueue() {
	buffer = NULL;
	bufferSize = 0;

	head = 0;
	tail = 0;

	ExpandMemory();
}

CQueue::~CQueue() {
	if (buffer != NULL) {
		delete[] buffer;
	}
}

void CQueue::Enqueue(int data) {
	if ((tail + 1) % bufferSize == head) {
		ExpandMemory();
		Enqueue(data);
	}
	else {
		buffer[(tail) % bufferSize] = data;
		tail = (tail + 1) % bufferSize;
	}
}

int CQueue::Dequeue() {
	if (head != tail) {
		int result = buffer[head];
		if (head == bufferSize - 1)
			head = 0;
		else {
			head++;
		}
		return result;
	}
	return -1;
}

int main() {

	CQueue queue;
	int n = 0;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int operation = 0;
		int value = 0;
		std::cin >> operation >> value;
		switch (operation) {
		case 2: {
			int queue_value = -1;
			if (!queue.IsEmpty()) {
				queue_value = queue.Dequeue();
			}
			if (queue_value != value) {
				std::cout << "NO" << std::endl;
				return 0;
			}
			break;
		}
		case 3:
			queue.Enqueue(value);
			break;
		default:
			std::cout << "NO" << std::endl;
			return 0;
		}
	}
	std::cout << "YES" << std::endl;
	return 0;
}
