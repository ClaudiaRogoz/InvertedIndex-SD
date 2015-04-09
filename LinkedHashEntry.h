#include<string.h>

#define LMAX 1050

class LinkedHashEntry {

private:
	std::string key;
	/* se construieste un vector de char-uri 
	care sa contina 1 sau 0*/
	//unsigned value[LMAX];
	//LinkedHashEntry *next;

public:
	LinkedHashEntry *next;	
	unsigned value[LMAX];
	int k;
      LinkedHashEntry(std::string key, int  val) {
            //int i;
	    this->key = key;
            this->next = NULL;
	   /*se initializeaza vectorul value*/
	    for (int i = 0; i< LMAX; i++)
	   	 this->value[i] = 0;
	    if (val < LMAX)
	    	this->value[val] = 1;
 
      }
 	
	/* se returneaza key = keyword-ul*/ 
      std::string getKey() {
            return key;
      }
	// returneaza numarul de indecsi 
	// pentru care value[i] ==1
      int getNoValues(){

	int nr = 0;
	for (int i = 0; i< LMAX;i++)
		if (value[i] != 0)
			nr++;
	return nr;

	}
 
	void setK(){
	k = -1;
	}

	// se returneaza pe rand indecsii "i"
	// pentru care value[i] == 1
      int getValue() {
		while(k< LMAX){
			k++;
			if (value[k] != 0){
				return k;
				}
			}
		return k;
           		
      }
	int getValueI(int i){
		return value[i];
	}

	int search(int v){
		// se verifica daca value[v] ==1
		if (v < LMAX){
		if (value[v] != 0)
			return 1;
		else return -1;}
		return -1;
	} 
      void setValue(int val) {
	//printf("\nvalue: %d\n", val);
	if (val < LMAX )
            value[val] = 1;
		/*for (int i = 0; i< LMAX; i++)
			std::cout<<" "<<value[i;*/
      }
 
      LinkedHashEntry *getNext() {
            return next;
      }
 
      void setNext(LinkedHashEntry *next) {
            this->next = next;
      }

};
