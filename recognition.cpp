#include "recognition.h"
#include "ImageUtils.h"      // Shervin's handy OpenCV utility functions.



// Start training from the collected faces.
// The face recognition algorithm can be one of these and perhaps more, depending on your version of OpenCV, which must be atleast v2.4.1:
//    "FaceRecognizer.Eigenfaces":  Eigenfaces, also referred to as PCA (Turk and Pentland, 1991).
//    "FaceRecognizer.Fisherfaces": Fisherfaces, also referred to as LDA (Belhumeur et al, 1997).
//    "FaceRecognizer.LBPH":        Local Binary Pattern Histograms (Ahonen et al, 2006).
cv::Ptr<FaceRecognizer> learnCollectedFaces(const std::vector<Mat> preprocessedFaces, const std::vector<int> faceLabels, const cv::string facerecAlgorithm)
{
    cv::Ptr<FaceRecognizer> model;

    cout << "Learning the collected faces using the [" << facerecAlgorithm << "] algorithm ..." << endl;

    // Make sure the "contrib" module is dynamically loaded at runtime.
    // Requires OpenCV v2.4.1 or later (from June 2012), otherwise the FaceRecognizer will not compile or run!
    bool haveContribModule = initModule_contrib();
    if (!haveContribModule) {
        cerr << "ERROR: The 'contrib' module is needed for FaceRecognizer but has not been loaded into OpenCV!" << endl;
        exit(1);
    }

    // Use the new FaceRecognizer class in OpenCV's "contrib" module:
    // Requires OpenCV v2.4.1 or later (from June 2012), otherwise the FaceRecognizer will not compile or run!
    model = cv::Algorithm::create<FaceRecognizer>(facerecAlgorithm);
    if (model.empty()) {
        cerr << "ERROR: The FaceRecognizer algorithm [" << facerecAlgorithm << "] is not available in your version of OpenCV. Please update to OpenCV v2.4.1 or newer." << endl;
        exit(1);
    }

    // Do the actual training from the collected faces. Might take several seconds or minutes depending on input!
    model->train(preprocessedFaces, faceLabels);

    return model;
}

// Convert the matrix row or column (float matrix) to a rectangular 8-bit image that can be displayed or saved.
// Scales the values to be between 0 to 255.
cv::Mat getImageFrom1DFloatMat(const cv::Mat matrixRow, int height)
{
    // Make it a rectangular shaped image instead of a single row.
    cv::Mat rectangularMat = matrixRow.reshape(1, height);
    // Scale the values to be between 0 to 255 and store them as a regular 8-bit uchar image.
    cv::Mat dst;
    normalize(rectangularMat, dst, 0, 255, cv::NORM_MINMAX, CV_8UC1);
    return dst;

}

