#include "common_define.h"

typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode, *pLNode;

void linked_list_init(pLNode& L)
{
	L = new LNode;
	L->next = nullptr;
}

bool linked_list_is_empty(pLNode& L)
{
	return L->next == nullptr;
}

void linked_list_destroy(pLNode& L)
{
	pLNode p;
	while (L) {
		p = L;
		L = L->next;
		delete p;
	}
}

void linked_list_clear_way0(pLNode& L)
{
	linked_list_destroy(L->next);
	L->next = nullptr;
}

void linked_list_clear_way1(pLNode& L)
{
	pLNode p, q;
	p = L->next;
	while (p) {
		q = p;
		p = p->next;
		delete q;
	}
	L->next = nullptr;
}

int linked_list_length(pLNode& L)
{
	int len = 0;
	pLNode p = L->next;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
}

bool linked_list_get_elem(pLNode& L, int idx, ElemType& e)
{
	bool ret = false;
	pLNode p = L->next;
	int i = 1;
	while (p && i < idx) {
		p = p->next;
		++i;
	}
	if (p && i == idx) {
		e = p->data;
		ret = true;
	}
	return ret;
}

pLNode linked_list_locate(pLNode& L, ElemType e)
{
	pLNode p = L->next;
	while (p && p->data != e)
	{
		p = p->next;
	}
	return p;
}

int linked_list_locate_idx(pLNode& L, ElemType e)
{
	pLNode p = L->next;
	int idx = 1;
	while (p && p->data != e)
	{
		p = p->next;
		idx++;
	}
	return idx;
}

Status linked_list_insert(pLNode& L, int idx, ElemType e)
{
	pLNode p = L;
	int k = 0;
	pLNode node = nullptr;

	//长度满足时，k=idx-1出循环
	while (p && k < idx - 1)
	{
		p = p->next;
		++k;
	}
	if (p && k == (idx - 1)) {
		node = new LNode;
		node->data = e;
		node->next = p->next;
		p->next = node;
		return OK;
	}
	return ERROR;
}

Status linked_list_remove(pLNode& L, int idx, ElemType& e)
{
	pLNode p = L;
	int k = 0;
	pLNode node = nullptr;
	
	while (p && k < idx - 1) {
		p = p->next;
		++k;
	}
	if (p && k == (idx - 1)) {
		node = p->next;
		p->next = p->next->next;
		e = node->data;
		delete node;
		return OK;
	}
	return ERROR;
}

void create_list_head(pLNode& L, int len)
{
	pLNode p = nullptr;
	L = new LNode;
	L->next = nullptr;
	for (int i = len; i > 0; --i) {
		p = new LNode;
		std::cin >> p->data;
		p->next = L->next;
		L->next = p;
	}
}

void create_list_tail(pLNode& L, int len)
{
	pLNode p, r;

	L = new LNode;
	L->next = nullptr;
	r = L;
	for (int i = 0; i < len; ++i) {
		p = new LNode;
		std::cin >> p->data;
		p->next = nullptr;
		r->next = p;
		r = p;
	}
}