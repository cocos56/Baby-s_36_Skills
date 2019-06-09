#pragma once

#include "QE.h"

class HelloWorld : public Layer
{
	QE_CreateSceneFromLayer_H(HelloWorld);
	Label* label;
	ListView* _listView;
public:
	void testListView();
	void setWidget(ListView* _listView, std::string str);
};