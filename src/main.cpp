#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include "objects.hpp"
#include "basics.hpp"
#include "maud.hpp"

using namespace std;




int main(int argc, char* argv[])
{
        // Lire et initialiser les données
        Instance instance;
        readInstance("instances/mother_of_all_warehouses.in", instance );
        int max_T = instance.T_horizon;
        int n_drones = instance.n_drones;
        // Tant que des drones ont le tant de faire des commandes
        int drone_actif = n_drones;
        // Initialise le vecteur temps des drones
        vector<int>  drone_temps(n_drones);
        vector<Case> drone_position(n_drones, Case(0,0));

        while(drone_actif>0){
            //On trouve le drone avec le temps le, plus petit
            int drone_id=-1;
            int temps_abs=max_T;
            int t=0;
            for(int i =0; i<n_drones; i++){
                t = drone_temps.at(i);
                if (t<temps_abs){
                    drone_id=i;
                    temps_abs=t;
                }
            }
            //on clacul le temps restant au drone
            int deltaT = max_T - temps_abs;
            //on appel la fonction de choix
            //deltaT = choix_next_move(instance, deltaT, drone_position.at(i),drone_id); 
            //TODO ajouter fstream chez maud
/*TODO*/    deltaT =-1; //TEST A ENLEVER!!!
            // si deltaT negatif, on retire le drone
            if (deltaT<0){
                drone_actif--;
                drone_temps.at(drone_id) = max_T+1;
            } else {
                drone_temps.at(drone_id) = max_T-deltaT;
            }
        }
        return 0;
}

