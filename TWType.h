//
// Created by SeeKHit on 09/09/2017.
//

#ifndef THOUGHTWORK_HOMEWORK_TWTYPE_H
#define THOUGHTWORK_HOMEWORK_TWTYPE_H

#include <string>
#include <vector>

using std::string;

struct Data
{
    int year,month,day;
    int starhour,starmin;
    int endhour,endmin;


    std::vector<int> timeLast;

    std::string date_str;

    bool isWorkingDay;

    //重载==
    bool operator==(const Data data)
    {

        return (data.date_str==date_str
                && data.starhour==starhour
                && data.starmin==starmin
                && data.endhour==endhour
                && data.endmin==endmin);
    };



    int CaculateWeekDay(int y, int m, int d)
    {
        if(m==1||m==2) //把一月和二月换算成上一年的十三月和是四月
        {
            m+=12;
            y--;
        }
        int week=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;

        if(week<5)
            isWorkingDay= true;
        else
            isWorkingDay= false;

        date_str=std::to_string(year)+"-"+std::to_string(month)
                             +"-"+std::to_string(day);

        return week;
    }




};

struct Order
{
    std::string userName;
    std::string site_s;

    Data data;
    bool isCancel=false;
    double orderPrice=0;

    int weekdayPrice[4]={30,50,80,60};
    int weekendPrice[3]={40,50,60};


    //重载==
    bool operator==(Order order)
    {

        return (order.data==data && order.userName==userName);
    };
    //判断订单格式合法，场馆合法
    bool isRightOrder(Data &data,std::string site)
    {
        if(data.year>9999)
            return false;
        if(data.month<=0 || data.month>12)
            return false;
        if(data.day>31)
            return false;

        if(data.starhour<9 || data.starhour>=22)
            return false;
        if(data.endhour<=9 || data.endhour>22)
            return false;

        if(data.starhour>=data.endhour)
            return false;

        if(data.starmin!=0||data.endmin!=0)
            return false;

        if(site.length()!=1 || site[0]-'A'<0 || site[0]-'A'>4)
            return false;

        return true;
    }

    int calPrice()
    {
        if(data.isWorkingDay)
        {
            for(int time=data.starhour;time<data.endhour;time++)
            {
                data.timeLast.push_back(time);
                if(time<12)
                    orderPrice+=weekdayPrice[0];
                else if(time<18)
                    orderPrice+=weekdayPrice[1];
                else if(time<20)
                    orderPrice+=weekdayPrice[2];
                else if(time<22)
                    orderPrice+=weekdayPrice[3];
            }
        } else
        {
            for(int time=data.starhour;time<data.endhour;time++)
            {
                data.timeLast.push_back(time);
                if(time<12)
                    orderPrice+=weekendPrice[0];
                else if(time<18)
                    orderPrice+=weekendPrice[1];
                else if(time<22)
                    orderPrice+=weekendPrice[2];
            }

        }
        return orderPrice;
    }

};

#endif //THOUGHTWORK_HOMEWORK_TWTYPE_H
