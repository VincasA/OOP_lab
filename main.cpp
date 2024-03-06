#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <fstream>
#include <sstream>
#include <vector>

#include "Studentas.h"
#include "calculateHomeworkAverage.h"
#include "calculateMedian.h"
#include "calculateFinalGrade.h"

int main() {
    std::vector<Studentas> studentai;
    Studentas temp;

    // Atidaryti input faila
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

    bool validInput = false;
    while (!validInput) {
        std::cout << "Pasirinkite apskaiciavimo buda ('vidurkis' arba 'mediana'): ";
        std::string calculationMethod;
        std::cin >> calculationMethod;

        if (calculationMethod == "vidurkis" || calculationMethod == "mediana") {
            validInput = true;

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
                temp.ND.erase(std::remove_if(temp.ND.begin(), temp.ND.end(), [](double g) { return g < 1.0 || g > 10.0; }), temp.ND.end());

                double finalGrade;
                if (calculationMethod == "vidurkis") {
                    finalGrade = calculateFinalGrade(calculateHomeworkAverage(temp.ND), temp.EGZ);
                } else {  // calculationMethod == "mediana"
                    finalGrade = calculateFinalGrade(calculateMedian(temp.ND), temp.EGZ);
                }

                temp.GalutinisVid = finalGrade;
                temp.GalutinisMed = finalGrade;

                studentai.push_back(temp);
                temp.ND.clear();
            }

            // Skirti studentus i dvi grupes pagal galutini rezultata
            std::vector<Studentas> kietieji;
            std::vector<Studentas> nuskriaustieji;

            for(const auto &student : studentai) {
                if(student.GalutinisVid>=5.0){
                    kietieji.push_back(student);
                } else {
                    nuskriaustieji.push_back(student);
                }
            } 

            // Atidaryti output failus
            std::ofstream outkietieji("kietieji.txt");
            std::ofstream outnuskriaustieji("nuskriaustieji.txt");

            if (!outkietieji.is_open() || !outnuskriaustieji.is_open()) {
                std::cerr << "Neisejo atidaryti output failu." << std::endl;
                return EXIT_FAILURE;
            }

            // Spausdinti antrastes
            outkietieji << std::left
                                  << std::setw(15) << "Pavarde"
                                  << std::setw(15) << "Vardas"
                                  << std::setw(20) << "Galutinis (" << calculationMethod << ")" << std::endl;
            outkietieji << std::string(45, '-') << std::endl;

            outnuskriaustieji << std::left
                              << std::setw(15) << "Pavarde"
                              << std::setw(15) << "Vardas"
                              << std::setw(20) << "Galutinis (" << calculationMethod << ")" << std::endl;
            outnuskriaustieji << std::string(45, '-') << std::endl;

            // Spausdinami rezultatai i atitinkamus failus
            for (const auto &student : kietieji) {
                outkietieji << std::setw(15) << student.Pavarde
                                      << std::setw(15) << student.Vardas;
                outkietieji << std::fixed << std::setprecision(2);
                outkietieji << std::setw(20) << ((calculationMethod == "vidurkis") ? student.GalutinisVid : student.GalutinisMed) << std::endl;
            }

            for (const auto &student : nuskriaustieji) {
                outnuskriaustieji << std::setw(15) << student.Pavarde
                                  << std::setw(15) << student.Vardas;
                outnuskriaustieji << std::fixed << std::setprecision(2);
                outnuskriaustieji << std::setw(20) << ((calculationMethod == "vidurkis") ? student.GalutinisVid : student.GalutinisMed) << std::endl;
            }

            // Uzdaryti output failus
            outkietieji.close();
            outnuskriaustieji.close();

        } else {
            std::cerr << "Netinka. Pasirinkite 'vidurkis' arba 'mediana'." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    file.close(); // Uzdaryti input faila

    return 0;
}