// Show the internal face recognition data, to help debugging.
void showTrainingDebugData(const cv::Ptr<FaceRecognizer> model, const int faceWidth, const int faceHeight)
{
    try {   // Surround the OpenCV calls by a try/catch block so we don't crash if some model parameters aren't available.

        // Show the average face (statistical average for each pixel in the collected images).
        cv::Mat averageFaceRow = model->get<cv::Mat>("mean");
        ImageUtils::printMatInfo(averageFaceRow, "averageFaceRow");
        // Convert the matrix row (1D float matrix) to a regular 8-bit image.
        cv::Mat averageFace = getImageFrom1DFloatMat(averageFaceRow, faceHeight);
        ImageUtils::printMatInfo(averageFace, "averageFace");
        imshow("averageFace", averageFace);

        // Get the eigenvectors
        cv::Mat eigenvectors = model->get<cv::Mat>("eigenvectors");
        ImageUtils::printMatInfo(eigenvectors, "eigenvectors");

        // Show the best 20 eigenfaces
        for (int i = 0; i < min(20, eigenvectors.cols); i++) {
            // Create a column vector from eigenvector #i.
            // Note that clone() ensures it will be continuous, so we can treat it like an array, otherwise we can't reshape it to a rectangle.
            // Note that the FaceRecognizer class already gives us L2 normalized eigenvectors, so we don't have to normalize them ourselves.
            cv::Mat eigenvectorColumn = eigenvectors.col(i).clone();
            //printMatInfo(eigenvectorColumn, "eigenvector");

            cv::Mat eigenface = getImageFrom1DFloatMat(eigenvectorColumn, faceHeight);
            //printMatInfo(eigenface, "eigenface");
            imshow(format("Eigenface%d", i), eigenface);
        }

        // Get the eigenvalues
        cv::Mat eigenvalues = model->get<cv::Mat>("eigenvalues");
        ImageUtils::printMat(eigenvalues, "eigenvalues");

        //int ncomponents = model->get<int>("ncomponents");
        //cout << "ncomponents = " << ncomponents << endl;

        std::vector<cv::Mat> projections = model->get<std::vector<cv::Mat> >("projections");
        cout << "projections: " << projections.size() << endl;
        for (int i = 0; i < (int)projections.size(); i++) {
            ImageUtils::printMat(projections[i], "projections");
        }

        //labels = model->get<Mat>("labels");
        //printMat(labels, "labels");

    } catch (cv::Exception e) {
        //cout << "WARNING: Missing FaceRecognizer properties." << endl;
    }

}


// Generate an approximately reconstructed face by back-projecting the eigenvectors & eigenvalues of the given (preprocessed) face.
cv::Mat reconstructFace(const cv::Ptr<cv::FaceRecognizer> model, const cv::Mat preprocessedFace)
{
    // Since we can only reconstruct the face for some types of FaceRecognizer models (ie: Eigenfaces or Fisherfaces),
    // we should surround the OpenCV calls by a try/catch block so we don't crash for other models.
    try {

        // Get some required data from the FaceRecognizer model.
        cv::Mat eigenvectors = model->get<cv::Mat>("eigenvectors");
        cv::Mat averageFaceRow = model->get<cv::Mat>("mean");

        int faceHeight = preprocessedFace.rows;

        // Project the input image onto the PCA subspace.
        cv::Mat projection = subspaceProject(eigenvectors, averageFaceRow, preprocessedFace.reshape(1,1));
        //printMatInfo(projection, "projection");

        // Generate the reconstructed face back from the PCA subspace.
        cv::Mat reconstructionRow = subspaceReconstruct(eigenvectors, averageFaceRow, projection);
        //printMatInfo(reconstructionRow, "reconstructionRow");

        // Convert the float row matrix to a regular 8-bit image. Note that we
        // shouldn't use "getImageFrom1DFloatMat()" because we don't want to normalize
        // the data since it is already at the perfect scale.

        // Make it a rectangular shaped image instead of a single row.
        cv::Mat reconstructionMat = reconstructionRow.reshape(1, faceHeight);
        // Convert the floating-point pixels to regular 8-bit uchar pixels.
        cv::Mat reconstructedFace = cv::Mat(reconstructionMat.size(), CV_8U);
        reconstructionMat.convertTo(reconstructedFace, CV_8U, 1, 0);
        //printMatInfo(reconstructedFace, "reconstructedFace");

        return reconstructedFace;

    } catch (cv::Exception e) {
        //cout << "WARNING: Missing FaceRecognizer properties." << endl;
        return cv::Mat();
    }
}


// Compare two images by getting the L2 error (square-root of sum of squared error).
double getSimilarity(const cv::Mat A, const cv::Mat B)
{
    if (A.rows > 0 && A.rows == B.rows && A.cols > 0 && A.cols == B.cols) {
        // Calculate the L2 relative error between the 2 images.
        double errorL2 = norm(A, B, CV_L2);
        // Convert to a reasonable scale, since L2 error is summed across all pixels of the image.
        double similarity = errorL2 / (double)(A.rows * A.cols);
        return similarity;
    }
    else {
        //cout << "WARNING: Images have a different size in 'getSimilarity()'." << endl;
        return 100000000.0;  // Return a bad value
    }
}
