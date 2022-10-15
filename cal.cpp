#include <iostream>
#include<string>
#include<cstring>
#include <iomanip>
using namespace std;
#include "cal.h"
#include<stack>

double cal(double num1,double num2,char oper1){
    //计算加减乘除
    if (oper1=='+'){
        return (num1+num2);
    }else if(oper1=='-'){
        return (num2-num1);
    }else if(oper1=='*'){
        return (num1*num2);
    }else {
        return (num2/num1);
    }
};

double pow(int ex,double x){//实现立方
    double pow=1;
    for (int i = 0; i < ex; ++i){
        pow=pow*x;
    }
    return pow;
}

double sqrt(double x){//实现平方根
    double temp = x;
    double tempdou = x*x;
    while (abs(tempdou - x) > 0.00001)
    {
        temp = (temp * temp + x) / (2 * temp);
        tempdou = temp * temp;
    }
    return temp;

}
void cal_no_variables(int pre,char input[]){
    /*
遇到），不断计算直到取出（，继续清空乘除余
遇到（，放进去，下一个符号也放进去
遇到其它，栈顶是乘除直接计算
最后留下的全是+-算完即可
*/

    stack<char> oper;//存操作符
    stack<double> num;//存数字
    int i,j ;
    for ( i = 0; input[i] !='\0'; i++)
    {   //清空空格
        if (input[i] != ' '){
            continue;
        }
        else{
            for ( j = i; j < strlen(input); j++)
            {
                input[j] = input[j + 1];
            }
        }

    }
//    for ( i = 0; input[i] !='\0'; i++)
//    {
//        cout<<input[i];
//    }
//    cout<<endl;

    for (int i = 0; i < strlen(input); i++)
    {
//        if (!oper.empty()){
//            cout<<i<<" ? "<<oper.top()<<endl;
//        }
//        if (!num.empty()){
//            cout<<i<<" ? "<<num.top()<<endl;
//        }
        char x=input[i];
        if ((x<='9' && x>='0' ) || x=='.')//如果为数字，加入数字栈
        {	string y;
            while ((input[i]<='9' && input[i]>='0')|| input[i]=='.')
            {
                y+=input[i];
                i++;

            }
            i--;
            double z = atof(y.c_str());
            num.push(z);
        } else if (oper.empty()){
            oper.push(x);
        }
        else if (x==')'){//如果为右括号，计算到左括号
            while (oper.top()!='(')
            {
                double num1=num.top();
                num.pop();
                double num2=num.top();
                num.pop();
                char oper1=oper.top();
                oper.pop();
                num.push(cal(num1,num2,oper1));
            }
            oper.pop();

        }else if (x=='('){//左括号进入操作栈
            oper.push(x);
        }else if ((x=='+'||x=='-')){//进入加减，上一则运算只要不是（即可执行
            if(oper.top()!='('){
                double num1=num.top();
                num.pop();
                double num2=num.top();
                num.pop();
                char oper1=oper.top();
                oper.pop();
                num.push(cal(num1,num2,oper1));
                oper.push(x);
            }else
                oper.push(x);

        } else {
            if(oper.top()=='*'||oper.top()=='/'){ //进入乘除，上一则运算是乘除才可以执行
                double num1=num.top();
                num.pop();
                double num2=num.top();
                num.pop();
                char oper1=oper.top();
                oper.pop();
                num.push(cal(num1,num2,oper1));
            }

            oper.push(x);
        }
    }
    while (!oper.empty()){
        double num1=num.top();
        num.pop();
        double num2=num.top();
        num.pop();
        char oper1=oper.top();
        oper.pop();
        num.push(cal(num1,num2,oper1));
    }
    cout << fixed << setprecision(pre) << num.top() << endl;




}

