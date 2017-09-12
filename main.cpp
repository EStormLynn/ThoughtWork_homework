#include <iostream>

#include <string>
#include "TWType.h"
#include "TWIO.h"
#include "TWOrderManager.h"

using namespace std;



int main() {
    string str;

    TWOrderManager *orderManager=new TWOrderManager();
    TWIO *io=new TWIO();
    while(getline(cin,str))
    {
        if(str=="")
            io->IncomeSummary(*orderManager);
        else
        {
            Order order;
            if(!io->parseUserInput(str,&order))
                cout<<"> Error: the booking is invalid!"<<endl;
            else
            {
                order.calPrice();

                if(order.isCancel)
                {
                    if(orderManager->cancelOrder(order))
                        cout<<"> Success: the booking is accepted!"<<endl;
                    else{
                        cout<<"> Error: the booking being cancelled does not exist!"<<endl;
                    }

                }
                else
                {
                    if(orderManager->addOrder(order))
                        cout<<"> Success: the booking is accepted!"<<endl;
                    else
                        cout<<"> Error: the booking conflicts with existing bookings!"<<endl;
                }
            }

        }

    }


    std::cout << "Hello, World!" << std::endl;
    return 0;
}

//user1 2017-11-12 14:00~15:00 A