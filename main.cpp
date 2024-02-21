#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <fstream>
#include <sstream>
#include <vector>

struct Studentas {
    std::string Vardas;
    std::string Pavarde;
    std::vector<double> ND;
    double EGZ;
    double GalutinisVid;
    double GalutinisMed;
};

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

int main() {
    std::vector<Studentas> studentai;
    Studentas temp;

    //Atidaryti input faila
    std::ifstream file("studentai10000.txt");
    if (!file.is_open()) {
        std::cerr << "Neisejo atidaryti input failo '" << std::endl;
        return EXIT_FAILURE;
    }

     // Atidaryti output faila
    std::ofstream outfile("studentai_rezultatai.txt");
    if (!outfile.is_open()) {
        std::cerr << "Neisejo atidaryti output failo." << std::endl;
        return EXIT_FAILURE;
    }
    
    std::cout << std::fixed << std::setprecision(2);

    std::string line;
    
    // Ignoruoti pirma input eilute
    std::getline(file, line);

    while (getline(file, line)) {
        std::istringstream iss(line);
        Studentas temp;
        iss >> temp.Vardas >> temp.Pavarde;
        
        double grade;
        while (iss >> grade) {
            // Nuskaityti ir laikyti ND rezultatus vektoriuje
            temp.ND.push_back(grade);
        }
        
        // Patikrinti ar tinkamas paskutinis skaicius (egzamo rezultatas) ir perkelti ji i ND vektoriu
        if (!temp.ND.empty() && temp.ND.back() >= 1.0 && temp.ND.back() <= 10.0) {
            temp.EGZ = temp.ND.back();
            temp.ND.pop_back();
        } else {
            std::cerr << "Error: Netinkamas arba nera egzamino rezultato '" << temp.Vardas << " " << temp.Pavarde << "'." << std::endl;
            continue; // Praleisti studenta jei egzamino rezultatas yra netinkamas arba nera
        }

        // Validate homework grades and remove invalid ones
        temp.ND.erase(std::remove_if(temp.ND.begin(), temp.ND.end(), [](double g){ return g < 1.0 || g > 10.0; }), temp.ND.end());

        temp.GalutinisVid = calculateFinalGrade(calculateHomeworkAverage(temp.ND), temp.EGZ);
        temp.GalutinisMed = calculateFinalGrade(calculateMedian(temp.ND), temp.EGZ);

        studentai.push_back(temp);
        temp.ND.clear();

    }

    file.close(); // Uzdaryti input faila

    // Spausdinti antraste
    outfile << std::left
            << std::setw(15) << "Pavarde"
            << std::setw(15) << "Vardas"
            << std::setw(20) << "Galutinis (Vid.)"
            << std::setw(20) << "Galutinis (Med.)" << std::endl;
    outfile << std::string(70, '-') << std::endl;

    // Spausdinami rezultatai
    for (const auto& student : studentai) {
        outfile << std::setw(15) << student.Pavarde
                << std::setw(15) << student.Vardas;
                outfile << std::fixed << std::setprecision(2);
                outfile << std::setw(20) << student.GalutinisVid
                << std::setw(20) << student.GalutinisMed << std::endl;
    }

    // Uzdaryti output faila
    outfile.close();

    return 0;
}