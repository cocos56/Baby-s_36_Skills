#pragma execution_character_set("utf-8")

#include "QMessageBox.h"

void QMessageBox(const string msg) { MessageBox(msg.c_str(), "通知"); }
void QMessageBox(const string msg, const string title) { MessageBox(msg.c_str(), title.c_str()); }