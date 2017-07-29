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

    //外带数据要继承此类
    class lpObject {
    public:
        lpObject() {}
        virtual ~lpObject(){}
        lpObject(const lpObject&& o) {}
        lpObject(const lpObject&) {}
        void operator=(const lpObject&) {}
    };
    
    typedef std::function<void(lpObject *)> func_type;

    //内部类，组合数据
    struct _Data {
        _Data() {
            _callback = nullptr;
            _object = nullptr;
        }
        _Data(func_type f, lpObject *object) : _callback(f), _object(object) {}
        
        func_type _callback;
        lpObject *_object;
    };
    
    typedef std::unordered_map<std::string, Notification::_Data> notification_map_type;
    typedef std::unordered_map<std::string, Notification::_Data>::const_iterator notification_itr_const;
    
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
            _Data data;
            data._callback = f;
            data._object = nullptr;
            std::pair<std::string, Notification::_Data> p = std::make_pair(name, data);
            _map.insert(p);
        }
        void addObserver(std::string name, func_type &&f, lpObject *data) {
            _Data dt;
            dt._callback = f;
            dt._object = data;
            std::pair<std::string, Notification::_Data> p = std::make_pair(name, dt);
            _map.insert(p);
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
                auto data = it->second;
                func_type callback = data._callback;
                callback(data._object);
            }
        }
        void postNotification(std::string name) {
            notification_itr_const it = _map.find(name);
            if(it != std::end(_map)) {
                auto data = it->second;
                func_type callback = data._callback;
                callback(data._object);
            }
        }
        void postNotification(std::string name, lpObject *data) { //value-result
            notification_itr_const it = _map.find(name);
            if(it != std::end(_map)) {
                auto dt = it->second;
                func_type callback = dt._callback;
                callback(dt._object);
            }
        }
    private:
        notification_map_type _map;
    };
}

#endif
