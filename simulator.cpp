#include "simulator.h"
#include <iostream>
#include <random>
#include <QString>
#include <QDebug>
#include <QRandomGenerator>

Simulator::Simulator(vector<char> airf, vector<int> m, int val)
{
    arif_dest=airf;
    multipliers=m;

    for(int i=0;i<val;++i)
    {
        GeneratMultip();
    }
}

void Simulator::GeneratMultip()
{
    int num_1,num_2;
    int k=rand()%multipliers.size();
    num_1=multipliers[k];
    num_2=rand()%(8)+2;

    if(rand()%2==1)
    {
        int r=num_1;
        num_1=num_2;
        num_2=r;
    }

    int it_arif=rand()%arif_dest.size();
    char arif_d=arif_dest[it_arif];
    int an=0;
    getAnswer(num_1,num_2,an,arif_d);

    AllDates dt(num_1,num_2,an,arif_d);
    dates.push_back(dt);
}

void Simulator::getAnswer(int &n1, int &n2, int &an, char c)
{
    switch (c)
    {
        case '*':
            an=n1*n2;
        break;

        case '/':
            int x=n1*n2;
            an=n1;
            n1=x;
        break;

    }
}
