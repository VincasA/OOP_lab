#include "calculateMedian.h"
#include <algorithm>

double calculateMedian(std::vector<double> paz) {
    if (paz.empty()) return 0.0;

    size_t size = paz.size();
    std::sort(paz.begin(), paz.end());

    if (size % 2 == 0) {
        return (paz[size / 2 - 1] + paz[size / 2]) / 2.0;
    } else {
        return paz[size / 2];
    }
}