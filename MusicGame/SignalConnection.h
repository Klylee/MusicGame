#pragma once

#include <iostream>
#include <map>
#include <functional>
#include <string>

typedef std::function<void(std::string)> EventFunc;

static std::map<std::string, EventFunc> signals;
static std::map<std::string, EventFunc> callbacks;
static std::multimap<std::string, std::string> connects;

#define GEN_SIGNAL(funcname)    void funcname(std::string e) \
                                { \
                                    auto it = connects.find(#funcname); \
                                    if(it == connects.end()){ \
                                        std::cout <<"can not find signal function: "<< #funcname << std::endl; \
                                        return; \
                                    } \
                                    int count = connects.count(#funcname); \
                                    for(int i =0; i < count; i++, it++){ \
                                        auto callback = callbacks.find(it->second); \
                                        if(callback == callbacks.end()){ \
                                            std::cout << "can not find callback function: " << it->second << std::endl; \
                                            return; \
                                        } \
                                        callback->second(e); \
                                    } \
                                } 


static void connect(const std::string signal, const std::string callback)
{
	auto signalfunc = signals.find(signal);
	if (signalfunc == signals.end()) {
		std::cout << "connect warning: no such signal function \"" << signal << "\"" << std::endl;
		return;
	}
	auto callbackfunc = callbacks.find(callback);
	if (callbackfunc == callbacks.end()) {
		std::cout << "connect warning: no such callback function \"" << callback << "\"" << std::endl;
		return;
	}

	connects.insert(std::pair<std::string, std::string>(signal, callback));
}

#define registerSignal(funcname)	signals.insert(std::pair<std::string, EventFunc>(#funcname, EventFunc(funcname)))

#define registerCallback(funcname)	callbacks.insert(std::pair<std::string, EventFunc>(#funcname, EventFunc(funcname)))
