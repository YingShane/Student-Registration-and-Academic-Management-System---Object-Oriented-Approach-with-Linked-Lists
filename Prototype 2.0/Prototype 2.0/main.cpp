#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <cctype>
#include "StudentList.h"
#include "PersonalInfoList.h"

using namespace std;

void currentDate(int& a, int& b, int& c) {
    c = 1970;
    b = 1;
    a = 0;
    time_t now = time(0);
    now += 28800;
    now /= 86400;

    while (now > 365) {
        if (c % 4 == 0) {
            now -= 366;
            c++;
        }
        else {
            now -= 365;
            c++;
        }
    }
    while (now > 31) {
        if (b == 1 || b == 3 || b == 5 || b == 7 || b == 8 || b == 10 || b == 12) {
            now -= 31;
            b++;
        }

        else if (b == 4 || b == 6 || b == 9 || b == 11) {
            now -= 30;
            b++;
        }

        else if (c % 4 == 0 && b == 2) {
            now -= 29;
            b++;

        }
        else if (c % 4 > 0 && b == 2) {
            now -= 28;
            b++;
        }
    }
    a = now + 1;
}

bool dateError(int& a, int& b, int& c) {
    bool logic = true;
    if (b == 1 || b == 3 || b == 5 || b == 7 || b == 8 || b == 10 || b == 12) {
        if (a < 1 || a > 31) {
            cout << "Date of birth is not valid!" << endl;
            logic = false;
        }

    }
    else if (b == 4 || b == 6 || b == 9 || b == 11) {
        if (a < 1 || a > 30) {
            cout << "Date of birth is not valid!" << endl;
            logic = false;
        }
    }
    else if (c % 4 == 0 && b == 2) {
        if (a < 1 || a > 29) {
            cout << "Date of birth is not valid!" << endl;
            logic = false;
        }
    }
    else if (c % 4 > 0 && b == 2) {
        if (a < 1 || a > 28) {
            cout << "Date of birth is not valid!" << endl;
            logic = false;
        }
    }

    if (b > 12 || b < 1) {
        cout << "Month is not valid!" << endl;
        logic = false;

    }

    return logic;
}

