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



int choix_next_move(Instance& instance, int delta_temps, Case& drone_position, int drone_number){
    
    int size = instance.products.size();
    
    Case position = ord->position;

    int score = -1;
    int num_order = 0;
    int num_best_ws = 0;
    vector<int> best_chargement_drone;
    int turn = -1;

    
    // parcours des ordres a traiter
    for(vector<Order>::iterator ord=(instance.orders).begin() ; ord < (instance.orders).end(); ord++) {
        
        int dist_d_w = 0, dist_w_o =0;
        
        
        
        
        // parcours des warehouses
        for( vector<Warehouse>::iterator wr=(instance.warehouses).begin() ; wr < (instance.warehouses).end(); wr++){
            
            int chargement_drone = 0;
            
            dist_d_w = distance(drone_position, wr->position);
            dist_w_o = distance(wr->position, ord->position);
            
            if ((dist_w_o+dist_d_w+2)> delta_temps) {
                score = -1;
                break;
            }
            
            vector<Product> objetsTries = trier_objects(ord->product_type);
            
            vector<Product>::iterator obj = objetsTries.begin();
            vector<int> stock_fictif_embarque(size);
            
            while ((obj!= objetsTries.end())&&(chargement_drone<=instance.max_load)) {
                if (((obj->weight + chargement_drone) < instance.max_load)&&((1+stock_fictif_embarque[obj->p])<= wr->available[obj->p])){
                    
                    chargement_drone += obj->weight;
                    stock_fictif_embarque[obj->p] +=1;
                    obj++;
                }
                
                break;
                
                // je prends le max d'objets dans le warehouse (disponibles et at capacite drone attention)
            }
            
            
            int nb_products = nbobjetsdifferents(stock_fictif_embarque,size);
            
            double score_f = (double) (chargement_drone)/(dist_d_w+dist_w_o+2*nb_products);
            
            if (((dist_d_w+dist_w_o+2*nb_products)<= delta_temps)&&(score_f> score)) {
                score=score_f;
                num_best_ws = ws->w;
                for (int i = 0; i<size; i++) {
                    best_chargement_drone[i] = stock_fictif_embarque[i];
                }
                
                turn = dist_d_w+dist_w_o+2*nb_products;
                num_order = ord->c;
            }
        }
    }
    if (score<0) {
        return -1;
    }
    
//    
//    int score = -1;
//    int num_order = 0;
//    int num_best_ws = 0;
//    vector<int> best_chargement_drone;
    
    // commentaire PRINT
    
    //mettre a jour stock warhouse
   
    for (int i = 0; i<size; i++) {
        (instance.warehouses[num_best_ws]).available[i] -= best_chargement_drone[i];
    }
    
     // commande en cours

    
    
    // update case drone
    drone_position = instance.orders[num_order].position;
    // renvoyer temps drone
    
    return turn;

}
