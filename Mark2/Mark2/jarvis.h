//#pragma once
////1.�ڹٷ���վ����C++ SDKѹ������
////
////2.�����ص�aip - cpp - sdk - version.zip��ѹ, �����ļ�Ϊ����ʵ�ִ����ͷ�ļ���
////
////3.��װ������libcurl����Ҫ֧��https�� openssl jsoncpp(> 1.6.2�汾��0.x�汾������֧��)��
////
////4.���빤��ʱ��� C++11 ֧��(gcc / clang ��ӱ������ - std = c++11), ��ӵ����������Ӳ��� lcurl, lcrypto, ljsoncpp��
////
////5.��Դ����include speech.h ������ѹ�����е�ͷ�ļ���ʹ��aip�����ռ��µ���ͷ�����
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


//ͼ���������
class TLRbt
{
public:
	//�����л���json������Ϣ��ͼ�鷢������
	Json::Value RbtRes(Json::Value& root);
	//��ɶԻ�
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
			std::cout << "��������Ϣ��";
			std::cin >> massage;

			std::cout << "Jarvis��" << bt_.Talk(massage) << std::endl;
		}

		return true;
	}
private:
	TLRbt bt_;
};