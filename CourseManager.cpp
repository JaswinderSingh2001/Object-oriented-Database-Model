#include <bits/stdc++.h>
using namespace std;
#include "Course.hpp"
class CourseManager : public Course
{
public:
    vector<Course*> data;
    map<string , int> CourseNumber;
    int datacounter = 0;
    void add(string name , string number , int credit , int semester)
    {
        ofstream fout;
        fout.open("stdout.txt",  ios:: app);
        if(fout)
        {
            if(CourseNumber.find(number) != CourseNumber.end())
            {
                fout<<"Problem: A course with number "<<number<<" already exists\n";
                fout.close();
                return;
            } else{
                Course* NewCourse = new Course();
                NewCourse->Course_Name = name;
                NewCourse->Course_Number= number;
                NewCourse->Course_Credits = credit;
                NewCourse->Course_Semester = semester;
                data.push_back(NewCourse);
                CourseNumber[number]= datacounter;
                datacounter++;
                fout<<"Added course: [Name="<<name<<", Number="<<number<<", Credits="<<credit<<", Semester="<<semester<<"]\n";
                fout.close();
                ofstream fout;
                fout.open("course-content.bin" , ios::app | ios::binary);
                fout<<"[Name="<<name<<", Number="<<number<<", Credits="<<credit<<", Semester="<<semester<<"]\n";
                fout.close();
            }

        } else{
            cout<<"Error in opening file \n";
            return;
        }
    }
    void del(string name , string number , int credit , int semester)
    {
        ofstream fout;
        fout.open("stdout.txt",  ios:: app);
        if(fout)
        {
            if(CourseNumber.find(number) == CourseNumber.end())
            {
                fout<<"Problem: No matching course found with number "<<number<<"\n" ;
                fout.close();
                return;
            } else {
                int idx = CourseNumber[number];
                data[idx]->Course_Semester = -1;
                data[idx]->Course_Credits = -1;
                data[idx]->Course_Number = "";
                data[idx]->Course_Name = "";
                CourseNumber.erase(number);
                fout << "Deleted course: [Name=" << name << ", Number=" << number << ", Credits=" << credit
                     << ", Semester=" << semester << "]\n";
                fout.close();
                ifstream fin("course-content.bin" , ios:: binary);
                ofstream fout;
                fout.open("temp.bin", ios::out | ios:: binary);
                string line;
                while(getline(fin , line))
                {
                    if(line.find(number) != string::npos)
                    {
                        continue;
                    } else{
                        fout<<line<<"\n";
                    }
                }
                fout.close();
                fin.close();
                remove("course-content.bin");
                rename("temp.bin", "course-content.bin");
            }
        }
        else{
            cout<<"Error in opening file \n";
        }
    }
    void mod(string name , string number , int credit , int semester) {
        ofstream fout;
        fout.open("stdout.txt", ios::app);
        if (fout) {
            if (CourseNumber.find(number) == CourseNumber.end()) {
                fout << "Problem: No matching course found with number " << number << "\n";
                return;
            } else {
                int idx = CourseNumber[number];
                data[idx]->Course_Semester = semester;
                data[idx]->Course_Credits = credit;
                data[idx]->Course_Number = number;
                data[idx]->Course_Name = name;
                fout << "Modified course: [Name=" << name << ", Number=" << number << ", Credits=" << credit
                     << ", Semester=" << semester << "]\n";
                fout.close();
                ifstream fin("course-content.bin" , ios:: binary);
                ofstream fout;
                fout.open("temp.bin", ios::out | ios:: binary);
                string line;
                while(getline(fin , line))
                {

                    if(line.find(number) != string::npos)
                    {
                        fout<<"[Name="<<name<<", Number="<<number<<", Credits="<<credit<<", Semester="<<semester<<"]\n";

                    } else{
                        fout<<line<<"\n";
                    }
                }
                fout.close();
                fin.close();
                remove("course-content.bin");
                rename("temp.bin", "course-content.bin");

            }
        } else {
            cout << "Error in opening file \n";
        }
    }
    void listby(string prop)
    {
        ofstream fout;
        fout.open("stdout.txt",  ios:: app);
        if(fout)
        {
            if(prop == "name" || prop == "number" || prop == "credits" || prop == "semester")
            {
                vector<Course> temp;
                int datasize = data.size();
                Course val;
                for(int i = 0 ; i < datasize ; i++)
                {

                    if(data[i]->Course_Semester != -1)
                    {
                        val.Course_Semester = (data[i]->Course_Semester);
                        val.Course_Name = (data[i]->Course_Name);
                        val.Course_Credits = (data[i]->Course_Credits);
                        val.Course_Number = (data[i]->Course_Number);
                        temp.push_back(val);
                    }
                }
                if(prop == "name")
                {
                    sort( temp.begin( ), temp.end( ), [ ]( const Course& lhs, const Course& rhs )
                    {
                        return lhs.Course_Name < rhs.Course_Name;
                    });
                    fout<<"Course list (sorted by name):\n";
                }
                else if(prop == "number")
                {
                    sort( temp.begin( ), temp.end( ), [ ]( const Course& lhs, const Course& rhs )
                    {
                        return lhs.Course_Number < rhs.Course_Number;
                    });
                    fout<<"Course list (sorted by number):\n";
                }
                else if(prop == "credits")
                {
                    sort( temp.begin( ), temp.end( ), [ ]( const Course& lhs, const Course& rhs )
                    {
                        return lhs.Course_Credits < rhs.Course_Credits;
                    });
                    fout<<"Course list (sorted by credit):\n";
                }
                else if(prop == "semester")
                {
                    sort( temp.begin( ), temp.end( ), [ ]( const Course& lhs, const Course& rhs )
                    {
                        return lhs.Course_Semester < rhs.Course_Semester;
                    });
                    fout<<"Course list (sorted by semester):\n";
                }
                for(auto value : temp)
                {
                    fout << "[Name=" << value.Course_Name << ", Number=" << value.Course_Number << ", Credits=" << value.Course_Credits << ", Semester=" << value.Course_Semester << "]\n";
                }
                temp.clear();
                fout.close();
            }
            else
            {
                fout<<"Problem: Invalid property "<<prop <<" supplied for sorting the courses\n";
                fout.close();
            }
        }
        else{
            cout<<"Error in opening file \n";
            return;
        }
    }
    ~ CourseManager()
    {
        data.clear();
        CourseNumber.clear();
    }


};
void PrintBinaryFile(void)
{
    ifstream fin("course-content.bin" , ios:: binary);
    ofstream fout;
    fout.open("binarytotext.txt", ios::out );
    string line;
    while(getline(fin , line))
    {
        
        fout<<line<<"\n";
        
    }
    fout.close();
    fin.close();
}
int main()
{
    CourseManager admin;
    fstream fout;
    fout.open("stdout.txt", ios::out | ios::trunc);
    fout.close();
    fout.open("course-content.bin", ios::out | ios::trunc | ios::binary);
    fout.close();
    ifstream fin;
    fin.open("operations.txt");
    string line;
    while (getline (fin,line)) {
        int n2 = line.size();
        if(n2 == 0)
            continue;
        if(n2 >= 3 && line[0] == 'a' && line[1] == 'd' && line[2] == 'd')
        {
            string name = "";
            int i , len = line.size();
            for(i = 4 ; i < len && line[i] != '|' ; i++ )
            {
                name.push_back(line[i]);
            }
            i++;
            if((int)name.size() == 0)
            {
                ofstream fout;
                fout.open("stdout.txt",  ios:: app);
                fout<<"Problem : Enter a valid name\n";
                continue;
            }
            string number = "";
            for( ; i < len && line[i] != '|' ; i++)
            {
                number.push_back(line[i]);
            }
            if((int)number.size() == 0)
            {
                ofstream fout;
                fout.open("stdout.txt",  ios:: app);
                fout<<"Problem : Enter a valid Number\n";
                continue;
            }
            i++;
            string cred = "";
            for( ; i<len && line[i]!= '|' ; i++)
            {
                cred.push_back(line[i]);
            }
            if((int)cred.size() == 0)
            {
                ofstream fout;
                fout.open("stdout.txt",  ios:: app);
                fout<<"Problem : Enter a valid credit number\n";
                continue;
            }
            i++;
            int credit = stoi(cred);
            string sem = "";
            for( ; i < len ; i++)
            {
                sem.push_back(line[i]);
            }
            if((int)sem.size() == 0)
            {
                ofstream fout;
                fout.open("stdout.txt",  ios:: app);
                fout<<"Problem : Enter a valid semester number\n";
                continue;
            }
            int semester=  stoi(sem);
            admin.add(name , number , credit , semester);

        }
        else if (n2 >= 3 && line[0] == 'm' && line[1] == 'o' && line[2] == 'd'){
            string name = "";
            int i , len = line.size();
            for(i = 4 ; i < len && line[i] != '|' ; i++ )
            {
                name.push_back(line[i]);
            }
            if((int)name.size() == 0)
            {
                ofstream fout;
                fout.open("stdout.txt",  ios:: app);
                fout<<"Problem : Enter a valid Name\n";
                continue;
            }
            i++;
            string number = "";
            for( ; i < len && line[i] != '|' ; i++)
            {
                number.push_back(line[i]);
            }
            if((int)number.size() == 0)
            {
                ofstream fout;
                fout.open("stdout.txt",  ios:: app);
                fout<<"Problem : Enter a valid Number\n";
                continue;
            }
            i++;
            string cred = "";
            for( ; i<len && line[i]!= '|' ; i++)
            {
                cred.push_back(line[i]);
            }
            if((int)cred.size() == 0)
            {
                ofstream fout;
                fout.open("stdout.txt",  ios:: app);
                fout<<"Problem : Enter a valid credit number\n";
                continue;
            }
            i++;
            int credit = stoi(cred);
            string sem = "";
            for( ; i < len ; i++)
            {
                sem.push_back(line[i]);
            }
            if((int)sem.size() == 0)
            {
                ofstream fout;
                fout.open("stdout.txt",  ios:: app);
                fout<<"Problem : Enter a valid Semester number\n";
                continue;
            }
            int semester=  stoi(sem);
            admin.mod(name , number , credit , semester);

        }
        else if (n2 >= 3 && line[0] == 'd' && line[1] == 'e' && line[2] == 'l'){
            string name = "";
            int i , len = line.size();
            for(i = 4 ; i < len && line[i] != '|' ; i++ )
            {
                name.push_back(line[i]);
            }
            if((int)name.size() == 0)
            {
                ofstream fout;
                fout.open("stdout.txt",  ios:: app);
                fout<<"Problem : Enter a valid Name\n";
                continue;
            }
            i++;
            string number = "";
            for( ; i < len && line[i] != '|' ; i++)
            {
                number.push_back(line[i]);
            }
             if((int)number.size() == 0)
            {
                ofstream fout;
                fout.open("stdout.txt",  ios:: app);
                fout<<"Problem : Enter a valid Number\n";
                continue;
            }
            i++;
            string cred = "";
            for( ; i<len && line[i]!= '|' ; i++)
            {
                cred.push_back(line[i]);
            }
            if((int)cred.size() == 0)
            {
                ofstream fout;
                fout.open("stdout.txt",  ios:: app);
                fout<<"Problem : Enter a valid credit number\n";
                continue;
            }
            int credit = stoi(cred);
            i++;
            string sem = "";
            for( ; i < len   ; i++)
            {
                sem.push_back(line[i]);
            }
            if((int)sem.size() == 0)
            {
                ofstream fout;
                fout.open("stdout.txt",  ios:: app);
                fout<<"Problem : Enter a valid Semester number\n";
                continue;
            }
            int semester=  stoi(sem);
            admin.del(name , number , credit , semester);
        }
        else if (n2 >= 4 && line[0] == 'l' && line[1] == 'i' && line[2] == 's' && line[3] == 't')
        {
            int len = line.size();
            if(len <= 12)
            {
                ofstream fout;
                fout.open("stdout.txt",  ios:: app);
                if(fout)
                    fout<<"Problem: A property for sorting the courses must be supplied\n";
                else
                {
                    cout<<"Error in opening file \n";
                }
                continue;

            }
            string prop = "";
            for(int i = len-1; i>=0 && line[i]!= ' ' ; i--)
            {
                prop.push_back(line[i]);
            }
            reverse(prop.begin() , prop.end());
            admin.listby(prop);
        }
        else
        {
            ofstream fout;
            fout.open("stdout.txt",  ios:: app);
            fout<<"Command "<<line <<" Not Recognised\n";
            fout.close();
        }
    }
    // For printing contenets of binary file to a txt file(creates a txt file)
    PrintBinaryFile();
    return 0;

}

