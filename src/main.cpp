#include <iostream>
#include <fstream>
#include <iterator>
#include "matrix.hpp"
#include <vector>
#include "objects.hpp"
#include "fonctions.hpp"
#include "carre.hpp"

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
		         //lit "\n"
		}
	}
	else cout << "Fichier non trouvé!! \n";
}




vector<Case> aPeindre(int const& n, int const& m, Matrix2D<int> const& image, vector<Case>& casesAPeindre){
    casesAPeindre.clear();

	for(int i=0;i<n;i++) {
			for(int j=0;j<m;j++) {
			  if(image(i,j)==1){Case CaseAPeindre(i,j);
			                    casesAPeindre.push_back(CaseAPeindre);
			  }
			}
	}
	return casesAPeindre;

  } 


void updateComposanteConnexeRec( Matrix2D<int>& carre_score,Matrix2D<int>& lignes_score, Matrix2D<int>& colonnes_score,  Matrix2D<int> visitStatus, vector<Case> aFaire ){

}


void updateComposanteConnexe( Matrix2D<int>&  image, int& n, int& m, Case const& caseCentrale,  Matrix2D<int>& carre, Matrix2D<int>& carre_score,  Matrix2D<int>& lignes,Matrix2D<int>& lignes_score, Matrix2D<int>& colonnes, Matrix2D<int>& colonnes_score){

  Matrix2D<int> traiteStatus(n,m);//initialise status à non_visité
  vector<Case> aFaire ;
  aFaire.push_back(caseCentrale);
  // updateComposanteConnexeRec( carre_score,lignes_score, colonnes_score, visitStatus, aFaire);

  Case courant(0,0);

  while(not(aFaire.empty())){
      courant=aFaire.back(); //access last element
      aFaire.pop_back(); //remove last element
      int i0=courant.i;
      int j0= courant.j;
      f_colonnes_point( n, m, i0, j0, image, colonnes, colonnes_score);

      f_lignes_point( n, m, i0,j0, image, lignes, lignes_score);

      fcarre(image, carre, carre_score, i0,j0 ); 

	traiteStatus(i0,j0)=1; //case traitée
      
      //voisin haut
      if((i0>0) && (traiteStatus(i0-1,j0)==0) && ((image(i0-1,j0)==1) ||  (image(i0-1,j0)==2) )){
	Case voisin(i0-1,j0);
	aFaire.push_back(voisin);
      }
 //voisin bas
      if((i0<n) && (traiteStatus(i0+1,j0)==0) && ((image(i0+1,j0)==1) ||  (image(i0+1,j0)==2) )){
	Case voisin(i0+1,j0);
	aFaire.push_back(voisin);
      }
 //voisin gauche
      if((j0>0) && (traiteStatus(i0,j0-1)==0) && ((image(i0,j0-1)==1) ||  (image(i0,j0-1)==2) )){
	Case voisin(i0,j0-1);
	aFaire.push_back(voisin);
      }
 //voisin droit
      if((j0<m) && (traiteStatus(i0,j0+1)==0) && ((image(i0,j0+1)==1) ||  (image(i0,j0+1)==2) )){
	Case voisin(i0,j0+1);
	aFaire.push_back(voisin);
      }
  }
    
}


int main(int argc, char* argv[])
{
   const char*  fileName;
  if(argc>1)//we passed the filename in arg
    fileName=argv[1];
  else fileName = "instances/right_angle.in";
  
  

  Matrix2D<int> image;
  int n=0,m=0;
  
  readInstance(fileName,n,m,image);
  
  Matrix2D<int> carre(n,m);
  Matrix2D<int> carre_score(n,m);
  Matrix2D<int> lignes(n,m);
  Matrix2D<int> lignes_score(n,m);
  Matrix2D<int> colonnes(n,m);
  Matrix2D<int> colonnes_score(n,m);

  f_lignes( n, m,image,  lignes,  lignes_score);
  f_colonnes( n, m,image,  colonnes,  colonnes_score);
  
  for (int i=0; i<n; i++){
    for (int j=0; j<m; j++){
        fcarre(image, carre, carre_score,i,j);
    }
  }
  vector<Case> casesAPeindre;
  aPeindre(n,m,image,casesAPeindre);

  vector<Case>::iterator iter;

  //iter = casesAPeindre.begin();
  
  Case choix(0,0);
  int compteur_operations=0;
  ofstream output_file ("ouputFile.out");
  while(not(casesAPeindre.empty()) && (compteur_operations<n*m)){
      
      aPeindre(n,m,image,casesAPeindre);

    choix = choix_next_move( n, m,image,  colonnes,  colonnes_score, lignes, lignes_score, carre, carre_score,casesAPeindre);
        updateComposanteConnexe( image, n, m, choix,  carre, carre_score, lignes, lignes_score,colonnes,colonnes_score);
        compteur_operations++;
    }
  cout<<"Nombre d'opération: " <<compteur_operations<<endl;


  for (int i=0; i<n; i++){
    for (int j=0; j<m; j++){
        if(image(i,j)==2){
            output_file<<"#";
        } else{
            output_file<<".";
        }
    }
    output_file<<"\n";
  }
  output_file.close();
            return 0;

}