bool isChar(char c)
{
    return ((c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z'));
}

// Function to check the character
// is an digit or not
bool isDigit(const char c)
{
    return (c >= '0' && c <= '9');
}

// Function to check email id is
// valid or not
bool isEmail(string email)
{
    // Check the first character
    // is an alphabet or not
    if (!isChar(email[0])) {

        // If it's not an alphabet
        // email id is not valid
        return 0;
    }
    // Variable to store position
    // of At and Dot
    int At = -1, Dot = -1;

    // Traverse over the email id
    // string to find position of
    // Dot and At
    for (int i = 0;
        i < email.length(); i++) {

        // If the character is '@'
        if (email[i] == '@') {

            At = i;
        }

        // If character is '.'
        else if (email[i] == '.') {

            Dot = i;
        }
    }

    // If At or Dot is not present
    if (At == -1 || Dot == -1)
        return 0;

    // If Dot is present before At
    if (At > Dot)
        return 0;

    // If Dot is present at the end
    return !(Dot >= (email.length() - 1));
}

bool isDigit(string strValue) {
    return isdigit(strValue[0]);
}

bool arrcheck(int arr[], int i) {
    for (int j = 0; j < (10); j++) {
        if (arr[j] == i) {
            return false;
            break;
        }
    }
    return true;
}

int countDigit(int n)
{
    if (n == 0)
        return 1;
    int count = 0;
    while (n != 0)
    {
        n = n / 10;
        ++count;
    }
    return count;
}

int main() {
    //Instance of class
    StudentList student;

    //Variables
    string studentInfo, semester, search_key;
    int studentMatricNum = 0, colNum = 0, cnt = 0;
    int matricNum = 0, position = 0, semkey = 0;
    char ch = ' ';
    float cgpa = 0.0;
    bool end = false;

    ifstream inputFile;
    inputFile.open("StudentsFile.txt", ios::in);

    while (!inputFile)
    {
        ifstream inputFile;
        inputFile.open("StudentsFile.txt", ios::in);
    }

    int checkPos = 0;

    inputFile.seekg(0, ios::end);
    checkPos = inputFile.tellg();

    if (checkPos != 0)
    {
        inputFile.seekg(0, ios::beg);
        //This while loop reads all information of each student into the different linked lists
        while (!inputFile.eof())
        {
            inputFile >> studentMatricNum;
            student.readMatricNum(studentMatricNum);

            ch = inputFile.get();
            cnt = 0;
            do
            {
                if (cnt < 7)
                {
                    getline(inputFile, studentInfo, '\t');
                    student.passPersonalInfo(studentInfo, studentMatricNum);
                    cnt++;
                }
                else
                {
                    inputFile >> studentInfo;
                    student.passPersonalInfo(studentInfo, studentMatricNum);

                    ch = inputFile.get();
                    inputFile.seekg(-1, ios::cur);
                }
            } while (ch != '\n');

            while (studentInfo != "CGPA" && !inputFile.eof())
            {
                //cout << "Debug 0" << endl;

                //Read semester
                do
                {
                    //cout << "Debug 1" << endl;
                    inputFile >> studentInfo;

                    //cout << endl << studentInfo << endl;

                    student.passStudentSem(studentInfo, studentMatricNum);
                    ch = inputFile.get();
                    inputFile.seekg(-1, ios::cur);
                } while (ch != '\n');

                //cout << "Debug 2" << endl;
                semester = studentInfo;
                position = inputFile.tellg();
                ch = ' ';
                int count = 0;

                while (ch != '\n')
                {
                    //cout << "Debug 3" << endl;
                    inputFile >> studentInfo;
                    ch = inputFile.get();
                    inputFile.seekg(-1, ios::cur);
                    count++;
                }

                //cout << "Debug 4" << endl;

                inputFile.seekg(0, ios::beg);
                inputFile.seekg(position, ios::cur);

                colNum = count;

                //Initialize a dynamic 2-D array to store the information of all courses of a student from the text file
                string** arrTemp = new string * [4];
                for (int row = 0; row < 4; row++)
                {
                    //cout << "Debug 5" << endl;

                    arrTemp[row] = new string[count];
                }

                //cout << "Debug 6" << endl;

                for (int i = 0; i < 4; i++)
                {
                    //cout << "Debug 7" << endl;

                    for (int j = 0; j < count; j++)
                    {
                        //cout << "Debug 8" << endl;

                        inputFile >> studentInfo;
                        arrTemp[i][j] = studentInfo;
                    }
                }

                for (int i = 0; i < count; i++)
                {
                    //cout << "Debug 9" << endl;

                    for (int j = 0; j < 4; j++)
                    {
                        //cout << "Debug 10" << endl;

                        //To pass the information of each course taken by the student, semester and matric number to be stored in the linked list
                        student.passStudentCourse(arrTemp[j][i], semester, studentMatricNum);
                    }
                }

                position = inputFile.tellg();
                inputFile >> studentInfo;

                //Check if the next student in text file has been reached
                if (studentInfo != "CGPA" && !inputFile.eof())
                {
                    inputFile.seekg(0, ios::beg);
                    inputFile.seekg(position, ios::cur);
                }

                //Delete the dynamic 2-D array
                for (int i = 0; i < 4; i++)
                {
                    delete[] arrTemp[i];
                }
                delete[]arrTemp;
            }

            inputFile >> cgpa;
            student.readCgpa(studentMatricNum, cgpa);
        }
    }
    inputFile.close();

    bool logic = false, keylogic = false;
    string temp, name;
    char yn = ' ';
    int id = 0;
    while (logic == false)
    {
        cout << "Please enter your matric number: ";
        cin >> temp;
        if (isDigit(temp))
        {
            id = stoll(temp);
            if (countDigit(id) == 6)
            {
                logic = true;
            }
            else
            {
                cout << "Invalid matric number! It must consist of 6 digits." << endl;
            }
        }
        else
        {
            cout << "Matric number must be a number!" << endl;
        }
    }
    bool wholelogic = false;
    while (wholelogic == false) {
        semkey = 0;
        int key;
        cout << "What do you want to do?" << endl;
        cout << "Press [1] to view existing information." << endl;
        cout << "Press [2] for new student to enter new information." << endl;
        cout << "Press [3] for existing student to enter new semester." << endl;
        cout << "Press [4] to drop course." << endl;
        cout << "Press [5] to drop out of CS." << endl;
        cin >> temp;

        if (isDigit(temp)) {
            key = stoi(temp);
            if (key > 5 || key < 1) {
                cout << "Invalid range! Please try again!" << endl;
                system("pause");
                system("cls");
                continue;
            }
        }
        else {
            cout << "Please enter a number!" << endl;
            continue;
        }

        studentMatricNum = id;

        if (key == 1)
        {
            if (!student.validateMatricNum(studentMatricNum)) {
                cout << "You're not yet registered!" << endl;
                cout << "Please pick the option 2 to register." << endl;
                system("pause");
                system("cls");
                continue;
            }
            else {
                //To validate the existence of a matric number in txt file based on the linked lists
                bool validate = false;
                validate = student.validateMatricNum(id);

                //Just a testing
                if (validate == true) {
                    cout << "Press [1] to view personal data." << endl;
                    cout << "Press [2] to view course data." << endl;
                    cout << "Press [3] to view both." << endl;
                    cin >> key;
                    system("cls");
                    while (key > 3 || key < 1)
                    {
                        cout << "Please enter a valid number!" << endl;
                        cout << "Press [1] to view personal data." << endl;
                        cout << "Press [2] to view course data." << endl;
                        cout << "Press [3] to view both." << endl;
                        cin >> key;
                        system("cls");
                    }

                    cout << endl;
                    int semchoice;
                    logic = false;
                    if (key == 2 || key == 3) {
                        cout << "What semester's data do you want to look at? Press 1-8 for the semester you want, press 0 to see all" << endl;
                        student.obtainSemester(id, semkey);
                        while (logic == false) {
                            cin >> temp;
                            if (isDigit(temp)) {
                                semchoice = stoi(temp);
                                if (semchoice >= 0 && semchoice <= semkey) {
                                    logic = true;
                                }
                                else {
                                    cout << "Please only enter the semester that you have taken!" << endl;
                                }
                            }
                            else {
                                cout << "Please key in a number!" << endl;
                            }
                        }
                    }
                    if (key == 1 || key == 3) {
                        //To display all the personal information of a student
                        student.displayPersonalInfoList(id);
                    }
                    if (key == 2 || key == 3) {

                        if (semchoice == 0) {
                            //To display the semesters and courses of a student
                            for (int i = 0; i <= semkey; i++) {
                                student.displayEverything(id, to_string(i));
                            }
                        }
                        else {
                            student.displayEverything(id, to_string(semchoice));
                        }
                        student.displayCgpa(id);
                    }
                }
            }
        }

        else if (key == 2)
        {
            if (student.validateMatricNum(studentMatricNum)) {
                cout << "You're already registered!" << endl;
                cout << "Please pick another options." << endl;
                system("pause");
                system("cls");
                continue;
            }
            else {

                student.insertMatricNum(studentMatricNum);
                cout << "Please enter your name: ";
                cin.ignore();
                getline(cin, name);
                
                while (name == "")
                {
                    cout << "Please enter a valid name: ";
                    getline(cin, name);
                }

                student.passPersonalInfo(name, studentMatricNum);

                long long int ic = 1000000000000;
                logic = false;
                bool gender, foreign;
                int age, day, month, year, cday, cmonth, cyear;
                string birthday;
                while (logic == false) {
                    cout << "Please enter your IC/Passport: ";
                    cin >> temp;
                    if (isDigit(temp)) {
                        ic = stoll(temp);
                        if (ic >= 1000000000000 && ic <= 10000000000) {
                            cout << "Invalid IC! Please try again." << endl;
                            system("pause");
                            system("cls");
                            continue;
                        }

                        year = ic / 10000000000;
                        month = (ic / 100000000) % 100;
                        day = (ic / 1000000) % 100;
                        if (!dateError(day, month, year)) {
                            cout << "Invalid IC! Please try again." << endl;
                            system("pause");
                            system("cls");
                            continue;
                        }
                        else {
                            logic = true;
                        }
                        if (day < 10) {
                            birthday = "0" + to_string(day) + "/";
                        }
                        else {
                            birthday = to_string(day) + "/";
                        }
                        if (month < 10) {
                            birthday = birthday + "0" + to_string(month) + "/";
                        }
                        else {
                            birthday = birthday + to_string(month) + "/";
                        }
                        if (year < 10) {
                            birthday = birthday + "0" + to_string(year);
                        }
                        else {
                            birthday = birthday + to_string(year);
                        }
                        cout << birthday << endl;
                        currentDate(cday, cmonth, cyear);

                        age = (cyear % 100) - year;
                        if (age < 0) {
                            age += 100;
                        }
                        if ((cmonth - month) < 0 || ((cmonth - month) == 0 && ((cday - day) < 0))) {
                            age--;

                        }
                        if ((ic % 10) % 2 == 0) {
                            gender = true;
                        }
                        else {
                            gender = false;
                        }
                        cout << age << endl;

                        //Here need to fix
                        if (floor(log10(ic)) == 10) {
                            string strIC = to_string(ic);
                            student.passPersonalInfo("0" + strIC, studentMatricNum);
                        }
                        else if (floor(log10(ic)) == 9) {
                            string strIC = to_string(ic);
                            student.passPersonalInfo("00" + strIC, studentMatricNum);
                        }
                        else if (floor(log10(ic)) == 8) {
                            string strIC = to_string(ic);
                            student.passPersonalInfo("000" + strIC, studentMatricNum);
                        }

                        if (gender) {
                            cout << "Female" << endl;
                            student.passPersonalInfo("F", studentMatricNum);
                        }
                        else {
                            cout << "Male" << endl;
                            student.passPersonalInfo("M", studentMatricNum);
                        }
                        foreign = false;
                    }
                    else {
                        char initial = temp.at(0);
                        if ((temp.length() == 8 || temp.length() == 9) && (initial >= 64 && initial <= 90)) {
                            foreign = true;
                            student.passPersonalInfo(temp, id);
                            keylogic = false;
                            int pbday;
                            while (keylogic == false) {

                                cout << "Please enter your date of birth (DDMMYY): ";
                                cin >> temp;
                                if (isDigit(temp)) {
                                    pbday = stoi(temp);
                                    year = pbday % 100;
                                    month = (pbday / 100) % 100;
                                    day = (pbday / 10000);
                                    if (!dateError(day, month, year)) {
                                        cout << "Invalid birthday! Please try again." << endl;
                                        system("pause");
                                        system("cls");
                                        continue;
                                    }
                                    else {
                                        keylogic = true;
                                    }
                                    if (day < 10) {
                                        birthday = "0" + to_string(day) + "/";
                                    }
                                    else {
                                        birthday = to_string(day) + "/";
                                    }
                                    if (month < 10) {
                                        birthday = birthday + "0" + to_string(month) + "/";
                                    }
                                    else {
                                        birthday = birthday + to_string(month) + "/";
                                    }
                                    if (year < 10) {
                                        birthday = birthday + "0" + to_string(year);
                                    }
                                    else {
                                        birthday = birthday + to_string(year);
                                    }

                                    currentDate(cday, cmonth, cyear);

                                    age = (cyear % 100) - year;
                                    if (age < 0) {
                                        age += 100;
                                    }
                                    if ((cmonth - month) < 0 || ((cmonth - month) == 0 && ((cday - day) < 0))) {
                                        age--;

                                    }
                                }
                                else
                                {
                                    cout << "Please key in a valid number!" << endl;
                                }
                            }

                            keylogic = false;
                            while (keylogic == false) {
                                char pgender = ' ';
                                cout << "Please enter your gender (M/F): ";
                                cin >> pgender;
                                if (pgender == 'M' || pgender == 'm') {
                                    gender = false;
                                    keylogic = true;
                                    student.passPersonalInfo("M", id);
                                }
                                else if (pgender == 'F' || pgender == 'f') {
                                    gender = true;
                                    keylogic = true;
                                    student.passPersonalInfo("F", id);
                                }
                                else {
                                    cout << "You might be non-binary but this doesn't sit well with USM registeration so denied." << endl;
                                    continue;
                                }
                            }
                            cout << birthday << endl;
                            cout << age << endl;
                            if (gender) {
                                cout << "Female" << endl;
                            }
                            else {
                                cout << "Male" << endl;
                            }
                            logic = true;
                        }
                        else {
                            cout << "Invalid IC/Passport! Please try again." << endl;
                            system("pause");
                            system("cls");
                            continue;
                        }
                    }
                }

                logic = false;
                string email;
                while (logic == false) {
                    cout << "Please enter your email: ";
                    cin >> email;

                    if (isEmail(email)) {
                        cout << "Confirm email '" << email << "' ? (Y for Yes)" << endl;
                        cin >> yn;
                        if (yn == 'Y' || yn == 'y') {
                            logic = true;
                            student.passPersonalInfo(email, studentMatricNum);
                        }
                    }
                    else {
                        cout << "Invalid email. Please try again." << endl;
                    }
                }

                logic = false;
                string address;
                while (logic == false) {
                    cout << "Please enter the address of your current residence: ";
                    cin.ignore();
                    getline(cin, address);

                    cout << "Confirm address '" << address << "' ? (Y for Yes)" << endl;
                    cin >> yn;
                    if (yn == 'Y' || yn == 'y') {
                        logic = true;
                        student.passPersonalInfo(address, studentMatricNum);
                    }
                }

                logic = false;
                string temp;
                while (logic == false) {
                    cout << "Please enter your country of origin (please be a legit country): ";
                    cin.ignore();
                    getline(cin, temp);
                    cout << "Confirm " << temp << " as country of origin? (Y for Yes)" << endl;
                    cin >> yn;
                    if (yn == 'Y' || yn == 'y') {
                        logic = true;
                        student.passPersonalInfo(temp, studentMatricNum);
                    }
                }
                
                student.passPersonalInfo(birthday, studentMatricNum);
                logic = false;

                while (logic == false) {
                    cout << "Please enter your mobile number (+XXXXXXXXXXXX format): ";
                    cin >> temp;

                    if (temp.at(0) == '+' && isDigit(temp.erase(0, 1))) {
                        cout << "Confirm phone number? '+" << temp << "' ? (Y for Yes)" << endl;
                        cin >> yn;
                        if (yn == 'Y' || yn == 'y') {
                            logic = true;
                            student.passPersonalInfo("+" + temp, studentMatricNum);
                        }
                    }
                    else {
                        cout << "Invalid number!" << endl;
                    }
                }

                string compulsoryCourses[3][4] = { {"CPT111", "CPT112", "CPC131", "HFF225"}, {"3", "4", "4", "2"}, {"T", "T", "T", "U"} };
                string languageCourses[3][2] = { {"LSP300", "LKM400"}, {"2", "2"}, {"U", "U"} };

                student.passStudentSem("1", studentMatricNum);

                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        student.passStudentCourse(compulsoryCourses[j][i], "1", studentMatricNum);

                    }
                    student.passStudentCourse("-", "1", studentMatricNum);
                }


                /*student.passStudentCourse("CPT111", "1", studentMatricNum);
                student.passStudentCourse("3", "1", studentMatricNum);
                student.passStudentCourse("T", "1", studentMatricNum);
                student.passStudentCourse("-", "1", studentMatricNum);
                student.passStudentCourse("CPT112", "1", studentMatricNum);
                student.passStudentCourse("4", "1", studentMatricNum);
                student.passStudentCourse("T", "1", studentMatricNum);
                student.passStudentCourse("-", "1", studentMatricNum);
                student.passStudentCourse("CPC131", "1", studentMatricNum);
                student.passStudentCourse("4", "1", studentMatricNum);
                student.passStudentCourse("T", "1", studentMatricNum);
                student.passStudentCourse("-", "1", studentMatricNum);
                student.passStudentCourse("HFF225", "1", studentMatricNum);
                student.passStudentCourse("2", "1", studentMatricNum);
                student.passStudentCourse("U", "1", studentMatricNum);
                student.passStudentCourse("-", "1", studentMatricNum);*/
                if (foreign == false) {
                    if (rand() % 2 == 0) {

                        for (int i = 0; i < 2; i++)
                        {
                            for (int j = 0; j < 3; j++)
                            {
                                student.passStudentCourse(languageCourses[j][i], "1", studentMatricNum);
                            }
                            student.passStudentCourse("-", "1", studentMatricNum);
                        }
                        /*student.passStudentCourse("LSP300", "1", studentMatricNum);
                        student.passStudentCourse("2", "1", studentMatricNum);
                        student.passStudentCourse("U", "1", studentMatricNum);
                        student.passStudentCourse("-", "1", studentMatricNum);
                        student.passStudentCourse("LKM400", "1", studentMatricNum);
                        student.passStudentCourse("2", "1", studentMatricNum);
                        student.passStudentCourse("U", "1", studentMatricNum);
                        student.passStudentCourse("-", "1", studentMatricNum);*/
                    }
                    else {
                        student.passStudentCourse("WSU101", "1", studentMatricNum);
                        student.passStudentCourse("2", "1", studentMatricNum);
                        student.passStudentCourse("U", "1", studentMatricNum);
                        student.passStudentCourse("-", "1", studentMatricNum);
                    }
                }
                else {
                    student.passStudentCourse("LKM100", "1", studentMatricNum);
                    student.passStudentCourse("2", "1", studentMatricNum);
                    student.passStudentCourse("U", "1", studentMatricNum);
                    student.passStudentCourse("-", "1", studentMatricNum);
                }
                student.readCgpa(studentMatricNum, 0.00);
            }
        }
        else if (key == 3) {
            if (!student.validateMatricNum(studentMatricNum)) {
                cout << "You're not yet registered!" << endl;
                cout << "Please pick the option 2 to register." << endl;
                system("pause");
                system("cls");
                continue;
            }
            else {
                student.obtainSemester(id, semkey);

                string inputs[912];
                int creds[912];
                int chosen[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
                int totcreds = 0, k = 0, i = 0;

                logic = false;
                ifstream course;
                course.open("Courses.txt");
                if (!course.is_open()) {
                    cout << "File not found/opened!" << endl;
                }
                else {
                    while (course) {

                        course >> inputs[i];
                        course >> creds[i];

                        i++;
                    }
                }
                course.close();

                float tempgpa = 0.0;
                student.editCourseList(studentMatricNum, to_string(semkey), tempgpa);
                student.calcCgpa(studentMatricNum, semkey, tempgpa);
                student.displayCgpa(id);

                semkey++;
                student.passStudentSem(to_string(semkey), id);

                while (logic == false) {
                    int count = 0;

                    if (keylogic == false) {
                        cout << endl;
                        cout << "Please enter a course code to register: ";
                        cin.clear();
                        cin >> search_key;

                        char* str;
                        str = new char[search_key.length()];

                        int i;
                        for (i = 0; i < search_key.length(); i++) {

                            str[i] = search_key[i];

                        }
                        int j = 0;
                        
                        for (int i = 0; i < search_key.length(); i++) {

                            str[i] = char(toupper(str[i]));

                        }
                        search_key.assign(str, search_key.length());
                    }

                    for (int i = 0; (i < sizeof(inputs) / sizeof(inputs[0]) - k); i++)
                    {
                        if (arrcheck(chosen, i)) {
                            if (inputs[i].find(search_key) != string::npos) {
                                count++;
                                cout << count << ". " << inputs[i] << " (" << creds[i] << ") " << endl;
                            }
                        }
                    }
                    cout << "Enter the number order of the course code to register.\nThe course will not be registered if you enter an out - of - range number : ";

                    if (count == 0) {
                        cout << "No subject matches your input! Please try again!" << endl;
                        system("pause");
                        system("cls");
                        continue;
                    }
                    keylogic = true;

                    int choice;
                    cin >> temp;
                    if (isDigit(temp)) {
                        choice = stoi(temp);

                        if (choice > count || choice < 1) {
                            cout << "Invalid range! Please try again!" << endl;
                            system("pause");
                            system("cls");
                            continue;
                        }
                    }
                    else {
                        cout << "Please key in a number!" << endl;
                        system("pause");
                        system("cls");
                        continue;
                    }
                    count = 0;
                    string type;
                    cout << endl;
                    cout << "Please pick the course type for the above subject (T/E/M/U)" << endl;
                    cin >> type;
                    while (!(type == "T" || type == "E" || type == "M" || type == "U" || type == "t" || type == "e" || type == "m" || type == "u")) {
                        cout << "Invalid course type! please key it in again!" << endl;
                        cin >> type;
                    }

                    for (int i = 0; i < type.length(); i++)
                    {
                        type[i] = toupper(type[i]);
                    }

                    for (int i = 0; (i < (sizeof(inputs) / sizeof(inputs[0]) - k)); i++)
                    {
                        if (arrcheck(chosen, i)) {
                            if (inputs[i].find(search_key) != string::npos) {
                                count++;
                                if (count == choice) {
                                    cout << endl;
                                    cout << "Are you sure you want to add in " << inputs[i] << " (" << creds[i] << " credits)? Please enter Y to confirm." << endl;
                                    cin >> yn;
                                    if (yn == 'y' || yn == 'Y') {
                                        totcreds = totcreds + creds[i];
                                        cout << endl;
                                        cout << "Total credits so far is " << totcreds << " credits." << endl << endl;
                                        student.passStudentCourse(inputs[i], to_string(semkey), id);
                                        student.passStudentCourse(to_string(creds[i]), to_string(semkey), id);
                                        student.passStudentCourse(type, to_string(semkey), id);
                                        student.passStudentCourse("-", to_string(semkey), id);
                                        student.displayEverything(id, to_string(semkey));
                                        logic = false;
                                        chosen[k] = i;
                                        if (totcreds >= 17 && totcreds <= 23) {
                                            cout << "Wow looks like its 17 or more credits and it's enough already, do you want to continue? Please enter Y to confirm." << endl;

                                            cin >> yn;
                                            if (yn == 'y' || yn == 'Y') {
                                                logic = false;
                                            }
                                            else {
                                                logic = true;
                                            }
                                        }
                                        else if (totcreds > 23) {
                                            cout << "Wow looks like its more than 23, is it enough or do you want to suffer? Please enter Y to confirm." << endl;
                                            cin >> yn;
                                            if (yn == 'y' || yn == 'Y') {
                                                logic = false;
                                            }
                                            else {
                                                logic = true;
                                            }
                                        }
                                    }
                                    else {
                                        continue;
                                    }
                                }
                            }
                        }
                    }
                    k++;
                    keylogic = false;
                    system("pause");
                    system("cls");
                }
            }
        }
        else if (key == 4) {
            if (!student.validateMatricNum(studentMatricNum)) {
                cout << "This matric number is not yet registered!" << endl;
                cout << "Please pick the option 2 to register." << endl;
                system("pause");
                system("cls");
                continue;
            }
            else {
                student.obtainSemester(id, semkey);
                cout << "A list of courses taken this semester:" << endl;
                student.displayEverything(id, to_string(semkey));

                cout << "What subject does this clown want to drop?" << endl;
                if (keylogic == false) {
                    cout << "Please enter your course code: ";
                    cin.clear();
                    cin >> search_key;

                    char* str;
                    str = new char[search_key.length()];

                    int i;
                    for (i = 0; i < search_key.length(); i++) {

                        str[i] = search_key[i];

                    }
                    int j = 0;
                    ch = ' ';
                    for (int i = 0; i < search_key.length(); i++) {

                        str[i] = char(toupper(str[i]));

                    }
                    search_key.assign(str, search_key.length());
                }

                student.passDeleteCourseData(id, (to_string(semkey)), search_key);

            }
        }
        else if (key == 5) {
            if (!student.validateMatricNum(studentMatricNum)) {
                cout << "This matric number is not yet registered" << endl;
                cout << "Please pick the option 2 to register." << endl;
                system("pause");
                system("cls");
                continue;
            }
            else {
                student.obtainSemester(id, semkey);
                student.removeStudent(id);
                system("pause");
                system("cls");
            }
        }

        if (key != 5)
        {
            cout << "Do you want to continue? Enter Y to continue. Enter anything to exit the program." << endl;
            cin >> yn;
            if (yn == 'y' || yn == 'Y') {
                wholelogic = false;
            }
            else {
                wholelogic = true;
            }
            system("pause");
            system("cls");
        }
        else
        {
            wholelogic = true;
        }
    }

    ofstream outputFile;
    outputFile.open("StudentsFile.txt", ios::out);

    if (!outputFile)
    {
        ofstream outputFile;
        outputFile.open("StudentsFile.txt", ios::out);
    }

    student.writeAllIntoFile(outputFile);
    outputFile.close();
    
    cout << endl << endl;
    cout << "********************************" << endl;
    cout << "Thank you for using our program" << endl;
    cout << "********************************" << endl;
    cout << endl << endl;

    return 0;
}
