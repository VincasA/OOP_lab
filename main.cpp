#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>

struct Studentas {
    std::string Vardas;
    std::string Pavarde;
    std::vector<double> ND;
    double EGZ;
    double GalutinisVid;
    double GalutinisMed;
};

// Funkcija nuskaityt ir patikrint ar naudotojo ivestas skaicius yra tinkamas
double getValidGrade() {
    double rez;
    while (true) {
        std::cin >> rez;
        if (rez == -1) {
            break;
        } else if (std::cin.fail() || rez < 1.0 || rez > 10.0) {
            std::cout << "Skaicius netinka. Iveskite reiksme nuo 1 iki 10, arba -1 jei norite pabaigti: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return rez;
}


// Funkcija suskaiciuot namu darbu vidurki
double calculateHomeworkAverage(const std::vector<double>& paz) {
    double sum = 0.0;
    for (double pazymys : paz) {
        sum += pazymys;
    }
    return paz.empty() ? 0.0 : sum / paz.size();
}


// Funkcija suskaiciuot namu darbu rezultatu mediana
double calculateMedian(std::vector<double> paz) {
    if (paz.empty()) return 0.0;

    size_t size = paz.size();
    sort(paz.begin(), paz.end());

    if (size % 2 == 0) {
        return (paz[size / 2 - 1] + paz[size / 2]) / 2.0;
    } else {
        return paz[size / 2];
    }
}


// Funkcija suskaiciuot galutini rezultata
double calculateFinalGrade(double ND, double EGZ) {
    return 0.4 * ND + 0.6 * EGZ;
}

// Atsitiktinai generuotas skaicius nuo 1 iki 10
double generateRandomGrade() {
    int randomNumber = rand() % 10 + 1;
    return randomNumber;
}

int main() {
    std::vector<Studentas> studentai;
    Studentas temp;

    srand(time(0));
    
    std::cout << std::fixed << std::setprecision(2);

    while (true) {
        std::cout << "Iveskite studento varda (arba 'exit' jei norite pabaigti): ";
        std::cin >> temp.Vardas;
        if (temp.Vardas == "exit") break;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Iveskite studento pavarde: ";
        std::getline(std::cin, temp.Pavarde);

        std::cout << "Atsitiktinai generuoti pazymius? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice == 'y') {
            std::cout << "Iveskite namu darbu ivertinimu kieki: ";
            int numGrades;
            std::cin >> numGrades;
            for (int i = 0; i < numGrades; ++i) {
                temp.ND.push_back(generateRandomGrade());}
        }
        else{
        std::cout << "Iveskite studento namu darbu ivertinima (arba -1 kad pabaigti): ";
        double gradeInput;
        while (true) {
            gradeInput = getValidGrade();
            if (gradeInput == -1) break;
            temp.ND.push_back(gradeInput);
        }

        std::cout << "Iveskite studento egzamino rezultata: ";
        temp.EGZ = getValidGrade();
        }

        double homeworkAverage = calculateHomeworkAverage(temp.ND);
        double homeworkMedian = calculateMedian(temp.ND);
        temp.GalutinisVid = calculateFinalGrade(homeworkAverage, temp.EGZ);
        temp.GalutinisMed = calculateFinalGrade(homeworkMedian, temp.EGZ);

        studentai.push_back(temp);
        temp.ND.clear();

    }

    std::cout << std::left;
    std::cout << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas"
          << std::setw(20) << "Galutinis (Vid.)"
          << std::setw(20) << "Galutinis (Med.)" << std::endl;
    std::cout << std::string(70, '-') << std::endl;



    for (const auto& student : studentai) {
    std::cout << std::setw(15) << student.Pavarde
              << std::setw(15) << student.Vardas
              << std::setw(20) << student.GalutinisVid
              << std::setw(20) << student.GalutinisMed << std::endl;
}
    return 0;
}
