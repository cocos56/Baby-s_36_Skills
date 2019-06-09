#include "HttpTest.h"

Label* HttpTest::label;

QE_CreateSceneFromLayer_CPP(HttpTest);
	label = Label::create("", "Marker Felt.ttf", 24);
	label->setAnchorPoint(Vec2(0, 0));
	label->setPosition(10, 300);
	addChild(label);

	label->setString("init");

	postHttpRequest();

	return true;
}

void HttpTest::postHttpRequest()
{
	HttpRequest* request = new HttpRequest();
	string url = "http://10.6.32.1:8080/user/login.action";
	url = "https://www.baidu.com:80/";

	request->setUrl(url);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(CC_CALLBACK_2(HttpTest::onHttpRequestCompleted, this));

	// write the post data
	const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
	postData = "";
	request->setRequestData(postData, strlen(postData));
	request->setTag("POST test");
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
}

void HttpTest::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
	string show;
	if (!response)
	{
		return;
	}

	// You can get original request type from: response->request->reqType
	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		CCLOG("%s completed", response->getHttpRequest()->getTag());
	}
	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
	CCLOG("response code: %d", statusCode);
	show += "status:";
	show += to_string(statusCode);
	if (!response->isSucceed())
	{
		CCLOG("response failed");
		CCLOG("error buffer: %s", response->getErrorBuffer());
		return;
	}
	// dump data
	//std::vector<char>* buffer = response->getResponseData()->data;
	std::vector<char>* buffer = response->getResponseData();
	CCLOG("Http Test, dump data: ");
	string buf;
	//CCLOG("%s", buffer);
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		buf += (*buffer)[i];
		//CCLOG("%c", );
	}
	show += ", buf:";
	show += buf;
	label->setString(show);
	CCLOG("%s", show.c_str());
	CCLOG("len = %d", buf.length());
}