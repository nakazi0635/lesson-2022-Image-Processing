#include <iostream>
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../Debug/dot_gray_rectangle.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define FILTER_SIZE (41)
#define COLOR_NUM (256)

int main(int argc, const char * argv[]) {
    int hist[COLOR_NUM];
    //画像の入力
    cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_GRAYSCALE);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    cv::Mat dst_img;
    
    double filter_h[FILTER_SIZE][FILTER_SIZE];
    for (int i = 0; i < FILTER_SIZE; i++) {
        for (int j = 0; j < FILTER_SIZE; j++) {
            filter_h[i][j] = 1.0/FILTER_SIZE*FILTER_SIZE;
        }
    }
    

    
    //配列をフィルタ行列kernelに変換
    cv::Mat kernel = cv::Mat(FILTER_SIZE ,FILTER_SIZE , CV_32F, filter_h);
    //正規化
    cv::normalize(kernel, kernel, 1.0, 0.0, cv::NORM_L1);
    //フィルタの計算
    cv::filter2D(src_img, dst_img, -1, kernel);
    
    for (int i = 0; i < COLOR_NUM; i++) {
        hist[i] = 0;
    }
    
    for (int y=0; y<dst_img.rows; y++) {
        for (int x=0; x<dst_img.cols; x++) {
            hist[dst_img.at<uchar>(y, x)]++;
        }
    }
    for (int i = 0; i < COLOR_NUM; i++) {
        printf("%d %d\n",i ,hist[i]);
    }

    
    for (int y=0; y<dst_img.rows; y++) {
        for (int x=0; x<dst_img.cols; x++) {

            uchar s = dst_img.at<uchar>(y, x);
            if (s < 75) {
                s = 255;
            }else{
                s = 0;
            }
            dst_img.at<uchar>(y, x) = s;
        }
    }
    
    cv::imshow(WINDOW_NAME_INPUT, src_img); //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(); //キー入力待ち (止める)

    return 0;
}
