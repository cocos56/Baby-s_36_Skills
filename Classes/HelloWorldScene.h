#pragma once

#include "QE.h"

class HelloWorld : public Layer
		, public SocketIO::SIODelegate, public EditBoxDelegate
{
	SIOClient *_sioClient;
	Label* label;
	ListView* _listView;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
	void menuSendMsgCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void onConnect(SIOClient* client);
    virtual void onMessage(SIOClient* client, const string& data);
    virtual void onClose(SIOClient* client);
    virtual void onError(SIOClient* client, const string& data);

	void callClientEvent(SIOClient *client, const string& data);

	void testEditBox();
	virtual void editBoxEditingDidBegin(EditBox* editBox);
	virtual void editBoxTextChanged(EditBox* editBox, const string& text);
	virtual void editBoxEditingDidEnd(EditBox* editBox);
	virtual void editBoxReturn(EditBox* editBox);

	void testListView();
	void setWidget(ListView* _listView, std::string str);
};