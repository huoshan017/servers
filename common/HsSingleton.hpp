#ifndef __HS_SINGLETON_H__
#define __HS_SINGLETON_H__

#include <stddef.h>

template <class T>
class HsSingleton
{
public:
	static T* getInstance() {
		if (instance_ == NULL) {
			instance_ = new T;
		}
		return instance_;
	}

	~HsSingleton() {
		if (instance_)
			delete instance_;
		instance_ = NULL;
	}

protected:
	HsSingleton() {}
	static T* instance_;
};

template<class T>
T* HsSingleton<T>::instance_ = NULL;

#endif
