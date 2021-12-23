#include <string>

class TestAdding {
public:
	template<typename Type>
	Type runTwo(Type a, Type b) {
		return a + b;
	}
};

class TestString {
public:
	std::string runStr(std::string name, std::string surname) {
		return std::string("named ") + name + " " + surname;
	}
};