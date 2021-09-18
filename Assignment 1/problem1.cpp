#include <iostream>
#include <fstream>
#include <string>

bool isSorted(int n, float array[])
{
    bool isSorted = true;
    for(int i = 0; i < n-1; i++)
    {
        if (array[i] > array[i+1]){
            isSorted = false;
        }
    }
    return isSorted;
}

void sortArray(int n, float array[])
{
    float temp;
    //sort the input array using bubble sort
    for(int i = 0; i < n-1; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if(array[j] > array[j+1])
            {
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

int addToArrayAsc(float sortedArray[], int numElements, float newValue)
{
    //insert new value into last index of array
    sortedArray[numElements] = newValue;
    
    if (numElements + 1 > 1) {
        while(!(isSorted(numElements + 1, sortedArray)))
        {
            sortArray(numElements + 1, sortedArray);
        }
    }
    
    return numElements +1;
}

int main (int argc, char const *argv[])
{
    float myArray[100];
    std::string temp;
    int i = 0; //number of elements inserted so far

    std::ifstream iFile;
    iFile.open(argv[1]);

    if(iFile.fail())
    {
        std::cout << "Failed to open the file." << std::endl;
        return 0;
    }

    while(!iFile.eof())
    {
        std::getline(iFile, temp);
        //std::cout << std::stof(temp);
        addToArrayAsc(myArray, i, std::stof(temp));
        i++;
        for(int j = 0; j < i; j++ )
        {
            if(j == 0)
            {
                std::cout << myArray[j];
            }
            else
            {
                std::cout << "," << myArray[j];
            }
        }
        std::cout << std::endl;
    }
    return 0;
}