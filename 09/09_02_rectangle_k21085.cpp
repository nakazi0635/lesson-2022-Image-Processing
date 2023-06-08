//
//  contour4student.cpp
//
//
//  Created by Masashi Morimoto on 2022/06/07.
//

#include <iostream>
#include <opencv2/opencv.hpp>

//ファイル
#define FILE_NAME_0 "../Debug/sample.jpg"
#define FILE_NAME_1 "../Debug/sample_rotate.jpg"
//ウィンドウ名
#define WINDOW_NAME_INPUT_0 "input_0"
#define WINDOW_NAME_INPUT_1 "input_1"
#define WINDOW_NAME_OUTPUT_0 "output_0"
#define WINDOW_NAME_OUTPUT_1 "output_1"

//二値化しきい値
#define BIN_TH (100)

int main(int argc, const char * argv[]) {
    //1. 画像の宣言 (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
    cv::Mat src0_img, src1_img, gray0_img, gray1_img,
    bin0_img, bin1_img, tmp0_img, tmp1_img, dst0_img, dst1_img;
    
    //2. 輪郭の座標リストの宣言 (New!)
    std::vector< std::vector< cv::Point > > contours_0;
    std::vector< std::vector< cv::Point > > contours_1;
    
    //3. 画像の入力 (カラーで入力)
    src0_img = cv::imread(FILE_NAME_0);
    src1_img = cv::imread(FILE_NAME_1);
    if (src0_img.empty() || src1_img.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
    dst0_img = src0_img.clone();
    dst1_img = src1_img.clone();

    cv::cvtColor(src0_img, gray0_img, cv::COLOR_BGR2GRAY);
    cv::cvtColor(src1_img, gray1_img, cv::COLOR_BGR2GRAY);

    cv::threshold(gray0_img, bin0_img, BIN_TH, 255, cv::THRESH_BINARY);
    cv::threshold(gray1_img, bin1_img, BIN_TH, 255, cv::THRESH_BINARY);

    tmp0_img = bin0_img.clone();
    tmp1_img = bin1_img.clone();
    
    cv::findContours(tmp0_img, contours_0, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    cv::findContours(tmp1_img, contours_1, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    
    double L,S;
    for (int i = 0; i < contours_0.size(); i++) {
        L = cv::arcLength(contours_0[i], true);
        S = cv::contourArea(contours_0[i]);

        double R = 4 * M_PI * S / pow(L, 2.0);
        printf("周囲長%lf 面積%lf \n",L,S);
        if (L >= 290 && S <= 4500) {
            cv::drawContours(dst0_img, contours_0, i, CV_RGB(255, 0, 255), -1);
        }
    }

    for (int i = 0; i < contours_1.size(); i++) {
        L = cv::arcLength(contours_1[i], true);
        S = cv::contourArea(contours_1[i]);

        double R = 4 * M_PI * S / pow(L, 2.0);
        if (L >= 290 && S <= 4500) {
            cv::drawContours(dst1_img, contours_1, i, CV_RGB(255, 0, 255), -1);
        }
    }

    cv::imshow(WINDOW_NAME_INPUT_0, src0_img);
    cv::imshow(WINDOW_NAME_INPUT_1, src1_img);
    cv::imshow(WINDOW_NAME_OUTPUT_0, dst0_img);
    cv::imshow(WINDOW_NAME_OUTPUT_1, dst1_img);
    cv::waitKey();
        
    return 0;
}

