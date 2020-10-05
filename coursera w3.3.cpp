#include <iostream>
#include <vector>
using namespace std;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> stops) {
    // write your code here
    int prev=0;
    int k=tank,p=0,i;
    int q=stops.size()+1;
    stops[q]=dist;
    for(i=0;i<q-1;i++)
    {
        if(tank<stops[i+1]-stops[i])
        {
            return -1;
        }
    }
    for(int j=0;j<q+1;j++)
        {

            if(tank<(stops[j]-prev)&&(stops[q]-prev)>=tank)
            {
                prev=stops[j-1];
                p=p+1;
            }
            else if(tank==(stops[j]-prev)&&(stops[q]-prev)>=tank)
            {
                prev=stops[j];
                p=p+1;
            }
            if(j!=0)
            {
                dist=dist-(stops[j]-stops[j-1]);
            }
            else
            {
                dist=dist-stops[j];
            }
        }
    return p;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}

