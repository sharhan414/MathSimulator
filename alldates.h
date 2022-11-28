#ifndef ALLDATES_H
#define ALLDATES_H
#include <QString>

class AllDates
{
public:
    AllDates(int n1,int n2,int an,char ar);

    bool readAnswers(int val);
    bool is_error();
    void setError(bool a);
    int getNum_1();
    int getNum_2();
    int getAnswer();
    QString getSign();

    QString if_IsError();
    private:
    QString ErrorPromptMultip();
    QString ErrorPromptDel();

    int answers;
    int num_1,num_2;
    char arif_sign;
    bool error;

};

#endif // ALLDATES_H
