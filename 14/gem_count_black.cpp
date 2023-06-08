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
#define COUNT (15)
#define TH (20) //色値
#define HIGHVAL (255) //色値

int main(int argc, const char * argv[]) {
    //画像の入力
    std::vector< std::vector< cv::Point > > contours;
    cv::Mat src_img,dst_img,gray_img,hsv_img,bin_img,tmp_img; //画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }

    //2. グレースケール画像
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    //3. 二値化
    cv::threshold(gray_img, bin_img, TH, MAX_VAL, cv::THRESH_BINARY_INV);
    //4. クロージング・オープニング
     cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT);
     cv::erode(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT*2);
     cv::dilate(bin_img, bin_img, cv::Mat(), cv::Point(-1,-1), COUNT);
    
    //cv::threshold(gray_img, dst_img, TH, HIGHVAL, cv::THRESH_BINARY_INV);
    
    tmp_img = bin_img.clone();
    cv::findContours(tmp_img, contours, cv::RETR_EXTERNAL,cv::CHAIN_APPROX_NONE); // 外輪郭のみ
    
    //6. 外接円を描画
    dst_img = src_img.clone(); //入力画像を出力画像にコピー
        for (int i=0; i<contours.size(); i++) {
            float radius;
            cv::Point2f center;
            cv::minEnclosingCircle(contours[i], center, radius);
            cv::circle(dst_img, center, (int)radius, CV_RGB(255, 0, 0), 2);
        }
    std::cout << "Black gem = " << contours.size() << std::endl;
    
    
    cv::imshow(WINDOW_NAME, src_img); //画像の表示
    cv::imshow(WINDOW_NAME_A, dst_img); //画像の表示
    
    cv::waitKey(); //キー入力待ち (止める)

    return 0;
}
