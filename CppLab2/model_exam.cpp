#include  "model_exam.h"

using namespace std;
Tasks::Tasks(ifstream& file)
{
	//if (!file.is_open())
	//{
	//	throw exception("File with tasks not found");
	//}
	QuadEq eq;
	while (!file.eof())
	{
		file >> eq;
		_eqs.push_back(eq);
	}
}

vector<Student*> init_simple_student_group()
{
	vector<Student*> group;
	const vector<string> names = { "Reutov" ,"Pertov" ,"Turchenko" ,"Ahmetshin" ,"Plotnikov" };
	for (int i = 0; i < 5; i++) {
		int type = rand() % 3;
		if (type == 0)
			group.push_back(new good(names[i]));
		else if (type == 1)
			group.push_back(new aveng(names[i]));
		else
			group.push_back(new bad(names[i]));
	}
	return group;
}


Solution good::solve_task(const QuadEq& eq) const
{
	return { get_name(), eq.roots(),eq};
}

Solution aveng::solve_task(const QuadEq& eq) const
{
	vector<double> roots = eq.roots();
	if (rand() % 2)
		roots = { 0 };
	return { get_name(), roots,eq };
}

Solution bad::solve_task(const QuadEq& eq) const
{
	return { get_name(), {0}, eq };
}


void Student::send_task(Teacher& teacher, const QuadEq& eq) const
{
	teacher.collect_solutions(solve_task(eq));
}


void Teacher::collect_solutions(const Solution& solution) 
{
	_queue_solutions.push_back(solution);
}


Table Teacher::get_table()
{
	map<string,int> table;

	for (const auto& sol:_queue_solutions)
	{
		table[sol._name];
		if (sol._eq.roots() == sol._roots)
			table[sol._name]++;
	}
	_queue_solutions.clear();
	return Table(table);
}

void Table::print() const
{
	if (_performance_table.empty())
		cout << "empty table";
	
	for (const auto& student:_performance_table)
		cout << student.first << ": " << student.second << endl;
}
