#include <iostream>
#include <opencv2/opencv.hpp>

//----------------------------

//全体の画像 (探索対象画像) のファイル名
#define TARGET_IMG_FILE "../Debug/input1.jpg"
#define WINDOW_NAME "intput"
#define WINDOW_NAME_Ans_0 "output_1"
#define WINDOW_NAME_Ans_1 "output_2"
#define WINDOW_NAME_Ans_Final "output_3"
//テンプレート画像
#define TEMPLATE_NUM (8)
#define Upper_limit (12000)
//----------------------------


int main (int argc, const char * argv[]){
    
    //画像を読み込むテンプレート
    cv::Mat template_img[TEMPLATE_NUM];
    char buf[256];
    for (int i=0; i < TEMPLATE_NUM; i++) {
        sprintf(buf, "template-%d.jpg", i);
        //fprintf(stderr, "%s\n", buf);
        template_img[i] = cv::imread(buf);
        if (template_img[i].empty()) {
            fprintf(stderr, "%s cannot be opened.", buf);
            return 0;
        }
    }
    
    cv::Vec3b val_right,val_left;
    cv::Mat ans_img_first,ans_img_second;
    
    int i,j,k,surch_first = 10,surch_second = 10,count = 0,min_img = 10;
    int ans_first_count = 1, ans_second_count = 1;
    int ans_first[4],ans_second[4];
    int min = 100000,judge = 0;
    
    //課題4からの変更点記述
    //4巡しないとなのでfor (k = 0; k < 4; k++)を追加
    for (k = 0; k < 4; k++) {
        //ここから課題4と同じ
        for (i = 0; i < TEMPLATE_NUM; i++) {
            for (j = 0; j < TEMPLATE_NUM; j++) {
                for (int y = 0; y < template_img[i].rows; y++){
                    val_right = template_img[i].at<cv::Vec3b>(y,template_img[i].cols-1);
                    val_left = template_img[j].at<cv::Vec3b>(y,0);
                    judge += abs(val_left[0]-val_right[0]);
                    judge += abs(val_left[1]-val_right[1]);
                    judge += abs(val_left[2]-val_right[2]);
                }
                if (min > judge) {
                    min = judge;
                    min_img = j;
                }
                judge = 0;
            }
            //fprintf(stderr, "%d -> %d \n",i,min_img);
            //ここまで課題4と同じ
            
            //2巡目以降の処理：1巡目に5 -> -1だった場合surch_firstに5が格納されている。
            if (surch_first == min_img) {
                //2 -> 5だったら2を格納
                ans_first[ans_first_count] = i;
                //2 -> 5だったら2を格納
                surch_first = i;
                ans_first_count++;
            }
            //2巡目以降の処理：1巡目に5 -> -1だった場合surch_firstに5が格納されている。
            if (surch_second == min_img) {
                //2 -> 5だったら2を格納
                ans_second[ans_second_count] = i;
                //2 -> 5だったら2を格納
                surch_second = i;
                ans_second_count++;
            }
            
            //2つ目の-1格納。一番右側の画像である-1を判定。-1が2つあるので、countを使いそれぞれの配列に格納
            if (min_img == -1 && count == 1) {
                //5 -> -1だったら5を格納
                ans_second[0] = i;
                //5 -> -1だったら5を格納
                surch_second = i;
                count++;
            }
            //1つ目の-1格納。一番右側の画像である-1を判定。-1が2つあるので、countを使いそれぞれの配列に格納
            if (min_img == -1 && count == 0) {
                //5 -> -1だったら5を格納
                ans_first[0] = i;
                //5 -> -1だったら5を格納
                surch_first = i;
                count++;
            }
            
            min = Upper_limit;
            min_img = -1;
        }
    }
    
    //(Ⅰ)の手順説明続き
    //4->0->2->5->-1を[5,2,0,4]のように格納されている
    for (i = 2; i >= 0; i--) {
        //1回目は4と2を連結させる。
        if (i == 2) {
            cv::hconcat(template_img[ans_first[i+1]], template_img[ans_first[i]], ans_img_first);
        //2回目以降は1回目に連結させた画像に追加で連結させていく
        }else{
            cv::hconcat(ans_img_first, template_img[ans_first[i]], ans_img_first);
        }
        
        //1回目は4と2を連結させる。
        if (i == 2) {
            cv::hconcat(template_img[ans_second[i+1]], template_img[ans_second[i]], ans_img_second);
        //2回目以降は1回目に連結させた画像に追加で連結させていく
        }else{
            cv::hconcat(ans_img_second, template_img[ans_second[i]], ans_img_second);
        }
    }
    //ここまでで4*1の（横長の）画像を2つにすることができた。
    //それぞれans_img_firstとans_img_secondという画像変数で、実行すると確認することができる
    
    
    cv::Vec3b ans_img_first_top, ans_img_first_last;
    cv::Vec3b ans_img_second_top, ans_img_second_last;
    cv::Mat ans_img_final;
    int judge1 = 0,judge2 = 0;
    
    //(Ⅱ)2つを連結させて完成。の手順説明
    //課題4で右端と左端で比較したように、今回は上端と下端で判定する。
    for (int x = 0; x < ans_img_first.cols; x++){
        //ans_img_firstの上端色値取得
        ans_img_first_top = ans_img_first.at<cv::Vec3b>(0,x);
        //ans_img_secondの上端色値取得
        ans_img_second_top = ans_img_second.at<cv::Vec3b>(0,x);
        //ans_img_firstの下端色値取得
        ans_img_first_last = ans_img_first.at<cv::Vec3b>(ans_img_first.rows-1,x);
        //ans_img_secondの下端色値取得
        ans_img_second_last = ans_img_second.at<cv::Vec3b>(ans_img_second.rows-1,x);
        //ans_img_firstの上端色値とans_img_secondの下端色値の誤差の絶対値を足していく
        judge1 = abs(ans_img_first_top[0]-ans_img_second_last[0]) + abs(ans_img_first_top[1]-ans_img_second_last[1]) + abs(ans_img_first_top[2]-ans_img_second_last[2]);
        //ans_img_firstの下端色値とans_img_secondの上端色値の誤差の絶対値を足していく
        judge2 = abs(ans_img_second_top[0]-ans_img_first_last[0]) + abs(ans_img_second_top[1]-ans_img_first_last[1]) + abs(ans_img_second_top[2]-ans_img_first_last[2]);
    }
    //judge1 < judge2なら、ans_img_firstの上端とans_img_secondの下端を連結させる
    if (judge1 < judge2) {
        cv::vconcat(ans_img_second, ans_img_first, ans_img_final);
    //judge1 > judge2なら、ans_img_firstの下端とans_img_secondの上端を連結させる
    }else{
        cv::vconcat(ans_img_first, ans_img_second, ans_img_final);
    }
    //横4つの画像を連結させた画像その1
    cv::imshow(WINDOW_NAME_Ans_0, ans_img_first);
    //横4つの画像を連結させた画像その2
    cv::imshow(WINDOW_NAME_Ans_1, ans_img_second);
    //すべて連結させた画像
    cv::imshow(WINDOW_NAME_Ans_Final, ans_img_final);
    
    cv::waitKey(0);
    return 0;
}



