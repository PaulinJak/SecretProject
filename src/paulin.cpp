
#include <iostream>
#include <fstream>
#include <iterator>
#include "matrix.hpp"
#include <vector>
#include "objects.hpp"
#include "paulin.hpp"
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include "basics.hpp"
using namespace std;


Warehouse findNearestWarehouse(Case const& pos,Instance const& instance){
  int bestDistance =distance(pos,(instance.warehouses[0]).position);
   int nearestWarehouseId =0;
   for(int i=1; i<<instance.warehouses.size(); i++){
int newdist=distance(pos,(instance.warehouses[i]).position);
     if (newdist<bestDistance){
       bestDistance=newdist;
       nearestWarehouseId=i;
     }
   }
   return instance.warehouses[nearestWarehouseId];
}


void initialSend(ofstream& outPut, vector<Case>& drones_positions, vector<int>& drones_temps, Instance& instance){

  vector<Case> uniformPositions(instance.n_drones,Case(0,0));

for (int drone=0; drone< instance.n_drones ;drone++){
uniformPositions[drone].i=rand() % instance.n;
uniformPositions[drone].j=rand() %instance.m;
}

// double area = instance.n*instance.m/instance.n_drones;


for (int drone=0; drone< instance.n_drones;drone++){
     
Warehouse wareh_id_to_send=findNearestWarehouse( uniformPositions[drone],instance);

outPut <<drone <<" L "<< wareh_id_to_send.w<< "0 0\n";

int distance_to_fly=distance(drones_positions[drone],wareh_id_to_send.position);

drones_positions[drone]=wareh_id_to_send.position;

drones_temps[drone]+=distance_to_fly+1;
}
}
 
