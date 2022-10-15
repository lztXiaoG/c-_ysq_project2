#include <iostream>
using namespace std;
#include <string>
#include <cstring>
#include "cal.h"

int main(int argc, char *argv[]){
    //命令行参数输入顺序：
    // 1.无变量：mode,precision,formula
    // 2.有变量：mode,precision,n,formula
    if (argc==1){//命令行没有输入参数，手动输入参数
        cout<<"please declare whether has variable (1:yes , 0:no)"<<endl;
        int mode;
        char input[64];
        cin.getline(input, 8);
        mode = atoi(input);
        cout<<"please declare precision"<<endl;
        cin.getline(input, 8);
        int pre;
        pre=atoi(input);
        int n;
        if (mode==1){
            cout<<"please declare number of variables"<<endl;
            cin.getline(input, 8);
            n=atoi(input);
        }
        cout<<"please input formula"<<endl;
        cin.getline(input, 64);
        if (mode==0){
            cal_no_variables(pre,input);
        } else{
            cal_with_variables(n,pre,input);
        }

    }else{
        if (*argv[1]=='1'){
            int pre=atoi(argv[2]);
            int n=atoi(argv[3]);
            char input [128];
            strcpy(input,argv[4]);
            cal_with_variables(n,pre,input);
        }else if (*argv[1]=='0'){
            int pre=atoi(argv[2]);
            char input [128];
            strcpy(input,argv[3]);
            cal_no_variables(pre,input);
        }
    }
    return 0;
}