//
// Created by SeeKHit on 09/09/2017.
//

#ifndef THOUGHTWORK_HOMEWORK_TWORDERMANAGER_H
#define THOUGHTWORK_HOMEWORK_TWORDERMANAGER_H

#include "TWType.h"
#include <vector>
#include <string>
#include <bitset>
#include <map>
#define SITECNT 4

struct Site
{
    double siteIncome=0;
    std::map<std::string,std::vector<Order>> orderMap;   //key 日期， value 订单

    std::map<std::string,std::bitset<24>> timeManager;
};

class TWOrderManager {

public:
    Site siteManager[SITECNT];   //ABCD四个场馆
    bool addOrder(Order &singleOrder);
    bool cancelOrder(Order &singleOrder);

private:
    bool isTimeConflict(Order &singleOrder);
};


#endif //THOUGHTWORK_HOMEWORK_TWORDERMANAGER_H
