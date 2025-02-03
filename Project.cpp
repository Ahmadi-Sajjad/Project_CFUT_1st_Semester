#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <iomanip>
using namespace std;
namespace fs = filesystem;

int n;
string computerID[100];
string industrialID[100];
string electricalID[100];
string mechanicalID[100];

struct studentProperty
{
    string fullName;
    string id;
    string major;
};

struct studentMark
{
    string subject;
    string unit;
    double mark;
};

void readline(string personProperty[4])
{
    studentProperty person;
    cout << "Enter Student's Name: ";
    cin >> person.fullName;
    cout << "Enter Student's ID: ";
    cin >> person.id;
    cout << "Entr Student's Major: ";
    cin >> person.major;
    personProperty[0] = person.fullName;
    personProperty[1] = person.id;
    personProperty[2] = person.major;
}

void marks_input(string personMark[][3], string personProperty[4])
{
    studentMark person;
    double average = 0;
    cout << "Enter the subject number: ";
    while (cin >> n){
        if (n > 10 && n < 1)
        {
            cerr << "Invalid number, Please Enter a valid number between '1' to '10'.";
            continue;
        }
        else
            break;
    }
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the subject: ";
        cin >> person.subject;
        cout << "Enter the unit: ";
        cin >> person.unit;
        cout << "Enter the mark: ";
        cin >> person.mark;
        personMark[i][0] = person.subject;
        personMark[i][1] = person.unit;
        personMark[i][2] = to_string(person.mark);
        average += person.mark;
    }
    average /= n;
    string avgStr = to_string(average);
    size_t decimalPos = avgStr.find('.');
    if (decimalPos != string::npos) {
        avgStr = avgStr.substr(0, decimalPos + 3);
    }
    personProperty[3] = avgStr;
}

int getMajorCode(const string &major)
{
    if (major == "Computer") return 0;
    if (major == "Industrial") return 1;
    if (major == "Electrical") return 2;
    if (major == "Mechanical") return 3;
}

void writeToFile(fstream &file, const string &filename, const string &data) 
{
    file.open(filename, ios::app);
    if (file.is_open()) 
    {
        file << data << endl;
        file.close();
    } 
    else 
    {
        cerr << "Error opening " << filename << "!\n";
    }
}

void sort_store(string students[][4], int count, fstream &Computer_list, fstream &Industrial_list, fstream &Electrical_list, fstream &Mechanical_list) 
{
    for (int i = 0; i < count - 1; i++) 
    {
        for (int j = 0; j < count - i - 1; j++) 
        {
            if (stod(students[j][3]) < stod(students[j + 1][3])) 
            {
                for (int k = 0; k < 4; k++) 
                {
                    swap(students[j][k], students[j + 1][k]);
                }
            }
        }
    }

    for (int i = 0; i < count; i++) 
    {
        string data = students[i][0] + " " + students[i][1] + " " + students[i][2] + " " + students[i][3];
        switch (getMajorCode(students[i][2])) 
        {
            case 0: writeToFile(Computer_list, "Computer_list.txt", data); break;
            case 1: writeToFile(Industrial_list, "Industrial_list.txt", data); break;
            case 2: writeToFile(Electrical_list, "Electrical_list.txt", data); break;
            case 3: writeToFile(Mechanical_list, "Mechanical_list.txt", data); break;
        }
    }
}

void reportCardMaker(string student[][4],string personMark[][3], int rsc, int &n)
{
    switch (getMajorCode(student[rsc-1][2]))
    {
        case 0:
        {
            fstream computer;
            computer.open(student[rsc-1][1]+".txt", ios::app);
            if (computer.is_open())
            {
                computer << student[rsc-1][0] << "\t" << student[rsc-1][1] << "\n" << student[rsc-1][2];
                for (int i = 0; i < n; i++)
                    computer << personMark[i][0] << personMark[i][1] << personMark[i][2] << "\n";
                computer.close();
            }
            computerID[rsc-1] = student[rsc-1][1];
            break;
        }
        case 1:
        {
            fstream industrial;
            industrial.open(student[rsc-1][1]+".txt", ios::app);
            if (industrial.is_open())
            {
                industrial << student[rsc-1][0] << student[rsc-1][1] << student[rsc-1][2] << student[rsc-1][3] << "\n";
                for (int i = 0; i < n; i++)
                    industrial << personMark[i][0] << personMark[i][1] << personMark[i][2] << "\n";
                industrial.close();
            }
            industrialID[rsc-1] = student[rsc-1][1];
            break;
        }
        case 2:
        {
            fstream electrical;
            electrical.open(student[rsc-1][1]+".txt", ios::app);
            if (electrical.is_open())
            {
                electrical << student[rsc-1][0] << student[rsc-1][1] << student[rsc-1][2] << student[rsc-1][3] << "\n";
                for (int i = 0; i < n; i++)
                    electrical << personMark[i][0] << personMark[i][1] << personMark[i][2] << "\n";
                electrical.close();
            }
            electricalID[rsc-1] = student[rsc-1][1];
            break;
        }
        case 3:
        {
            fstream mechanical;
            mechanical.open(student[rsc-1][1]+".txt", ios::app);
            if (mechanical.is_open())
            {
                mechanical << student[rsc-1][0] << student[rsc-1][1] << student[rsc-1][2] << student[rsc-1][3] << "\n";
                for (int i = 0; i < n; i++)
                    mechanical << personMark[i][0] << personMark[i][1] << personMark[i][2] << "\n";
                mechanical.close();
            }
            mechanicalID[rsc-1] = student[rsc-1][1];
            break;
        }
    }
}

