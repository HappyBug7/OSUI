#include<iostream>
#include <cstdlib>
#include "../include/calculator.h"
int main(){
  calculator cal;
  cal.val_num = 0;
  for(;;){
    string str;
    calculator::_string strs;
    std::cout<<">>> ";
    std::getline(std::cin, str);
    str = cal.remove_space(str);
    strs = cal.Spilt_func(str);
    for(int i = 0; i < strs.num; i++){
      if(strs.str[i]=="exit()"){
        return 0;
      }
      if(cal.TypeCheck(strs.str[i])){
        cal.assign_func(strs.str[i]);
      }else{
        std::cout<<cal.Cal(cal.var_translate(strs.str[i]))<<std::endl;
      }
    }
  }
}