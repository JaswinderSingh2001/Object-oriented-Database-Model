#ifndef COURSE_HPP
#define COURSE_HPP
class Course
{
public:
    string Course_Name;
    string Course_Number;
    int Course_Credits;
    int Course_Semester;
    Course()
    {
        Course_Name = "";
        Course_Number = "";
        Course_Credits = -1;
        Course_Semester = -1;
    }
};
#endif