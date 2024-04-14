#include<iostream>
#include <cstdlib>
#include "../include/calculator.h"
int main(){
  calculator cal;
  cal.val_num = 0;
  cal.LoadVal();
  for(;;){
    string str;
    calculator::_string strs;
    std::cout<<">>> ";
    std::getline(std::cin, str);
    str = cal.RemoveSpace(str);
    strs = cal.SpiltFunc(str);
    for(int i = 0; i < strs.num; i++){
      if(strs.str[i]=="exit()"){
        cal.SaveVal();
        return 0;
      }
      if(cal.TypeCheck(strs.str[i])){
        cal.AssignFunc(strs.str[i]);
      }else{
        std::cout<<cal.Cal(cal.VarTranslate(strs.str[i]))<<std::endl;
      }
    }
  }
}