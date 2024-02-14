#include <iostream>

using namespace std;

struct studentas{
    string vardas;
    string pavarde;
    int ND;
    int EGZ;
};

int main()
{
    studentas X;
    cout << "Iveskite varda" << endl;
    cin >> X.vardas;
    cout << "Iveskite pavarde" << endl;
    cin >> X.pavarde;
    cout << "Iveskite ND rezultata" << endl;
    cin >> X.ND;
    cout << "Iveskite egzamino rezultata" << endl;
    cin >> X.EGZ;
}