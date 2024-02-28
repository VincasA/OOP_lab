#include "calculateHomeworkAverage.h"

double calculateHomeworkAverage(const std::vector<double>& paz) {
    double sum = 0.0;
    for (double pazymys : paz) {
        sum += pazymys;
    }
    return paz.empty() ? 0.0 : sum / paz.size();
}