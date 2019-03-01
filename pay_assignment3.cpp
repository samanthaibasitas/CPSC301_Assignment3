#include "person_assignment3.cpp"
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std; 
void readData(vector<Person> &employees); 
void getCompanies(vector<string> &cNames, vector<Person> &employees); 
void printHighestPaid(vector<Person> &employees); 
void separateAndSave(vector<string> &cNames, vector<Person> &employees); 
void readData(vector<Person> &employees)
{
	string fName; 
	string lName; 
	string cName; 
	int id; 
	float pay; 
	float hours; 
	string line; 
	Person person; 
	ifstream file("input_assignment3.txt"); 
	if(file.is_open())
	{
		while(file >> fName >> lName >> id >> cName >> hours >> pay) 
		{
			person.setFirstName(fName); 
			person.setLastName(lName); 
			person.setEmployeeId(id); 
			person.setCompanyName(cName); 
			person.setHoursWorked(hours); 
			person.setPayRate(pay);
			employees.push_back(person); 
		}
	}
	file.close(); 
}
void getCompanies(vector<string> &cNames, vector<Person> &employees)
{
	string temp; 
	for(int i = 0; i < employees.size(); i++) 
	{
			temp = employees.at(i).getCompanyName(); 
			if(count(cNames.begin(), cNames.end(), temp) == 0)
				cNames.push_back(temp); 
	}
}
void printHighestPaid(vector<Person> &employees)
{
	float highest; 
	float compare; 
	int index; 
	string name; 
	int id; 
	string cName; 
	for(int i = 0; i < employees.size(); i++)
	{
		compare = employees.at(i).totalPay(); 
		if(compare > highest)
		{
			highest = compare; 
			index = i; 
		}
	}
	name = employees.at(index).fullName(); 
	id = employees.at(index).getEmployeeId(); 
	cName = employees.at(index).getCompanyName(); 
	cout << "Highest Paid: " << name << endl; 
	cout << "Employee ID: " << id << endl; 
	cout << "Employer: " << cName << endl; 
	cout << setprecision(2) << fixed; 
	cout << "Total Pay: $" << employees.at(index).totalPay() << endl; 
}
void separateAndSave(vector<string> &cNames, vector<Person> &employees)
{
	cout << setprecision(2) << fixed; 
	string compare; 
	string employeeCompany; 
	string fName;
	string lName; 
	int id; 
	string coName; 
	float employeeTotal; 
	float companyTotal; 
	for(int i = 0; i < cNames.size(); i++) 
	{
		companyTotal = 0.0; 
		compare = cNames.at(i); 
		ofstream file(compare + ".txt"); 
		file.close(); 
		file << "-----------------------------------------" << endl;
		file << setprecision(2) << fixed; 
		for(int j = 0; j < employees.size(); j++) 
		{
			ofstream file(compare + ".txt", std::ofstream::out | std::ofstream::app); 
			employeeCompany = employees.at(j).getCompanyName(); 
			if(compare == employeeCompany)
			{
				if(file.is_open())
				{
					fName = employees.at(j).getFirstName(); 
					lName = employees.at(j).getLastName(); 
					id = employees.at(j).getEmployeeId(); 
					coName = employees.at(j).getCompanyName(); 
					employeeTotal = employees.at(j).getPayRate() * employees.at(j).getHoursWorked(); 
					file << setprecision(2) << fixed; 
					file << setw(10) << left << fName << setw(7) << left << lName << setw(4) << right << id << " " << setw(cNames[i].size()) << coName << " $" << employeeTotal << endl;  
					companyTotal += employeeTotal; 
				} 
			}
			if(j == (employees.size() - 1))
			{
				file << setprecision(2) << fixed; 
				file << "Total\t" << "$" << companyTotal << endl; 
			}
		}
		file.close(); 
	}
}
int main()
{
	vector<string> companyNames; 
	vector<Person> people; 
	readData(people); 
	getCompanies(companyNames, people); 
	printHighestPaid(people); 
	separateAndSave(companyNames, people); 
	system("PAUSE"); 
	return 0; 
}
