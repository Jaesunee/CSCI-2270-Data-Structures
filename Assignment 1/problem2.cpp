#include <iostream>
#include <fstream>
#include <string>

struct studentData{
    std::string studentName;
    int homework;
    int recitation;
    int quiz;
    int exam;
    double average;
};

void addStudentData (studentData students[], std::string studentName, int homework, int recitation, int quiz, int exam, int length)
{
    studentData student;
    student.studentName = studentName;
    student.homework = homework;
    student.recitation = recitation;
    student.quiz = quiz;
    student.exam = exam;

    student.average = (homework + recitation + quiz + exam) / 4.0;

    students[length] = student;


}

char calcLetter(double avg)
{
    if (avg >= 90){
        return 'A';
    }
    else if(avg >= 80)
    {
        return 'B';
    }
    else if(avg >= 70)
    {
        return 'C';
    }
    else if(avg >=60)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}

double calcUpperBound(std::string letter)
{
    if (letter == "A"){
        return 100.0;
    }
    else if(letter == "B")
    {
        return 89.99;
    }
    else if(letter == "C")
    {
        return 79.99;
    }
    else if(letter == "D")
    {
        return 69.99;
    }
    else
    {
        return 59.99;
    }
}

double calcLowerBound(std::string letter)
{
    if (letter == "A"){
        return 90.0;
    }
    else if(letter == "B")
    {
        return 80.0;
    }
    else if(letter == "C")
    {
        return 70.0;
    }
    else if(letter == "D")
    {
        return 60.0;
    }
    else
    {
        return 0.0;
    }
}

void printList(const studentData students[], int length)
{
    for(int i = 0; i < length; i++)
    {
        std::cout << students[i].studentName << " earned " << students[i].average;
        std::cout << " which is a(n) " << calcLetter(students[i].average) << std::endl;
    }
}

int main (int argc, char const *argv[]){
    std::string ifileName = argv[1];
    std::string ofileName = argv[2];
    std::string lowerBound = argv[3];
    std::string upperBound = argv[4];
    std::string name, homework, recitation, quiz, exam; 
    studentData students[100];
    int length = 0;

    std::ifstream ifile;
    ifile.open(ifileName);

    if(ifile.fail())
    {
        std::cout << "Failed to open the file." << std::endl;
        return 0;
    }

    while(!ifile.eof())
    {
        std::getline(ifile, name, ',');
        if(name.empty()){
            break;
        }
        std::getline(ifile, homework, ',');
        std::getline(ifile, recitation, ',');
        std::getline(ifile, quiz, ',');
        std::getline(ifile, exam);
        addStudentData(students, name, stoi(homework), stoi(recitation), stoi(quiz), stoi(exam), length);
        length++;
    }

    printList(students, length);

    std::ofstream ofile;
    ofile.open(ofileName);
    
    for(int i = 0; i < length; i++)
    {
        if(students[i].average <= calcUpperBound(upperBound) && students[i].average >= calcLowerBound(lowerBound)){
            ofile << students[i].studentName << "," << students[i].average << "," << calcLetter(students[i].average) << std::endl;
        }
    }

    ofile.close();

    return 0;
}



