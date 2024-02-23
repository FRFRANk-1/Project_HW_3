#include "TaskRunner.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <task_number> <image_path> [additional_parameters]" << std::endl;
        std::cerr << "For Task 1: [image_path] [kernel_size] [threshold_value] [max_val]" << std::endl;
        std::cerr << "For Task 2: [image_path] [dilation_size] [erosion_size]" << std::endl;
        std::cerr << "For Task 3: [image_path] [min_size]" << std::endl;
        std::cerr << "For Task 4: [image_path] [min_size]" << std::endl;
        return -1;
    }

    int taskNumber = std::stoi(argv[1]);
    std::string imagePath = argv[2];
    TaskRunner runner;

    switch (taskNumber) {
        case 1:
            if (argc != 6) {
                std::cerr << "Usage for Task 1: " << argv[0] << " 1 <image_path> <kernel_size> <threshold_value> <max_val>" << std::endl;
                return -1;
            }
            {
                int kernelSize = std::stoi(argv[3]);
                int thresholdValue = std::stoi(argv[4]);
                int maxVal = std::stoi(argv[5]);
                runner.runTask1(imagePath, kernelSize, thresholdValue, maxVal);
            }
            break;
        case 2:
            if (argc != 5) {
                std::cerr << "Usage for Task 2: " << argv[0] << " 2 <image_path> <dilation_size> <erosion_size>" << std::endl;
                return -1;
            }
            {
                int dilationSize = std::stoi(argv[3]);
                int erosionSize = std::stoi(argv[4]);
                runner.runTask2(imagePath, dilationSize, erosionSize);
            }
            break;
        case 3:
            if (argc != 4) {
                std::cerr << "Usage for Task 3: " << argv[0] << " 3 <image_path> <min_size>" << std::endl;
                return -1;
            }
            {
                int minSize = std::stoi(argv[3]);
                runner.runTask3(imagePath, minSize);
            }
            break;
        case 4:
            if (argc != 4) {
                std::cerr << "Usage for Task 4: " << argv[0] << " 4 <image_path> <min_size>" << std::endl;
                return -1;
            }
            {
                int minSize = std::stoi(argv[3]);
                runner.runTask4(imagePath, minSize);
            }
            break;
        default:
            std::cerr << "Error: Unknown task number." << std::endl;
            return -1;
    }

    return 0;
}
