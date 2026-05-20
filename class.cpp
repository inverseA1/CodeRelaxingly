#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Person {
    string name;
    int age;
public:
    Person() : name("Unknown"), age(0) {}
    Person(string n, int a) : name(n), age(a) {}

    void GetName(string name_){name = name_;}
    
    void display() {
        cout << name << ", " << age << "岁" << endl;
    }
};

int main() {
    Person person[10];
    string str;
    string name;
    int i = 0;

    getline(cin, str);
    stringstream str_(str);
    while(getline(str_,name,',')){
        person[i].GetName(name);
        i++;
    }

    for(int j = 0 ; j < i ; j++){
        person[j].display();
    }

    return 0;
}