
/*#ifndef DEBUG
#define DEBUG 
#endif
*/
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
	/*il costo deve essere per forza lineare? non così...*/


	//good part:
	for (int j =0 ; j<P.length(); ++j)
		{
			
			int e = 1;
				while( e <= Z[j] && SP[j+e-1]==0){
					SP[j+e-1]=e;
					e++;
				}
			
		}

}


void setUpSP_Gusf(string P , int SP[]){

	int _SP[P.length()];

	for (int i = 0; i < P.length(); ++i)
	{
		/* code */
		SP[0]=_SP[i]=0;
	}

	int Z[P.length()];
	
	zeta(P, Z);

	/*Z caclcolata*/

	
/*	for (int i = 0; i < P.length(); ++i)
	{
		cout << i << " -> " << Z[i] << endl;
	}
	cout << endl;
*/
	/* SP calcolato.*/

	/*il costo deve essere per forza lineare? non così...*/

	for (int  j= P.length()-1; j>=1; --j)
	{

		int i=j+Z[j]-1;
		_SP[i]=i-j+1;
	}


/*
	for (int i = 0; i < P.length(); ++i)
		{
			cout << i << " -> _SP  " << _SP[i] << endl;
		}
*/

	SP[P.length()-1]=_SP[P.length()-1];


	for (int i = P.length()-2; i>=1; --i)
	{

		SP[i]= std::max(SP[i+1]-1, _SP[i]);

	}


}



