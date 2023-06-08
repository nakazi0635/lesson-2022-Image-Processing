#include <iostream>
#include <opencv2/opencv.hpp>

//画像ファイル (サイズは小さめが良い)
#define FILE_NAME "../Debug/input1.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char * argv[]) {
    //画像の入力と成功判定テンプレート
    cv::Mat src_img = cv::imread(FILE_NAME); //画像の型と変数
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    cv::Mat dst_img;
    //入力画像をグレースケールに変換
    cv::Mat gray_img = cv::Mat(src_img.size(), CV_8UC1);
    cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);
    
    //ソーベルフィルター設定
    double filter_h[] = {-1.,0.,1.,
                        -2.,0.,2.,
                        -1.,0.,1.};
    
    //配列をフィルタ行列kernelに変換
    cv::Mat kernel = cv::Mat(3, 3, CV_64F, filter_h);
    
    //一時的格納画像変数
    cv::Mat tmp_img;
    
    //ソーベルフィルタ関数
    cv::Sobel(gray_img, tmp_img, CV_32F, 1, 0);
    //絶対値をとり適切な倍率で値を変換する
    cv::convertScaleAbs(tmp_img, dst_img);
    
    cv::imshow(WINDOW_NAME_INPUT, src_img); //画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//
    cv::waitKey(); //キー入力待ち (止める)

    return 0;
}

