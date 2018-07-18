//
// Created by haotian on 7/18/18.
//
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv){
    if (argc != 3) {
        cout << "usage: feature_extraction img1 img2" << endl;
        return 1;
    }

    // --read images
    Mat img_1 = imread( argv[1], CV_LOAD_IMAGE_COLOR );
    Mat img_2 = imread( argv[2], CV_LOAD_IMAGE_COLOR );

    // --initialization
    vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptors_1, descriptors_2;
    Ptr<ORB> orb = ORB::create( 500, 1.2f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31, 20);

    // --compute ORB descriptors based on key-points
    orb->detect( img_1, keypoints_1, descriptors_1 );
    orb->detect( img_2, keypoints_2, descriptors_2 );

    // --compute BRIEF
    orb->compute( img_1, keypoints_1, descriptors_1);
    orb->compute( img_2, keypoints_2, descriptors_2);

    Mat outimg1;
    drawKeypoints( img_1, keypoints_1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
    imshow("ORB Features", outimg1);

    // --compute Hamming distance between two imgs
    vector<DMatch> matches;
    BFMatcher matcher (NORM_HAMMING);
    matcher.match( descriptors_1, descriptors_2, matches );

    // --do the selection
    // compute min_dist and max_dist
    double min_dist=10000, max_dist=0;
    for (int i = 0; i < descriptors_1.rows; i++) {
        double dist = matches[i].distance;
        if (dist < min_dist ) min_dist = dist;
        if (dist > max_dist ) max_dist = dist;
    }

    printf( "-- Max dist: %f \n", max_dist );
    printf( "-- Min dist: %f \n", min_dist );

    // if distance > 2*min_dist, cause error
    // Usually, Hamming distance < 2*min_dist
    vector<DMatch> good_matches;
    for (int j = 0; j < descriptors_1.rows; j++) {
        if (matches[j].distance <= max( 2*min_dist, 30.0 )){
            good_matches.push_back( matches[j] );
        }
    }

    // Visualization
    Mat img_match;
    Mat img_goodmatch;

    drawMatches( img_1, keypoints_1, img_2, keypoints_2, matches, img_match );
    drawMatches( img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch );

    imshow("All matches", img_match);
    imshow("Only good matches", img_goodmatch);
    waitKey(0);

    destroyAllWindows();
    return 0;
}