int main()
{

    const int MAX_STUDENTS = 100;
    string students[MAX_STUDENTS][4]; // آرایه برای ذخیره موقت دانشجو ها به سبک هادی
    int Registered_student_Count = 0; // تعداد دانش‌آموزان ثبت‌ شده
    fstream Computer_list;
    fstream Industrial_list;
    fstream Electrical_list;
    fstream Mechanical_list;

    while (true)
    {
        cout << "1. Add new student\n"
             << "2. Students list\n"
             << "3. Student grades\n"
             << "4. Report card\n"
             << "5. Exit\n"
             << "Enter your choice: ";

        int input_number;
        cin >> input_number;

        switch (input_number)
        {
            case 1: {
                        if (Registered_student_Count >= MAX_STUDENTS)
                        {
                            cout << "Maximum number of students reached!\n";
                            break;
                        }

                        readline(students[Registered_student_Count]);

                        cout << "Do you want to add his/her grades? (y/n): ";
                        char yes_no;
                        cin >> yes_no;

                        if (yes_no == 'y' || yes_no == 'Y')
                        {
                            string student_grades[10][3]; // فرض کردیم حداکثر ۱۰ درس وجود دارد
                            marks_input(student_grades, students[Registered_student_Count]);
                            Registered_student_Count++;
                            sort_store(students,Registered_student_Count,Computer_list,Industrial_list,Electrical_list,Mechanical_list);
                            reportCardMaker(students,student_grades,Registered_student_Count,n);
                            n = 0;
                        }
                        else if (yes_no == 'n' || yes_no == 'N')
                        {
                            Registered_student_Count++;
                            students[Registered_student_Count][3] = "0"; // اگر نمره‌ای وارد نشد، معدل ۰
                            sort_store(students,Registered_student_Count,Computer_list,Industrial_list,Electrical_list,Mechanical_list);
                        }
                        else
                        {
                            cout << "Invalid input. Please enter 'y' or 'n'.\n";
                        }
                        
                        break;
                    }

            case 2: {
                        int filter_input;
                        cout << "Press '1' to show all " << "\n"
                             << "Press '2' to filter by Computer Engineering" << "\t"
                             << "Press '3' to filter by Industrial Engineering" << "\n"
                             << "Press '4' to filter by Electrical Engineering" << "\t"
                             << "Press '5' to filter by Mechanical Engineering" << "\n"
                             << "press '6' to menu and main" << "\n";
                             while (cin >> filter_input)
                             {
                                if (filter_input > 6 || filter_input < 1)
                                    cout << "invalid input, Please enter a number betwen '1' to '6'." << "\n" << "Enter your choice: ";
                                else
                                    break;
                             }

                             if (filter_input == 6) break;

                             switch (filter_input)
                             {
                                case 1: {
                                            Computer_list.open("Computer_list.txt", ios::in);
                                                {
                                                    if(Computer_list.is_open())
                                                    {
                                                        string output_Computer;
                                                        while (getline (Computer_list, output_Computer))
                                                        {
                                                            cout << output_Computer << "\n";
                                                        }
                                                        Computer_list.close();
                                                    }
                                                }

                                            Industrial_list.open("Industrial_list.txt", ios::in);
                                                {
                                                    if(Industrial_list.is_open())
                                                    {
                                                        string output_Industrial;
                                                        while (getline(Industrial_list, output_Industrial))
                                                        {
                                                            cout << output_Industrial << "\n";
                                                        }
                                                        Industrial_list.close();
                                                    }
                                                }

                                            Electrical_list.open("Electrical_list.txt", ios::in);
                                                {   if(Electrical_list.is_open())
                                                    {
                                                        string output_Electrical;
                                                        while (getline(Electrical_list, output_Electrical))
                                                        {
                                                            cout << output_Electrical << "\n";
                                                        }
                                                        Electrical_list.close();
                                                    }
                                                }

                                            Mechanical_list.open("Mechanical_list.txt", ios::in);
                                                {   if(Mechanical_list.is_open())
                                                    {
                                                        string output_Mechanical;
                                                        while (getline(Mechanical_list, output_Mechanical))
                                                        {
                                                            cout << output_Mechanical << "\n";
                                                        }
                                                        Mechanical_list.close();
                                                    }
                                                }
                                        break;
                                        }

                                case 2: {
                                            Computer_list.open("Computer_list.txt", ios::in);
                                            {
                                                if(Computer_list.is_open())
                                                {
                                                    string output_Computer;
                                                    while (getline(Computer_list, output_Computer))
                                                    {
                                                        cout << output_Computer << "\n";
                                                    }
                                                    Computer_list.close();
                                                }
                                            }
                                        break;
                                        }

                                case 3: {
                                            Industrial_list.open("Industrial_list.txt", ios::in);
                                            {
                                                if(Industrial_list.is_open())
                                                {
                                                    string output_Industrial;
                                                    while (getline(Industrial_list, output_Industrial))
                                                    {
                                                        cout << output_Industrial << "\n";
                                                    }
                                                    Industrial_list.close();
                                                }
                                            }
                                        break;
                                        }

                                case 4: {
                                            Electrical_list.open("Electrical_list.txt", ios::in);
                                            {   if(Electrical_list.is_open())
                                                {
                                                    string output_Electrical;
                                                    while (getline(Electrical_list, output_Electrical))
                                                    {
                                                        cout << output_Electrical << "\n";
                                                    }
                                                    Electrical_list.close();
                                                }
                                            }
                                        break;
                                        }

                                case 5: {
                                            Mechanical_list.open("Mechanical_list.txt", ios::in);
                                            {   if(Mechanical_list.is_open())
                                                {
                                                    string output_Mechanical;
                                                    while (getline(Mechanical_list, output_Mechanical))
                                                    {
                                                        cout << output_Mechanical << "\n";
                                                    }
                                                    Mechanical_list.close();
                                                }
                                            }
                                        break;
                                        }
                            }


                    break;
                    }

            case 3: {
                    int filter_input;
                    bool valid = false;
                    while (!valid)
                    {
                        cout << "Press '1' to show Computer Engineering students" << "\n"
                             << "Press '2' to filter by Industrial Engineering students" << "\n"
                             << "Press '3' to filter by Electrical Engineering students" << "\n"
                             << "Press '4' to filter by Mechanical Engineering students" << "\n";
                        cin >> filter_input;
                        switch (filter_input)
                        {
                            case 1:
                            {
                                valid = true;
                                while (true)
                                {
                                    string id;
                                    for (string i :computerID)
                                        cout << i << "\n";
                                    cout << "Enter the id of student;";
                                    cin >> id;
                                    id +=".txt";
                                    if (fs::exists(id))
                                    {
                                        fstream idfile(id,ios::in);
                                        if (idfile.is_open())
                                        {
                                            string line;
                                            while (getline(idfile,line))
                                                cout << line << "\n";
                                            idfile.close();
                                        }
                                        break;
                                    }
                                    else
                                        cerr << "id not found";
                                }
                                break;
                            }
                            case 2:
                            {
                                valid = true;
                                while (true)
                                {
                                    string id;
                                    for (string i :industrialID)
                                        cout << i << "\n";
                                    cout << "Enter the id of student;";
                                    cin >> id;
                                    id +=".txt";
                                    if (fs::exists(id))
                                    {
                                        fstream idfile(id,ios::in);
                                        if (idfile.is_open())
                                        {
                                            string line;
                                            while (getline(idfile,line))
                                            cout << line << "\n";
                                            idfile.close();
                                        }
                                        break;
                                    }
                                    else
                                        cerr << "id not found";
                                }
                                break;
                            }
                            case 3:
                            {
                                valid = true;
                                while (true)
                                {
                                    string id;
                                    for (string i :electricalID)
                                        cout << i << "\n";
                                    cout << "Enter the id of student;";
                                    cin >> id;
                                    id +=".txt";
                                    if (fs::exists(id))
                                    {
                                        fstream idfile(id,ios::in);
                                        if (idfile.is_open())
                                        {
                                            string line;
                                            while (getline(idfile,line))
                                            cout << line << "\n";
                                            idfile.close();
                                        }
                                        break;
                                    }
                                    else
                                        cerr << "id not found";
                                }
                                break;
                            }
                            case 4:
                            {
                                valid = true;
                                while (true)
                                {
                                    string id;
                                    for (string i :mechanicalID)
                                        cout << i << "\n";
                                    cout << "Enter the id of student;";
                                    cin >> id;
                                    id +=".txt";
                                    if (fs::exists(id))
                                    {
                                        fstream idfile(id,ios::in);
                                        if (idfile.is_open())
                                        {
                                            string line;
                                            while (getline(idfile,line))
                                            cout << line << "\n";
                                            idfile.close();
                                        }
                                        break;
                                    }
                                    else
                                        cerr << "id not found";
                                }
                                break;
                            }
                            default:
                                cout << "Invalid input. Please enter a number between 1 and 4.\n";
                                break;
                        }
                    }
                break;
            }

            case 4: {

                    break;
                    }

            case 5: {
                        cout << "Exiting...\n";
                        return 0;
                    }

        }
    }
}