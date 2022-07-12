#include <iostream>
#include <map>
#include <string>

using namespace std;

void print_map(map<string, int> m)
{
    map<string, int>::iterator iter;

    for( iter = m.begin(); iter != m.end(); iter++) {
        cout << iter->first << ": " << iter->second << '\n';
    }
}

int main() {
    map<string, int> m;

    cout << "** First Step **\n";
    m.insert(make_pair("Global", 10));
    m.insert(make_pair("Handong", 30));
    m.insert(make_pair("CSEE", 20));
    m.insert(make_pair("MCNL", 15));
    print_map(m);

    cout << "\n** Second Step **\n";
    m["Pohang"] = 50;
    m["Korea"] = 60;
    print_map(m);

    cout << "\n** Third Step **\n";
    m["CSEE"] = 100;
    m.erase("Global");
    print_map(m);

    cout << "\n** Fourth Step **\n";
    string key = "MCNL";
    if (m.find(key) != m.end()) {
        cout << key << " Exists! \n"; 
    } else {
        cout << key << " does not exist! \n";
    }

    cout << "\n** Fifth Step **\n";
    key = "Yunmin";
    if (m.find(key) != m.end()) {
        cout << key << " Exists! \n"; 
    } else {
        cout << key << " does not exist! \n";
    }
    
    return 0;
}