
#ifndef DEBUG1
#define DEBUG1 
#endif

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
 
#include "zeta.h"

void searchBM(string text, string pattern);


void reverse_array( int array[], int arraylength )
{
    for (int i = 0; i < (arraylength / 2); i++) {
        int temporary = array[i];                 // temporary wasn't declared
        array[i] = array[(arraylength - 1) - i];
        array[(arraylength - 1) - i] = temporary;
    }
}


void setUpSGSR(string P, int Z[] , int SGSR[]){

	for (int i = 0; i < P.length(); ++i)
	{
		/* code */
		SGSR[i]=-99;
	}

	int inc[P.length()];
	for (int i = 0; i < P.length(); ++i)
	{
		inc[i]=0;
	}

	for (int i = P.length()-1; i>=1; --i)
	{
		if(Z[i]>0){
			SGSR[Z[i]+inc[Z[i]]] = i+Z[i];
			inc[Z[i]]+=i;
		}

	}
	for (int i = P.length()-1; i>=1; --i)
	{
		
		cout << "i = "<<i << " i+Z[i]="<< i+Z[i] << endl;

	}
	for (int i = P.length()-1; i>=0; --i)
	{
		
		cout << "SGSR["<<i<<	"] = "<<SGSR[i] << endl;

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
	cout << toId('a')<<endl;

    int l = pattern.length();

    cout << pattern << endl;


    int bcr[l][ SIGMA ];

    calcoloBCR(pattern,bcr, ALFABETO ); 

    std::reverse(pattern.begin(),pattern.end());
    
    // Construct Z array
    int Z[l];//per la sgsr
    zeta(pattern, Z);

    for (int i = 0; i < l; ++i)
    {
    	cout << i << " -zeta - "<<pattern[i]<<" -> " << Z[i]<< endl;
    }


    int SGSR[l];//per la sgsr
	setUpSGSR(pattern,Z,SGSR);



    for (int i = 0; i < l; ++i)
      	cout << i << " - " << pattern[i] << " - "  << Z[i] << " \n";



	cout << endl;

	for (int i = 0; i < l; ++i)
      	cout << i << " * " << pattern[i] << " - "  << SGSR[i] << " \n";



    reverse_array(Z,l);
    std::reverse(pattern.begin(),pattern.end());
    

	int h=pattern.length()-1;

	while(h<text.length()){


    	int i=pattern.length()-1;

    	int j = h; // j serve a salvare l'allineamento sul testo

		int exi =0;		

		    //	cout << " h = " << h << " i = " << i  << " j = "<< j << endl;

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

    	while (exi==0 && i>=0)
    	{
    		if(pattern[i]==text[h]){

    			//cout << "confronto "<< pattern[i]<< " con " << text[h]<< "  " << (pattern[i]==text[h]) <<  endl;
    			
    			if( i==0){
    			//cout << "Ho trovato "<< i  << endl;
 //   			cout << "***h = " << h << " i = " << i  << " j = "<< j << endl;
    			cout << "Occorrenza " << h <<endl;

    			}

    			h--;
    			i--;
    			
    		}else{

		    	exi=1;
		    	cout << "Miss match in "<< i << " e "<< h << endl;
    	

    		}
    	}

    	int a = bcr[i][toId(text[h])];

    	//int Zi= SGSR[i];


    	if(a >=0 && i>=0){//se a=-1 significa che text[h] non occorre in P, se i =-1 significa che in questo turno ho trovato il pattern (NON HA SENSO APPLICARE LA bcr)
    		//cout<< "BCR a ="<< a<< " i = " << i <<"\n";
		j += i - a;
		h=j;			
		}else{
			h=j+1;
		}
    	i = pattern.length()-1;
    	

    }
    
}


// Driver program
int main()
{
	string text = "aaaaaaaafffffffffffaaaaaaaaaaaaaafffffffffffaaaaaaaaaaaaaaffffffffffffffffaaaaaaaaaaaaaaafffafafafafafafafafafaf";
    string pattern = "abcabcabcdabc";

    cout << text << endl;
    
	searchBM(text,pattern);
    
 

    return 0;
}

