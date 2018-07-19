/*
#ifndef DEBUG1
#define DEBUG1 
#endif
*/
#ifndef ALFABETO
#define ALFABETO "abcdefg"
#endif

#ifndef SIGMA
#define SIGMA 7
#endif

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
 

#include "sp.h"

void searchBM(string text, string pattern);


void reverse_array( int array[], int arraylength )
{
    for (int i = 0; i < (arraylength / 2); i++) {
        int temporary = array[i];                 // temporary wasn't declared
        array[i] = array[(arraylength - 1) - i];
        array[(arraylength - 1) - i] = temporary;
    }
}




void calcoloBCR(string P , int bcr[][SIGMA] , string Sigma){

	for (int j = 0; j < Sigma.length(); ++j)
	{
		
		char currentCharapter=Sigma[j];
	
		int lastPosition=-1;
		for (int i = 0; i <P.length(); ++i)
		{
			if(P[i]!=currentCharapter){
				bcr[i][j]= lastPosition;
			}else{
				bcr[i][j]= i; //per se stesso non ha molta importanza che valore assuma (non si può avere un miss match fra due caratteri identici...)
				lastPosition=i;
			}
		}

	}

	#ifdef DEBUG1
	for (int j = 0; j < Sigma.length(); ++j)
	{
	
		cout << Sigma[j] <<  " ... \n";

		for (int i = 0; i <P.length(); ++i)
		{
			cout <<	bcr[i][j] << " " ;
		}
		cout << endl;
		for (int i = 0; i < P.length(); ++i)
		{
			cout <<	P[i]<< " " ;

		}
		cout << endl;
	}

	#endif 

}

int toId( char t){


	if(t=='a') return 0;
	if(t=='b') return 1;
	if(t=='c') return 2;
	if(t=='d') return 3;
	if(t=='e') return 4;
	if(t=='f') return 5;
	if(t=='g') return 6;
	if(t=='h') return 7;
}

void searchBM(string text, string pattern)


{

    int l = pattern.length();

   // cout << pattern << endl;


    int bcr[l][ SIGMA ];

    /*Calcolo Bad charapter Rule*/
    calcoloBCR(pattern,bcr, ALFABETO ); 


    /*Calcolo GoodSuffix Rule*/

    std::reverse(pattern.begin(),pattern.end());
 
    int RSP[l];

	setUpSP_Gusf( pattern , RSP );


/*    for (int i = 0; i < l; ++i)
      	cout << i << " - " << pattern[i] << " RSP - "  << RSP[i] << " \n";
*/

	reverse_array(RSP,l);
    std::reverse(pattern.begin(),pattern.end());

    for (int i = 0; i < l; ++i)
    {
    	RSP[i] = l-RSP[i];
    }
    
    int _RSP[l];
    for (int i = 0; i < l; ++i)
    {
    	/*init*/
    	_RSP[i]=-1;
    }
    for (int i = 0; i < l; ++i)
    {
    	_RSP[RSP[i]]=i;
    }

  /*  for (int i = 0; i < l; ++i)
      	cout << i << " - " << pattern[i] << " -  RSP_Reversed ->"  << _RSP[i] << " ///// " <<RSP[i] << " \n";
*/


      //BoyerMoore


	int h=pattern.length()-1;

	while(h<text.length()){


    	int i=pattern.length()-1;

    	int j = h; // j serve a salvare l'allineamento sul testo

		int exi =0;		

	
		cout << text << endl;

		for (int i = 0; i < +1+j-pattern.length(); ++i)
		{
			cout << " ";
		}
		for (int i = 0; i < pattern.length(); ++i)
		{
			cout << pattern[i];
		}
		cout << endl;

    	int foundOcc=false;

    	while (exi==0 && i>=0)
    	{
    		if(pattern[i]==text[h]){

    			if( i==0){
    			cout << "Occorrenza " << h <<endl;
    			foundOcc=true;
    			}

    			h--;
    			i--;
    			
    		}else{

		    	exi=1;
		    	cout << "Miss match in "<< i << " e "<< h << endl;
    	

    		}
    	}

    	int bc = bcr[i][toId(text[h])];
		if(i<0) bc =-1;//per prevenire bug     	
    	int gs=_RSP[i+1];//se è avvenuto il mismatch sull'indice i guarda alla posizione prima (ho scritto l'indice sull'inizio del suffisso)
    	if (i+1<0) gs=-1;//per prevenire bug 
    	

    	if (bc<=gs)
    	{
	    	cout << "Bad charapter <<"<< bc << endl;

	    	if(bc >=0 && i>=0){
	    					   //se bc=-1 significa che text[h] non occorre in P, se i =-1 significa che in questo turno ho trovato il pattern (NON HA SENSO APPLICARE LA bcr)
	    		               //cout<< "BCR a ="<< a<< " i = " << i <<"\n";
			j += i - bc;
			h=j;			
			}else{
				if (bc==-1 && i>=0)
				{	
					h=j+ i+1; //hai trovato un
					cout<< j+pattern.length()- i <<endl; 
				}else{
					h=j+1;
				}
			}

    	}else{
	    	cout << "Good suffix <<"<< gs << endl;

    		if(gs >=0 && i>=0){
    			j+=i-gs+1;
    			h=j;
    		}else{
    			if (gs==-1 && i>=0)
				{	
					h=j+pattern.length(); //hai trovato un 
				}else{
					h=j+1;
				}
    		}
    	}

    	i = pattern.length()-1;

    }
    
}

// Driver program
int main()
{
	string text = "aagaaagaaaaagaaaaafabcabccabcabccbbacbgbbacbgaaaaaaaaaaaabcabccbbacbgaaaaaaaaaaaaaa";
    string pattern = "abcabccbgacbg";

	searchBM(text,pattern);

    return 0;
}

