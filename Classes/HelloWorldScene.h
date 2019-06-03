#pragma once

#include "QE.h"

class HelloWorld : public Layer
		, public SocketIO::SIODelegate, public EditBoxDelegate
{
	SIOClient *_sioClient;
	Label* label;
	ListView* _listView;
public:
    static Scene* createScene();

    virtual bool init();  
    
	void menuSendMsgCallback(Ref* pSender);
    
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