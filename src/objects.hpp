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
  Product(int p0, int w):
    p(p0), weight(w){};

  int p ; //product number
  int weight ; 
};

class Warehouse{
public :
  
  Warehouse(int& w0, Case& pos):
    w(w0), position(pos), available(){};
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
  vector<Order> orders;
  vector<Product> products;
  vector<Warehouse> warehouses;
  
};




#endif
