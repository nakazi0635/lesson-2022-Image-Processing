//
//  posterization.cpp
//
//
//  Created by Masashi Morimoto on 2022/04/19.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "../Debug/shell.jpg"
#define FILE_NAME_2 "../Debug/03_02_input_k21085.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_SAKURA_INPUT "sakurainput"
#define WINDOW_SAKURA_OUTPUT "sakuraoutput"
#define COLOR_NUM (256) //色値

int main(int argc, const char * argv[]) {
    //画像の入力 (グレースケール入力)
    cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_GRAYSCALE);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    cv::Mat sakura_img = cv::imread(FILE_NAME_2, cv::IMREAD_GRAYSCALE);
    if (sakura_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME_2);
        return (-1);
    }
    
    uchar dst_1[COLOR_NUM];
    uchar dst_2[COLOR_NUM];
    uchar dst_3[COLOR_NUM];
    uchar a = 0,b = 0,c = 0;
    for(int i = 0; i < COLOR_NUM; i++){
        if (i <= 63) {
            dst_1[i] = 255;//B
            dst_2[i] = 4*i;//G
            dst_3[i] = 0;//R
        }else if(i > 63 && i <= 127){
            dst_1[i] = 255-4*a;
            dst_2[i] = 255;
            dst_3[i] = 0;
            a = a + 1;
        }else if(i > 127 && i <= 191){
            dst_1[i] = 0;
            dst_2[i] = 255;
            dst_3[i] = 4*b;
            b = b + 1;
        }else if(i > 191 && i <= 255){
            dst_1[i] = 0;
            dst_2[i] = 255-4*c;
            dst_3[i] = 255;
            c = c + 1;
        }
        //printf("i=%d[B%hu,G%hu,R%hu]\n",i,dst_1[i],dst_2[i],dst_3[i]);
    }
    
    cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);
    
    //画像の走査
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            uchar sr = src_img.at<uchar>(y, x);
            
            cv::Vec3b s = dst_img.at<cv::Vec3b>(y, x);
            s[0] = dst_1[sr];
            s[1] = dst_2[sr];
            s[2] = dst_3[sr];
            
            dst_img.at<cv::Vec3b>(y, x) = s;
            
        }
    }
    
    cv::Mat sakuracolor_img = cv::Mat(sakura_img.size(), CV_8UC3);
    for (int y=0; y<sakura_img.rows; y++) {
        for (int x=0; x<sakura_img.cols; x++) {
            uchar sr = sakura_img.at<uchar>(y, x);
            
            cv::Vec3b s = sakuracolor_img.at<cv::Vec3b>(y, x);
            s[0] = dst_1[sr];
            s[1] = dst_2[sr];
            s[2] = dst_3[sr];
            
            sakuracolor_img.at<cv::Vec3b>(y, x) = s;
            
        }
    }
    
    cv::imshow(WINDOW_NAME_INPUT , src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::imshow(WINDOW_SAKURA_INPUT , sakura_img);
    cv::imshow(WINDOW_SAKURA_OUTPUT, sakuracolor_img);
    cv::waitKey();
    
    return 0;
}


