#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const char *filenameIn = "students.csv";
const char *filenameOut = "rating.csv";

class Student {
private:
	string surname;
	double average;
	bool contract;

	static vector<string> split(string s, string d) {
		vector<string> ret;
		size_t pos = 0;
		string token;
		while ((pos = s.find(d)) != string::npos) {
			token = s.substr(0, pos);
			ret.push_back(token);
			s.erase(0, pos + d.length());
		}
		ret.push_back(s);
		return ret;
	}

public:
	double getAverage() {
		return average;
	}

	bool isContract() {
		return contract;
	}

	bool operator<(Student& s) {
		return average > s.average;
	}

	friend istream& operator>>(istream&, Student&);
	friend ostream& operator<<(ostream&, Student&);
};

istream& operator>>(istream& stream, Student& s) {
	string line;
	getline(stream, line);
	vector<string> args = Student::split(line, ",");

	s.surname = args[0];

	const int n = 5;

	double a = 0.0;
	for (int i = 0; i < n; i++) {
		a += stod(args[i + 1]);
	}

	a /= 5;
	s.average = a;

	s.contract = (args[n + 1] == "TRUE");

	return stream;
}

ostream& operator<<(ostream& stream, Student& s) {
	stream << s.surname << ",";
	stream << fixed;
	stream << setprecision(3);
	stream << s.getAverage();
	return stream;
}

class GrantCalculator {
private:
	vector<Student> students;

public:
	void readStudents() {
		ifstream fi(filenameIn);

		int n;
		fi >> n;
		fi.ignore();

		for (int i = 0; i < n; i++) {
			Student t;
			fi >> t;
			if (!t.isContract()) {
				students.push_back(t);
			}
		}

		fi.close();
	}

	void writeRating() {
		ofstream fo(filenameOut);

		sort(students.begin(), students.end());
		int n = students.size() * 0.4;

		for (int i = 0; i < n; i++) {
			fo << students[i] << endl;
		}
		fo << "min," << students[n - 1].getAverage() << endl;

		fo.close();
	}
};

int main() {
	cout << "hello world" << endl;

	GrantCalculator gc;
	gc.readStudents();
	gc.writeRating();

	cout << "Done." << endl;

	return 0;
}
