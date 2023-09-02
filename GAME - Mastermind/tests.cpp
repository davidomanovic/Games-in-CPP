#include "std_lib_facilities.h"
#include "tests.h"

void testCallByValue()
{
	int v0 = 5;
	int increment = 2;
	int iterations = 10;
	int result = incrementByValueNumTimes(v0, increment, iterations);
	cout << "v0: " << v0 << " increment: " << increment
		 << " iterations: " << iterations << " result: " << result << '\n';
}

void testCallByReference()
{
	int v0 = 5;
	int increment = 2;
	int iterations = 10;
	incrementByValueNumTimesRef(v0, increment, iterations);
	cout << "v0: " << v0 << " increment: " << increment
		 << " iterations: " << iterations << '\n';
}

void testStudentStruct(){
	Student s1;
	s1.name = "Bob";
	s1.studyProgram = "Math";
	s1.age = 20;
	printStudent(s1);

	// Alternativ initialisering av medlemsvariablene
	Student s2 = {"Alice", "Physics", 21};
	printStudent(s2);

	cout << boolalpha << s1.name << " is in Math? " << isInProgram(s1, "Math") << '\n'
		 << s2.name << " is in Math? " << isInProgram(s2, "Math") << '\n';
}
// 2e) utilities.h blir inkludert flere ganger. Burde skrive #pragma once i h-filene for å hindre dette

void testString()
{
	static constexpr int numGrades = 8;
	string grades{randomizeString(numGrades, 'A', 'F')};
	cout << "Random grades: " << grades << '\n';

	// h)
	vector<int> gradeCount(6);
	int score = 0;
	for (int i = 0; i < 6; ++i) {
		gradeCount[i] = countChar(grades, 'A' + i);
		score += (5 - i) * gradeCount[i];
	}

	double gpa = score / double{numGrades}; // gpa = grade point average
	cout << "Grade point average = " << fixed << setprecision(1) << gpa << '\n';
}
