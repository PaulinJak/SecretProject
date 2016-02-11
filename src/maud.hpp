//
//  m.hpp
//
//
//  Created by Maud Doumergue on 10/02/2016.
//
//

#ifndef fonctions_hpp
#define fonctions_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include "matrix.hpp"
#include "objects.hpp"
#include "basics.hpp"

using namespace std;

int choix_next_move(Instance& instance, int delta_temps, Case& drone_position, int drone_number);

#endif /* fonctions_hpp */