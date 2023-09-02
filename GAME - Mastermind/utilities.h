#pragma once
#include "std_lib_facilities.h"

int incrementByValueNumTimes(int startValue, int increment, int numTimes);
void incrementByValueNumTimesRef(int& startValue, int increment, int numTimes);

void swapNumbers(int& a, int& b);

string randomizeString(int n, char lower, char upper);
string readInputToString(unsigned int n, char lower, char upper);
int countChar(string str, char ch);

struct Student{
    string name;
    string studyProgram;
    int age;
};

void printStudent(const Student& student);
bool isInProgram(const Student& student, const string& program);
