#include <iostream>
#include "Wrapper.hpp"
#include "Engine.hpp"
#include "Tester.hpp"



int main(void) {
	TestAdding A;
	// test int
	Wrapper<int> wrapper1(&A, &TestAdding::runTwo<int>, { {"arg1", 0}, {"arg2", 0} });
	Engine engine;
	engine.register_command<int>(&wrapper1, "command1");
	std::cout << "5 + 12 = " << engine.execute<int>("command1", {{"arg1", 5}, {"arg2", 12}}) << std::endl;

	// test double 
	Wrapper<double> wrapper2(&A, &TestAdding::runTwo<double>, { {"arg1", 0.0}, {"arg2", 0.0} });
	engine.register_command<double>(&wrapper2, "command2");
	std::cout << "3.5 + 10.5 = " << engine.execute<double>("command2", { {"arg1", 3.5}, {"arg2", 10.5} }) << std::endl;
    
	// test strings
	TestString B;
	Wrapper<std::string> wrapper3(&B, &TestString::runStr, { {"arg1", ""}, {"arg2", ""} });
	engine.register_command<std::string>(&wrapper3, "command3");
	std::cout << "My string " << engine.execute<std::string>("command3", { {"arg1", "test"}, {"arg2", "string"} }) << std::endl;

	return 0;
}