//
// Created by SeeKHit on 11/09/2017.
//

#ifndef THOUGHTWORK_HOMEWORK_TWIO_H
#define THOUGHTWORK_HOMEWORK_TWIO_H

#include "TWType.h"
#include "TWOrderManager.h"

class TWIO {
public:
    void IncomeSummary(TWOrderManager &orderManager);

    bool parseUserInput(string userInput,Order *order);

};


#endif //THOUGHTWORK_HOMEWORK_TWIO_H
