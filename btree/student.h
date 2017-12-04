#ifndef STUDENT_H
#define STUDENT_H

#include<string>

using namespace std;

class student{
public:
    float num;
    string name;
    int grade;
    string department;
    string mailbox;
    student(float a,string b, int c, string d,string g)
    {
        num  =a;
        name = b;
        grade = c;
        department = d;
        mailbox = g;
    }
    student()
    {
        num  =0;
        name = "0";
        grade = 0;
        department = "0";
        mailbox = "0";
    }
};

#endif // STUDENT_H
