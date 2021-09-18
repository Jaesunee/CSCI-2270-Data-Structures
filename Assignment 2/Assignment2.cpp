#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct wordRecord
{
    string word;
    int count;
};

void getCommonWords(const char *commonWordFileName, string* commonWords)
{
    ifstream inStream;
    inStream.open(commonWordFileName);
    if( inStream.fail() ) {
        cout << "Failed to open " << commonWordFileName << endl;
    }

    int i = 0;
    string word;
    while (inStream >> word)
    {   
        commonWords[i] = word;
        i++;
    }
    inStream.close();
}

bool isCommonWord(string word, string* commonWords)
{
    for(int i = 0; i < 50; i++){
        if (word == commonWords[i])
        {
            return true;
        }
    }
    return false;
}

int getTotalNumberUncommonWords(wordRecord* distinctWords, int length)
{
    int total = 0;
    for(int i = 0; i < length; i++)
    {
        total = total + distinctWords[i].count; 
    }
    return total;
}

void sortArray(wordRecord* distinctWords, int length)
{
    for (int i = length; i >=0; i--)
    {
        for(int j = length; j > length - i; j--)
        {
            if (distinctWords[j].count > distinctWords[j - 1].count)
            {
                swap(distinctWords[j], distinctWords[j-1]);
            }else if (distinctWords[j].count == distinctWords[j - 1].count){
                if(distinctWords[j].word < distinctWords[j - 1].word)
                {
                    swap(distinctWords[j], distinctWords[j-1]);
                }
            }
        }
    }
}

void printNFromM(wordRecord* distinctWords, int M, int N, int totalNumWords)
{
    for(int i = M; i < M + N; i++)
    {
        cout << fixed << setprecision(5);
        cout << (float) distinctWords[i].count / totalNumWords << " - " << distinctWords[i].word << endl;
    }
}

int main(int argc, char const *argv[])
{
    if(argc != 5){
        cout << "Usage: ./Assignment2 <inputfilename> <commonWordsfilename> <M> <N>" << endl;
        return -1;
    }

    string readFilename = argv[1];
    string commonFilename = argv[2];
    int M = stoi(argv[3]);
    int N = stoi(argv[4]);
    int capacity = 100;
    int timesDoubled = 0;
    bool isDuplicate = false;
    string commonWords[50];
    getCommonWords(commonFilename.c_str(), commonWords);
    ifstream readFile;
    readFile.open(readFilename.c_str());
    
    wordRecord *arrayPtr = new wordRecord[capacity];
    int numUniqueWords = 0;
    string temp; 
    
    while(readFile >> temp)
    {   
        isDuplicate = false;
        cout<< numUniqueWords;
        if(numUniqueWords == capacity)
        {
            int oldCapacity = capacity;
            capacity = capacity * 2;
            wordRecord *newArray = new wordRecord[oldCapacity];
            
            for(int i = 0; i < oldCapacity; i++)
            {
                newArray[i] = arrayPtr[i];
            }
            
            delete [] arrayPtr;
            arrayPtr = nullptr;
            arrayPtr = new wordRecord[capacity];

            for(int j = 0; j < oldCapacity; j++)
            {
                arrayPtr[j] = newArray[j];
            }

            delete [] newArray;
            newArray = nullptr;

            timesDoubled++;
        }
        
        if (isCommonWord(temp, commonWords)){
            continue;
        }else if(numUniqueWords == 0){
            arrayPtr[numUniqueWords].word = temp;
            arrayPtr[numUniqueWords].count++;
            numUniqueWords++;
            isDuplicate = true;
        }else{
            for(int x = 0; x < numUniqueWords; x++)
            {
                if(arrayPtr[x].word == temp){
                    arrayPtr[x].count++;
                    isDuplicate = true;
                }
            }
        }

        if (!isDuplicate){
            arrayPtr[numUniqueWords].word = temp;
            arrayPtr[numUniqueWords].count++;
            numUniqueWords++;
        }

        if (numUniqueWords > 1)
        {
            sortArray(arrayPtr, numUniqueWords);
        }
        
    }
    
    readFile.close();
 
    cout << "Array doubled: " << timesDoubled << endl;
    cout << "Distinct uncommon words: " << numUniqueWords << endl;
    cout << "Total uncommon words: " << getTotalNumberUncommonWords(arrayPtr, numUniqueWords) << endl;
    cout << "Probability of next " << N << " words from rank " << M << endl;
    cout << "---------------------------------------" << endl;
    printNFromM(arrayPtr, M, N, getTotalNumberUncommonWords(arrayPtr, numUniqueWords));
    delete [] arrayPtr;
    return 0;
}