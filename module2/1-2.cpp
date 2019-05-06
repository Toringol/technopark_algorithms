/*
* Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. 
* Хранимые строки непустые и состоят из строчных латинских букв.
* Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
* Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, 
* когда коэффициент заполнения таблицы достигает 3/4.
* Структура данных должна поддерживать операции добавления строки в множество, 
* удаления строки из множества и проверки принадлежности данной строки множеству.
* 
* Для разрешения коллизий используйте двойное хеширование.
*/

#include <iostream>
#include <vector>
#include <string>

const int BaseTableSize = 8;
const int HashConstFirst = 17;	
const int HashConstSecond = 19;
const double FillingTable = 0.75;

class HashTable {
public:
	HashTable() : hashArray(BaseTableSize, "Empty"), realSize(0) {}
	~HashTable() {}
	bool Insert(const std::string &key);
	bool Remove(const std::string &key);
	bool Search(const std::string &key);
	void ReHash();
private:
	std::vector<std::string> hashArray;
	int realSize;
	int HashFuncFisrt(std::string str, int tableSize);
	int HashFuncSecond(std::string str, int tableSize);
	int HashFunc(int firstHash, int secondHash, int iterator, int tableSize);
};

int HashTable::HashFuncFisrt(std::string str, int tableSize) {
	int hash = 0;
	for (int i = 0; i < static_cast<int>(str.size()); i++) {
		hash = (hash * HashConstFirst + str[i]) % tableSize;
	}
	return hash;
}

int HashTable::HashFuncSecond(std::string str, int tableSize) {
	int hash = 0;
	for (int i = 0; i < static_cast<int>(str.size()); i++) {
		hash = (hash * HashConstSecond + str[i]) % tableSize;
	}
	return (hash * 2 + 1) % tableSize;
}

int HashTable::HashFunc(int firstHash, int secondHash, int iterator, int tableSize) {
	return ((firstHash + iterator * secondHash) % tableSize);
}

bool HashTable::Insert(const std::string &key) {
	if ((static_cast<double>(realSize) / static_cast<double>(hashArray.size())) >= FillingTable) {
		ReHash();
	}
	int hashFirst = HashFuncFisrt(key, static_cast<int>(hashArray.size()));
	int hashSecond = HashFuncSecond(key, static_cast<int>(hashArray.size()));
	for (int i = 0; i < static_cast<int>(hashArray.size()); i++) {
		int hash = HashFunc(hashFirst, hashSecond, i, static_cast<int>(hashArray.size()));
		if (hashArray[hash] == key) {
			return false;
		}
		if (hashArray[hash] == "Empty" || hashArray[hash] == "Deleted") {
			hashArray[hash] = key;
			realSize++;
			return true;
		}
	}
	return false;
}

bool HashTable::Search(const std::string &key) {
	int hashFirst = HashFuncFisrt(key, static_cast<int>(hashArray.size()));
	int hashSecond = HashFuncSecond(key, static_cast<int>(hashArray.size()));
	for (int i = 0; i < static_cast<int>(hashArray.size()); i++) {
		int hash = HashFunc(hashFirst, hashSecond, i, static_cast<int>(hashArray.size()));
		if (hashArray[hash] == "Empty")
			return false;
		if (hashArray[hash] == "Deleted")
			continue;
		if (hashArray[hash] == key) {
			return true;
		}
	}
	return false;
}

bool HashTable::Remove(const std::string &key) {
	int hashFirst = HashFuncFisrt(key, static_cast<int>(hashArray.size()));
	int hashSecond = HashFuncSecond(key, static_cast<int>(hashArray.size()));
	for (int i = 0; i < static_cast<int>(hashArray.size()); i++) {
		int hash = HashFunc(hashFirst, hashSecond, i, static_cast<int>(hashArray.size()));
		if (hashArray[hash] == "Empty")
			return false;
		if (hashArray[hash] == key) {
			hashArray[hash] = "Deleted";
			realSize--;
			return true;
		}
	}
	return false;
}

void HashTable::ReHash() {
	std::vector<std::string> oldArray = hashArray;
	int newTableSize = static_cast<int>(hashArray.size()) * 2;
	hashArray.assign(newTableSize, "Empty");
	realSize = 0;
	for (int i = 0; i < static_cast<int>(oldArray.size()); i++) {
		if (oldArray[i] != "Empty" && oldArray[i] != "Deleted") {
			Insert(oldArray[i]);
		}
	}
	
}

int main() {
	HashTable table;
	while (true) {
		char command = 0;
		std::string value;
		std::cin >> command >> value;
		if (std::cin.fail()) {
			break;
		}
		switch (command) {
		case '?':
			std::cout << (table.Search(value) ? "OK" : "FAIL") << std::endl;
			break;
		case '+':
			std::cout << (table.Insert(value) ? "OK" : "FAIL") << std::endl;
			break;
		case '-':
			std::cout << (table.Remove(value) ? "OK" : "FAIL") << std::endl;
			break;
		}
	}
	return 0;
}
