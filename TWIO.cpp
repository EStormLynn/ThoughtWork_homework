//
// Created by SeeKHit on 11/09/2017.
//
#include <iostream>
#include <iomanip>
#include "TWIO.h"

using std::cout;
using std::endl;

void TWIO::IncomeSummary(TWOrderManager &orderManager){

    double sumIncome=0.0;
    cout<<"> 收入汇总"<<endl;
    cout<<"> ---"<<endl;

    //场馆
    for(int siteID=0;siteID<SITECNT;siteID++)
    {
        double siteIncome=0.0;
        char ID='A'+siteID;
        cout<<"> 场地:"<<ID<<endl;

        //场馆订单
        for(auto orderID:orderManager.siteManager[siteID].orderMap)
        {
            //日期订单
            for(auto dayOrderID=0;dayOrderID<orderID.second.size();dayOrderID++)
            {
                string singleOrderStr="> ";
                singleOrderStr+=orderID.first+" ";
                if(orderID.second[dayOrderID].data.starhour==9)
                    singleOrderStr+="0";
                singleOrderStr+=std::to_string(orderID.second[dayOrderID].data.starhour)+":"
                        +std::to_string(orderID.second[dayOrderID].data.starmin)+"0~"
                        +std::to_string(orderID.second[dayOrderID].data.endhour)+":0"
                        +std::to_string(orderID.second[dayOrderID].data.endmin)+" ";

                if(orderID.second[dayOrderID].isCancel)
                    singleOrderStr+="违约金 ";

                cout<<singleOrderStr;
                cout<<std::fixed<<std::setprecision(2)<<orderID.second[dayOrderID].orderPrice;
                cout<<"元"<<endl;
            }
        }
        sumIncome+=orderManager.siteManager[siteID].siteIncome;
        cout<<"> 小计"<<orderManager.siteManager[siteID].siteIncome<<"元"<<endl;

        cout<<endl;
    }
    cout<<"> ---"<<endl;
    cout<<"总计:"<<sumIncome<<"元"<<endl;

    //cout<<"income Summary"<<endl;
}

bool TWIO::parseUserInput(string userInput, Order *order)
{
    string username="";
    Data data;
    string site;

    for(int i=0;i<userInput.length();i++)
    {
        string temp;
        while(i<userInput.length() && userInput[i]!=' ')
        {
            temp+=userInput[i];
            i++;
        }

        username=temp;

        int t=4;
        i++;
        temp="";
        while(i<userInput.length()&&t--)
        {
            temp+=userInput[i];
            i++;
        }
        data.year=atoi(temp.c_str());

        t=2;
        i++;
        temp="";
        while(i<userInput.length()&&t--)
        {
            temp+=userInput[i];
            i++;
        }
        data.month=atoi(temp.c_str());

        t=2;
        i++;
        temp="";
        while(i<userInput.length()&&t--)
        {
            temp+=userInput[i];
            i++;
        }
        data.day=atoi(temp.c_str());

        t=2;  i++;  temp="";
        while(i<userInput.length()&&t--)
        {
            temp+=userInput[i];
            i++;
        }
        data.starhour=atoi(temp.c_str());

        t=2;  i++;  temp="";
        while(i<userInput.length()&&t--)
        {
            temp+=userInput[i];
            i++;
        }
        data.starmin=atoi(temp.c_str());

        t=2;  i++;  temp="";
        while(i<userInput.length()&&t--)
        {
            temp+=userInput[i];
            i++;
        }
        data.endhour=atoi(temp.c_str());

        t=2;  i++;  temp="";
        while(i<userInput.length()&&t--)
        {
            temp+=userInput[i];
            i++;
        }
        data.endmin=atoi(temp.c_str());

        i++;
        if(i<userInput.length())
            site=userInput[i];

        i+=2;
        if(i<userInput.length()&&userInput[i]=='C')
            order->isCancel= true;
        data.CaculateWeekDay(data.year,data.month,data.day);

        order->data=data;
        order->site_s=site;

        if(order->isRightOrder(data,site))
            return true;
        else
            return false;

    }

}