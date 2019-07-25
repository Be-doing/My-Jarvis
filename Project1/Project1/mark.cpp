#include"Jarvis.h"

Json::Value TLRbt::RbtRes(Json::Value& root)
{
	std::string response;//接收图灵响应

	//int post(url,params,body,headers,response)
	//发起请求
	this->client_.post(url_, nullptr, root, nullptr, &response);

	//parse：将收到的数据反序列化为json格式
	Json::CharReaderBuilder crbuilder;
	Json::Value obj;//保存序列化后的结果
	std::string err;//错误信息
	std::unique_ptr<Json::CharReader> reader(crbuilder.newCharReader());

	bool res = reader->parse(response.data(), response.data() + response.size(), &obj, &err);
	//test#############################
	//Json::StreamWriterBuilder wb; 
	//stringstream os;
	//unique_ptr<Json::StreamWriter> jsonWriter(wb.newStreamWriter()); 
	//jsonWriter->write(obj, &os); 
	//string s = os.str(); 
	//cout << s << endl;
	//test################################
	if (!res || !err.empty())
	{
		std::cout << "read error " << err << std::endl;
		return obj;
	}
	return obj;
}

std::string TLRbt::Talk(std::string& massage)
{
	//将输入进来的文本进行序列话，
	//组织HTTP请求，方法为POST
	//将序列化后的字符串组织在body中
	//发起请求

	//正文序列化的格式为
	//{
	//	"reqType":0,
	//		"perception" : {
	//		"inputText": {
	//			"text": "附近的酒店"
	//		},
	//	},
	//		"userInfo": {
	//		"apiKey": "",
	//			"userId" : ""
	//	}
	//}

	Json::Value root; //最外面的json
	Json::Value perjson;//第二层的json
	Json::Value textjson;//第三层的json
	Json::Value inputjson;
	Json::Value infojson;//第二层配置json
	root["reqType"] = 0;
	inputjson["text"] = massage;
	perjson["inputText"] = inputjson;
	root["perception"] = perjson;

	infojson["apiKey"] = apikey_;
	infojson["userId"] = myid_;
	root["userInfo"] = infojson;
	//test#################################
	//Json::StreamWriterBuilder wb; 
	//stringstream os;
	//unique_ptr<Json::StreamWriter> jsonWriter(wb.newStreamWriter()); 
	//jsonWriter->write(root, &os); 
	//string s = os.str(); 
	//cout << s << endl;
	//test##################################


	//开始组织请求，将上面的序列化文本放到正文，接收TLRBT发来的响应
	Json::Value ret = RbtRes(root);
	//在返回的格式中，我们只关注result这个json，result为一个数组
	Json::Value result = ret["results"];
	Json::Value rtextjson = result[0]["values"];

	return rtextjson["text"].asString();
}