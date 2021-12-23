#pragma once
#include "Wrapper.hpp"
#include <string>


class Engine {
public:
	template<typename Type>
	void register_command(Wrapper<Type>* wrapper, const std::string& nameCommand) {
		if (functions.find(nameCommand) != functions.end())
			throw std::exception("ENGINE: This command already exist");
		functions.insert({ nameCommand, wrapper });
	}

	template<typename Type>
	Type execute(const std::string& nameCommand, const std::map<std::string, Type>& args) {
		auto it = functions.find(nameCommand);
		if (it == functions.end())
			throw std::exception("ENGINE: This command is not registred");
		
		Wrapper<Type>* wrapper = static_cast<Wrapper<Type>*>(it->second);
		return wrapper->execute(args);
	}
private:
	std::map<std::string, void*> functions;
};