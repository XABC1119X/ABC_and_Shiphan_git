#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sched.h>
#include <string>
#include <fstream>

class Student {
protected:
	int num;
	std::string name;
	int sum;
	Student* ptr;
public:
	Student(int num, std::string name) {
		this->num = num;
		this->name = name;
		this->sum = 0;
	}
	int getNum() {
		return this->num;
	}
	std::string getName() {
		return this->name;
	}
	int getSum() {
		return this->sum;
	}
	virtual void setPtr(Student* ptr) {
		this->ptr = ptr;
	}
	virtual Student* getPtr() {
		return this->ptr;
	}
	virtual void printInfo(){
		std::cout << "----------" << std::endl;
		std::cout << std::setw(20) << "No. " << std::setw(6) << this->num << std::endl;
		std::cout << std::setw(20) << "Name: " << std::setw(6) << this->name << std::endl;
	}
	virtual void printRank(int rank) {
		std::cout << "---[ " << rank << " place ]";
		this->printInfo();
	}
	virtual std::string getData() {
		return "{\n\tname=" + std::to_string(this->getNum()) + "\n" + "\tname=" + this->getName() + "\n}\n";
	}
};

class StudentNode1 :public Student {
protected:
	int prg;
	int eng;
public:
	StudentNode1(int num, std::string name, int prg, int eng) :Student(num, name) {
		this->ptr = nullptr;
		this->prg = prg;
		this->eng = eng;
		this->sum = prg + eng;
	}
	int getPrg() {
		return this->prg;
	}
	int getEng() {
		return this->eng;
	}
	void printInfo() override {
		std::cout << "----------" << std::endl;
		std::cout << std::setw(20) << "No. " << std::setw(6) << this->num << std::endl;
		std::cout << std::setw(20) << "Name: " << std::setw(6) << this->name << std::endl;
		std::cout << std::setw(20) << "Programming score: " << std::setw(6) << this->prg << std::endl;
		std::cout << std::setw(20) << "English score: " << std::setw(6) << this->eng << std::endl;
	}
	std::string getData() override {
		return "{\n\tnum=" + std::to_string(this->getNum()) + "\n" + "\tname=" + this->getName() + "\n" + "\tprg=" + std::to_string(this->getPrg()) + "\n" + "\teng=" + std::to_string(this->getEng()) + "\n}\n";
	}
};

class StudentNode2 :public Student {
protected:
	int run;
public:
	StudentNode2(int num, std::string name, int run) :Student(num, name) {
		this->ptr = nullptr;
		this->run = run;
		this->sum = run;
	}
	int getRun() {
		return this->run;
	}
	void printInfo() override {
		std::cout << "----------" << std::endl;
		std::cout << std::setw(20) << "No. " << std::setw(6) << this->num << std::endl;
		std::cout << std::setw(20) << "Name: " << std::setw(6) << this->name << std::endl;
		std::cout << std::setw(20) << "Run score: " << std::setw(6) << this->run << std::endl;
	}
	std::string getData() override {
		return "{\n\tnum=" + std::to_string(this->getNum()) + "\n" + "\tname=" + this->getName() + "\n" + "\trun=" + std::to_string(this->getRun()) + "\n}\n";
	}
};

