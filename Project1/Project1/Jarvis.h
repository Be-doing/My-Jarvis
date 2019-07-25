#pragma once
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif
#include <iostream>
#include <thread>
#include<fstream>
#include<sstream>
#include <string>
#include <memory>
#include <json/json.h>
#include "sdk/speech.h"
#include "sdk/base/http.h"

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