#include "memory"

FREE freeList;
ALLOC allocList;

const int TIME_LIMIT = 1000;
const int REQUEST = 20;
int main() {
  srand(0);
  freeNode p = {{0,1000}};
  freeList.push(p);
  for ( int time = 0 ; time  < TIME_LIMIT ; time++) {
  //
  // check if it's time to generate an allocation request
  //
  //		 cout << "Time -> " << time << endl;
         if ( 0 == time  % REQUEST) {
            int size = rand() % 100;
            int lease = rand() % 10;
            cout << "     " << size  << " " << lease << "  " << time + lease << endl;
            if (freeList.top().hole.size > size ) {
                          freeNode p = {{freeList.top().hole.start+size, freeList.top().hole.size-size}};
                          allocNode q = {{freeList.top().hole.start,size},time + lease};
                          freeList.pop();
                          freeList.push(p);
                          allocList.push(q);
                          cout << "request granted\n";
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
