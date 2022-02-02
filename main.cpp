#include "sortic.h"

int itc_len(string str){
    long long kol = 0;
    for(long long i = 0; str[i] != '\0'; i++){
        kol++;
    }
    return kol;
}

long long itc_toInt(string s){
    long long num = 0;
    for(long long i = 0; i < itc_len(s); i++){
        if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            return 0;
        num += s[i] - 48;
        num *= 10;
    }
    num /= 10;
    return num;
}

void printArray(const vector<int> arr, ofstream &inputToFile){
    for(long long i = 0; i < arr.size(); i++){
        cout << arr[i] << " ";
        inputToFile << arr[i] << " ";
    }
    inputToFile << endl;
    cout << endl;
}

bool isSorted(vector<int> arr){
    long long length = arr.size();
    if(length <= 1)
        return true;
    for(long long i = 0; i < length - 1; i++){
        if(arr[i] > arr[i + 1])
            return false;
    }
    return true;
}

int maxNumIndex(vector<int> arr){
    int length = arr.size();
    if(length == 0 || length == 1)
        return 0;
    int index = 0;
    for(long long i = 1; i < length - 1; i++){
        if(arr[i] > arr[index])
            index = i;
    }
    if(arr[length - 1] > arr[index])
        index = length - 1;
    return index;
}

void printStep(const vector<int> &a, const vector<int> &b, HANDLE Console, string functionName, ofstream &outputToFile){
    SetConsoleTextAttribute(Console, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    cout << functionName << endl;
    outputToFile << functionName << endl;
    SetConsoleTextAttribute(Console, 15);
    cout << "Vector a: ";
    outputToFile << "Vector a: ";
    printArray(a, outputToFile);
    cout << "Vector b: ";
    outputToFile << "Vector b: ";
    printArray(b, outputToFile);
    outputToFile << endl;
    cout << endl;
}

void sorter(vector<int> &a, vector<int> &b, HANDLE Console, ofstream &outputToFile){
    int buffer;
    if(!isSorted(a)){
        while(a.size() != 0){
            buffer = maxNumIndex(a);
            for(long long i = 0; i < buffer; i++){
                rra(a);
                printStep(a, b, Console, "rra", outputToFile);
            }
            pb(b, a);
            printStep(a, b, Console, "pb", outputToFile);
        }
        cout << endl;
        printArray(b, outputToFile);
    }
    else
        printArray(a, outputToFile);
    outputToFile.close();
}

bool checkFileName(string name){
    int length = itc_len(name);
    if(length > 32)
        return false;
    string forbiddenChars = "\\/?:*\"><|";
    for(long long i = 0; i < length; i++){
        for(int j = 0; j < 10; j++){
            if(forbiddenChars[j] == name[i]){
                cout << forbiddenChars << " <---- these symbols are forbidden!" << endl;
                return false;
            }
        }
    }
    return true;
}

string outputFileName(){
    string line;
    cout << "Input file name(max 32 characters): ";
    cin >> line;
    while(!checkFileName(line)){
        cout << "Input file name(max 32 characters): ";
        cin >> line;
    }
    return line;
}

void readFromFile(ifstream &inputFromFile, vector<int> &a){
    string stringOfNumbers = "";
    string bufferStringForReading;
    for(inputFromFile >> bufferStringForReading; !inputFromFile.eof(); inputFromFile >> bufferStringForReading)
        stringOfNumbers += bufferStringForReading + " ";
    long long length = itc_len(stringOfNumbers);
    bufferStringForReading = "";
    for(long long i = 0; i < itc_len(stringOfNumbers); i++){
        if(!(stringOfNumbers[i] >= '0' && stringOfNumbers[i] <= '9')){
            if(itc_len(bufferStringForReading) != 0)
                a.push_back(itc_toInt(bufferStringForReading));
            bufferStringForReading = "";
        }
        else
            bufferStringForReading += stringOfNumbers[i];
    }
    inputFromFile.close();
}
//SWAP
//sa(sb) swap first 2 of a(b)
//ss

//PUT TO A, PUT TO B
//pa(a, b) delete first of b and put it to a
//pb(b, a)

//ra(a), rb(b) shift elements of a vector to the one right
//rr
//rra(a), rrb(b) shift element of a vector to the one left
//rrr
int main(){
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    bool WantToRead = false;
    string line;
    vector<int> a, b;
    cout << "Do you want to read from file? Type \"yes\" if you do: ";
    cin >> line;
    if(line == "yes"){
        WantToRead = true;
        cout << "Enter name of the file to read from: ";
        cin >> line;
        ifstream inputFromFile("d:\\project\\SorticProject\\" + line + ".txt");
        while(!inputFromFile){
            cout << "There is no such file!" << endl << "Try again: ";
            cin >> line;
            inputFromFile.open("d:\\project\\SorticProject\\" + line + ".txt");
        }
        readFromFile(inputFromFile, a);
    }
    line = outputFileName();
    ofstream outputToFile("d:\\project\\SorticProject\\" + line + ".txt");
    if(!WantToRead){
        cin >> line;
        outputToFile << line << endl;
        while(line != "!"){
            a.push_back(itc_toInt(line));
            cin >> line;
            outputToFile << line << endl;
        }
    }
    cout << "Start: ";
    outputToFile << "Start: ";
    printArray(a, outputToFile);
    outputToFile << endl;
    cout << endl;
    sorter(a, b, Console, outputToFile);
}
