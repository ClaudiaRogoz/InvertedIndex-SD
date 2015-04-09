#ifndef COUNT
#define COUNT

#include "queue.h"
#include "stack.h"

class Counter {
	private:
		
		int MAX_weight;
		int MIN_weight;
		int open;	
		Stack S;
	public:
		Queue Q;
		Queue Move;
		void OPEN_WINDOW(int wm, int wM,int Q,int K);
		void ADD_PERSON(int id, int w);
		int PROCESS(int n);
		int PRINT_STACKS();
		int FLUSH_STACKS();
		int PRINT_QUEUES();
		int isOpen();
		int getsizeQ();
		Counter();
		~Counter(){};			
};

int Counter::getsizeQ(){
return Q.sizeQ();
}

Counter::Counter(){
open=0;
}

int Counter::isOpen(){
return (open==1);
}

void Counter::OPEN_WINDOW( int wm, int wM, int q, int K ){
	//se deschide un nou ghiseu
	// se seteaza informatiile necesare ghiseului
	open = 1;
	MAX_weight = wM;
	MIN_weight = wm;
	S.setLEVEL(q);
	S.setWEIGHT(K); 
}

void Counter::ADD_PERSON( int id, int w ){
	//se adauga in cadrul cozii o noua persoana
	Q.enqueue(id,w);
}

int Counter::PRINT_QUEUES(){
	//se afiseaza persoanele care stau la coada
	return Q.print();
}

int Counter::PRINT_STACKS(){
	//se afiseaza coletele din cadrul stivei
	return S.print();
}

int Counter::FLUSH_STACKS(){
	//se elibereaza stiva de colete
	int ok;	
	ok = S.print();
	S.deletes();
	return ok;
}

int Counter::PROCESS(int n){
	//se proceseaza n persoane
	int i,index, gr,ok=0;
	for (i=0; i<n ;i++){
		//se retin detaliile persoanei la rand
		index = Q.peek_index();
		gr = Q.peek_grams();
		// se verifica daca pachetul se afla in limitele
		//greutatii acceptate de ghiseul curennt
		if ( (gr >= MIN_weight) && (gr <=MAX_weight) )
			{
			S.push(index, gr);
			}
		else {
			//in cazul in care nu e acceptata
			//persoana e trcuta in lista Move
			Move.enqueue(index,gr);
			ok=1;
		} 
	Q.dequeue();
	}
	if (ok==1)
		return -1;
	else return 0;
};
#endif
