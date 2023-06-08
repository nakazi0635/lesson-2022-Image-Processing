#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../Debug/gem1.jpg"
#define WINDOW_NAME "output"
#define COLOR_NUM (256) //色値

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img,dst_img,gray_img; //画像の型と変数
    src_img = cv::imread(FILE_NAME); //画像の読み込み
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "読み込み失敗\n");
        return (-1);
    }
    
    
    //2. グレースケール画像
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    int hist[COLOR_NUM];
    
    if (src_img.empty()) {
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    
    for (int i = 0; i < COLOR_NUM; i++) {
        hist[i] = 0;
    }
    
    for (int y=0; y<gray_img.rows; y++) {
        for (int x=0; x<gray_img.cols; x++) {
            hist[gray_img.at<uchar>(y, x)]++;
//            uchar s = gray_img.at<uchar>(y,x); //画素値の取得
//            hist[(int)s]++;
        }
    }
    for (int i = 0; i < COLOR_NUM; i++) {
        //std::cout << hist[i] << std::endl;
        printf("%d\n",hist[i]);
    }
    cv::waitKey(); //キー入力待ち (止める)

    return 0;
}
