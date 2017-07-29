/*
 类似 Cocoa中的NSNotificationCenter
 */

#ifndef __LPNOTIFICATIONCENTER_H_
#define __LPNOTIFICATIONCENTER_H_

#include <iostream>
#include <functional>
#include <list>
#include <unordered_map>

typedef std::unordered_map<std::string, std::function<void(void)>> notification_map_type;
typedef std::unordered_map<std::string, std::function<void(void)>>::const_iterator notification_itr_const;

typedef std::function<void(void)> func_type;

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
        //add notifications
        void addObserver(std::string name, func_type &&f) {
            std::pair<std::string, func_type> p = std::make_pair(name, f);
            _map.insert(p);
        }
        void addObserver(std::string name, func_type &&f, void *data) {
            
        }
        void removeAllObservers() {
            for(auto it = _map.begin(); it != _map.end(); ++it) {
                _map.erase(it);
            }
        }
        void removeObserver(std::string name) {
            notification_itr_const it = _map.find(name);
            if(it != std::end(_map)) {
                _map.erase(it);
            }
        }
        
        //post notifications
        void postNotification() {
            for(auto it = _map.begin(); it != _map.end(); ++it) {
                func_type f = it->second;
                f();
            }
        }
        void postNotification(std::string name) {
            notification_itr_const it = _map.find(name);
            if(it != std::end(_map)) {
                func_type f = it->second;
                f();
            }
        }
        
    private:
        notification_map_type _map;
    };
}

#endif
