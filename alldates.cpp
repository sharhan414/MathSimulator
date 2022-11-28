#include "alldates.h"

AllDates::AllDates(int n1, int n2, int an, char ar)
{
    num_1=n1;
    num_2=n2;
    answers=an;
    arif_sign=ar;
    error=true;
}

bool AllDates::readAnswers(int val)
{
    if(val==getAnswer())
    {
        error=false;
        return true;
    }
    else
    {
        error=true;
        return false;
    }
}
bool AllDates::is_error()
{
    return error;
}

void AllDates::setError(bool a)
{
    error=a;
}

int AllDates::getNum_1()
{
    return num_1;
}

int AllDates::getNum_2()
{
    return num_2;
}

int AllDates::getAnswer()
{
    return answers;
}

QString AllDates::getSign()
{
    if(arif_sign=='*')
    {
        return "×";
    }
    else if(arif_sign=='/')
    {
        return  "÷";
    }
}

QString AllDates::if_IsError()
{
    if(!is_error())
    {
        return "";
    }
    if(arif_sign=='*')
    {
        return ErrorPromptMultip();
    }
    else if(arif_sign=='/')
    {
        return  ErrorPromptDel();
    }
}

QString AllDates::ErrorPromptMultip()
{
    QString text="<br><font face=\"Comic Sans MS, Tahoma, Arial\" color=\"red\" size=\"5\"> <strong><center>Ответ неверный</center></strong></font></br>"
            "<font face=\"Comic Sans MS, Tahoma, Arial\" color=\"black\" size=\"4\"> <strong><br><center>Представим произведение в</center></br>"
            "<center>виде суммы:</center>";
    text+="<center>";
    for(int i=0;i<num_1;++i)
    {
        if(i==0)
        {
          text+= QString::number(num_2);
        }
        else if(i > 0)
        {
            text+='+'+QString::number(num_2);
        }
    }
    text+='='+QString::number(answers);
    text+="</center>";

    text+="<center>";
    for(int i=0;i<num_2;++i)
    {
        if(i==0)
        {
            text+= QString::number(num_1);
        }
        else if(i > 0)
        {
            text+='+'+QString::number(num_1);
        }
    }

    text+='='+QString::number(answers);
    text+="</center></strong></font><br></br>";

    return text;
}

QString AllDates::ErrorPromptDel()
{
    QString text="<br><font face=\"Comic Sans MS, Tahoma, Arial\" color=\"red\" size=\"5\"> <strong><center>Ответ неверный</center></strong></font></br>"
            "<font face=\"Comic Sans MS, Tahoma, Arial\" color=\"black\" size=\"4\"> <strong><br><center>Представим делимое в </center> "
            "<center>виде суммы:</center>";
    text+="<center>";
    text+='(';
    QString text_1,text_2;
    for(int i=0;i<num_2;++i)
    {
        if(i==0)
        {
            text+= QString::number(answers);
        }
        else if(i > 0)
        {
            text+='+'+QString::number(answers);
        }
   }
    text+=')';
    text+=QChar(L'÷')+QString::number(num_2);
    text+=QChar(L'=')+QString::number(answers);
    text+="</center>";

    text+="<center>";
    text+='(';
    for(int i=0;i<answers;++i)
    {
        if(i==0)
        {
        text+= QString::number(num_2);
        }
        else if(i > 0)
        {
            text+='+'+QString::number(num_2);
        }
    }
    text+=')';
    text+=QChar(L'÷')+QString::number(num_2);
    text+=QChar(L'=')+QString::number(answers);

    text+="</center></strong></font><br></br>";

    return text;
}
