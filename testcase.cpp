//
//  main.cpp
//  lpNotificationCenter
//
//  Created by zhTian on 2017/7/28.
//  Copyright © 2017年 zhTian. All rights reserved.
//

#include <iostream>
#include "lpNotificationCenter.h"

void test(void) {
    printf("test\n");
}


int main(int argc, const char * argv[]) {
    
    Notification::lpNotificationCenter *ins = Notification::lpNotificationCenter::defaultCenter();
    ins->addObserver(std::string("test"), test);
    ins->addObserver(std::string("print"), [](){ printf("this is print.\n"); });
    ins->postNotification("print");
    
    ins->removeObserver(std::string("print"));
    ins->postNotification();    
    
    
    return 0;
}
