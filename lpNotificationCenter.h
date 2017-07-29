/*
 类似 Cocoa中的NSNotificationCenter
 */

#ifndef __LPNOTIFICATIONCENTER_H_
#define __LPNOTIFICATIONCENTER_H_

#include <iostream>
#include <functional>
#include <list>
#include <unordered_map>

namespace Notification {
    class lpNotificationCenter {
    public:
        static lpNotificationCenter *defaultCenter() {
            static lpNotificationCenter *_instance = new lpNotificationCenter();
            return _instance;
        }
        
    private:
        lpNotificationCenter(){}
        ~lpNotificationCenter(){}
        
    public:
        lpNotificationCenter(const lpNotificationCenter&) = delete;
        void operator=(const lpNotificationCenter&) = delete;
        
    public:
        
        void addObserver(std::string name, std::function<void(void)> &&f) {
            std::pair<std::string, std::function<void(void)>> p = std::make_pair(name, f);
            _map.insert(p);
        }
        void addObserver(std::string name, std::function<void(void)> &&f, void *data) {
            
        }
        void removeAllObservers() {
            for(auto it = _map.begin(); it != _map.end(); ++it) {
                _map.erase(it);
            }
        }
        void removeObserver(std::string name) {
            std::unordered_map<std::string, std::function<void(void)>>::iterator it = _map.find(name);
            if(it != std::end(_map)) {
                _map.erase(it);
            }
        }
        
        //post notifications
        void postNotification() {
            for(auto it = _map.begin(); it != _map.end(); ++it) {
                std::function<void(void)> f = it->second;
                f();
            }
        }
        void postNotification(std::string name) {
            std::unordered_map<std::string, std::function<void(void)>>::iterator it = _map.find(name);
            if(it != std::end(_map)) {
                std::function<void(void)> f = it->second;
                f();
            }
        }
        
    private:
        std::unordered_map<std::string, std::function<void(void)>> _map;
    };
}

#endif
