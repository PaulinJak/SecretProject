#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <iostream>
#include <fstream>
using namespace std;

class Case{

public:

  Case(int i0, int j0):
    i(i0), j(j0){};

  void print(){
    cout<<"("<<i<<";"<<j<<")"<<endl;
  }
  int i;
  int j;
};


#endif
