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
#define HUE_MIN (20.0) // Hの最小値
#define HUE_MAX (60.0) // Hの最大値
#define SAT_MIN (100.0) // Sの最小値
#define SAT_MAX (200.0) // Sの最大値
#define MAX_VAL (255)
#define COUNT (15)
#define TH (20) //色値
#define HIGHVAL (255) //色値


void expansion_contraction(cv::Mat &dst){
    cv::dilate(dst, dst, cv::Mat(), cv::Point(-1,-1), COUNT);
    cv::erode(dst, dst, cv::Mat(), cv::Point(-1,-1), COUNT*2);
    cv::dilate(dst, dst, cv::Mat(), cv::Point(-1,-1), COUNT);
}
int main(int argc, const char * argv[]) {
    //画像の入力
    std::vector< std::vector< cv::Point > > contours;
    cv::Mat src_img,dst_img,gray_img,hsv_img,hsvans_img,bin_img,tmp_img,ans_img,tolco_img; //画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }
    ans_img = src_img.clone();
    cv::Vec3b p; //色値
    
    //2. グレースケール画像
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    //3. 二値化
    cv::threshold(gray_img, bin_img, TH, MAX_VAL, cv::THRESH_BINARY_INV);
    //4. クロージング・オープニング
    expansion_contraction(bin_img);
    
    tmp_img = bin_img.clone();
    cv::findContours(tmp_img, contours, cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE); // 外輪郭のみ
    
    //6. 外接円を描画
    dst_img = src_img.clone(); //入力画像を出力画像にコピー
        for (int i=0; i<contours.size(); i++) {
            cv::Rect bb = cv::boundingRect(contours[i]);
            cv::rectangle(ans_img, bb, CV_RGB(255, 0, 0), 3);
        }
    std::cout << "Black gem = " << contours.size() << std::endl;
    contours.clear();
    
    
    tolco_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    
    
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            p = src_img.at<cv::Vec3b>(y, x); //各画素のBGR値を取得
    // RGB色空間で緑色を検出
            if (p[1] >= G_MIN && p[1] <= G_MAX && p[2] >= R_MIN && p[2] <=R_MAX) {
                tolco_img.at<uchar>(y,x) = MAX_VAL; // しきい値条件が適合したら白画素
            }
        }
    }
    
    expansion_contraction(tolco_img);
    
    cv::findContours(tolco_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    for (int i=0; i<contours.size(); i++) {
        cv::drawContours(ans_img, contours, i, CV_RGB(0, 255, 0), cv::FILLED);
    }
    
    std::cout << "Green gem= " << contours.size() << std::endl;
    contours.clear();
    
    hsvans_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);
    
    for (int y=0; y<hsv_img.rows; y++) {
        for (int x=0; x<hsv_img.cols; x++) {
            p = hsv_img.at<cv::Vec3b>(y, x); // 各画素のHSV値を取得
            // HSV色空間で色を検出
            if (p[0] >= HUE_MIN && p[0] <=HUE_MAX && p[1] >= SAT_MIN && p[1] <=SAT_MAX) {
                hsvans_img.at<uchar>(y,x) = MAX_VAL;
            }
        }
    }
    
    expansion_contraction(hsvans_img);
    
    cv::findContours(hsvans_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    std::cout << "Golden gem = " << contours.size() << std::endl;
    
    
    for (int i=0; i<contours.size(); i++) {
            float radius;
            cv::Point2f center;
            cv::minEnclosingCircle(contours[i], center, radius);
            cv::circle(ans_img, center, (int)radius, CV_RGB(255, 255, 255), 3);
    }
    contours.clear();
    
    cv::imshow(WINDOW_NAME, src_img); //画像の表示
    cv::imshow(WINDOW_NAME_A, ans_img); //画像の表示
    
    cv::waitKey(); //キー入力待ち (止める)

    return 0;
}
