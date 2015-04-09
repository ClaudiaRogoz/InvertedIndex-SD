#define NMAX 100
#ifndef _QUEUE
#define _QUEUE
class Queue {
    private:
        int queueArray[NMAX];
	int queueWeight[NMAX];
        int head, tail,size;
    public:
        void enqueue(int x, int y) {
            if (tail >= NMAX) {
                return;
            }
            queueArray[tail] = x;
	    queueWeight[tail] = y;
            tail++;
	    size++;
        }

        int dequeue(){
            if (isEmpty()) {
                int x;
                return x;
            }
            int x = queueArray[head];
	    int y = queueWeight[head];
            head++;
	    size--;
            return x;
        }
	int peek_index() {
            if (isEmpty()) {
                int x;
                return x;
            }
            return queueArray[head];
        }
	int peek_grams(){
		if (isEmpty()){
			int x;	
			return x;
			}	
		return queueWeight[head];
	}

        int isEmpty() {
            return (size==0);
        }
	
	int sizeQ(){
	return size;

	}

	    Queue() {
        head = tail = 0; 
	size=0;  
  }
	int print()
	{
	int i,ok=0;
	for(i=head;i<tail;i++){ok=1;
		std::cout<<" ("<<queueArray[i]<<", "<<queueWeight[i]<<")";
		if (i!=tail-1 && i!=tail)
			std::cout<<",";} 
	return ok;	
	}	
};
#endif
