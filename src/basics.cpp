#include "basics.hpp"
#include "objects.hpp"
using namespace std;


void readInstance(const char* nom_fichier, Instance& instance ) { 


  char char1;
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

	



            
    }
    else cout << "Fichier non trouvé!! \n";
}

