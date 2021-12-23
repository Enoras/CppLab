#pragma once
#include <vector>
#include <map>
#include <functional>
#include <exception>

template<typename Type>
class Wrapper {
public:
	template<typename Obj, typename... Args>
	Wrapper(Obj *object, Type(Obj::*func)(Args...), std::vector<std::pair<std::string, Type>> args) {
		for (auto& p : args) {
			argName.push_back(p.first);
		}

		// init function caller
		caller = [this, object, func](std::vector<Type>& argsForFunc) {
			return executeFunction(object, func, argsForFunc, std::make_index_sequence<sizeof...(Args)>{});
		};

	}

	Type execute(const std::map<std::string, Type>& argsMap) {
		std::vector<Type> argsVec;
		for (auto& arg : argsMap) {
			if (!isExist(arg.first))
				throw std::exception("WRAPPER: This command is not init");

			argsVec.push_back(arg.second);
		}
		return caller(argsVec);
	}
private:
	bool isExist(std::string name) {
		for (auto& n : argName) {
			if (n.compare(name) == 0)
				return true;
		}
		return false;
	}

	template<typename Obj, typename FuncName, size_t... Indxs>
	Type executeFunction(Obj *object, FuncName funcName, std::vector<Type>& args, std::index_sequence<Indxs...>) {
		return ((object->*funcName)(args[Indxs]...));
	}

	std::function<Type(std::vector<Type>& )> caller;
	std::vector<std::string> argName;
};
