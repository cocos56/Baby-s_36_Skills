#pragma once

/*
Quick Engine所属的快速设计模式模块
用途：使开发者可以使用用宏快速创建设计模式
*/

//**单例模式
//*QE_SINGLETON_H与QE_SINGLETON_CPP应配合使用，缺一不可
#define QE_SINGLETON_H(__TYPE__) \
private: \
static __TYPE__* instance; \
__TYPE__() {}; \
~__TYPE__() {}; \
 \
public: \
	static __TYPE__* getInstance() { return instance; };

#define QE_SINGLETON_CPP(__TYPE__) __TYPE__* __TYPE__::instance = new __TYPE__;