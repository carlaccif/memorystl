#include "memory"

FREE freeList;
ALLOC allocList;

const int TIME_LIMIT = 100;
const int REQUEST = 10;
const int MIN_LEASE = 10;
const int MAX_LEASE = 20;
const int MIN_ALLOC = 100;
const int MAX_ALLOC = 200;

int main() {

  srand(0);
  
  FREE tmp;
  freeNode p = {{0,1000}};
  freeList.push(p);
  
  for ( int time = 0 ; time  < TIME_LIMIT ; time++) {
  //
  // check if it's time to generate an allocation request
  //
  //		 cout << "Time -> " << time << endl;
         if ( 0 == time  % REQUEST) {
         
            int size = MIN_ALLOC + rand() % MAX_ALLOC;
            int lease = MIN_LEASE + rand() % MAX_LEASE;
            
            cout << "Time -> " << time <<  "     " << size  << " " << lease << "  " << time + lease << endl;
  //
  //  search freeList for a right-sized hole move non-candidates to a tmp queue
  //          
            while (!freeList.empty() && freeList.top().hole.size < size ) {
                 tmp.push(freeList.top());
                 freeList.pop();
            }
            
            if (freeList.empty() ) {
                cout << "request denied\n";
                freeList = tmp;
             } 
             else
             {
			  freeNode p = {{freeList.top().hole.start+size, freeList.top().hole.size-size}};
			  allocNode q = {{freeList.top().hole.start,size},time + lease};
			  freeList.pop();
			  freeList.push(p);
			  allocList.push(q);
			  cout << "request granted\n";
	//
	// some elements in tmp queue must be re-inserted into freeList
	//
			  while (!tmp.empty()) {
			        freeList.push(tmp.top());
			        tmp.pop();
			  }
            }
         }
   //
   //  check to see if a lease has expired
   //

         while ( !allocList.empty() && allocList.top().leaseExpiry == time) {
             cout << time << "**\n";
             freeNode p = {allocList.top().allocated.start,  allocList.top().allocated.size};  
             freeList.push(p);
             allocList.pop();
         }
              
  }
  cout << "----------------------FREELISTS----------------------\n";
  while (!freeList.empty()) {
       cout << freeList.top().hole.start << "   " 
            << freeList.top().hole.size <<endl;
       freeList.pop();
  }
  cout << "----------------------ALLOCLISTS----------------------\n";
  while (!allocList.empty()) {
       cout << allocList.top().leaseExpiry << "   "  
            << allocList.top().allocated.start << "   "  
            << allocList.top().allocated.size  << endl;
       allocList.pop();
  }
  return 0;
}
