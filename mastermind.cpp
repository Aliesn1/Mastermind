#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tentativi 10

void leggi(unsigned int codificatore[]);	//prototipo funzione lettura file
void confronto(int *cont,unsigned int codificatore[],unsigned int decodificatore[], int s);	//prototipo confronto combinazione coificatore con ombinazione decodificatore
bool doppi(unsigned int decodificatore[], int j);
void menu(int cont);


int main ()
{
	
	FILE *f;
	unsigned int codificatore [4], decodificatore [4];
	int i=0, j,cont=0,s=0,a;
	bool doppio = false;
	bool m=true;
	char c;
	
	
	do
	{
		
		
		 if(cont==tentativi+1){
			
			cont=0;
			menu (cont);
			printf("\n inserisci la tua scelta =>");
			m=false;
			scanf("%d",&s);
		}
		
		
		else if (m==true){
			menu(cont);
			printf("\n inserisci la tua scelta =>");
		
			scanf("%d",&s);
			m=false;
			
		}
		else if (m==false){
			s=3;
		}
	
	
		
	
		switch (s){
			
			
			case 1: 
						f = fopen ("record.txt","w+");		//apertura in lettura e scritture
						if (f == NULL){
							printf ("impossibile aprire il file \n");	//controllo se il file è stato aperto
						}
						cont=0;	//azzero il contatore
						
						srand(time(NULL));
						//carico il decodificatore con 4 numeri casuali tra 0 e 9
						for(i = 0; i < 4; i++){
						   codificatore[i]=0+rand()%9; //numeri casuali tra 0 e 9 tramite la funzione rand contenuta in stdlib.h
							   for(j=0;j<i;j++) {
						       		if(codificatore[j]==codificatore[i]) {
						           	i--;
						        	}
							   
							   	}
					   	}	
						
						for(i = 0; i < 4; i++){
						
						   	printf("%d\t", codificatore[i]); //stampo il codificatore
					   	}	
					   	s=3;
						break;
						
			case 2: 	
						exit(1);
						break;
			
			case 3: 	
						f = fopen ("record.txt","a"); //file in append
						if (f == NULL){
							printf ("impossibile aprire il file \n");
						}
						
						
						
						for (j=0;j<4;j++){
							
							printf("\n Inserisci il %d numero: ", j+1);
							
							do{
								doppio = false;
								do{
									scanf("%d",&decodificatore[j]); //carico il decodificatore
									if (decodificatore [j]<0 || decodificatore[j]>9){	//verifica del valore inserito in input
										printf("Numero non valido, ricorda che il numero deve essere compreso tra 0 e 9 \n");
									}
								} while (decodificatore [j]<0 || decodificatore[j]>9);
								
								doppio = doppi(decodificatore, j);
								
							} while (doppio == true);
							fprintf (f, "%d \t", decodificatore[j]); //scrivo sul file la combinazione
				
						
						}
						fprintf (f, "\n"); //inserisco su file lo spazio tra le combinazioni
						fclose (f);
						
						system("cls");	//pulizia dello schermo
						
						for (j=0;j<4;j++){
							
							printf("%d ",decodificatore[j]); //stampo il decodificatore
						}
						
						printf("\n");
						
						
						confronto(&cont, codificatore, decodificatore,1); //chiamata a funzione per il confronto tra codificatore e decodificatore
						if (cont!=11){
							
							printf("\n se vuoi tornare al menu premi m, altrimenti premi un tasto qualsiasi => ");
							scanf("%s",&c);
							if (c=='m'){
								m=true;
							}
							else{
								m=false;
							}
								
						}
						
						
						
						break;
			
			case 4:			
					printf("\n questo e' il contenuto del file: \n");
			
					leggi(codificatore); 	//chiamata a funzione per leggere il file
					m=true;
					break;
					
					
			default: printf("Scelta errata");
		
	}
				
			
	
		
		
			
	}while (1);	//termino il programma quando ho raggiunto il massimo di tentativi
	
fclose (f);
	
}

void leggi(unsigned int codificatore []){

	unsigned int v[4];
	char buff[200];
	FILE *f;
	char *res;
	f = fopen ("record.txt","r"); 
	
	
	
	system("cls");
	while(1) {
	    res=fgets(buff, 200, f);
	    if( res==NULL ){ //controllo se il puntatore è a null = fine del file
	    	 break;
		}
	     
	
	      sscanf(buff, "%d %d %d %d",&v[1], &v[2], &v[3], &v[4]);
	      printf("%d %d %d %d \n", v[1], v[2], v[3], v[4]);
	      confronto(NULL,codificatore,v,2);
	      
    }
	
	
	fclose (f);
}

void confronto (int *cont, unsigned int codificatore[], unsigned int decodificatore[], int s ){ //cont passato per riferimento, mentre i vettori per valore
	int i, j, pos_cor=0, pos_sb=0;
	
	
	switch (s){
		case 1:	
				for(i=0;i<4;i++){
						
						for (j=0;j<4;j++){
							
							if (codificatore[i]==decodificatore[j]){ //confronto un elemento del vettore codificatore con tutti gli elementi del vettore decodificatore
								
								if (i==j){
									
									pos_cor++;
									
								}
								
								else{
									
									pos_sb++;
									
								}
							}
							
						}
					}
					
					if (pos_cor==4){
						*cont=tentativi+1;
						printf("Complimenti, hai indovinato la combinazione");
						
					}
					else{
						(*cont)++;
						
						printf("il numero di tentativi effettuati e': %d \n",*cont);
						printf("\n");
						printf("i numeri giusti nella posizione corretta sono: %d",pos_cor);
						printf("\n");
						printf("i numeri giusti nella posizione sbagliata sono: %d \n", pos_sb);
						
					}
					
				
					if (*cont==tentativi){
						printf("hai perso, il numero massimo di tentativi è stato raggiunto");
						*cont=tentativi+1;
					}
				
				break;
				
				
	case 2:		for(i=0;i<4;i++){
						
						for (j=0;j<4;j++){
							
							if (codificatore[i]==decodificatore[j]){ //confronto un elemento del vettore codificatore con tutti gli elementi del vettore decodificatore
								
								if (i==j){
									
									pos_cor++;		//incremento il contatore dei numeri nella posizione corretta
									
								}
								
								else{
									
									pos_sb++;		//incremento il contatore dei numeri nella posizione sbagliata
									
								}
							}
							
						}
					}
					
					
						printf("i numeri giusti nella posizione corretta sono: %d",pos_cor);
						printf("\n");
						printf("i numeri giusti nella posizione sbagliata sono: %d", pos_sb);
						printf("\n \n");
					
		
				break;
	default: printf("Errore");
				exit(1);
	}
	
}


bool doppi(unsigned int decodificatore[], int j){
	bool doppio=false;
	for (int i=0;i<j;i++){
					if (decodificatore [i]==decodificatore[j]){		//verifica dei doppi
						printf("Il numero %d e' gia' stato inserito, non puoi inserire doppi \n",decodificatore[j]);				
							doppio=true;
						}
				}
	return doppio;
}



void menu(int cont){
	printf("\n1) Inizia una nuova partita \n2) Esci dal gioco\n");
		if (cont !=0 && cont <10){
			printf ("3) Continua la partita \n4) Visualizza le tue giocate precedenti ");
		}
}

