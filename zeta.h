


void zeta(string S, int Z[]);


void zeta(string S, int Z[]){

	int n = S.length();

	//Inizializzo Z
	int i;
	for ( i = 0; i <= n-1; i++) Z[i]=0;
	//Lo Z blocco più a destra incontrato sin ora
	int l=0;
	int r=0;

	for (i=1; i <= n-1; i++){

		#ifdef DEBUG
		cout << endl << "posizione i = " << i  << endl;
		cout << " z blocco = [" << l << ", " << r << "]" << endl; 
		#endif
		//int eccedendo=0;

		if(i<=r){//Caso in cui i e' dentro nell'ultimo z blocco


			#ifdef DEBUG
			cout<< " i e' dentro lo z blocco ..." << endl;
			cout << " Lo z blocco e' lungo r ="<< r << " meno l = " << l <<" +1 cioe' : " << r-l+1 << endl;
			#endif
			
			//Qui discrimino i 3 casi (beta sottostringa dello z blocco alpha, beta suffisso dello z blocco e  beta che sfora lo zeta blocco)->

			int k = i-l;
			
			#ifdef DEBUG
			cout << "i cade nel prefisso del testo in posizione k = " << k << endl;
			#endif
			
			if (k+Z[k]/*-1*/  /*in Z[k] conto anche il carattere T[k] quindi -1*/<r-l+1 /*l e r sono entrambi dentro lo z blocco quindi sottraendoli mangio un carattere quindi +1*/
						) 
			// La lunghezza di aplha e' r-l+1 
			{

				if(i+Z[k]< S.length()){
				
					#ifdef DEBUG
					cout << "Copio il valore di Z dalla posizione k = "<< k << " alla posizione i = " << i << endl;
					#endif
					
					Z[i]=Z[k];
				
				}else{
					
					#ifdef DEBUG
					cout << "Starei eccedendo..."<< endl;
					cout << "Copio il valore di Z dalla posizione k = "<< k << " alla posizione i = " << i << endl;
					#endif
					
					Z[i]= S.length()-i;
				}

				#ifdef DEBUG
				cout << "Questo era il caso contenuto strettamente , valore finale di Z[i]="<< Z[i] << endl;
				#endif
			}
			if (k+Z[k]/*-1*/ ==r-l+1)
				{

					Z[i]= r-i+1;

					#ifdef DEBUG
					cout << "Meglio procedere con i confronti...";
					cout  << "Li ricomincio fra r+1 = "<< r+1<< "e  r-l+1 =" <<  r-l+1 << endl;
					#endif

					int start1 = r+1; //r+1;
					int start2 = r-i+1;  //la lunghezza di gamma ;
					int jj=0;
					
					while(S[start1+jj] == S[start2+jj] && start1+jj < S.length()) {
						Z[i]++;
						jj++;
					}

					if(jj>0){

						l=i;
						r=i+Z[i]-1;

						#ifdef DEBUG
						cout << "Aggiorno lo Z blocco"<< endl;
						#endif

					}

					#ifdef DEBUG
					cout << "Questo era il caso gamma suffisso alpha, valore finale di Z[i]="<< Z[i] << endl;
					#endif

			}

			if (k+Z[k]>r-l+1 ){ 

				#ifdef DEBUG
				cout << "k + Z[k] eccede lo z blocco ... "<< k + Z[k] <<" > "<< r-l+1 << endl;
				#endif

				Z[i]=r-i+1; // la lunghezza di gamma. Ricorda, considero sempre interni gli indici che delimitano una stringa.

				/*Si noti che ora k+Z[i] vale esattamente la lunghezza di alpha cioe' i -l +  r -i + 1 */
				
				int start1 = r+1;
				int start2 = r-l +1;
				int jj=0;

				#ifdef DEBUG
				cout << "Sarebbe meglio procedere con i confronti...";
				cout  << "Li ricomincio fra k+1 = "<< k+Z[k]+1<< "e i+Z[i]+1 =" << i+Z[i]+1 << endl;
				#endif
				
				while(S[start1+jj] == S[start2+jj]) {
					Z[i]++;
					jj++;
				}

				if(jj>0){

					l=i;
					r=i+Z[i]-1;
				
					#ifdef DEBUG
					cout << "Aggiorno lo Z blocco"<< endl;
					#endif
				
				}

			}

		}else{// caso in cui i e' oltre lo z blocco (continuo i confronti regolarmente)

			#ifdef DEBUG
			cout << "i e' fuori lo z blocco ..." << endl;
			#endif

			int j=0;

			while(S[i+j]==S[j]){

				Z[i]++;
				j++;
			}

			if(j>0){
				//se siamo andati almeno un passo avanti:
				
				#ifdef DEBUG
				cout << "siamo andati avanti con i confronti per j =" << j << " posizioni." << endl;				
				#endif
				
				r=i+Z[i]-1;
				l=i;
			}

		}
	}

}