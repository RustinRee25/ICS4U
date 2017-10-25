#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cstdio>
#include <stdio.h>
#include <apstring.cpp>
#include <apstring.h>
#include <string.h>
#include <string>
#include <fstream>
#include <time.h>
#include <apmatrix.h>
#include <limits.h>
using namespace std;
class justinStack{
private:
    vector<string> stackParts;
public:
    void push(string number){
        stackParts.resize(stackParts.size()+1);
        for (int i = stackParts.size()-1; i > 0; i--){
            stackParts[i] = stackParts[i-1];
        }
        stackParts[0] = number;
    }
    string pop(){
        string temp = stackParts[0];
        for (int i = 0; i < stackParts.size()-1; i++){
                stackParts[i] = stackParts[i+1];
        }
        stackParts.resize(stackParts.size()-1);
        return temp;
    }
    bool isEmpty(){
        if (stackParts.size() <= 0)
            return true;
        else
            return false;
    }
};
class calculator:justinStack {
  //  private:
};

float doMath(justinStack &stack, string operation){
    if (operation == "*"){
        string s1 = stack.pop();
        string s2 = stack.pop();
        if (s1 == "+" || s1 == "-" || s1 == "/" || s1 == "*"){
            return stoi(s2) * doMath(stack, s1);
        }
        else if (s2 == "+" || s2 == "-" || s2 == "/" || s2 == "*"){
            return stoi(s1) * doMath(stack, s2);
        }
        else
            return stoi(s2) * stoi(s1);
    }
    else if (operation == "+"){
        string s1 = stack.pop();
        string s2 = stack.pop();
        if (s1 == "+" || s1 == "-" || s1 == "/" || s1 == "*"){
            return stoi(s2) + doMath(stack, s1);
        }
        else if (s2 == "+" || s2 == "-" || s2 == "/" || s2 == "*"){
            return stoi(s1) + doMath(stack, s2);
        }
        else
            return stoi(s2) + stoi(s1);
    }
    else if (operation == "-"){
        string s1 = stack.pop();
        string s2 = stack.pop();
        if (s1 == "+" || s1 == "-" || s1 == "/" || s1 == "*"){
            return stoi(s2) - doMath(stack, s1);
        }
        else if (s2 == "+" || s2 == "-" || s2 == "/" || s2 == "*"){
            return  doMath(stack, s2) - stoi(s1);
        }
        else
            return stoi(s2) - stoi(s1);
    }
    else if (operation == "/"){
        string s1 = stack.pop();
        string s2 = stack.pop();
        if (s1 == "+" || s1 == "-" || s1 == "/" || s1 == "*"){
            return stoi(s2) / (float)doMath(stack, s1);
        }
        else if (s2 == "+" || s2 == "-" || s2 == "/" || s2 == "*"){
            return  doMath(stack, s2) / (float)stoi(s1);
        }
        else
            return stoi(s2) / (float)stoi(s1);
    }
    return -32;
}
int main(){
    string line;
    justinStack stack;
    //vector for number of spaces
    vector<int> spaceLocations;
    int operationCounter = 0;

    getline(cin,line);

    for (int i = 0; i < line.size(); i++){
        if (line.substr(i,1) == " "){
            spaceLocations.push_back(i);
            }
    }
    //reads in the first string
    stack.push(line.substr(0,spaceLocations[0]));

    for (int i = 0; i < spaceLocations.size(); i++){
        stack.push(line.substr(spaceLocations[i]+1, spaceLocations[i+1]-spaceLocations[i]-1));
    }

    cout << doMath(stack, stack.pop());
}
