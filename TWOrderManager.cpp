//
// Created by SeeKHit on 09/09/2017.
//

#include <mach/task.h>
#include "TWOrderManager.h"

bool TWOrderManager::addOrder(Order &singleOrder)
{
    int siteNum=singleOrder.site_s[0]-'A';

    //时间冲突
    if(isTimeConflict(singleOrder))
        return false;

    siteManager[siteNum].orderMap[singleOrder.data.date_str].push_back(singleOrder);
    siteManager[siteNum].siteIncome+=singleOrder.orderPrice;

    return true;

}

bool TWOrderManager::isTimeConflict(Order &singleOrder)
{
    int siteNum=singleOrder.site_s[0]-'A';
    for(int i=singleOrder.data.starhour;i<singleOrder.data.endhour;i++)
    {
        if(siteManager[siteNum].timeManager[singleOrder.data.date_str][i]==1)
            return true;
    }

    //时间不冲突
    for(int i=singleOrder.data.starhour;i<singleOrder.data.endhour;i++)
        siteManager[siteNum].timeManager[singleOrder.data.date_str][i]=1;
    return false;

}

bool TWOrderManager::cancelOrder(Order &singleOrder)
{
    singleOrder.isCancel=true;

    int siteNum=singleOrder.site_s[0]-'A';

    //订单存在
    string orderDataStr=singleOrder.data.date_str;
    bool orderExist=false;
    for(auto &orderItem : siteManager[siteNum].orderMap[orderDataStr])
    {
        //时间用户满足,原订单未被取消
        if(orderItem==singleOrder && orderItem.isCancel==false)
        {
            orderExist=true;
            orderItem.isCancel=true;

            if(singleOrder.data.isWorkingDay)
            {
                singleOrder.orderPrice/=2;
            } else
            {
                singleOrder.orderPrice/=4;
            }

            orderItem.orderPrice=singleOrder.orderPrice;

            siteManager[siteNum].siteIncome-=singleOrder.orderPrice;
        }
    }
    if(!orderExist)
        return false;


    for(int i=singleOrder.data.starhour;i<singleOrder.data.endhour;i++)
        siteManager[siteNum].timeManager[singleOrder.data.date_str][i]=0;

    return true;

}
