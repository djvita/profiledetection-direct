#ifndef DETECTOBJECT_H
#define DETECTOBJECT_H

#pragma once


#include <stdio.h>
#include <iostream>
#include <vector>

// Include OpenCV's C++ Interface
#include "opencv2/opencv.hpp"
#include <opencv2/opencv.hpp>
#include "iostream"
#include "cv.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

class detectObject
{
public:
    // Search for just a single object in the image, such as the largest face, storing the result into 'largestObject'.
    // Can use Haar cascades or LBP cascades for Face Detection, or even eye, mouth, or car detection.
    // Input is temporarily shrunk to 'scaledWidth' for much faster detection, since 240 is enough to find faces.
    // Note: detectLargestObject() should be faster than detectManyObjects().
    static void detectLargestObject(const cv::Mat &img, cv::CascadeClassifier &cascade, cv::Rect &largestObject, int scaledWidth = 320);


    // Search for many objects in the image, such as all the faces, storing the results into 'objects'.
    // Can use Haar cascades or LBP cascades for Face Detection, or even eye, mouth, or car detection.
    // Input is temporarily shrunk to 'scaledWidth' for much faster detection, since 240 is enough to find faces.
    // Note: detectLargestObject() should be faster than detectManyObjects().
    static void detectManyObjects(const cv::Mat &img, cv::CascadeClassifier &cascade, std::vector<Rect> &objects, int scaledWidth = 320);

    static void detectObjectsCustom(const Mat &img, CascadeClassifier &cascade, vector<Rect> &objects, int scaledWidth, int flags, Size minFeatureSize, float searchScaleFactor, int minNeighbors);

};



#endif // DETECTOBJECT_H
