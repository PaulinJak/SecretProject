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

        // Tant que des drones ont le tant de faire des commandes
        int drone_actif = instance.n_drones;
        // Initialise le vecteur temps des drones
        vector<int>  drone_temps(instance.n_drones);
        vector<Case> drone_position(instance.n_drones, Case(0,0));

        while(drone_actif>0){
            //On trouve le drone avec le temps le, plus petit
            int drone_id;
            int temps_abs=max_T;
            int i=0;
            for(int t : drone_temps){
                if (t<temps_abs){
                    drone_id=i;
                    temps_abs=t;
                }
                i++;
            }
            int deltaT = max_T - temps_abs;
            //on appel la fonction de choix
            //deltaT = choix_next_move(instance, deltaT, drone_position.at(i),i); 
/*!!!!*/    deltaT =-1; //TEST A ENLEVER!!!
            // si deltaT negatif, on retire le drone
            if (deltaT<0){
                drone_actif--;
                drone_temps.at(i) = max_T+1;
            } else {
                drone_temps.at(i) = max_T-deltaT;
            }
        }
        return 0;
}

