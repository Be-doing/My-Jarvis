//#pragma once
////1.在官方网站下载C++ SDK压缩包。
////
////2.将下载的aip - cpp - sdk - version.zip解压, 其中文件为包含实现代码的头文件。
////
////3.安装依赖库libcurl（需要支持https） openssl jsoncpp(> 1.6.2版本，0.x版本将不被支持)。
////
////4.编译工程时添加 C++11 支持(gcc / clang 添加编译参数 - std = c++11), 添加第三方库链接参数 lcurl, lcrypto, ljsoncpp。
////
////5.在源码中include speech.h ，引入压缩包中的头文件以使用aip命名空间下的类和方法。
//
//
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif
#pragma comment( lib, "opencv_highgui231d.lib")
#pragma comment( lib, "opencv_core231d.lib")
#include <iostream>
#include <thread>
#include<fstream>
#include<sstream>
#include <string>
#include <memory>
#include "sdk/speech.h"
#include "sdk/base/http.h" // aip lib
#include <json/json.h> // ?


//图灵机器人类
class TLRbt
{
public:
	//将序列化的json主机信息向图灵发起请求
	Json::Value RbtRes(Json::Value& root);
	//完成对话
	std::string Talk(std::string& massage);
private:
	std::string url_ = "openapi.tuling123.com/openapi/api/v2";
	std::string apikey_ = "cd9103856ea74714a614250a5e960901";
	std::string myid_ = "mark1";
	aip::HttpClient client_;
};

//jarvis
class Jarvis
{
public:
	bool Run()
	{
		std::string massage;
		while (1)
		{
			std::cout << "请输入信息：";
			std::cin >> massage;

			std::cout << "Jarvis：" << bt_.Talk(massage) << std::endl;
		}

		return true;
	}
private:
	TLRbt bt_;
};