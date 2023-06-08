#include <iostream>
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../Debug/apple_grayscale.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_NAME55_OUTPUT "55output"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img = cv::imread(FILE_NAME,0); //画像の型と変数
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    cv::Mat dst_img;
    cv::Mat dst55_img;
    
//    double filter_h[] = {1/9.,1/9.,1/9.,
//                        1/9.,1/9.,1/9.,
//                        1/9.,1/9.,1/9.};
    
    double filter_h[] = {1./16.,2./16.,1./16.,
                        2./16.,4./16.,2./16.,
                        1./16.,2./16.,1./16.};
    
    double filter55_h[] = {1/25.,1/25.,1/25.,1/25.,1/25.,
                        1/25.,1/25.,1/25.,1/25.,1/25.,
                        1/25.,1/25.,1/25.,1/25.,1/25.};
    //配列をフィルタ行列kernelに変換
    cv::Mat kernel = cv::Mat(3, 3, CV_32F, filter_h);
    //正規化
    cv::normalize(kernel, kernel, 1.0, 0.0, cv::NORM_L1);
    //フィルタの計算
    cv::filter2D(src_img, dst_img, -1, kernel);
    
    
    cv::Mat kernel55 = cv::Mat(5, 5, CV_32F, filter55_h);
    //正規化
    cv::normalize(kernel55, kernel55, 1.0, 0.0, cv::NORM_L1);
    //フィルタの計算
    cv::filter2D(src_img, dst55_img, -1, kernel55);
    
    cv::imshow(WINDOW_NAME_INPUT, src_img); //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::imshow(WINDOW_NAME55_OUTPUT, dst55_img);
    cv::waitKey(); //キー入力待ち (止める)

    return 0;
}