void cal_with_variables(int n,int pre,char input[]){
    stack<char> oper;//存操作符
    stack<double> num;//存数字
    string variable[n];//存变量名
    double value[n];//存变量大小
    int i,j ;
    for ( i = 0; i<n; i++){ //读取变量名和大小
        cout<<"please input "<<i+1<<" th variable"<<endl;
        char in[32];
        cin.getline(in,32);
        string name;
        string val;
        bool ok= true;
        for (char r : in) {
            if (r==' '&&ok){
                continue;
            } else if (r!='='&&ok){
                name.append(1,r);
            } else if (r!=' '&& (!ok)){
                val+=r;
            }
            if (r=='='){
                ok= false;
            }
        }
        variable[i]=name;
        double a=atof(val.c_str());
        value[i]=a;
//        cout<<value[i]<<endl;
//        cout<<variable[i]<<endl;
    }

    for ( i = 0; input[i] !='\0'; i++)
    {   //清空空格
        if (input[i] != ' '){
            continue;
        }
        else{
            for ( j = i; j < strlen(input); j++)
            {
                input[j] = input[j + 1];
            }
        }

    }
//    for ( i = 0; input[i] !='\0'; i++)
//    {
//        cout<<input[i];
//    }
//    cout<<endl;
//


    for (int i = 0; i < strlen(input); i++)
    {
//        if (!oper.empty()){
//            cout<<i<<" ? "<<oper.top()<<endl;
//        }
//        if (!num.empty()){
//            cout<<i<<" ? "<<num.top()<<endl;
//        }
        char x=input[i];

        if ((x<='9' && x>='0' ) || x=='.'){
            string y;
            while ((input[i]<='9' && input[i]>='0')|| input[i]=='.')
            {
                y+=input[i];
                i++;

            }
            i--;
            double z = atof(y.c_str());
            num.push(z);
        }else if (input[i]!='+'&&input[i]!='-'&&input[i]!='*'&&input[i]!='/'&&input[i]!='('&&input[i]!=')'){
             string val;  //处理变量名，将它变成数字存入数字栈，剩下的操作与cal_no_variables完全相同,顺便判断是否是sqrt或者pow
             while (input[i]!='+'&&input[i]!='-'&&input[i]!='*'&&input[i]!='/'&&input[i]!='('&&input[i]!=')'&&i< strlen(input)){
                 val+=input[i];
                 i++;
             }i--;
             if (val=="sqrt"){
                 i+=2;
                 string x_sqrt;
                 while (input[i]!=')'){
                     x_sqrt+=input[i];
                     i++;
                 }
                 num.push(sqrt(atof(x_sqrt.c_str())));
             } else if (val=="pow"){
                 i+=2;
                 string x_pow;
                 while (input[i]!=','){
                     x_pow+=input[i];
                     i++;
                 }
                 int x_po=atof(x_pow.c_str());
                 i+=1;
                 string y_pow;
                 while (input[i]!=')'){
                     y_pow+=input[i];
                     i++;
                 }
                 double y_po=atof(y_pow.c_str());
                 num.push(pow(x_po,y_po));


             }
             for (int k = 0; k < n; ++k) {
                 if (variable[k]==val){
                     num.push(value[k]);
                 }
             }

         }
        else if (oper.empty()){
            oper.push(x);
        }
        else if (x==')'){
            while (oper.top()!='(')
            {
                double num1=num.top();
                num.pop();
                double num2=num.top();
                num.pop();
                char oper1=oper.top();
                oper.pop();
                num.push(cal(num1,num2,oper1));
            }
            oper.pop();

        }else if (x=='('){
            oper.push(x);
        }else if ((x=='+'||x=='-')&&oper.top()!='('){
            if(oper.top()!='('){
                double num1=num.top();
                num.pop();
                double num2=num.top();
                num.pop();
                char oper1=oper.top();
                oper.pop();
                num.push(cal(num1,num2,oper1));
                oper.push(x);
            }else
                oper.push(x);
        } else {
            if(oper.top()=='*'||oper.top()=='/'){
                double num1=num.top();
                num.pop();
                double num2=num.top();
                num.pop();
                char oper1=oper.top();
                oper.pop();
                num.push(cal(num1,num2,oper1));
            }

            oper.push(x);
        }
    }
    while (!oper.empty()){
        double num1=num.top();
        num.pop();
        double num2=num.top();
        num.pop();
        char oper1=oper.top();
        oper.pop();
        num.push(cal(num1,num2,oper1));
    }
    cout << fixed << setprecision(pre) << num.top() << endl;



}

