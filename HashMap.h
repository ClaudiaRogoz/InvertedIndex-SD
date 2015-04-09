#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include "LinkedHashEntry.h"

#define MAX 1050

using namespace std;

const int DEFAULT_TABLE_SIZE = 126;

unsigned int hashFunction(std::string key)
{
	unsigned int hash = 5381;
	for (unsigned i = 0; i< key.size(); i++)
		{
		hash = ((hash << 5) + hash) + (int)key[i];
		}
	return hash;
}        
 

class HashMap {

private:
      float threshold;
      int maxSize;
      int tableSize;
      int size;
      LinkedHashEntry **table;
      
	//redimensionarea hash-table
      void resize() {
            int oldTableSize = tableSize;
            tableSize *= 2;
            maxSize = (int) (tableSize * threshold);
            LinkedHashEntry **oldTable = table;
            table = new LinkedHashEntry*[tableSize];
            for (int i = 0; i < tableSize; i++)
                  table[i] = NULL;
            size = 0;
	    int siz;
            for (int hash = 0; hash < oldTableSize; hash++)
                  if (oldTable[hash] != NULL) {
                        LinkedHashEntry *oldEntry;
                        LinkedHashEntry *entry = oldTable[hash];
                        while (entry != NULL){
			// se copiaza pe rand vechile inregistrari
			// in noul hash-table 
			     siz = entry->getNoValues();
			     entry->setK();
			     for (int l = 0 ; l < siz ; l++)	            
			     	put(entry->getKey(), entry->getValue());
                             oldEntry = entry;
                             entry = entry->next;
                             delete oldEntry;
                        }
                  }
            delete[] oldTable;
      }
 
public:
      int *array;
      int *v;
      HashMap() {
		//factorul de incarcare stabilit la 70% 
            threshold = 0.70f;
		// dimensiunea maxima pe care o poate suporta
		// hashtable inainte de redimensionare 
		// maxSize = 70% din tableSize
            maxSize = (int) 126 * 0.7;
            tableSize = DEFAULT_TABLE_SIZE;
            size = 0;
            table = new LinkedHashEntry*[tableSize];
            for (int i = 0; i < tableSize; i++)
                  table[i] = NULL;
    }
 
      void setThreshold(float threshold) {
            this->threshold = threshold;
            maxSize = (int) (tableSize * threshold);
      }
 
	int* comparison(const std::string &words,int& j) {
	    char *words_tok = strdup(words.c_str());
	    char *command = strtok(words_tok, " ");
	    char *word = strtok(NULL, " ");
	    if (strcmp(command,"GET")!=0){
			free(words_tok);
			return NULL;}
	    unsigned int key = hashFunction(word);
	    int hash = (key % tableSize);
	    int i;
	    // prin intermediul operatiilor pe biti 
	    // se construieste vectorul indecsilor 
	    unsigned a[MAX];
	    for (i = 0; i< MAX;i++)
		a[i] = 1;
	    while (word != NULL)
		{
		key = hashFunction(word);
		hash = (key % tableSize);
           	 if (table[hash] == NULL){
			free(words_tok);			
			j = 0;                  	
			return NULL;}
            	else {
                  	LinkedHashEntry *entry = table[hash];
                 	if (entry == NULL){
				j = 0;
				free(words_tok);
                       		return NULL;}
                 	 else	{
		while (strcmp(entry->getKey().c_str(),word) !=0 
					&& entry->next != NULL)
					{
					entry = entry->next;
					}
		if (strcmp(entry->getKey().c_str(),word)!=0)		
				{
				j = 0; 
				free(words_tok);
				return NULL;
				}			
				for (i = 0;i<MAX; i++){
					a[i] = a[i] & entry->value[i];
					}	
				}
            		}
		word = strtok(NULL," ");
      		}
		for (i = 0; i< MAX ; i++)
			if (a[i] != 0){
				j++;				
				}
		int *p = new int[j];
		int k = 0;
		for (i = 0; i< MAX ; i++)
			if (a[i] != 0){
				p[k] = i;
				k++;				
				}
		v = p;
		free(words_tok);
	return v;
	}

      int get(std::string key1) {
	    unsigned int key = hashFunction(key1);
            int hash = (key % tableSize);
            if (table[hash] == NULL)
                  return -1;
            else {
                  LinkedHashEntry *entry = table[hash];
                  while (entry != NULL && entry->getKey() != key1)
                        entry = entry->getNext();
                  if (entry == NULL)
                        return -2;
                  else	{
			int siz;
			int *array1;
			siz = entry->getNoValues();
			array1 = new int[siz];
			entry->setK();
			for (int i = 0;i< siz; i++){		
				array1[i] = entry->getValue();
				}
			array = array1;
			delete[] array1;
			return 1;			
			}
            }
      }
	int search(std::string key1, int index) {
	// se returneaza -1 sau 1 daca nu s-a gasit/ s-a gasit  
	// key1 in site-ul cu indexul "index"	
	    unsigned int key = hashFunction(key1);
            int hash = (key % tableSize);
            if (table[hash] == NULL)
		{
                  return -1;}
            else {
                  LinkedHashEntry *entry = table[hash];
                  while (entry != NULL && entry->getKey() != key1)
                        entry = entry->getNext();
                  if (entry == NULL){
                        return -1;}
                  else	{
			return entry->search(index);
			}
            }
      }
      void put(std::string key1, int value) {
        // se insereaza site-ul cu indexul value 
	// in cadrul intarii cheii key1
	unsigned int key = hashFunction(key1);
	int hash = (key % tableSize);
            if (table[hash] == NULL) {
                  table[hash] = new LinkedHashEntry(key1, value);
                  size++;
            } else {
                  LinkedHashEntry *entry = table[hash];
                  while (entry->getNext() != NULL && entry->getKey() != key1)
                        entry = entry->getNext();
                  if (entry->getKey() == key1){
                        entry->setValue(value);}
                  else {
                        entry->setNext(new LinkedHashEntry(key1, value));
                        size++;
                  }
            }
            if (size >= maxSize)
                  resize();
      }


	int tablesize(){
		return tableSize;
	}
	
	//destructorul
      ~HashMap() {
            for (int hash = 0; hash < tableSize; hash++)
                  if (table[hash] != NULL) {
                        LinkedHashEntry *prevEntry = NULL;
                        LinkedHashEntry *entry = table[hash];
                        while (entry != NULL) {
                             prevEntry = entry;
                             entry = entry->getNext();
                             delete prevEntry;
                        }
                  }
            delete[] table;
      }
};
