# Object-oriented-Database-Model
## Title: ##
Object Oriented Database Model

A simple Course Manager which can perform CRUD (Create, Read, Update, Delete) and Sort operations on the course-related data at the institute.Staff using your tool can,

a. Add a new course

b. Modify an existing course

c. Delete an existing course

d. View the list of all existing courses

The list of the courses, can be sorted in more ways than one, before being shown. There are two classes to meet these requirements. The Course class holds four pieces of information:
1. Course Name
2. Course Number [must be unique, i.e., only one course with a particular course number is allowed]
3. Course Credits
4. Course Semester (the semester in which the course is offered)
Any of these fields can be used to sort the list of the courses.

The class called CourseManager performs the aforementioned operations. A file called course-data.bin is used for storing the information.
## Sample Input/Output: ##
A file called operations.txt contains the sample operations. After running your code, two files are produced, called stdout.txt and course-data.bin containing the output of the program and the final list of courses.Example is in the repository. 
Format of the contents of operations.txt:

[add, delete and modify courses]: < op-code > < name >|< number >|< credits >|< semester >

[sort and list courses]: list all by < course property >

List of op-codes: add, del, mod

List of course properties: name, number, credits, semester

For the del operation, all properties other than number are ignored.
