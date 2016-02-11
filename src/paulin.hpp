#ifndef PAULIN_HPP
#define PAULIN_HPP


#include <iostream>
#include <fstream>
#include <iterator>
#include "matrix.hpp"
#include <vector>
#include "objects.hpp"
#include <math.h>
#include <stdlib.h>
#include "basics.hpp"
using namespace std;


Warehouse findNearestWarehouse(Case const& pos,Instance const& instance);

void initialSend(ofstream& outPut, vector<Case>& drones_positions, vector<int>& drones_temps, Instance& instance);
#endif
