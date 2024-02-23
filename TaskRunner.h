#ifndef TASKRUNNER_H
#define TASKRUNNER_H

#include "ImageProcessor.h"

class TaskRunner {
public:
    void runTask1(const std::string& imagePath, int kernelSize, int thresholdValue, int maxVal); // Task for thresholding and blurring
    
    void runTask2(const std::string& imagePath, int dilation_size, int erosion_size);

    void runTask3(const std::string& imagePath, int minSize);
};

#endif // TASKRUNNER_H
