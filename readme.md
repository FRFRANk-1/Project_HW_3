## Author: Runcheng Li
github_link_this_project: https://github.com/FRFRANk-1/Project_HW_3

## Operating system: Window11. IDE: VS code

## Project_3 - "Real-time 2-D Object Recognition"

## To run task 1: 
<image_path> <kernel_size> <threshold_value> <max_val>

Obeservation 1: The higher kernel_size value -> The more smoothness of the image is, computation become heavy if kernel_size become larger than 35, plus the best kernal_size as tested should be less than 15.

Observation 2: The lower the threshold_value, the more light comes in, effect apply contrastly. Ideal threshold_value as tested: 100.

Observatio 3: Max_value is the maxmium receive for selecting light source, automatically set to 255 is fair enough for running.

terminal input examples: .\Project_HW_3 1 "D:/NEU study file/5330/Project_HW_3/Proj03Examples/img5p3.png" 15 100 255 5

## To run task 2:
<image_path> <dilation_size> <erosion_size>

Observation 1: The larger dilation_size, the more smoothness of the image is, and the noise will be reduce. Over large value can lose details of the image, where the optimal value currently is set at 1.

Observation 2: The larger erosion_size, the more details of image it might lose, where over-smoothing effect apply which decrease the effectiveness of image processing, also more computational time required. The optimal value currently is at 2

Observation 3: Apply dilated_effect value with 1 and erode_effect value at 2 appear has the best optimal graphic output, where is futher smooth out the edges for all different image (img1p3, img2p3, img5p3)

terminal input examples ->  
Selection_1: .\Project_HW_3 2 "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_1/img1p3_15,100,255,5/thresholded.jpg" 3 2

selection_2: .\Project_HW_3 2 "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_1/img2p3_15,100,255,5/thresholded.jpg" 3 2
 
selection_3: .\Project_HW_3 2 "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_1/img5p3_15,100,255,5/thresholded.jpg" 3 2

## To run task 3:
<image_path> <min_size>

Observation 1: With the larger min_size value input, the graph sementation get region would become less effective since the area size defined become large. currently with optimal value is 75 where the image results is good enough to detect small segment region but good enough not overdone losing detection of big region. 

Observation 2: 

There are basically two color phrase in the results image.

First, black color region does not being identified as components by the algorithm since they are smaller than the min_size threshold(75).

Second, blue color region is considered largest connected components that being identified since which is greater than the min_size threshold(75)
 
Last, other random color have been assigned to be considered as other connected components.

terminal input examples -> .\Project_HW_3 3 "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_1/img2p3_15,100,255,5/thresholded.jpg" 75

## To run task 4:

Observation 1: The green rectangles in the output images is to visualize the axis-aligned bounding boxes of regions that are larger than the specified min_size value(75).
in the results image of img1p3, img2p3, img5p3, because those image have been applied with morphological filter(dilated + erosion methods) which already smoothering the image, thus those 3 images all have pretty identical central moment location where is located sligthly one the left from the center image. By comparsion, I used one of the unfilter image, img4p3, which is the example image provided from the project resource, have not been applied to any morphological filter, thus the image results have a lot of green dots which represent the centroids of these image region. In conclusion, it is obvious that applied morphological filter before finding the centroid of image is cruicial.

Observation 2: 
for the task_4, here are the following features calcuated for each connected components.
- Area: The number of pixcels within the connected components
- Percent filed: the ratio of the area of connected component of its bounding box represented in percentage
- Aspect Ratio: The ratio of the width to height of the bounding box, where this feature to help determine the shape and orientation of the component
- Hu Moments: The set of numbers calculated from the moments of the connected components that are invariant to image transformation.

Taking img2p3 image and report as an examples.
in the component 1, with the largest area and a precent filed value of 79.9688%, also the component has a aspect ratio that is larger than 1, which mean the image is wider than the height, given this circumstance we could conclude that the component one should be a large gray box.
in the component 2, with a area number of 12 pixel, which is a very small area but with a high precent filed ratio, presummeably should be the green dot centroid in the image.
in the component 3, with the area of 98 pixel, percent filled 76.5625% and aspect ratio of 0.125, supposely should be the green vertical line near the right side of the image.
in the component 4, with the area of 185 pixel, percent filled 88.0925% and aspect ratio of 0.119, which should be the left side long line on the image

terminal input examples -> 
.\Project_HW_3 4 "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_1/img4p3_15,100,255,5/thresholded.jpg" 5

.\Project_HW_3 4 "D:/NEU study file/5330/Project_HW_3/Proj03Examples/img4p3.png" 5

## To run task 5:

Explanation: The task_5 collecting trainning data basically follow 4 major features functionalities: 1. Image Features data extraction obtainning [first: if we choose the image from the Proj03Examples which have 3 channels rgb, we convert it to grayscale first, then apply task_4 ImageProcessor::calculatePercentFilled & calcualteAspectRatio function defined eariler to formula the data for each image for further saving to the .txt file. We also choose the images that already been fliter by the previous task_2, also obtain the task_2 image features data] 2. Features saving to objectDB.txt file. 3. Task 5 implementation for display and save image to task_5 folder. 4. Combine image and dataset form into a comparsion image for data analyzation.

terminal input examples ->
.\Project_HW_3 5 "D:/NEU study file/5330/Project_HW_3/Proj03Examples/img5p3.png" 10

.\Project_HW_3 5 "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_2/img2p3_ 1 2/dilated_eroded.jpg" 10

## To run task 6:

terminal input examples -> 
.\Project_HW_3 6 "D:/NEU study file/5330/Project_HW_3/Report_Folder/task_2/img1p3_ 1 2/dilated_eroded.jpg" 10

.\Project_HW_3 6 "D:/NEU study file/5330/Project_HW_3/Proj03Examples/img4p3.png" 10