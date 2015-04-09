#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

#include "counter.h"

#define P 13
#define VMAX 17
#define M 100
#define MAXITEMS 8

int hfunc(char* key) {
    int hkey = 0;
    for (int i = 0; i < strlen(key) && key[i]!=' '; i++)
        hkey = (hkey * P + key[i]) % VMAX;
    return hkey;
}

int main(int argc, char *argv[]) {


    /* aici fac verificarea sa fi primit exact 2 argumente */
    if (argc != 2)
    {
        fprintf(stderr, "Usage : %s input_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*freopen  redeschide stdin-ul sa pointeze catre fisierul de unde se citeste */
    freopen(argv[1], "r", stdin);

	int N,i,size,k;
	int a[5],hkey,l=0;
	char *p;
	scanf( "%d", &N );
	char comanda[M];
    
	Counter *G = new Counter[N];
	//se retin comenzile posibile
	char *x[MAXITEMS] = { "OPEN_WINDOW", "ADD_PERSON", "PROCESS", "PROCESS_ALL", "PRINT_STACKS", "FLUSH_STACKS", "PRINT_QUEUES"};
	int y[MAXITEMS]={1,13,12,14,4,11,16};
	while( fgets( comanda, 100, stdin ) )
		{
		p = strtok(comanda, " ");
		hkey = hfunc(p);
		if (hkey==y[0])
			{
			for( i=0 ; i<5 ; i++ ) {
				p = strtok( NULL, " " );
				a[i] = atoi(p);
				}
			// se apeleaza functia OPEN cu parametrii
			G[a[0]].OPEN_WINDOW(a[1],a[2],a[3],a[4]);
			}
		if (hkey == y[1])
			{
			i = 0;
			for ( i=0 ; i<3 ; i++ )
				{
				p=strtok( NULL, " " );
				a[i] = atoi(p);
				}
			//se adauga o noua persoana
			//la ghiseul cu indexul a[0]
			G[a[2]].ADD_PERSON(a[0],a[1]);
			}

		if ( hkey == y[2] )
			{
			i=0;
			for ( i=0 ; i<2 ; i++ )
				{
				p=strtok( NULL, " ");
				a[i] = atoi(p);
				}
			//k=indexul urmatorului ghiseu deschis

			k=a[0];
			for (i=k+1;i<N;i++)
				if (G[i].isOpen()==1)
					{
					k=i;break;}
			if (k==a[0])
				for (i=0;i<k ;i++)
					if (G[i].isOpen()==1)
						{k=i;break;}
			//se verifica daca exista persoane care
			//trebuie mutate la alt ghiseu
			if (G[a[0]].PROCESS(a[1])==-1)
				{
			//se adauga lista de persoane de mutat
			//(Move) la ghiseul cu index k
			while(!G[a[0]].Move.isEmpty()){
G[k].Q.enqueue(G[a[0]].Move.peek_index(),G[a[0]].Move.peek_grams());
					G[a[0]].Move.dequeue();}
					}
			}

		if ( hkey == y[3])
			{
			i=0;
			p = strtok(NULL, " ");
			a[i] = atoi(p);
			size=G[a[0]].getsizeQ();
			//k= indexul urmatorului ghiseu deschis
			k=a[0];
			for (i=k+1;i<N;i++)
				if ((G[i].isOpen()==1) && i!=k)
					{k=i;break;}
			if (k==a[0])
				for (i=0;i<k ;i++)
					if ((G[i].isOpen()==1) && (i!=k))
						{k=i;break;}
			//se verifica daca exista persoane care
			//trebuie mutate la alt ghiseu
			if (G[a[0]].PROCESS(size)==-1){
				while (!G[a[0]].Move.isEmpty()){
G[k].Q.enqueue(G[a[0]].Move.peek_index(),G[a[0]].Move.peek_grams());
				G[a[0]].Move.dequeue();
				}
				}
			}

		if ( hkey == y[4] ){
			// se afiseaza Stiva de colete
			if (l!=0)
				printf("\n");
			printf("STACKS:");
			for (i=0;i<N;i++)
				if (G[i].isOpen()==1){
					printf("\n%d:",i);
					if (G[i].PRINT_STACKS()==0)
						printf(" ");
				}
			l=1;
			}
		if ( hkey == y[5] ){
			//se apeleaza functia FLUSH_STACKS
			if (l!=0)
				printf("\n");
			printf("FLUSHING:");
			for (i=0;i<N;i++)
				if (G[i].isOpen()==1){
					printf("\n%d:",i);
				if(G[i].FLUSH_STACKS()==0)
				printf(" ");
					}
			l=1;
			}
		if ( hkey == y[6] ){
			//se afiseaza cozile de la ghseele deschise
			if (l!=0)
				printf("\n");
			printf("QUEUES:");
			for (i=0;i<N;i++)
				if(G[i].isOpen()==1){
					printf("\n%d:",i);
					if (G[i].PRINT_QUEUES()==0)
						printf(" ");
					}
			l=1;
			}
		//se readuce vectorul parametrilor la 0
		for ( i=0; i<5 ;i++ )
			a[i]=0;
		}
    	delete[] G;
	return 0;
}
