
#ifndef DEBUG
#define DEBUG 
#endif

#include<iostream>
#include <vector>
#include <algorithm> // std::min_element
#include <iterator>  // std::begin, std::end
using namespace std;

#include "zeta.h"



void setUpSP(string P , int SP[]){

	for (int i = 0; i < P.length(); ++i)
	{
		/* code */
		SP[i]=0;
	}

	int Z[P.length()];
	
	zeta(P, Z);

	/*Z caclcolata*/

	/*
	for (int i = 0; i < P.length(); ++i)
	{
		cout << i << " -> " << Z[i] << endl;
	}*/

//versione non corretta (non lineare)
/*	for (int j = P.length() - 1 ; j>=0; --j)
	{
		
		for (int e = 1; e <= Z[j]; ++e)
		{
			SP[j+e-1]=e;
		}

	}
*/

	/* SP calcolato.*/

	/*il costo deve essere per forza lineare? non così...*/

for (int j =0 ; j<P.length(); ++j)
	{
		
		int e = 1;
			while( e <= Z[j] && SP[j+e-1]==0){
				SP[j+e-1]=e;
				e++;
			}
		

	}

}




void search(string T, string P){

	int m = T.length();
	int n = P.length();

	int SP[P.length()];
	setUpSP(P, SP);




	for (int i = 0; i < P.length(); ++i)
	{
		cout << i << "- " << P[i] << " - "  << SP[i] << " \n";
	}



		int h=0;//posizione sul testo
	int k=0;//posizione sul pattern			
	while(h<=m-n)
	{
			while(T[h+k] == P[k] && k<n) k++;

			if(k==n){ cout << "Pattern trovato in " << h<< endl; 
			#ifdef DEBUG
			for (int i = 0; i < h+k; ++i)
		{
			cout << T[i];
		}
		//cout << "-";
		for (int i = h+k; i < T.length(); ++i)
		{
						cout << T[i];
			/* code */
		}
		cout << endl ;
		for (int i = 0; i < h; ++i)
		{
			cout << " ";
		}
		for (int i = 0; i < P.length(); ++i)
		{
			cout << P[i];
		}
		cout << endl;
			#endif

			//ATTENZIONE ! SE DECIDO DI MUOVERE IL PATTERN IN AVANTI DI |P|=n==k posizioni RINUNCIO A TUTTE LE OCCORRENZE CHE INIZIANO COME SUFFISSO DI QUELLA CHE HO APPENA TROVATO.
			/*h+=k; k=0;*/ } 
			else{
			//h+k è la pos del mismatch.
			//sp[k-1] ti dice quanti caratteri dall'inizio del pattern non devi ricontrollare


			/*h += SP[k-1]+1;
			k = SP[k-1];
			*/
		
		#ifdef DEBUG
		cout << "Miss match in posizione " << h+k << " sul testo, e sul pattern "<< k << endl;
		for (int i = 0; i < h+k; ++i)
		{
			cout << T[i];
		}
		//cout << "-";
		for (int i = h+k; i < T.length(); ++i)
		{
						cout << T[i];
			/* code */
		}
		cout << endl ;
		for (int i = 0; i < h; ++i)
		{
			cout << " ";
		}
		for (int i = 0; i < P.length(); ++i)
		{
			cout << P[i];
		}
		cout << endl;

		cout << "Shift di " << SP[k]+1<< " sul testo del pattern" << endl;
		#endif
		}

		#ifdef DEBUG
				if(k<n)
					cout << "Shift di (k="<<k<<") " << SP[k]+1<< " sul testo del pattern" << endl;
				else
					cout << "Shift di (k="<<k<<") " << SP[k-1]+1<< " sul testo del pattern" << endl;
		
				cout << endl << endl;

		#endif


		if(k<n){
			h += SP[k]+1;
			k = SP[k];
		}else{
			h += SP[n-1]+1;
			k = 0;
		}
		
	

}

}
// Driver program
int main()
{
    string text = "ababababa";
    string pattern = "ababa";
    search(text, pattern);
    return 0;
}