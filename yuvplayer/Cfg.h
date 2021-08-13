#pragma once
#include <string>
using namespace std;
class CCfg
{
public:
	static void CCfg::parse(LPTSTR str);
	static CCfg* makeInstance() {
		if (instance == nullptr) {
			instance = new CCfg();
			return instance;
		}
		return instance;
	}
	static CCfg* getInstance() {
		return instance;
	}
	int width;
	int height;
	float zoom = 1.0f;
	int color = 0;
private:
	static CCfg* instance;
};

