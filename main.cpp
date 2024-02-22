#include "TaskRunner.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " <task_number> <image_folder> <kernel_size> <threshold_value> <maxval> <thresh_type>" << std::endl;
        return -1;
    }

    int taskNumber = std::stoi(argv[1]);
    std::string imageFolder = argv[2];
    int kernelSize = std::stoi(argv[3]);
    int thresholdValue = std::stoi(argv[4]);
    int maxVal = std::stoi(argv[5]);
    int thresholdType = std::stoi(argv[6]);

    TaskRunner runner;

    switch (taskNumber) {
        case 1:
            runner.runTask1(imageFolder, kernelSize, thresholdValue, maxVal, thresholdType);
            break;
        // Add cases for other tasks
        default:
            std::cerr << "Error: Unknown task number." << std::endl;
    }

    return 0;
}