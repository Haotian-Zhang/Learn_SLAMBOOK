//
// Created by haotian on 7/18/18.
//

#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
using namespace std;
using namespace cv;


/* Pay attention, here the epipolar constraint are extracted from
 * x_2 = R*x_1 + t (img1 -> img2)*/
void find_feature_matches (
        const Mat& img_1, const Mat& img_2,
        std::vector<KeyPoint>& keypoints_1,
        std::vector<KeyPoint>& keypoints_2,
        std::vector< DMatch >& matches );

void pose_estimation_2d2d(
        vector<KeyPoint> keypoints_1,
        vector<KeyPoint> keypoints_2,
        vector<DMatch> matches,
        Mat& R, Mat& t);

Point2d pixel2cam ( const Point2d& p, const Mat& K );

int main( int argc, char** argv){
    if (argc != 3){
        cout << "usage: feature extraction img1 img2" << endl;
        return 1;
    }
    Mat img_1 = imread( argv[1], CV_LOAD_IMAGE_COLOR );
    Mat img_2 = imread( argv[2], CV_LOAD_IMAGE_COLOR );

    vector<KeyPoint> keypoints_1, keypoints_2;
    vector<DMatch> matches;
    find_feature_matches( img_1, img_2, keypoints_1, keypoints_2, matches);
    cout << "All found " << matches.size() << " keypoints" << endl;

    // R,t estimation
    Mat R, t;
    pose_estimation_2d2d( keypoints_1, keypoints_2, matches, R, t );

    // Verification: E=t^R*scale
    Mat t_x = ( Mat_<double> ( 3,3 ) <<
                                     0,                      -t.at<double> ( 2,0 ),     t.at<double> ( 1,0 ),
            t.at<double> ( 2,0 ),      0,                      -t.at<double> ( 0,0 ),
            -t.at<double> ( 1.0 ),     t.at<double> ( 0,0 ),      0 );
    cout << "t^R" << endl << t_x*R << endl;

    // Verification: Epipolar constraint = 0
    Mat K = ( Mat_<double> ( 3,3 ) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1 );
    for (DMatch m: matches) {
        Point2d pt1 = pixel2cam (keypoints_1[m.queryIdx].pt, K);
        Mat y1 = ( Mat_<double> ( 3,1 ) << pt1.x, pt1.y, 1 );
        Point2d pt2 = pixel2cam (keypoints_2[m.trainIdx].pt, K);
        Mat y2 = ( Mat_<double> ( 3,1 ) << pt2.x, pt2.y, 1 );
        Mat d = y2.t() * t_x * R * y1;
        cout << "epipolar constraint = " << d << endl;
    }
    return 0;
}

Point2d pixel2cam (const Point2d& p, const Mat& K ){
    return Point2d(
                    (p.x - K.at<double> ( 0,2 ) ) / K.at<double>( 0,0 ),
                    (p.y - K.at<double> ( 1,2 ) ) / K.at<double> ( 1,1 )
            );
}

void find_feature_matches ( const Mat& img_1, const Mat& img_2,
                            std::vector<KeyPoint>& keypoints_1,
                            std::vector<KeyPoint>& keypoints_2,
                            std::vector< DMatch >& good_matches ) {
    // --initialization
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

    printf ( "-- Max dist : %f \n", max_dist );
    printf ( "-- Min dist : %f \n", min_dist );

    // if distance > 2*min_dist, cause error
    // Usually, Hamming distance < 2*min_dist
    for (int j = 0; j < descriptors_1.rows; j++) {
        if (matches[j].distance <= max( 2*min_dist, 30.0 )){
            good_matches.push_back( matches[j] );
        }
    }
}

void pose_estimation_2d2d(
        vector<KeyPoint> keypoints_1,
        vector<KeyPoint> keypoints_2,
        vector<DMatch> matches,
        Mat& R, Mat& t
        ){
    //camera intrinsic matrix
    Mat K = (Mat_<double> (3,3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1 );

    //turn matrix to vector <Point2f>
    vector<Point2f> points1;
    vector<Point2f> points2;

    for (int i = 0; i < (int) matches.size(); i++) {
        points1.push_back( keypoints_1[matches[i].queryIdx].pt );
        points2.push_back( keypoints_2[matches[i].trainIdx].pt );
    }

    // Compute Fundamental Matrix
    Mat fundamental_matrix;
    fundamental_matrix = findFundamentalMat( points1, points2, CV_FM_8POINT );
    cout << "fundamental matrix is" << endl << fundamental_matrix << endl;

    // Compute Essential Matrix
    Point2d principal_point( 325.1, 249.7); // camera cx, cy
    double focal_length = 521;
    Mat essential_matrix;
    essential_matrix = findEssentialMat( points1, points2, focal_length, principal_point );
    cout << "essential matrix is " << endl << essential_matrix << endl;

    // Compute Homography matrix
    Mat homography_matrix;
    homography_matrix = findHomography( points1, points2, RANSAC, 3 );
    cout << "homography matrix is " << endl << homography_matrix << endl;

    // recover R and t from essential matrix
    recoverPose( essential_matrix, points1, points2, R, t, focal_length, principal_point );
    cout << "R is " << endl << R << endl;
    cout << "t is " << endl << t << endl;
}