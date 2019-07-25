#include"Jarvis.h"

Json::Value TLRbt::RbtRes(Json::Value& root)
{
	std::string response;//����ͼ����Ӧ

	//int post(url,params,body,headers,response)
	//��������
	this->client_.post(url_, nullptr, root, nullptr, &response);

	//parse�����յ������ݷ����л�Ϊjson��ʽ
	Json::CharReaderBuilder crbuilder;
	Json::Value obj;//�������л���Ľ��
	std::string err;//������Ϣ
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
	//������������ı��������л���
	//��֯HTTP���󣬷���ΪPOST
	//�����л�����ַ�����֯��body��
	//��������

	//�������л��ĸ�ʽΪ
	//{
	//	"reqType":0,
	//		"perception" : {
	//		"inputText": {
	//			"text": "�����ľƵ�"
	//		},
	//	},
	//		"userInfo": {
	//		"apiKey": "",
	//			"userId" : ""
	//	}
	//}

	Json::Value root; //�������json
	Json::Value perjson;//�ڶ����json
	Json::Value textjson;//�������json
	Json::Value inputjson;
	Json::Value infojson;//�ڶ�������json
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


	//��ʼ��֯���󣬽���������л��ı��ŵ����ģ�����TLRBT��������Ӧ
	Json::Value ret = RbtRes(root);
	//�ڷ��صĸ�ʽ�У�����ֻ��עresult���json��resultΪһ������
	Json::Value result = ret["results"];
	Json::Value rtextjson = result[0]["values"];

	return rtextjson["text"].asString();
}