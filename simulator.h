#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <vector>
#include <string>
#include <QString>
#include "alldates.h"
using namespace std;

class Simulator
{
public:

  Simulator(vector<char> airf,vector<int> m,int val);

    vector<AllDates> getData()
    {
        return dates;
    }
private:

    vector<char> arif_dest;
    vector<int> multipliers;

    vector<AllDates> dates;
    void getAnswer(int& n1,int &n2,int& an,char c);
    void GeneratMultip();

};

#endif // SIMULATOR_H
