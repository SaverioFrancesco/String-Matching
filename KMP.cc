
/*#ifndef DEBUG
#define DEBUG 
#endif
*/
#include<iostream>
#include <vector>
#include <algorithm> // std::min_element
#include <iterator>  // std::begin, std::end
using namespace std;


/*Versione Zantoni*/
void KMP(string T,  string P){
	

	int m = T.length();
	int n = P.length();

	int SP[n];
	int i, j =0;

	for (int i = 0; i < n; ++i)
	{

		/*
						   x              x?=y                    y
		+----------------------------------------------------------------+
		+-----------------+o                    +----------------+i
				gamma      sp(i-1)=|gamma|              gamma

		*/
		
		//j==i-1

		//poi... j'=sp(i-1)-1


		/*
						   x                                      y
		+----------------------------------------------------------------+
		+-----------------+                     +----------------+i
		                                                         j
				gamma      sp(i-1)=|gamma|              gamma

			 x'                        x'?=y                      y			  
		+-----------------+                     +----------------+i
		+---+o        +---+                     +---+o       +---+                                    
			 j'
		gamma'            
		*/

	/*  ESEMPIO:

		abac.....abab

		c!=a quindi cerco il amssimo prefisso/suffisso in aba nella speranza che sia seguito  da P[i] = b */
		


		j=i-1;
		SP[i]=0;
		while(P[SP[j]] != P[i] && j>0) j=SP[j]-1;

		if(j>=0 && P[i]==P[SP[j]]) SP[i]=SP[j]+1;

	}

	#ifdef DEBUG
	for (int i = 0; i < n; ++i)
	{
		cout <<P[i] <<  " -> " << SP[i] << endl;

	}
	#endif

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
			h += n - SP[k-1];
			k = SP[k-1];
		}
		
	}

}

// Driver program
int main()
{
    //string text = "michele michele michelle lelle rene irene imene michele ene michiremich"; 
    //string pattern = "abcdabcdfabcdabcdf";

    string text = "aasbaababcacbabcabcacbabcabaabababfaba";
    string pattern = "abcacbabcaba";
    KMP(text, pattern);

    for (int i = 0; i < text.length(); ++i)
    {
    	cout << i << "--->"<< text[i]<<" "<<endl;
    }
    cout<<endl;
    return 0;
}