// algorithm.cpp : 
// Schelet cod Tema 3 SD - Inverted index
// Autor: octavian.rinciog@gmail.com
#include <string>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "algorithm.h"
#include "HashMap.h"

using namespace std;

/**Functia de hash*/
unsigned int hashFunction1(std::string key)
{
	unsigned int hash = 5381;
	for (unsigned i = 0; i< key.size(); i++)
		{
		hash = ((hash << 5) + hash) + (int)key[i];	
		}
	
	return hash;
}        

HashMap H;


Algorithm::Algorithm(void)
{

}

Algorithm::~Algorithm(void)
{

}


void Algorithm::indexSite(const std::string &row)
{
	char *row_tok=strdup(row.c_str());
	char *command=strtok(row_tok," ");
	if (strcmp(command,"PUT")!=0)
	{
		free(row_tok);
		return;
	}
	char *site=strtok(NULL," ");
	char *word=strtok(NULL," ");

	// se returneaza indexul site-ului "site"
  
	int index = LL.addFirst(site);

	// pentru fiecare cuvant din cadrul comenzii
	// se introduce in hash-table asocierea word-index 
	while(word)
	{
		H.put(word,index);
		word = strtok(NULL," ");
	}
	free(row_tok);
}

void Algorithm::getSites(const std::string &row)
{
	int ok = 0;

	//se returneaza vectorul cu indecsi corespunzatori
	//site-urilor comune cuvintelor dorite
 
	int *v = H.comparison(row,ok);

	//ok = marimea vectorului

	if (ok == -1 || ok == 0)
		printf("\nSITE_NOT_FOUND");

	else
		if (v != NULL)		
		 {
		int i,j;
		std::string *z;
		char *x[ok];
		z = new std::string[ok];
		for ( i = 0; i< ok; i++)
			{
			//se gaseste site-ul corespunzator
			//fiecarui index
			z[i] = LL.search(v[i]);			
			x[i] = strdup(z[i].c_str()); 							
			}
		char *aux;
		// se sorteaza site-urile 
		for (i = 0; i< ok-1;i++)
			for (j = i+1;j< ok ;j++)
				if (strcmp(x[j],x[i])< 0)
					{
					aux = x[j];
					x[j] = x[i];
					x[i] = aux;
					}
		std::cout<<"\n";
		for (i = 0;i< ok; i++)
			std::cout<<x[i]<<" ";
		delete[] z;
		for (i = 0; i< ok; i++)
			free(x[i]);
	}
	delete[] v;
}

void Algorithm::wordInSite(const std::string &row)
{
	char *row_tok=strdup(row.c_str());
	char *command=strtok(row_tok," ");
	if (strcmp(command,"SITE")!=0)
	{
		free(row_tok);
		return;
	}
	
	char *site=strtok(NULL," ");
	char *word=strtok(NULL," ");

	//se returneaza index-ul site-ului 

	int index = LL.addFirst(site);

	int ok = 1;
	int ok1;	

	while(word && ok == 1)
	{
		// se returneaza valoarea de 
		// adevar pentru asocierea 
		// word - index 
	
		ok1 = H.search(word,index);
		(ok1 == -1) ? ok1= 0 : ok1 = 1;
		ok = ok & ok1;
		word=strtok(NULL," ");
	}
	if (ok == 1)
		printf("\nWORD_FOUND");
	else printf("\nWORD_NOT_FOUND");
	free(row_tok);
}

void Algorithm::resolve()
{
	string row;
	while ( std::cin.good() )
	{
		std::getline(std::cin,row);
		//nu iau in considerare linii cu mai putin de 3 caractere
		if (row.size()<3)
			continue;
		switch(row[0])
		{
		//PUT
		case 'P':
			indexSite(row);
			break;
		//GET
		case 'G':
			getSites(row);
			break;
		//SITE
		case 'S':
			wordInSite(row);
			break;
		default:
			cout<<"Invalid option"<<endl;
		}
	}
}


