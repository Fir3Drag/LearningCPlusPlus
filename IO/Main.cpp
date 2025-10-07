#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define number 1
#define text "Hello"
#define trueOrFalse false

string input;
short s = 111111111111.1212121211;
long l = 11111111111111.1212112121212;
double d = 1111111111111.211221121212121212;
double long dl = 11111111111111111.121211212122112;
float f = 1111111111111111.12121121212122112;

struct person
{
	string name;
	string phone;
	int age;
}p;

vector<double> parseNumbers(string s)
{
	int cutoff = 0;
	vector<double> numbers;
	int i;
	string temp;

	for (i = 0; i < s.length(); i++)
	{
		temp = s.substr(i,1);

		if (temp == "x" || temp == "/" || temp == "+" || temp == "-" || temp == "=")
		{
			numbers.push_back(stod(s.substr(cutoff, i-cutoff)));
			cutoff = i + 1;
		}
	}
	return numbers;
}

vector<string> parseOperations(string s)
{
	vector<string> operations;
	int i;
	string temp;

	for (i = 0; i < s.length(); i++)
	{
		temp = s.substr(i, 1);

		if (temp == "x" || temp == "/" || temp == "+" || temp == "-")
		{
			operations.push_back(temp);
		}
	}
	return operations;
}

string vectorToString(vector<string> l)
{
	string s;

	for (auto it = l.begin(); it != l.end(); it++)
	{
		s += *it;

		if (next(it) != l.end())
		{
			s += " ";
		}
	}
	return s + "\n";
}

string vectorToString(vector<double> l)
{
	string s;

	for (auto it = l.begin(); it != l.end(); it++)
	{
		s += to_string(*it);

		if (next(it) != l.end())
		{
			s += " ";
		}
	}
	return s + "\n";
}

string calculate(string s)
{
	vector<double> numbers = parseNumbers(s);
	vector<string> operations = parseOperations(s);
	vector<string> tempOperations = operations;
	vector<string> bidmas = { "/", "x", "+", "-" };

	cout << vectorToString(numbers);
	cout << vectorToString(operations);

	int counter;
	double tempNum = 0;

	for (auto i = bidmas.begin(); i != bidmas.end(); i++)
	{
		for (int j = 0; j < operations.size(); j++)
		{
			if (*i == operations.at(j))
			{
				if (*i == "/")
				{
					tempNum = numbers.at(j) / numbers.at(j + 1);	
				}
				else if (*i == "x")
				{
					tempNum = numbers.at(j) * numbers.at(j + 1);
				}
				else if (*i == "+")
				{
					tempNum = numbers.at(j) + numbers.at(j + 1);
				}
				else if (*i == "-")
				{
					tempNum = numbers.at(j) - numbers.at(j + 1);
				}

				if (operations.size() != 1)
				{
					tempOperations = operations;
					tempOperations.erase(tempOperations.begin() + j);
				}
				numbers.erase(numbers.begin() + j + 1);
				numbers.at(j) = tempNum;
			}
		}
		operations = tempOperations;
	}
	return to_string(numbers[0]);
}

//void testFunction();

int main()
{
	string calculation = "100x20="; // 30
	cout << calculate(calculation) << "\n";

}





	/*string totalStr = "10.000000";
	int i;
	string totalStrTemp = totalStr;

	for (i = totalStr.length() - 1; i > -1; i--)
	{
		cout << totalStrTemp.substr(i, i + 1) << "loop\n";
		if (totalStrTemp.substr(i, i + 1) == "0")
		{
			totalStrTemp = totalStrTemp.substr(0, i);
		}
		else
		{
			if (totalStrTemp.substr(totalStrTemp.length() - 1, totalStrTemp.length()) == ".")
			{
				totalStrTemp = totalStrTemp.substr(0, totalStrTemp.length() - 1);
			}
			break;
		}
	}
	cout << totalStrTemp;*/

	/*
	cout << "Hi " << number << " " << text << " " << trueOrFalse << "\n";

	cin >> input;

	if (input == "test")
	{
		cout << "Yes\n";
	}
	else
	{
		cout << "No\n";
	}
	cout << s << " " << sizeof(s) << "\n";
	cout << l << " " << sizeof(l) << "\n";
	cout << d << " " << sizeof(d) << "\n";
	cout << dl << " " << sizeof(dl) << "\n";
	cout << f << " " << sizeof(f) << "\n";

	p.age = 5;
	p.name = "Johnny";
	p.phone = "07...";

	cout << p.age << " " << p.name << " " << p.phone << "\n";

	testFunction();
}

void testFunction()
{
	cout << "it works";
	return;
}

list<string> parseNumbers(string s)
{
	int cutoff = 0;
	list<string> numbers;
	int i;
	string temp;

	for (i = 0; i < s.length(); i++)
	{
		temp = s.substr(i,1);

		if (temp == "x" || temp == "/" || temp == "+" || temp == "-" || temp == "=")
		{
			numbers.push_back(s.substr(cutoff, i-cutoff));
			cutoff = i + 1;
		}
	}
	return numbers;
}

list<string> parseOperations(string s)
{
	list<string> operations;
	int i;
	string temp;

	for (i = 0; i < s.length(); i++)
	{
		temp = s.substr(i, 1);

		if (temp == "x" || temp == "/" || temp == "+" || temp == "-")
		{
			operations.push_back(temp);
		}
	}
	return operations;
}

string listToString(list<string> l)
{
	string s;

	for (auto it = l.begin(); it != l.end(); it++)
	{
		s += *it;

		if (next(it) != l.end())
		{
			s += " ";
		}
	}
	return s;
}

void calculate(string s)
{
	list<string> numbers = parseNumbers(s);
	list<string> operations = parseOperations(s);
	list<string> bidmas = { "/", "x", "+", "s" };

	int counter;

	for (auto i = bidmas.begin(); i != bidmas.end(); i++)
	{
		counter = 0;

		for (auto j = operations.begin(); j != operations.end(); j++)
		{
			if (*i == *j)
			{
				list<string>::iterator it = operations.begin();
				advance(it, counter);

				cout << *it <<
			}
			counter++;
		}
	}
}*/