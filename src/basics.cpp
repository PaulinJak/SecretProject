#include "basics.hpp"

using namespace std;


void readInstance(const char* nom_fichier,int& n, int& m, Matrix2D<int>& image ) { 


  char char1;

    ifstream fichier(nom_fichier);
    if(fichier) {
        //pour n
        fichier >> n  >> m ;
        cout <<"n="<< n <<", m=" << m <<"\n";

        image=Matrix2D<int>(n,m);

        for(int i=0;i<n;i++) {

            for(int j=0;j<m;j++) {
                fichier >> char1;
                if(char1=='#') image(i, j)=1;
                else image(i,j)=0;

            }
        }
    }
    else cout << "Fichier non trouvé!! \n";
}

