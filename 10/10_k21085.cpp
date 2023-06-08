

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

//ファイル
#define FILE_NAME "../Debug/issue1.jpg"
//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_BINARY "binary"
#define WINDOW_NAME_OUTPUT "output"

//二値化閾値
#define BIN_TH (100)


int main(int argc, const char * argv[]) {
    //1. 画像の宣言 (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
    cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img;

    //色値の設定
    
    //2. 輪郭の座標リストの宣言
    std::vector< std::vector< cv::Point > > contours;
    
    //3. 画像の入力 (カラーで入力)
    src_img = cv::imread(FILE_NAME);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
    //4. 入力画像を結果画像にコピー
    dst_img = src_img.clone();
    
    //5. グレースケール化
    cv::cvtColor(src_img, gray_img,cv::COLOR_BGR2GRAY);
    
    //6. 二値化 (固定閾値で実装．閾値: 100)
    cv::threshold(gray_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);
    
    //二値画像コピー
    tmp_img = bin_img.clone();
    
    //7. 輪郭抽出
    cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    
    double L,S;
    for (int i = 0; i < contours.size(); i++) {
        L = cv::arcLength(contours[i], true);
        S = cv::contourArea(contours[i]);
        
        double R = 4 * M_PI * S / pow(L, 2.0);
        if (R >= 0.8 && S >= 1000) {
            cv::drawContours(dst_img, contours, i, CV_RGB(0, 0, 0), cv::FILLED);
        }
    }
    
    cv::Scalar color[]{
        CV_RGB(255, 0, 255),
        CV_RGB(255, 0, 0),
        CV_RGB(0, 0, 0),
    };
    //8. 輪郭の描画
        //輪郭の描画
    cv::drawContours(dst_img, contours, 3, color[0], cv::FILLED);
    cv::drawContours(dst_img, contours, 2, color[2], cv::FILLED);
    cv::drawContours(dst_img, contours, 1, color[0], cv::FILLED);
    
    cv::drawContours(dst_img, contours, 6, color[1], cv::FILLED);
    cv::drawContours(dst_img, contours, 5, color[2], cv::FILLED);
    cv::drawContours(dst_img, contours, 4, color[1], cv::FILLED);
    
    
    //9. 表示
    cv::imshow(WINDOW_NAME_INPUT, src_img);
    cv::imshow(WINDOW_NAME_BINARY, bin_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey();
    
    
    return 0;
}

