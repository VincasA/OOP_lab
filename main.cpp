#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm> // For std::sort
#include <limits>
#include <cstdlib>  //required for rand(), srand()
#include <ctime>

struct Studentas {
    std::string Vardas;
    std::string Pavarde;
    std::vector<double> ND;
    double EGZ;
    double GalutinisVid; // Final grade using average
    double GalutinisMed; // Final grade using median
};

// Function to get a valid grade from the user
double getValidGrade() {
    double grade;
    while (true) {
        std::cin >> grade;
        if (grade == -1) {
            break; // Allow -1 to exit the loop
        } else if (std::cin.fail() || grade < 1.0 || grade > 10.0) {
            std::cout << "Invalid grade. Please enter a value between 1 and 10, or -1 to finish: ";
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the input
        } else {
            break; // Valid grade entered
        }
    }
    return grade;
}


// Function to calculate the average of homework grades
double calculateHomeworkAverage(const std::vector<double>& grades) {
    double sum = 0.0;
    for (double grade : grades) {
        sum += grade;
    }
    return grades.empty() ? 0.0 : sum / grades.size();
}


// Function to calculate the median of homework grades
double calculateMedian(std::vector<double> grades) {
    if (grades.empty()) return 0.0;

    size_t size = grades.size();
    sort(grades.begin(), grades.end());

    if (size % 2 == 0) {
        return (grades[size / 2 - 1] + grades[size / 2]) / 2.0;
    } else {
        return grades[size / 2];
    }
}


// Function to calculate the final grade
double calculateFinalGrade(double homeworkResult, double EGZ) {
    return 0.4 * homeworkResult + 0.6 * EGZ;
}

// Function to generate a random grade between 1 and 10
double generateRandomGrade() {
    int randomNumber = rand() % 10 + 1;
    return randomNumber;
}

int main() {
    std::vector<Studentas> studentai;
    Studentas temp;

    srand(time(0));
    
    std::cout << std::fixed << std::setprecision(2);

    // Gather data from the user
    while (true) {
        std::cout << "Enter the student's first name (or 'exit' to finish): ";
        std::cin >> temp.Vardas;
        if (temp.Vardas == "exit") break;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover newline

        std::cout << "Enter the student's last name: ";
        std::getline(std::cin, temp.Pavarde); // Use getline to allow names with spaces

        std::cout << "Generate grades randomly? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice == 'y') {
            std::cout << "Enter number of homework grades to generate: ";
            int numGrades;
            std::cin >> numGrades;
            for (int i = 0; i < numGrades; ++i) {
                temp.ND.push_back(generateRandomGrade());}
        }
        else{
        std::cout << "Enter the student's homework grades (type -1 to end): ";
        double gradeInput;
        while (true) {
            gradeInput = getValidGrade();
            if (gradeInput == -1) break;
            temp.ND.push_back(gradeInput);
        }

        std::cout << "Enter the student's exam grade: ";
        temp.EGZ = getValidGrade();
        }
        // Inside the while loop, after collecting grades
        double homeworkAverage = calculateHomeworkAverage(temp.ND);
        double homeworkMedian = calculateMedian(temp.ND);
        temp.GalutinisVid = calculateFinalGrade(homeworkAverage, temp.EGZ);
        temp.GalutinisMed = calculateFinalGrade(homeworkMedian, temp.EGZ);

        // Then add the modified student object to the list
        studentai.push_back(temp);
        temp.ND.clear();

    }

    // Output header
    std::cout << std::left;
    std::cout << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas"
          << std::setw(20) << "Galutinis (Vid.)"
          << std::setw(20) << "Galutinis (Med.)" << std::endl;
std::cout << std::string(70, '-') << std::endl;



    // Output the data for each student
    for (const auto& student : studentai) {
    std::cout << std::setw(15) << student.Pavarde
              << std::setw(15) << student.Vardas
              << std::setw(20) << student.GalutinisVid
              << std::setw(20) << student.GalutinisMed << std::endl;
}

    return 0;
}
