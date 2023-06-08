


#include <iostream>
#include <opencv2/opencv.hpp>

//----------------------------

//全体の画像 (探索対象画像) のファイル名
#define TARGET_IMG_FILE "../Debug/gazoDora.jpg"

//テンプレート画像
#define TEMPLATE_IMG_FILE_1 "../Debug/red.jpg"

//----------------------------
cv::Mat src_img, result_img;
cv::Mat template1_img;
cv::Mat compare_img;


int main (int argc, const char * argv[]){
    double min_val, max_val;
    cv::Point min_loc, max_loc;
    
    //入力画像
    src_img = cv::imread(TARGET_IMG_FILE, 0);
    
    //テンプレート画像
    template1_img = cv::imread(TEMPLATE_IMG_FILE_1, 0);
    
    if(src_img.empty()||template1_img.empty()) {
        fprintf(stderr, "File is not opened.\n");
        
        return (-1);
    }
    
    compare_img = cv::Mat(cv::Size(src_img.rows - template1_img.rows + 1, src_img.cols - template1_img.cols + 1), CV_32F, 1);

    cv::matchTemplate(src_img, template1_img, compare_img, cv::TM_SQDIFF_NORMED);
    
    result_img = cv::Mat(compare_img.size(), CV_8UC1);
    float s;
    for (int y = 0; y < compare_img.rows; y++) {
        for (int x = 0; x < compare_img.cols; x++) {
            s = compare_img.at<float>(y, x);
            s = s * 255;
            result_img.at<float>(y, x) = s;
        }
    }
    
    cv::imshow("input", src_img);
    cv::imshow("template1", template1_img);
    cv::imshow("compare", compare_img);
    cv::waitKey(0);


    return 0;
}


