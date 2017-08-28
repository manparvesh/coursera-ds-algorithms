#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;


double get_optimal_value(double capacity, vector<double> weights, vector<double> values) {
    double value = 0.0;
    int n = weights.size();

    vector< pair<double, double> > fk;
    for (int i = 0; i < n; i++) {
        fk.push_back(make_pair(values[i] / weights[i], weights[i]));
    }
    sort(fk.begin(), fk.end());

    int i = n - 1;
    double temp_value;
    while (capacity > 0.0 && i >= 0) {
        if (fk[i].second >= capacity) {
            // add fractional quantity
            value += (fk[i].first * capacity);
            capacity = 0.0;
            break;
        } else {
            // add everything
            value += (fk[i].first * fk[i].second);
            capacity -= fk[i].second;
        }
        i--;
    }

    return value;
}

int main() {
    int n;
    double capacity;
    std::cin >> n >> capacity;
    vector<double> values(n);
    vector<double> weights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> values[i] >> weights[i];
    }

    double optimal_value = get_optimal_value(capacity, weights, values);

    std::cout.precision(10);
    std::cout << optimal_value << std::endl;
    return 0;
}
