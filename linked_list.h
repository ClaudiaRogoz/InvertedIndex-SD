#include <stdio.h>
#include <stdlib.h>
#include<iostream>

template<typename T> struct list_elem {
    int info;
    T site;
    struct list_elem<T> *next, *prev;
};

template <typename T> class LinkedList {
    public:
        struct list_elem<T> *pfirst, *plast;
	int nr; 
        
	int addFirst(T x) {
            struct list_elem<T> *paux;
	    if (findFirstOccurrence(x) == NULL){
            paux = new struct list_elem<T>;
	    paux->site = x;
            paux->prev = NULL;
            paux->next = pfirst;
	    paux->info = nr; 
	    nr++;
	    
            if (pfirst != NULL) pfirst->prev = paux;
            pfirst = paux;
			   
            if (plast==NULL) plast=pfirst;
		return nr-1;
	}
	else 
		{
		return search_string(x);		      
		}
	}	
	T search(int inf){
		int ok = 0;
		struct list_elem<T> *paux;
		paux = pfirst;
		while (paux != NULL && ok == 0)
			{
			if (paux->info == inf)
				ok = 1;
			else paux = paux->next;
			}
		return paux->site;

	}
	
	int search_string(T x){
	int ok = 0;
	struct list_elem<T> *paux;
	paux = pfirst;
	while (paux != NULL && ok == 0)
		{
		if (paux->site == x){
			ok = 1;}
		else {paux = paux->next;}
		}
	return paux->info;
	}

	void print(){
	struct list_elem<T> *paux;
	paux = pfirst;
	while (paux != NULL)
		{
		std::cout<<"\n"<<paux->info<<"-"<<paux->site;
		paux = paux->next;
		}

	}

        struct list_elem<T>* findFirstOccurrence(T x) {
            struct list_elem<T> *paux;

            paux = pfirst;
            while (paux != NULL) {
                if (paux->site == x)
                    return paux;
                paux = paux->next;
            }
            return NULL;
        }

        int isEmpty() {
            return (pfirst == NULL);
        }

    LinkedList() {
        pfirst = plast = NULL;
	nr = 0;    
	}

    ~LinkedList(){
	struct list_elem<T> *paux = pfirst;
	struct list_elem<T> *temp;	
	while (paux)
		{
		temp = paux->next;
		delete paux;
		paux = temp;
		}
	nr = 0;
	}
	
};
