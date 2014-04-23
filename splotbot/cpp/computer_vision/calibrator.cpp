#include <stdexcept>
#include <opencv2/opencv.hpp>
#include <vector>
#include <stdio.h>
#include <unistd.h>

#include "calibrator.h"

using namespace std;

/**
 * Constructs a new image stitcher
 */
Calibrator::Calibrator(string configFile):configFile(configFile) {
    // Empty constructor
    // All fields are initialized at this point
}

/**
 * Create camera calibration matrices for the given images.
 * Returns whether calibration is successful
 */
bool Calibrator::calibrate(vector<cv::Mat> images,
        cv::Mat *distortionCoeffs, cv::Mat *intrinsicMatrix) {

    cout << "GOT IMAGES?? \n\n" << images.size() << "\n\n" << endl;
    int n_boards = 9;
    int board_w = 9;
    int board_h = 6;
    int board_total = board_w * board_h;

    cv::Size board_size = cv::Size(board_w,board_h);
    vector< vector< Point2f> > imagePoints;
    vector< vector< Point3f> > objectPoints;
 
    cv::Mat image;
    int hits = 0, runs = 0;
    for (auto it = images.begin(); it != images.end(); ++it) {
        runs++;
        image = (cv::Mat) (*it);

        cv::Mat gray;

        cvtColor(image, gray, CV_RGB2GRAY);
        vector< Point2f> corners;

        bool sCorner = findChessboardCorners(gray,board_size,corners);

        if(sCorner && corners.size() == board_total)
        {
            hits++;
            //cornerSubPix(gray, corners, Size(11,11),
            //Size(-1,-1), TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,
            //30, 0.1));
            drawChessboardCorners(image, board_size, corners, sCorner);

            vector<Point2f> v_tImgPT;
            vector<Point3f> v_tObjPT;

            //save 2d coordenate and world coordinate
            for(int j=0; j< corners.size(); ++j)
            {
                Point2f tImgPT;
                Point3f tObjPT;

                tImgPT.x = corners[j].x;
                tImgPT.y = corners[j].y;

                tObjPT.x = j%board_w;
                tObjPT.y = j/board_w;
                tObjPT.z = 0;

                v_tImgPT.push_back(tImgPT);
                v_tObjPT.push_back(tObjPT);
            }

            imagePoints.push_back(v_tImgPT);
            objectPoints.push_back(v_tObjPT);
        }
        return hits==runs;
    }

    vector<cv::Mat> rvecs, tvecs;
    cv::Mat intrinsic_Matrix(3,3, CV_64F);
    cv::Mat distortion_coeffs(8,1, CV_64F);

    calibrateCamera(objectPoints, imagePoints, image.size(),
            intrinsic_Matrix, distortion_coeffs, rvecs, tvecs);

    *distortionCoeffs = distortion_coeffs;
    *intrinsicMatrix = intrinsic_Matrix;

    cv::FileStorage fs(configFile,FileStorage::WRITE);
    fs << "distortion_coefficients" << distortion_coeffs;
    fs << "intrinsic_matrix" << intrinsic_Matrix;
}

void Calibrator::getCalibrationFromFile(cv::Mat *distortionCoeffs,
        cv::Mat *intrinsicMatrix){

    FileStorage fs(configFile,FileStorage::READ);

    fs["distortion_coefficients"] >> *distortionCoeffs;
    fs["intrinsic_matrix"] >> *intrinsicMatrix;

}

bool Calibrator::isCalibrated(){
    return access(configFile.c_str(), F_OK) != -1;
}

bool Calibrator::unCalibrate(){
    return remove(configFile.c_str()) != -1;
}
