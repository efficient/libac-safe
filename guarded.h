#ifndef GUARDED_H_
#define GUARDED_H_

#include <iostream>

template<typename T> T default_val();

template<typename T> struct Guarded {
	const char *tag;
	T val;

	Guarded(const char *tag): tag(tag), val(default_val<T>()) {
		using std::cout;
		using std::endl;

		cout << "tagged(" << tag << ")" << endl;
	}

	virtual ~Guarded() {
		using std::cout;
		using std::endl;

		cout << "drop(" << tag << ")" << endl;
	}

	operator T() {
		return val;
	}
};

#endif
