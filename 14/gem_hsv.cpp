#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../Debug/gem1.jpg"
#define WINDOW_NAME "intput"
#define WINDOW_NAME_A "output"
#define HUE_MIN (20.0) // Hの最小値
#define HUE_MAX (60.0) // Hの最大値
#define SAT_MIN (100.0) // Sの最小値
#define SAT_MAX (200.0) // Sの最大値
#define MAX_VAL (255)

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img,dst_img,gray_img,hsv_img; //画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }
    
    cv::Vec3b p; //色値
    dst_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);
    
    for (int y=0; y<hsv_img.rows; y++) {
        for (int x=0; x<hsv_img.cols; x++) {
            p = hsv_img.at<cv::Vec3b>(y, x); // 各画素のHSV値を取得
            // HSV色空間で色を検出
            if (p[0] >= HUE_MIN && p[0] <=HUE_MAX && p[1] >= SAT_MIN && p[1] <=SAT_MAX) {
                dst_img.at<uchar>(y,x) = MAX_VAL; // しきい値条件が適合したら白画素
                
            }
        }
    }
    
    cv::imshow(WINDOW_NAME, src_img); //画像の表示
    cv::imshow(WINDOW_NAME_A, dst_img); //画像の表示
    
    cv::waitKey(); //キー入力待ち (止める)

    return 0;
}
