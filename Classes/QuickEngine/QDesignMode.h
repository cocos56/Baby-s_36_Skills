#pragma execution_character_set("utf-8")
#pragma once

/*
Quick Engine所属的快速设计模式模块
用途：使开发者可以使用用宏快速创建设计模式
*/

//**单例模式
//*QE_SINGLETON_H与QE_SINGLETON_CPP应配合使用，缺一不可
#define QE_SINGLETON_H(__TYPE__) \
private: \
static __TYPE__* _instance; \
__TYPE__() {}; \
~__TYPE__() {}; \
 \
public: \
	static __TYPE__* getInstance() { return _instance; };

#define QE_SINGLETON_CPP(__TYPE__) __TYPE__* __TYPE__::_instance = new __TYPE__;
#define QE_SINGLETON2_CPP(__TYPE__) __TYPE__* __TYPE__::_instance = nullptr;