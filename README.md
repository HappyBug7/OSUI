# OSUI

## Introduction

​    This is a practice project, which is used to understand how an operate system works at the user interface. And that is the reason why this project is called OSUI(operate system user interface)

## Usage

​	1) Clone this repository and run `main.exe`

## Directory Structure

```
OSUI/
|-- src/
|   |-- calculate.cpp
|-- include/
|   |-- calculator.h
|-- |-- path_reader.h
|-- bin/
|   |-- calculate.exe
|-- lib/
|-- temp/
|-- user/
|   |-- HappyBug/
|-- History/
|-- README.md
|-- main.cpp
|-- main.exe
```

### Calculate

#### Generate Introduction

​    The `calculate.exe` is a simple calculator, which enables user to execute simple operation `+` `-` `*` and`/`, it also included variable declaration and multiple action. 

#### Usage

​    You can simply type `calculate` to enter calculator as below:

```
HappyBug@HappyBugsComputer:~$ calculate
>>>
```

#### Elementary Arithmetic Operation

```
>>> 11+5
16
>>> 11-5
6
>>> 12*3
36
>>> 12/3.1
3.87097
```

​	One thing to notice is that you can add any amount of `space` at any place, the calculator will simply ignore it. Thus the operation below is totally legal: 

```
>>> 12 + 1
13
```

​	Also, you can add `(` and `)` to prioritize the operation inside as below:

```
>>> (2*(11.05+12.00))+1
47.1
```

#### Variable Declaration

​	In this calculator, you can declare variables to simplify your equation:
```
>>> x = (2*(11.05+12.00))+1
>>> x + 1
48.1
```

 	Notice that if you redeclared a variable, the value of the variable will simply be replaced without any warnings!

```
>>> x = 1
>>> x = 2
>>> x
2
```

#### Variable Save

to be implemented

#### Quit

​	You can type `exit()` to return to the OSUI

```
>>> exit()
HappyBug@HappyBugsComputer:~$
```

