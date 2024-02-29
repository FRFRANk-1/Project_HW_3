#ifndef TASKRUNNER_H
#define TASKRUNNER_H

#include "ImageProcessor.h"
#include "labeler.h"

class TaskRunner {
public:
    void runTask1(const std::string& imagePath, int kernelSize, int thresholdValue, int maxVal); // Task for thresholding and blurring
    
    void runTask2(const std::string& imagePath, int dilation_size, int erosion_size);

    void runTask3(const std::string& imagePath, int minSize);

    void runTask4(const std::string& imagePath, int minSize);

    void runTask5(const std::string& folderPath, const std::string& imagePath, int minSize);

    void runTask6(const std::string& imagePath, int minSize);

    void runTask7(const std::vector<std::pair<std::string, std::string>>& imageData, const std::string& databasePath);

    void runTask8(const std::vector<std::pair<std::string, std::string>>& imageData, const std::string& databasePath, int k);

};


#endif // TASKRUNNER_H
