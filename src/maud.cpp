//
//  m.cpp
//
//
//  Created by Maud Doumergue on 10/02/2016.
//
//

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include "matrix.hpp"
#include "objects.hpp"
#include "basics.hpp"

using namespace std;

int nbobjetsdifferents(vector<int>& stock_fictif_embarque, int taille){
    int cpt = 0;
    
    for (int i = 0; i< taille; i++) {
        if (stock_fictif_embarque[i]>0) {
            cpt +=1;
        }
    }
    return cpt;
}

void update_orders(Instance& instance, int id, vector<int> &chargement){
    Order o = instance.orders[id];
    vector<int>  new_order(0);

    for(vector<int>::iterator elt=o.product_type.begin(); elt<o.product_type.end(); elt++){
        if (chargement[(*elt)]>0){
            chargement[(*elt)]--;
        }else{
            new_order.push_back(*elt);
        }
    }
    instance.orders[id].product_type = new_order;

}



int choix_next_move(Instance& instance, int delta_temps, Case& drone_position, int drone_number, ofstream &fichier ){
    
    int size = instance.products.size();
    

    int score = -1;
    int num_order = 0;
    int num_best_ws = 0;
    vector<int> best_chargement_drone(size);
    int turn = -1;

    
    // parcours des ordres a traiter
    for(vector<Order>::iterator ord=(instance.orders).begin() ; ord < (instance.orders).end(); ord++) {

        Case position = ord->position;
        
        int dist_d_w = 0, dist_w_o =0;
        
        
        
        // parcours des warehouses
        for( vector<Warehouse>::iterator wr=(instance.warehouses).begin() ; wr < (instance.warehouses).end(); wr++){
            
            int chargement_drone = 0;
            dist_d_w = distance(drone_position, wr->position);
            dist_w_o = distance(wr->position, ord->position);
            
            if ((dist_w_o+dist_d_w+2)> delta_temps) {
                score = -1;
              //  cout <<"distance impossible"<<"\n";
                continue;
            }
            
            vector<Product> objetsTries(ord->product_type.size(), Product(0,0));
            int ii=0;
            for(vector<int>::iterator elt=ord->product_type.begin(); elt<ord->product_type.end(); elt++){
                objetsTries[ii]=instance.products[*elt];
                ii++;
            }
            products_sort(objetsTries);
            
            vector<Product>::iterator obj = objetsTries.begin();
            vector<int> stock_fictif_embarque(size);
            
            while ((obj!= objetsTries.end())&&(chargement_drone<=instance.max_load)) {
                if (((obj->weight + chargement_drone) < instance.max_load)&&((1+stock_fictif_embarque[obj->p])<= wr->available[obj->p])){
                    
                    chargement_drone += obj->weight;
                    stock_fictif_embarque[obj->p] +=1;
                }
                obj++;
                
                // je prends le max d'objets dans le warehouse (disponibles et at capacite drone attention)
            }
            
            
            int nb_products = nbobjetsdifferents(stock_fictif_embarque,size);
            
            double score_f = ((double) (chargement_drone))/((double)(dist_d_w+dist_w_o+2*nb_products));
            
            if (((dist_d_w+dist_w_o+2*nb_products)<= delta_temps)&&(score_f> score)) {
                score=score_f;
                num_best_ws = wr->w;
                for (int i = 0; i<size; i++) {
                    best_chargement_drone[i] = stock_fictif_embarque[i];
                }
                
                turn = dist_d_w+dist_w_o+2*nb_products;
                num_order = ord->c;
            }
        }
    }
    if (score<0) {
        cout<<"negatif"<<score<<"\n";
        return -1;
    }
    
//    
//    int score = -1;
//    int num_order = 0;
//    int num_best_ws = 0;
//    vector<int> best_chargement_drone;
    
    // commentaire PRINT
    for(int i=0; i<size; i++){
        if (best_chargement_drone[i]>0){
            fichier <<drone_number<<" "<<"L"<<" "<<num_best_ws<<" "<<i<<" "<<best_chargement_drone[i]<<"\n";
        }
    }
    for(int i=0; i<size; i++){
        if (best_chargement_drone[i]>0){
            fichier <<drone_number<<" "<<"D"<<" "<<num_order<<" "<<i<<" "<<best_chargement_drone[i]<<"\n";
        }
    }
    //mettre a jour stock warhouse
   
    for (int i = 0; i<size; i++) {
        (instance.warehouses[num_best_ws]).available[i] -= best_chargement_drone[i];
    }
    
     // commande en cours
   update_orders(instance, num_order, best_chargement_drone);
    
    
    // update case drone
    drone_position = instance.orders[num_order].position;
    // renvoyer temps drone
    cout<<"pas negatif"<<turn<<"\n";
    return turn;

}
