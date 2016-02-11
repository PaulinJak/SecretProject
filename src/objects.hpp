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

class Product{
public :
  int p ; //product number
  int weight ; 
};

class Warehouse{
public :
  int w;
  Case position;
  vector<int> available ; //products available
};

  class Order{
  public:
    int c ; //identity
    Case position;
    int number_items;
    vector<int> product_type;
  };
class Instance{
public :
  int n; //rows
  int m; //columns
  int n_drones ;
  int T_horizon ;
  int max_load ;
  

};




#endif
