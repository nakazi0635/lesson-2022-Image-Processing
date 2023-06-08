#include <iostream>
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../Debug/apple_grayscale.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //画像の入力
    cv::Mat src_img = cv::imread(FILE_NAME,0); //画像の型と変数
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    cv::Mat dst_img;
    cv::Mat tmp_img;//一時的格納画像変数
    
    double filter_t[] = {1/3.,1/3.,1/3.};
    
    double filter_b[] = {-1.,0.,1.};
    
    double filter_h[] = {-1.,0.,1.,
                        -2.,0.,2.,
                        -1.,0.,1.};
    
    cv::Sobel(src_img, tmp_img, CV_32F, 1, 0);
    //配列をフィルタ行列kernelに変換
    //cv::Mat kernel = cv::Mat(3, 3, CV_64F, filter_h);
    //正規化
    //cv::normalize(kernel, kernel, 1.0, 0.0, cv::NORM_L1);
    //フィルタの計算
    //cv::filter2D(src_img, tmp_img, CV_64F, kernel);
    
    cv::convertScaleAbs(tmp_img, dst_img);
    
    
    cv::imshow(WINDOW_NAME_INPUT, src_img); //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
    cv::waitKey(); //キー入力待ち (止める)

    return 0;
}
