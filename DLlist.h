#pragma once
#include <string>
using namespace std;

struct DLNode;
void push_front(DLNode*& head, DLNode*& tail, const string& value);
void push_back(DLNode*& head, DLNode*& tail, const string& value);
void pop_front(DLNode*& head, DLNode*& tail);
void pop_back(DLNode*& head, DLNode*& tail);
void delete_value(DLNode*& head, DLNode*& tail, const string& value);
void read_list_from_head(DLNode* head);
void read_list_from_tail(DLNode* tail);