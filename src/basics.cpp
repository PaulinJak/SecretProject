#include "basics.hpp"
#include "objects.hpp"
#include <fstream>
#include <math.h>
#include <algorithm>    // std::sort
#include <vector>       // std::vector

using namespace std;


int distance(Case const& c1, Case const& c2){

  return ceil(sqrt( (c1.i-c2.i)*(c1.i-c2.i) + (c1.j-c2.j)*(c1.j-c2.j))); 

}

bool compProductWeight (Product i,Product j) { return (i.weight>j.weight); }
void products_sort(vector<Product>& list_products){
sort(list_products.begin(), list_products.end(), compProductWeight);

}

void readInstance( char const * nom_fichier, Instance& instance ) { 


  //char char1;
  int tmp;
    ifstream fichier(nom_fichier);
    if(fichier) {
        //pour n
      fichier >> instance.n  >> instance.m >> instance.n_drones >>instance.T_horizon >>instance.max_load ;
      cout <<"n="<<  instance.n  <<", m=" <<  instance.m <<", n_drones= <<"<<  instance.n_drones <<"\n";

      int P_products=0;
      
      fichier >> P_products;
      cout <<"number of products = "<< P_products << "\n";

        for(int i=0;i<P_products;i++) {

                fichier >> tmp;
		Product nouveau(i,tmp);
		instance.products.push_back(nouveau);
	}

   int W_warehouse=0;
      
      fichier >> W_warehouse;
      cout <<"number of warehouse = "<< W_warehouse << "\n";

      for(int i=0;i<W_warehouse;i++) {
	int tmp2=0; 
	fichier >> tmp;//position1
	fichier >> tmp2; //position2
	Case pos_w(tmp,tmp2);
	
	Warehouse new_warehouse(i,pos_w);
	for(int j=0;j<P_products;j++){

	     fichier >> tmp;
	     new_warehouse.available.push_back(tmp); //avail of product j
	}
	instance.warehouses.push_back(new_warehouse);

	//cout<< "test" <<(instance.warehouses[0]).available[0]<<endl;
	}

	

       int C_orders=0;
      
      fichier >> C_orders;
      cout <<"number of orders = "<< C_orders << "\n";

      for(int i=0;i<C_orders;i++) {
	int tmp1=0;
	int tmp2=0; 
	fichier >> tmp1;//position1
	fichier >> tmp2; //position2
	Case pos_order(tmp,tmp2);
	int number_it_order=0;
	fichier>> number_it_order; //number items
	
	Order new_order(i, pos_order, number_it_order);
	
		for(int j=0;j<number_it_order;j++){

	     fichier >> tmp;
	     new_order.product_type.push_back(tmp); //avail of product j
	}
	instance.orders.push_back(new_order);

	}


      //cout<< "test" <<(instance.orders[0]).product_type[0]<<endl;


            
    }
    else cout << "Fichier non trouvé!! \n";
}


void writeOutput(ofstream& outputStream, int const& nb_operations){

  outputStream.seekp(0,ios::beg);
  outputStream<< nb_operations<<"\n";
	  
	}