class StudentList {
protected:
	Student* head;
	Student* endPtr;
	int length;
public:
	StudentList() {
		this->head = nullptr;
		this->endPtr = nullptr;
		this->length = 0;
	}
	void addNode(Student* nodePtr) {
		if (this->head == nullptr){
			this->head = nodePtr;
		} else {
			endPtr->setPtr(nodePtr);
		}
		endPtr = nodePtr;
		this->length++;
	}
	bool removeNodefNum(int num){
		Student* ptr = this->head;
		if (head == NULL){
			return false;
		} else if (this->head->getNum() == num){
			this->head = this->head->getPtr();
			delete ptr;
			this->length--;
			return true;
		} else {
			while (ptr->getPtr() != NULL){
				if (ptr->getPtr()->getNum() == num){
					Student* newPtr = ptr->getPtr()->getPtr();
					delete ptr->getPtr();
					ptr->setPtr(newPtr);
					this->length--;
					return true;
				}
				ptr = ptr->getPtr();
			}
			return false;
		}
	}
	Student* findFirst(int num){
		Student* ptr = this->head;
		while (ptr != NULL){
			if (ptr->getNum() == num){
				return ptr;
			}
			ptr = ptr->getPtr();
		}
		return NULL;
	}
	bool findAndPrintAllfName(std::string name){
		Student* ptr = this->head;
		bool found = false;
		while (ptr != NULL){
			if (ptr->getName() == name){
				ptr->printInfo();
				found = true;
			}
			ptr = ptr->getPtr();
		}
		return found;
	}
	void printList() {
		Student* ptr = this->head;
		std::cout << "head -> ";
		while (ptr){
			std::cout << ptr->getNum();
			std::cout << " -> ";
			ptr = ptr->getPtr();
		}
		std::cout << "||" << std::endl;
	}
	void printTranscript() {
		if (this->length <= 0) {
			std::cout << "There is no student data." << std::endl;
			return;
		}

		//print transcript
		int realSort = 1;
		int sort = 1;
		bool isPrinted[this->length] = {};
		bool run = true;

		while (run){
			//get max that print
			int sumMax;
			Student* ptr = this->head;
			int i = 0;
			while (ptr != NULL){
				if (!i[isPrinted]){
					sumMax = ptr->getSum();

					//std::cout << "1\n";
					break;
				} else if (ptr->getPtr() == NULL) {
					run = false;
					
					//std::cout << "2\n";
				}
				ptr = ptr->getPtr();
				i++;
			}
			i = 0;
			ptr = this->head;
			while (ptr != NULL){
				int sum = ptr->getSum();
				if (!i[isPrinted] && sum > sumMax){
					sumMax = sum;

					//std::cout << "3\n";
				}
				ptr = ptr->getPtr();
				i++;
				
				//std::cout << "4\n";
			}
			//got it
			
			//print node that match
			i = 0;
			ptr = this->head;
			while (ptr != NULL){
				int sum = ptr->getSum();
				if (sum == sumMax && !i[isPrinted]){
					realSort++;
					isPrinted[i] = true;
					ptr->printRank(sort);
							
					//std::cout << "5\n";
				}
				ptr = ptr->getPtr();
				i++;
						
				//std::cout << "6\n";
			}
			sort = realSort;
		}
	}
	std::string getDatas() {
		std::string datas = "";
		Student* ptr = this->head;
		while (ptr != NULL) {
			datas.append(ptr->getData());
			ptr = ptr->getPtr();
		}
		return datas;
	}
};

class Menu{
private:
	int select;
	int listIndex;
public:
	Menu() {
		this->select = -1;
		this->listIndex = -1;
	}
	void show(){
		std::cout << "######################" << std::endl;
		std::cout << "	MENU" << std::endl;
		std::cout << "(1). Insertion" << std::endl;
		std::cout << "(2). Search" << std::endl;
		std::cout << "(3). Deletion" << std::endl;
		std::cout << "(4). Print List Data" << std::endl;
		std::cout << "(5). Print Transcript" << std::endl;
		std::cout << "(0). Exit" << std::endl;
		std::cout << "Please select one... ";
		std::cin >> this->select;
		if (this->select < 1 || this->select > 5) {
			this->listIndex = -1;
		} else {
			std::cout << "Lists of students:" << std::endl;
			std::cout << "(0). Computer Science" << std::endl;
			std::cout << "(1). Physical Education" << std::endl;
			std::cout << "Please select one... ";
			std::cin >> this->listIndex;
			if (this->listIndex < 0 || this->listIndex > 1) {
				this->listIndex = -1;
				this->select = -1;
			}
		}
	}
	int getSelect(){
		return this->select;
	}
	int getListIndex(){
		return this->listIndex;
	}
};

void insertion(StudentList lists[], int listIndex) {
	int num;
	std::cout << "## Add data:" << std::endl << "number(<=0 for cancel): ";
	std::cin.ignore();
	std::cin >> num;
	if (num <= 0){
		std::cout << "add canceled." << std::endl;
	} else if (lists[listIndex].findFirst(num)){
		std::cout << "number existing." << std::endl;
		std::cout << "add canceled." << std::endl;
	} else {
		std::string name;
		std::cout << "name: ";
		std::cin.ignore();
		std::getline(std::cin, name);
		switch (listIndex) {
			case 0: {
				int prg;
				int eng;
				std::cout << "Programming score: ";
				std::cin >> prg;
				std::cout << "English score: ";
				std::cin >> eng;
				Student* newNodePtr = new StudentNode1(num, name, prg, eng);
				lists[0].addNode(newNodePtr);
				break;
			}
			case 1: {
				int run;
				std::cout << "Run score: ";
				std::cin >> run;
				Student* newNodePtr = new StudentNode2(num, name, run);
				lists[1].addNode(newNodePtr);
				break;
			}
			default: {
				std::cout << "invalid list index." << std::endl;
				break;
			}
		}
	}
}

