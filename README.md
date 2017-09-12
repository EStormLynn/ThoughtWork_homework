# ThoughtWork代码作业  :  羽毛球馆

## 开发环境
* 系统：MAC OS
* 编程语言：C++ 11
* IDE：Clion
* CMake Version 3.6

## 文件结构
```
tree -f
.
├── CMakeLists.txt
├── TWIO.cpp    
├── TWIO.h                  # IO模块
├── TWOrderManager.cpp      
├── TWOrderManager.h        # 订单管理
├── TWType.h                # 数据类型包含Date，Order
├── cmake-build-debug
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   ├── Makefile
│   ├── ThoughtWork_homework
│   ├── ThoughtWork_homework.cbp
│   └── cmake_install.cmake
└── main.cpp
```

## 程序流程

<div align=center><img src="http://oo8jzybo8.bkt.clouddn.com/TW%E7%A8%8B%E5%BA%8F%E6%B5%81%E7%A8%8B.png" width="350" height="650" alt="程序界面"/></div>

## 程序说明
* 1.合法性检测
输入须要为
```
{用户ID} {预订日期 yyyy-MM-dd} {预订时间段 HH:mm~HH:mm} {场地} {是否取消（可为缺省项）}
```
且年月日，时段满足时间要求
```C++
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
```

* 2.工作日检测
使用基姆拉尔森计算公式，计算当前日期周几
```
W= (d+2m+3(m+1)/5+y+y/4-y/100+y/400+1)%7
```

* 3.订单数据结构
```C++
class Order{
    std::string userName;
    std::string site_s;

    Data data;
    bool isCancel=false;
    double orderPrice=0;

    int weekdayPrice[4]={30,50,80,60};
    int weekendPrice[3]={40,50,60};

    //重载==
    bool operator==(Order order);
    bool isRightOrder(Data &data,std::string site)
}
```

* 4.场馆管理数据结构
```C++
struct Site
{
    double siteIncome=0;
    //key 日期， value 订单，方便查询冲突
    std::map<std::string,std::vector<Order>> orderMap;  
    //维护当日，被占用的时间 用bitset，节约空间
    std::map<std::string,std::bitset<24>> timeManager;
};
```
* 5.订单管理
```c++
class TWOrderManager {
public:
    Site siteManager[SITECNT];   //ABCD四个场馆
    bool addOrder(Order &singleOrder);
    bool cancelOrder(Order &singleOrder);

private:
    bool isTimeConflict(Order &singleOrder);//时间段是否冲突
};
```

## 测试用例结果
* 测试用例一
<div align=center><img src="http://oo8jzybo8.bkt.clouddn.com/Screen%20Shot%202017-09-11%20at%208.08.34%20PM.png" width="350" height="650" alt="程序界面"/></div>



* 测试用例二
<div align=center><img src="http://oo8jzybo8.bkt.clouddn.com/Screen%20Shot%202017-09-11%20at%208.09.31%20PM.png" width="350" height="650" alt="程序界面"/></div>

