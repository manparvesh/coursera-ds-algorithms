#include <iostream>
using namespace std;
int get_change(int m) {
    int j=0,n=0;
            if(m>=10)
            {
                j=m/10;
                m=m%10;
                n=n+j;
            }
            if(m>=5&&m<10)
            {
                j=m/5;
                m=m%5;
                n=n+j;
            }
            if(m>=1&&m<5)
            {
                j=m;
                m=0;
                n=n+j;
            }
  return n;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
  return 0;
}

