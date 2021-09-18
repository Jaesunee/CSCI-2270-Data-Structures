#include <fstream>
#include <iostream> 

using namespace std;

int main ()
{
    //File Writing
    //Creates instance of ofstream and opens the file
    ofstream oFile ("filename.txt");
    //outputs to filename.txt through oFile
    oFile << "Inserted this text into filename.txt";
    //Close the file stream
    oFile.close();
}