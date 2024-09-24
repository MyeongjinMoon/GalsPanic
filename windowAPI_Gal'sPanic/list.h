#pragma once
struct List {
	POINT p;

	List* next = nullptr;
	List* pre = nullptr;
};

bool HaveNext(List* l)
{
	if (l->next == nullptr)
		return false;
	return true;
}

bool HavePre(List* l)
{
	if (l->pre == nullptr)
		return false;
	return true;
}

void AttachList(List* list, List* newListhead, List* newListtail)
{
	List* temp = list->next;
	list->next = newListhead;
	newListhead->pre = list; 
	temp->pre = newListtail;
	newListtail->next = temp;
}

void DeleteList(List* l)
{
	l = l->pre;
	if (l != nullptr)
		l->next = nullptr;
}
