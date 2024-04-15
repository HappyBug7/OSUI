#ifndef CALCULATOR_H
#define CALCULATOR_H

#include<iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "env.h"
using namespace std;

class calculator{
  public:
    
    //structs
    struct _string
    {
      public:
        string* str;
        int num;
    };

    struct element{
    public:
      double val;/*
      value of the element(for opraters:{
        1:+
        2:-
        3:*
        4:/
      })
      */
      bool type;/*
      type of the element{
        0:oprator
        1:variable
      }*/ 
    };

    struct _stack{
      public:
        element* stack;
        int top;
    };

    struct var{
      public:
        double value;//value of the variable
        string name;//name of the variable
    };

    //data
    var *var_stack = new var[0];
    int val_num;

    //methods
    double StringToDouble(const string& str);

    element Pop(element stack[], int *top);

    void Push(element stack[], int *top, element val);

    void Express(element stack[], int top);

    _stack FrontTranslate(string str, element stack[]);

    element BaseCal(_stack stack);

    double Cal(string str);

    void StrAppend(string*& arr, int& size, string val);

    void VarAppend(var*& arr, int& size, var val);

    _string SpiltFunc(string str);

    int TypeCheck(string str);

    bool ChangeVal(string str, double val);

    string VarTranslate(string str);

    void AssignFunc(string str);

    double GetVal(string str);

    string RemoveSpace(string str);

    void LoadVal();

    void SaveVal();
};

double calculator::StringToDouble(const string& str) {
    char* end;
    return strtod(str.c_str(), &end);
}

calculator::element calculator::Pop(element stack[], int *top) {
  element val = stack[*top];
  *top -= 1;
  return val;
}
void calculator::Push(element stack[], int *top, element val) {
  *top += 1;
  stack[*top] = val;
}

void calculator::Express(element stack[], int top){
  for(int i = 1; i<= top; i++){
    if(stack[i].type==1){
      printf("%f",stack[i].val);
    }else{
      switch (int(stack[i].val))
      {
        case 1:
          printf("+");
          break;

        case 2:
          printf("-");
          break;

        case 3:
          printf("*");
          break;

        case 4:
          printf("/");
          break;
      }
    }
  }
  printf("\n");
}

calculator::_stack calculator::FrontTranslate(string str, element stack[]){
  const int size = str.length();
  int top=0;
  int* pointer = &top;
  string num_curr = "";
  for(int i=0; i<size; i++){
    if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'){
      element ele;
      ele.type = 0;
      switch (str[i]){
        case '+':
        ele.val = 1;
          break;

        case '-':
          ele.val = 2;
            break;
        
        case '*':
          ele.val = 3;
            break;
        
        case '/':
          ele.val = 4;
            break;
      }
      element num;
      num.val = StringToDouble(num_curr);
      num.type = 1;
      num_curr = "";
      Push(stack, pointer ,num);
      Push(stack, pointer ,ele);
    }else{
      num_curr.append(string(1,str[i]));
    }
  }
  element num;
  num.val = StringToDouble(num_curr);
  num.type = 1;
  num_curr = "";
  Push(stack, pointer ,num);

  // element ulti_val = Pop(stack, pointer);
  // return ulti_val.val;
  _stack return_stack;
  return_stack.stack = stack;
  return_stack.top = top;
  return return_stack;
}

calculator::element calculator::BaseCal(_stack stack){
  int p_top = 0;
  int* pointer = &stack.top;
  int* p_pointer = &p_top;
  element processed_stack[stack.top];
  for(int i = 1; i <= stack.top; i++){
    if((stack.stack[i].type == 0)&&(stack.stack[i].val>2)){
      element ob_1 = Pop(processed_stack, p_pointer);
      element op = stack.stack[i];
      i++;
      element ob_2 = stack.stack[i];
      element val;
      val.type = 1;
      switch (int(op.val))
      {
        case 3:
          val.val = ob_1.val * ob_2.val;
          break;
        
        case 4:
          val.val = ob_1.val / ob_2.val;
          break;
      }
      Push(processed_stack, p_pointer, val);
    }else{
      Push(processed_stack, p_pointer, stack.stack[i]);
    }
  }

  // Express(processed_stack, p_top);

  element ultimate_stack[p_top];
  int u_top = 0;
  int* u_pointer = &u_top;
  for(int i = 1; i <= p_top; i++){
    if(processed_stack[i].type == 0){
      element ob_1 = Pop(ultimate_stack, u_pointer);
      element op = processed_stack[i];
      i++;
      element ob_2 = processed_stack[i];
      element val;
      val.type = 1;
      switch (int(op.val))
      {
        case 1:
          val.val = ob_1.val + ob_2.val;
          break;
        
        case 2:
          val.val = ob_1.val - ob_2.val;
          break;
      }
      Push(ultimate_stack, u_pointer, val);
    }else{
      Push(ultimate_stack, u_pointer, processed_stack[i]);
    }
  }
  element val = Pop(ultimate_stack, u_pointer);
  return val;
}

