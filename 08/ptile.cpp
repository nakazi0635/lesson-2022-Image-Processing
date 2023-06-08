#include <iostream>
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME_1 "../Debug/ptile.jpg"

#define HIGHVAL (255)//閾値
#define LOWVAL (0)
#define COLOR_NUM (256) //色値


#define WINDOW_NAME_INPUT_1 "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img = cv::imread(FILE_NAME_1,0); //画像の型と変数
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME_1);
        return (-1);
    }
    
    
    cv::Mat gray_img = cv::Mat(src_img.size(), CV_8UC1);//グレー変数
    
    
    
    int hist[COLOR_NUM];
    int total = 0;
    int TH;
    for (int i = 0; i < COLOR_NUM; i++) {
        hist[i] = 0;
    }
    
    for (int y=0; y<src_img.rows; y++) {
        for (int x=0; x<src_img.cols; x++) {
            hist[src_img.at<uchar>(y, x)]++;
        }
    }
    for (int i = 0; i < COLOR_NUM; i++) {
        total += hist[i];
        printf("%d %d\n",i ,hist[i]);
    }
    printf("%d\n",total);
    int judge = total * 4/(4+1);
    printf("%d\n",judge);
    
    total = 0;
    for (int i = 0; i < COLOR_NUM; i++) {
        total += hist[i];
        if (total > judge) {
            TH = i;
            break;
        }
    }
    for(int y = 0; y < src_img.rows; y++){
        for (int x = 0; x < src_img.cols; x++) {
            cv::threshold(src_img, gray_img, TH, HIGHVAL, cv::THRESH_BINARY);
        }
    }
    printf("%d\n",TH);
    
    
    //出力
    cv::imshow(WINDOW_NAME_INPUT_1, src_img);
    cv::imshow(WINDOW_NAME_OUTPUT, gray_img);
    cv::waitKey();

    return 0;
}

