#include <stdexcept>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "customstitcher.h"

using namespace std;

/**
 * Constructs a new CustomStitcher
 */
CustomStitcher::CustomStitcher() {
    // Empty constructor
}

/**
 * Stitches together the given vector of images
 */
cv::Mat CustomStitcher::stitch(vector<cv::Mat> images) {
    cv::Mat result = images[0];

    for (int i = 1; i < images.size(); i++) {
        cv::Mat image = images[i];
        result = stitchTwo(result, image);
    }

    return result;
}


/**
 * Stitches together the given two images
 */
cv::Mat CustomStitcher::stitchTwo(cv::Mat image1, cv::Mat image2) {
    cv::Mat gray_image1;
    cv::Mat gray_image2;

    // Convert to Grayscale
    cv::cvtColor( image1, gray_image1, CV_RGB2GRAY );
    cv::cvtColor( image2, gray_image2, CV_RGB2GRAY );
     
    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;
     
    cv::SurfFeatureDetector detector( minHessian );
     
    std::vector< cv::KeyPoint > keypoints_object, keypoints_scene;
     
    detector.detect( gray_image1, keypoints_object );
    detector.detect( gray_image2, keypoints_scene );
     
    //-- Step 2: Calculate descriptors (feature vectors)
    cv::SurfDescriptorExtractor extractor;
     
    cv::Mat descriptors_object, descriptors_scene;
     
    extractor.compute( gray_image1, keypoints_object, descriptors_object );
    extractor.compute( gray_image2, keypoints_scene, descriptors_scene );
     
    //-- Step 3: Matching descriptor vectors using FLANN matcher
    cv::FlannBasedMatcher matcher;
    std::vector< cv::DMatch > matches;
    matcher.match( descriptors_object, descriptors_scene, matches );
     
    double max_dist = 0; double min_dist = 100;
     
    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors_object.rows; i++ ) {
        double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }
     
    printf("-- Max dist : %f \n", max_dist );
    printf("-- Min dist : %f \n", min_dist );
     
    //-- Use only "good" matches (i.e. whose distance is less than 3*min_dist )
    std::vector< cv::DMatch > good_matches;
     
    for( int i = 0; i < descriptors_object.rows; i++ ) {
        if( matches[i].distance < 3*min_dist ) {
            good_matches.push_back( matches[i]);
        }
    }

    std::vector< cv::Point2f > obj;
    std::vector< cv::Point2f > scene;
     
    for( int i = 0; i < good_matches.size(); i++ ) {
        //-- Get the keypoints from the good matches
        obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
    }
 
    // Find the Homography Matrix
    cv::Mat H = cv::findHomography( obj, scene, CV_RANSAC );
    
    // Use the Homography Matrix to warp the images
    cv::Mat result;
    cv::warpPerspective(image1,result,H,cv::Size(image1.cols+image2.cols,image1.rows));
    cv::Mat half(result,cv::Rect(0,0,image2.cols,image2.rows));
    image2.copyTo(half);

    return result; 
}
