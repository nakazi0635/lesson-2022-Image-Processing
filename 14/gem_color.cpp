#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../Debug/gem1.jpg"
#define WINDOW_NAME "intput"
#define WINDOW_NAME_A "output"
#define R_MIN (0) //Rの最小値
#define R_MAX (50) //Rの最大値
#define G_MIN (50) //Gの最小値
#define G_MAX (100) //Gの最大値
#define MAX_VAL (255) //Gの最大値

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img,dst_img,gray_img; //画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }
    
    cv::Vec3b p; //色値
    dst_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    
    
    //2. グレースケール画像
    //cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            p = src_img.at<cv::Vec3b>(y, x); //各画素のBGR値を取得
    // RGB色空間で緑色を検出
            if (p[1] >= G_MIN && p[1] <= G_MAX && p[2] >= R_MIN && p[2] <=R_MAX) {
                dst_img.at<uchar>(y,x) = MAX_VAL; // しきい値条件が適合したら白画素
                
            }
        }
    }
    
    //cv::threshold(gray_img, dst_img, TH, HIGHVAL, cv::THRESH_BINARY_INV);
    cv::imshow(WINDOW_NAME, src_img); //画像の表示
    cv::imshow(WINDOW_NAME_A, dst_img); //画像の表示
    
    cv::waitKey(); //キー入力待ち (止める)

    return 0;
}
