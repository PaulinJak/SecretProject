#ifndef __BASIC_HPP_
#define __BASIC_HPP_

#include "matrix.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "objects.hpp"
#include <math.h>
#include <algorithm>    // std::sort
#include <vector>       // std::vector



int distance(Case const& c1, Case const& c2);

bool compProductWeight (Product i,Product j);
void products_sort(vector<Product>& list_products);

void readInstance( char const * nom_fichier,Instance& instance );

void writeOutput(ofstream& outputStream, int const& nb_operations);

#endif /*__BASIC_HPP_*/