double calculator::Cal(string str){
  int len = str.length();
  int layer = 0;
  int max_layer = 0;
  for(int i = 0; i<len; i++){
    if(str[i]=='('){
      layer++;
    }
    if(layer > max_layer){
      max_layer = layer;
    }
    if(str[i]==')'){
      layer--;
    }
  }
  
  string curr_str = str;
  for(int i=0; i<max_layer; i++){
    int curr_layer=max_layer-i;
    layer = 0;
    string cul_str = "";
    string process_str = "";
    for(int i = 0; i<curr_str.length(); i++){
      if(curr_str[i]=='('){
        layer++;
      }
      if(curr_str[i]==')'){
        if(layer == curr_layer){
          element stack[cul_str.length()];
          element* processed;
          _stack data;
          data = FrontTranslate(cul_str, stack);
          element val = BaseCal(data);
          char buffer[255];
          sprintf(buffer, "%f", val.val);
          std::string ss_str(buffer);
          process_str.append(ss_str);
          cul_str = "";
          layer--;
          continue;
        }
        layer--;
      }
      if(layer == curr_layer){
        if(curr_str[i]!='('){
          cul_str.append(string(1,curr_str[i]));
        }
      }else{
        process_str.append(string(1,curr_str[i]));
      }
    }
    curr_str = process_str;
  }
  element stack[curr_str.length()];
  element* processed;
  _stack data;
  data = FrontTranslate(curr_str, stack);
  element val = BaseCal(data);
  return val.val;
}

void calculator::StrAppend(string*& arr, int& size, string val){
  int newsize = size +1;
  string* newarr = new string[newsize];
  for(int i = 0; i < size; i++){
    newarr[i] = arr[i];
  }
  newarr[size] = val;
  delete[] arr;
  arr = newarr;
  size = newsize;
}

void calculator::VarAppend(var*& arr, int& size, var val){
  int newsize = size +1;
  var* newarr = new var[newsize];
  for(int i = 0; i < size; i++){
    newarr[i] = arr[i];
  }
  newarr[size] = val;
  delete[] arr;
  arr = newarr;
  size = newsize;
}

calculator::_string calculator::SpiltFunc(string str){
  string curr_str = "";
  string* strs = new string[0];
  int num = 0;
  for(int i = 0; i < str.length(); i++){
    if(str[i]!=';'){
      curr_str.append(string(1,str[i]));
    }else{
      StrAppend(strs, num, curr_str);
      curr_str="";
    }
  }
  StrAppend(strs, num, curr_str);
  curr_str="";
  _string _str;
  _str.num = num;
  _str.str = strs;
  return _str;
}

int calculator::TypeCheck(string str){
  /*
  0:assignment
  1:calculate
  */
  for(int i = 0; i < str.length(); i++){
    if(str[i]=='='){
      return 1;
    }
  }
  return 0;
}

bool calculator::ChangeVal(string str, double val){
  for(int i = 0; i<val_num; i++){
    if(var_stack[i].name == str){
      var_stack[i].value = val;
      return 0;
    }
  }
  return 1;
}

string calculator::VarTranslate(string str){
  string name_str = "";
  string return_str = "";
  bool state = 0;
  for(int i = 0; i < str.length(); i++){
    if((str[i]>='0'&&str[i]<='9'||str[i]=='.')||(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='('||str[i]==')')){
      if(state){
        double value = GetVal(name_str);
        char buffer[255];
        sprintf(buffer, "%f", value);
        std::string ss_str(buffer);
        return_str.append(ss_str);
        state = 0;
        name_str = "";
        return_str.append(string(1,str[i]));
        continue;
      }
      return_str.append(string(1,str[i]));
    }else{
      state = 1;
      name_str.append(string(1,str[i]));
    }
  }
  if(state){
    double value = GetVal(name_str);
    char buffer[255];
    sprintf(buffer, "%f", value);
    std::string ss_str(buffer);
    return_str.append(ss_str);
    state = 0;
    name_str = "";
  }
  return return_str; 
}

void calculator::AssignFunc(string str){
  string name_str = "";
  string value_str = "";
  bool state = 0;
  for(int i = 0; i < str.length(); i++){
    if(str[i]=='='){
      state = 1;
      continue;
    }
    if(state){
      value_str.append(string(1,str[i]));
    }else{
      name_str.append(string(1,str[i]));
    }
  }
  var val;
  val.value = Cal(VarTranslate(value_str));
  val.name = name_str;
  if(ChangeVal(name_str, val.value)){
    VarAppend(var_stack, val_num, val);
  }
}

double calculator::GetVal(string str){
  for(int i = 0; i<val_num; i++){
    if(var_stack[i].name == str){
      return var_stack[i].value;
    }
  }
  return 0;
}

string calculator::RemoveSpace(string str){
  string return_str = "";
  for(int i = 0; i < str.length(); i++){
    if(str[i]!=' '){
      return_str.append(string(1,str[i]));
    }
  }
  return return_str;
}

void calculator::LoadVal(){
  string str;
  ifstream file;
  file.open(base_path + "/user/HappyBug/calculate.txt");
  while(getline(file, str)){
    AssignFunc(str);
  }
  file.close();
}

void calculator::SaveVal(){
  ofstream file;
  file.open(base_path + "/user/HappyBug/calculate.txt");
  for(int i = 0; i<val_num; i++){
    file << var_stack[i].name << "=" << var_stack[i].value << endl;
  }
  file.close();
}

#endif
