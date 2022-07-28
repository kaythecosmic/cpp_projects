#include <iostream>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <windows.h>
#include <cctype>

using namespace std;

class Company
{
private:
    struct user
    {
        string fname, lname, post, department;
        int salary, ID, age;
        char gender;
    } user;

public:
    void choice();
    void getdata();
    void showdata();
    void deldata();
    void exitoption();

    string capitals(string);
};

int main()
{
    system("cls");
    system("COLOR f");

    cout << endl;
    cout << "\t============================" << endl;
    cout << "\t Employee Management System" << endl;
    cout << "\t============================";
    cout << endl;

    int counter();
    void sortdata();

    Company a;
    a.choice();

    sortdata();
    return 0;
}

void Company ::choice()
{
    int exittrig = 0;
    while (exittrig == 0)
    {
        char choice;
        cout << endl;
        cout << "What would you like to do: " << endl;
        cout << "1 -> Enter a new record." << endl;
        cout << "2 -> Show a particular record." << endl;
        cout << "3 -> Delete a particular record." << endl;
        cout << "4 -> Exit." << endl;

        cout << "\nEnter your choice: " << endl
             << "-> ";
        cin >> choice;
        Sleep(90);

        switch (choice)
        {
        case '1':
            Company ::getdata();
            break;

        case '2':
            Company ::showdata();
            break;

        case '3':
            Company ::deldata();
            break;

        case '4':
            exittrig = 1;
            exitoption();
            break;

        default:
            break;
        }
    }
}

void Company ::exitoption()
{
    system("cls");
    cout << "\t================================================" << endl;
    cout << "\t Thank you for using Employee Management System" << endl;
    cout << "\t================================================" << endl
         << endl;
}

int counter()
{

    ifstream countfile("Records.csv");
    string strtemp;
    int counter = 0;
    while (!countfile.eof())
    {
        getline(countfile, strtemp);
        counter++;
    }

    return counter - 1;
}

void Company ::getdata()
{

    system("cls");
    ifstream tempfile("Records.csv");
    int counter = 0, trigg = 0;
    char ch;
    string emptstr;
    if (tempfile.is_open())
    {

        while (!tempfile.eof())
        {
            getline(tempfile, emptstr);
            counter++;

            if (emptstr == "")
            {
                trigg = 1;
                break;
            }
        }
        tempfile.close();
    }

    if (trigg == 0)
    {
        counter = 0;
        ifstream countfile("Records.csv");
        while (!countfile.eof())
        {
            countfile >> ch;
            if (ch == ',')
            {
                counter++;
                cout << counter << endl;
            }
        }
        countfile.close();
    }
    else
    {
        counter--;
        counter = counter * 6;
    }

    system("cls");
    cout << "<<<<< Enter Data >>>>>" << endl
         << endl;
    cout << "Enter data for User " << (counter / 6) << ":" << endl;
    user.ID = (counter / 6);
    cout << "First Name: ";
    cin >> user.fname;
    cout << "Last Name: ";
    cin >> user.lname;
    cout << "Gender (M/F): ";
    cin >> user.gender;
    cout << "Age: ";
    cin >> user.age;
    cout << "Post: ";
    cin >> user.post;
    cout << "Salary: ";
    cin >> user.salary;

    fstream myFile;
    myFile.open("Records.csv", ios::app); // write
    if (myFile.is_open())
    {
        myFile << "\n"
               << user.ID << "," << capitals(user.fname) << "," << capitals(user.lname) << ","
               << (char)toupper(user.gender) << "," << user.age << "," << capitals(user.post) << "," << user.salary;
        myFile.close();
    }

    cout << endl
         << "<<<<< Record Entered Successfully >>>>>";
    Sleep(2000);
    system("cls");
}

void Company ::showdata()
{
    system("cls");
    int tempID;
    cout << "\t<<<<< Show Data >>>>>" << endl
         << endl;
    cout << "Enter ID of the User you want view: ";
    cin >> tempID;

    int max = counter();

    if (tempID <= max)
    {
        ifstream tempfile("Records.csv");

        string str;
        string head[7]{"ID", "First Name", "Last Name", "Gender", "Age", "Post", "Salary"};

        if (tempfile.is_open())
        {

            for (int i = 0; i <= tempID; i++)
            {
                getline(tempfile, str);

                if (i == tempID)
                {
                    int len = str.length();
                    int k = 0;
                    cout << endl
                         << head[k] << ": ";

                    for (int j = 0; j <= len; j++)
                    {

                        if (str[j] == ',')
                        {
                            cout << endl;
                            k++;
                            cout << head[k] << ": ";
                        }

                        else
                        {
                            cout << str[j];
                        }
                    }
                }
            }
            tempfile.close();
        }
    }

    else
    {
        cout << endl
             << "Data of User ID " << tempID << " doesn't exists." << endl;
    }

    cout << endl
         << "\t     <<<<< x >>>>>" << endl
         << endl;
}

void Company ::deldata()
{

    int tempID;
    system("cls");
    cout << "\t<<<<< Delete Data >>>>>" << endl
         << endl;
    cout << "Enter ID of the User you want to delete: ";
    cin >> tempID;

    int max = counter();
    vector<string> vec;
    string str;
    if (tempID <= max)
    {
        fstream tempfile("Records.csv", ios ::in);
        int i = 0;
        while (!tempfile.eof())
        {
            getline(tempfile, str);

            if (i == tempID)
            {
                str = "";
            }
            vec.push_back(str);
            i++;
        }
        tempfile.close();
        fstream tempfileo("Records.csv", ios ::out);

        int size = vec.size();

        for (int k = 0; k < size; k++)
        {
            tempfileo << vec.at(k) << endl;
        }
        tempfileo.close();
    }

    else
    {
        cout << endl
             << "Data of User ID " << tempID << " doesn't exists." << endl;
    }

    Sleep(100);
    cout << endl
         << "<<<<< Record Deleted Successfully >>>>>";
    Sleep(2000);
    system("cls");
}

void sortdata()
{

    vector<string> sortvec;
    string sortstr;
    fstream tempfilei("Records.csv", ios ::in);
    if (tempfilei.is_open())
    {
        while (!tempfilei.eof())
        {
            getline(tempfilei, sortstr);
            sortvec.push_back(sortstr);
        }
        tempfilei.close();
    }

    fstream tempfileo("Records.csv", ios ::out);
    if (tempfileo.is_open())
    {
        int p = 49; // 49 is the ASCII value of '1'.
        int len = sortvec.size();

        tempfileo << sortvec.at(0) << endl;
        for (int i = 1; i < len; i++)
        {

            for (int j = 0; j < len; j++)
            {
                if (sortvec.at(j)[0] == p)
                {
                    tempfileo << sortvec.at(j) << endl;
                    p++;
                }
            }
        }
        tempfileo.close();
    }
}

string Company::capitals(string text)
{

    for (int p = 0; p < text.length(); p++)
    {

        if (p == 0)
        {
            text[p] = toupper(text[p]);
        }

        else
        {
            text[p] = text[p];
        }
    }

    return text;
}