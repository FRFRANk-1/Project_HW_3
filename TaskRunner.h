#ifndef TASKRUNNER_H
#define TASKRUNNER_H

#include "ImageProcessor.h"

class TaskRunner {
public:
    void runTask1(const std::string& imageFolder, int kernelSize, int thresholdValue, int maxVal, int thresholdType); // Task for thresholding and blurring
    // Add declarations for other tasks as needed
};

#endif // TASKRUNNER_H
