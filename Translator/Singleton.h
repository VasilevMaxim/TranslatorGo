#pragma once

template<class T>
class Singleton
{
private:
	static T* _instance;
public:
	static T* GetInstance();
};

template<class T> T* Singleton<T>::_instance = nullptr;

template<class T>
inline T* Singleton<T>::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new T();
	}

	return _instance;
}
