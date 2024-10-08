#pragma once
#include <string>
using namespace std;

struct SLNode;
void push_front(SLNode*& head, const string& value);
void push_back(SLNode*& head, const string& value);
void pop_front(SLNode*& head);
void pop_back(SLNode*& head);
void delete_value(SLNode*& head, const string& value);
void read_list(SLNode* head);