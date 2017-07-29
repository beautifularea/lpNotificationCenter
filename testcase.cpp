//
//  main.cpp
//  lpNotificationCenter
//
//  Created by zhTian on 2017/7/28.
//  Copyright © 2017年 zhTian. All rights reserved.
//

#include <iostream>
#include "lpNotificationCenter.h"

class Data : public Notification::lpObject {
public:
    int value;
};

void test(Notification::lpObject *object) {
    printf("test\n");
    
    Data *d = (Data *)object;
    printf("value = %d\n", d->value);
}

int main(int argc, const char * argv[]) {
    
    Data *data = new Data();
    data->value = 3;
    
    Notification::lpNotificationCenter *ins = Notification::lpNotificationCenter::defaultCenter();
    
    ins->addObserver(std::string("data"), test, data);
    ins->postNotification(std::string("data"));
    
    
    return 0;
}
