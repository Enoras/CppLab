#include<iostream>
#include"deque.h"

int main(){
	Deque<int> d1({ 0, 1, 2, 3 });
	std::cout << d1 << std::endl;
	Deque<int> d2(d1);
	std::cout << d2 << std::endl;
	std::cout << d2.Size() << std::endl;
	std::cout << d2.peekFront() << std::endl;
	std::cout << d2.peekBack() << std::endl;
	std::cout << d2.at(2) << std::endl;
	std::cout << d2[3] << std::endl;
	
	d2.pushFront(-1);
	d2.pushBack(4);
	std::cout << d2 << std::endl;
	
	int n = 5;
	Deque<int> d3(d1);
	d3.pushFront(n);
	d3.popFront();
	d3.popBack();
	std::cout << d3 << std::endl;

	d1.concat(std::move(d2));
	std::cout << d1 << std::endl;

	return 0;
}