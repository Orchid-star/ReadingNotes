#include "common_define.h"

#define LIST_INIT_SIZE 100
typedef struct {
	ElemType *elem;
	int length;
}SqList;

Status init_sqlist(SqList& L) {
	L.elem = new ElemType[LIST_INIT_SIZE];
	if (!L.elem) {
		exit(OVERFLOW);
	}
	L.length = 0;
	return OK;
}

void destroy_sqlist(SqList& L) {
	if (L.elem) {
		delete [] L.elem;
	}
}

void clear_sqlist(SqList& L) {
	L.length = 0;
}

int length_sqlist(SqList& L) {
	return L.length;
}

bool is_empty(SqList& L) {
	return (L.length == 0);
}

bool get_elem(SqList& L, int idx, ElemType& e) {
	//逻辑为止，起始为1
	if (idx < 1 || idx > L.length) {
		return false;
	}
	e = L.elem[idx - 1];
	return true;
}

int find_elem(SqList& L, ElemType e) {
	for (int i = 0; i < L.length; ++i) {
		if (L.elem[i] == e) {
			return (i + 1); //逻辑位置
		}
		return 0;
	}
}

bool insert_sqlist(SqList& L, int idx, ElemType e) {
	if (L.length == LIST_INIT_SIZE) {
		return false;
	}
	if ((idx < 1) || (idx > L.length + 1)) {
		return false;
	}	
	for (int i = L.length; i >= idx; i--) {
		L.elem[i] = L.elem[i - 1];
	}
	L.elem[idx - 1] = e;
	L.length++;
	return true;
}

bool sqlist_remove(SqList& L, int idx) {
	if (idx < 1 || idx > L.length) {
		return false;
	}
	for (int i = idx; i <= (L.length-1); ++i) {
		L.elem[i - 1] = L.elem[i];
	}
	L.length--;
	return true;
}