#define NMAX 100
#ifndef _STACK
#define _STACK

class Stack {
    private:
        int stackArray[NMAX];
        int WEIGHT;
	int LEVEL;
	int total;
	int topLevel;
    public:
        int push(int index, int weight) {
	// se verifica daca stiva terbuie golita
	//daca ar depasi numarul  de nivele disponibile
	//daca ar depasi greutatea disponibila
	if ((topLevel >= LEVEL- 1) || ((total+ weight) >WEIGHT)) {
		                
		topLevel=-1;
		total=0;
		}
	topLevel++;
        stackArray[topLevel] = weight;
	total = total + weight;
	return 0;
        }

        int pop() {
	    if (isEmpty()) {
                int x;
                return x;
            }
            int x = stackArray[topLevel];
            topLevel--;
            return x;
        }
	int peek() {
            if (isEmpty()) {
                int x;
                return x;
            }
            return stackArray[topLevel]; }

        int isEmpty() {
            return (topLevel < 0); }

	Stack() { 
	        topLevel = -1; 
		total=0;
	}
	int count(){
	return (topLevel+1);
	}
	~Stack(){ 
	}
	int print(){
	// se afiseaza stiva 
	int i,ok=0;
	for (i=topLevel;i>=0;i--){ok=1;
		std::cout<<" "<<stackArray[i];
		if (i!=0)
			std::cout<<","; 
		}
	return ok;
	}
	
	void deletes(){
	//se elibereaza stiva de toate pachetele 
	topLevel = -1;
	total = 0;
	}
	
	void setLEVEL(int l){
	//se seteaza numarul de pachete admise
	LEVEL=l;
	}
	
	void setWEIGHT(int w){
	//se seteaza greutatea totala care e admisa
	WEIGHT=w;
	}
 
};
#endif
