#ifndef RECOGNITION_H
#define RECOGNITION_H
#pragma once


#include <stdio.h>
#include <iostream>
#include <vector>

// Include OpenCV's C++ Interface
#include "opencv2/opencv.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

class recognition
{
public:
    // Start training from the collected faces.
    // The face recognition algorithm can be one of these and perhaps more, depending on your version of OpenCV, which must be atleast v2.4.1:
    //    "FaceRecognizer.Eigenfaces":  Eigenfaces, also referred to as PCA (Turk and Pentland, 1991).
    //    "FaceRecognizer.Fisherfaces": Fisherfaces, also referred to as LDA (Belhumeur et al, 1997).
    //    "FaceRecognizer.LBPH":        Local Binary Pattern Histograms (Ahonen et al, 2006).
    static cv::Ptr<FaceRecognizer> learnCollectedFaces(const std::vector<Mat> preprocessedFaces, const std::vector<int> faceLabels, const cv::string facerecAlgorithm = "FaceRecognizer.Eigenfaces");

    // Show the internal face recognition data, to help debugging.
    static void showTrainingDebugData(const cv::Ptr<FaceRecognizer> model, const int faceWidth, const int faceHeight);

    // Generate an approximately reconstructed face by back-projecting the eigenvectors & eigenvalues of the given (preprocessed) face.
    static cv::Mat reconstructFace(const cv::Ptr<FaceRecognizer> model, const cv::Mat preprocessedFace);

    // Compare two images by getting the L2 error (square-root of sum of squared error).
    static double getSimilarity(const cv::Mat A, const cv::Mat B);
};

#endif // RECOGNITION_H
