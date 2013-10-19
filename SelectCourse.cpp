

#include <iostream>
#include <iomanip>
#include <string>

#define IS_NULL(p, ret)\
    if(p == NULL) return ret;
using namespace std;

// Data struct
enum DataType;
class ILink;
class Link;
class Student;
class Course;
class SelectedCourse;

// Forehead declaration.
void TestSelectCourse();
int main()
{
    TestSelectCourse();
    return 0;
}

enum DataType
{
    DataTypeStudent,
    DataTypeCourse,
    DataTypeSelectedCourse
};

class ILink
{
public:
    virtual Link* nextCourse() const= 0;
    virtual Link* nextStudent() const= 0;
    virtual DataType getType() const= 0;
    virtual string getName() const= 0;
};

class Link : ILink
{
public:
    Link(Link* nextCourse, Link* nextStudent, DataType nodeType, const string& name);
    virtual Link* nextCourse() const;
    virtual Link* nextStudent()const;
    virtual string getName()const;
    virtual DataType getType()const;
private:
    Link();
    Link(const Link& rhs);
    Link& operator = (const Link& rhs);
    Link* nextCourse_;
    Link* nextStudent_;
    DataType type_;
    string name_;
};

class Student : virtual public Link
{
public:
    Student(Link* nc, string& name);
private:
    virtual Link* nextStudent(){return NULL;}
};

class Course : virtual public Link
{
public:
    Course(Link* ns, string& name);
private:
    virtual Link* nextCourse(){return NULL;}
};

class SelectedCourse : virtual public Link
{
public:
    SelectedCourse(Link* lc, Link* ls);
private:
    virtual string getName() const{return "";}
};

// Forehead function decalarition.
void GetSelectedCourse(const Student* s);
void GetSignInStudent(const Course* c);
Student* GetStudentFromSelectedCourse(const Link* sc);
Course* GetCourseFromSelectedCourse(const Link* sc);

void TestSelectCourse()
{

}
void GetSelectedCourse(const Student* s)
{
    Link* tmp = s->nextCourse();
    const DataType t = DataTypeSelectedCourse;
    cout << s->getName() << " Selected Course: " << endl;
    while((void*)tmp != (void*)s)
    {
        if(tmp->getType() != t) continue;
        cout << GetCourseFromSelectedCourse(tmp)->getName() << endl;
    }
}
void GetSignInStudent(const Course* c)
{
    Link* tmp = c->nextStudent();
    const DataType t = DataTypeSelectedCourse;
    cout << c->getName() << " is Selected By: " << endl;
    while((void*)tmp != (void*)c)
    {
        if(tmp->getType() != t) continue;
        cout << GetStudentFromSelectedCourse(tmp)->getName() << endl;
    }
}

Student* GetStudentFromSelectedCourse(const Link* sc)
{
    Link* tmp = sc->nextStudent();
    while(tmp->getType() == DataTypeSelectedCourse)
    {
        tmp = tmp->nextStudent();
    }
    return dynamic_cast<Student*>(tmp);
}

Course* GetCourseFromSelectedCourse(const Link* sc)
{
    Link* tmp = sc->nextCourse();
    while(tmp->getType() == DataTypeSelectedCourse) 
    {
        tmp = tmp->nextCourse();
    }
    return dynamic_cast<Course*>(tmp);
}

Link::Link(Link* lc, Link* ls, DataType t, const string& name):
    nextCourse_(lc),
    nextStudent_(ls),
    type_(t),
    name_(name)
{

}

DataType Link::getType()const
{
    return type_;
}

string Link::getName()const
{
    return name_;
}

Link* Link::nextCourse()const
{
    return nextCourse_;
}

Link* Link::nextStudent()const
{
    return nextStudent_;
}

Course::Course(Link* ns, string& name):
Link(NULL, ns, DataTypeCourse, name)
{

}

Student::Student(Link* nc, string& name):
    Link(nc, NULL, DataTypeStudent, name)
{

}

SelectedCourse::SelectedCourse(Link* lc, Link* ls):
    Link(lc, ls, DataTypeSelectedCourse, "")
{

}
