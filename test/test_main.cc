#include "../client/api/client.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    cout << "Test Rail Ticket System" << endl;
    rail_ticket::Client cli;

    cli.login("admin", "admin");

    string trip = "G8924";
    vector<string> stationList = {"秦皇岛", "北戴河", "滦河",
                                  "唐山",   "天津西", "北京南"};

    int CASE_NUM = 6 * 5 * 6; // 6 carriage * 5 seat * 6 station
    for(int i = 0 ; i < CASE_NUM ; i++){
        int startPos = rand() % 5;
        int endPos = rand() % (5-startPos) + startPos + 1;
        cli.buyTicket(trip, stationList[startPos], stationList[endPos], 2);
        cout << startPos << " " << endPos << endl;
    }

    auto res = cli.sum();
    cout << "Total: " << res.second["data"].asFloat() << endl;
        
    return 0;
}
