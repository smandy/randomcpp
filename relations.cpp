using namespace std;

#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

int find_network_endpoint( int startNodeId, vector<int> fromIds, vector<int> toIds) {

    unordered_map<int,int> relations;
    for (int i = 0; i < fromIds.size();i++) {
        cout << "Inserting " << fromIds[i] << " -> " << toIds[i] << endl;
        relations[ fromIds[i] ] = toIds[i];
    };

    cout << "Have " << relations.size() << " relations\n";

    for_each( begin(relations), end(relations), [=](auto &x ) {
        cout << " x is " << x.first << " = " << x.second << endl;
    });

    int current = startNodeId;
    while(true) {
        cout << "Current is " << current << endl;
        auto it = relations.find(current);
        //        cout << " it is " << it->first << " second is " << it->second << endl;
        if ( it  == relations.end() ) {
            cout << "Breaking at " << current << endl;
                return current;
        } else {
            cout << "setting current to " << relations[it->first] << endl;
            current = relations[it->first];
        }
    }
    
};

int main() {
    //unordered_map<int,int> relations;
    
    auto froms = vector<int> { 1,7,3,4,2,6,9};
    auto tos = vector<int> { 3,3,4,6,6,9,5 };

    cout << find_network_endpoint(1, froms, tos) << endl;

    cout << "Woot" << endl;

    for_each( froms.cbegin(), froms.cend(), [&](auto x) {
        cout << x << endl;
    });
}
