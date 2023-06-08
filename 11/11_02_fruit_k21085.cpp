#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../Debug/fruit_image.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define H_YELLOW (30) //Hのしきい値
#define S_YELLOW (255) //Hのしきい値
#define V_YELLOW (255) //Hのしきい値

#define H_MAX (25) //Hのしきい値
#define H_MIN (17) //Hのしきい値

#define S_MAX (255) //Sのしきい値
#define S_MIN (200) //Sのしきい値

#define V_MAX (255) //Vのしきい値
#define V_MIN (200) //Vのしきい値

int main(int argc, const char * argv[]) {
    //変数の宣言
    int x, y; //走査用
    cv::Vec3b p; //色値
    
    //画像の宣言 (入力画像，出力画像)
    cv::Mat src_img, dst_img, hsv_img, bgr_img;
    
    std::vector< std::vector< cv::Point > > contours;
    
    // 1. カラー画像の入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    
    // 2. 出力二値画像の領域を確保（初期値ゼロ：黒）
    dst_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
    
    cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);
    
    
    // 3. しきい値処理
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            p = hsv_img.at<cv::Vec3b>(y, x);
            if (H_MIN <= p[0] && H_MAX >= p[0] && S_MIN <= p[1] && S_MAX >= p[1] && V_MIN <= p[2] && V_MAX >= p[2]) {
                p[0] = H_YELLOW;
                p[1] = S_YELLOW;
                p[2] = V_YELLOW;
                
                hsv_img.at<cv::Vec3b>(y, x) = p;
                dst_img.at<uchar>(y, x) = 255;
            }
        }
    }
    
    cv::findContours(dst_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    
    double L,S;
    for (int i = 0; i < contours.size(); i++) {
        S = cv::contourArea(contours[i]);
        if (S <= 100) {
            cv::drawContours(dst_img, contours, i, 0, -1);
        }
    }
    cv::dilate(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 3);
    
    unsigned char s;
    
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {
            p = hsv_img.at<cv::Vec3b>(y, x);
            s = dst_img.at<uchar>(y, x);
            if (s == 255) {
                p[0] = H_YELLOW;
                p[1] = S_YELLOW;
                p[2] = V_YELLOW;
                
                hsv_img.at<cv::Vec3b>(y, x) = p;
            }
        }
    }
    
    cv::cvtColor(hsv_img, bgr_img, cv::COLOR_HSV2BGR);
    
    // 4. 表示
    cv::imshow(WINDOW_NAME_INPUT , src_img);//入力画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, bgr_img);//出力画像の表示
    cv::waitKey(); //キー入力待ち (止める)
    
    return 0;
}