void search(StudentList& list) {
	std::cout << "search by name... ";
	std::string name;
	std::cin.ignore();
	std::getline(std::cin, name);
	if (!list.findAndPrintAllfName(name)) {
		std::cout << "No match result." << std::endl;
	}
}

void remove(StudentList& list) {
	int rmNum;
	std::cout << "select the number you want to delete... ";
	std::cin >> rmNum;
	if (list.removeNodefNum(rmNum)){
		std::cout << "No." << rmNum << " has been deleted." << std::endl;
	} else {
		std::cout << "No." << rmNum << " is not in the list." << std::endl;
	}
}

void exitMenu(StudentList lists[]) {
	std::cout << "saving..." << std::endl;
	std::ofstream file("data.txt");
	for (int i = 0; i < 2; i++) {
		switch (i) {
			case 0: {
				file << "Computer Science=\n"; 
				break;
			}
			case 1: {
				file << "Physical Education=\n"; 
				break;
			}
			default: {
				file << "unknown=\n";
				break;
			}
		}
		file << lists[i].getDatas() << std::endl;  
	}
	file.close();
	std::cout << "exit..." << std::endl;
}

bool menuSelectHandler(int select, int listIndex, StudentList lists[]) {
	switch (select) {
		case 0:
			exitMenu(lists);
			return false;
		case 1:
			insertion(lists, listIndex);
			return true;
		case 2:
			search(lists[listIndex]);
			return true;
		case 3:
			remove(lists[listIndex]);
			return true;
		case 4:
			lists[listIndex].printList();
			return true;
		case 5:
			lists[listIndex].printTranscript();
			return true;
		default:
			std::cout << "selection unfined, consider other option" << std::endl;
			return true;
	}
}

void recoverLists(StudentList lists[]) {
	std::ifstream datafile("data.txt");
	int listIndex = 0;
	std::string line;

	while (getline(datafile, line)) {
		if (line == std::string("{") && listIndex == 0) {
			int num;
			std::string name;
			int prg;
			int eng;

			getline(datafile, line);
			while (line.find_first_of("}") == std::string::npos) {
				size_t equalIndex = line.find_first_of("=");
				if (equalIndex == std::string::npos) {
					getline(datafile, line);
					continue;
				}

				size_t keyPos = line.find_first_not_of(" \t");
				std::string key = line.substr(keyPos, equalIndex - keyPos);
				std::string value = "";
				if (equalIndex < line.size() - 1) {
					value = line.substr(equalIndex + 1);
				}

				if (key == std::string("num")) {
					num = std::stoi(value);	
				} else if (key == std::string("name")) {
					name = value;
				} else if (key == std::string("prg")) {
					prg = std::stoi(value);	
				} else if (key == std::string("eng")) {
					eng = std::stoi(value);	
				}

				getline(datafile, line);
			}
			lists[listIndex].addNode(new StudentNode1(num, name, prg, eng));
		} else if (line == std::string("{") && listIndex == 1) {
			int num;
			std::string name;
			int run;

			getline(datafile, line);
			while (line.find_first_of("}") == std::string::npos) {
				size_t equalIndex = line.find_first_of("=");
				if (equalIndex == std::string::npos) {
					getline(datafile, line);
					continue;
				}

				size_t keyPos = line.find_first_not_of(" \t");
				std::string key = line.substr(keyPos, equalIndex - keyPos);
				std::string value = "";
				if (equalIndex < line.size() - 1) {
					value = line.substr(equalIndex + 1);
				}

				if (key == std::string("num")) {
					num = std::stoi(value);	
				} else if (key == std::string("name")) {
					name = value;
				} else if (key == std::string("run")) {
					run = std::stoi(value);	
				}

				getline(datafile, line);
			}
			lists[listIndex].addNode(new StudentNode2(num, name, run));
		} else if (line == std::string("Computer Science=")) {
			listIndex = 0;
		} else if (line == std::string("Physical Education=")) {
			listIndex = 1;
		} else if (line == std::string("unknown=")) {
			listIndex = -1;
		}
	}
}

int main() {
	bool running = true;
	Menu menu = Menu();
	StudentList lists[2] = {StudentList(), StudentList()};

	recoverLists(lists);

	while (running) {
		menu.show();
		running = menuSelectHandler(menu.getSelect(), menu.getListIndex(), lists);
	}
}
