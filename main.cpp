#include "memory"

FREE freeList;
ALLOC allocList;

int main() {
  srand(0);
  freeNode p = {{0,1000}};
  freeList.push(p);
  for ( int i = 0 ;i < 10; i++) {
         int size = rand() % 100;
         cout << size  <<endl;
//         while!freeList.empty() {
              if (freeList.top().hole.size > size ) {
                          freeNode p = {{freeList.top().hole.start+size, freeList.top().hole.size-size}};
                          allocNode q = {{freeList.top().hole.start,size},size / 10};
                          freeList.pop();
                          freeList.push(p);
                          allocList.push(q);
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
