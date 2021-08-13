#include "stdafx.h"
#include "cfg.h"
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <Windows.h>

using namespace::std;

string ws2s(wstring wstr)
{
	string result;
	//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//宽字节编码转换成多字节编码  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

enum color_format { YUV420_10BE, YUV420_10LE, YUV444, YUV422, YUV420, UYVY, YUYV, YYY, PACKED_YUV444, NV12, NV21, RGB32, RGB24, RGB16 };
enum segment_type { SEGMENT16x16 = 1, SEGMENT32x32 = 2, SEGMENT64x64 = 4 };
CCfg* CCfg::instance = nullptr;
void CCfg::parse(LPTSTR str) {
	if (str == nullptr) return;
	vector<wstring> result;

	wstring param = str;
	int index = 0;
	do {
		int pos = param.find(L" ", index);
		if (pos == -1) {
			result.push_back(param.substr(index));
			break;
		}
		wstring elem = param.substr(index, pos - index);
		if (!elem.empty()) {
			result.push_back(elem);
		}
		index = pos + 1;
	} while (1);

	for (int i = 0; i < result.size(); i++) {
		if (i + 1 >= result.size() ){
			return;
		}
		wstring value = result[i + 1];
		if (result[i] == L"-s") {
			int pos = value.find(L"x");
			if (pos == wstring::npos) {
				return;
			}
			makeInstance()->width = atoi(ws2s(value.substr(0, pos)).c_str());
			makeInstance()->height = atoi(ws2s(value.substr(pos + 1)).c_str());
			i++;
		}
		else if (result[i] == L"-z") {
			if (value == L"4:1") {

				makeInstance()->zoom = 4.0f;
			}
			else if (value == L"2:1") {
				makeInstance()->zoom = 2.0f;
			}
			else if (value == L"1:1") {
				makeInstance()->zoom = 1.0f;

			}
			else if (value == L"1:2") {
				makeInstance()->zoom = 0.5f;
			}
			else if (value == L"1:4") {
				makeInstance()->zoom = 0.25f;
			}
			i++;
		}
		else if (result[i] == L"-c") {
			map<wstring, color_format> colorMap;
			colorMap.insert(std::make_pair(L"YUV420_10LE", YUV420_10LE));
			colorMap.insert(std::make_pair(L"YUV420_10BE", YUV420_10BE));
			colorMap.insert(std::make_pair(L"YUV444", YUV444));
			colorMap.insert(std::make_pair(L"YUV422", YUV422));
			colorMap.insert(std::make_pair(L"YUV420", YUV420));
			colorMap.insert(std::make_pair(L"PACKED_YUV444", PACKED_YUV444));
			colorMap.insert(std::make_pair(L"NV21", NV21));
			colorMap.insert(std::make_pair(L"NV12", NV12));
			colorMap.insert(std::make_pair(L"UYVY", UYVY));
			colorMap.insert(std::make_pair(L"YUYV", YUYV));
			colorMap.insert(std::make_pair(L"RGB32", RGB32));
			colorMap.insert(std::make_pair(L"RGB24", RGB24));
			colorMap.insert(std::make_pair(L"RGB16", RGB16));
			colorMap.insert(std::make_pair(L"YYY", YYY));
			if (colorMap.find(value) != colorMap.end()) {
				makeInstance()->color = colorMap[value];
			}
		}
	}
	getInstance();

}

