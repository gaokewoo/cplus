//This file is for implementing the List of <<Data Structures and Algorithm Anaylysis in C>>
#include <iostream>
#include <cstdlib>

using namespace std;

typedef int ElementType;

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty( List L );
int IsEmpty( List L );
int IsLast( Position P, List L );
Position Find( ElementType X, List L );
void Delete( ElementType X, List L );
Position FindPrevious( ElementType X, List L );
void Insert( ElementType X, List L, Position P );
void DeleteList( List L );
ElementType Retrieve( Position P );

struct Node{
	ElementType data;
	Position next;
};


//if has data,then delete all datas,only save the list head
List MakeEmpty( List L ){
	if( L != NULL ){
		DeleteList(L);
	}
	else {
		L = new Node;
		L->next = NULL;
	}

	return L;
}

void DeleteList( List L ){
	Position tmp;
	while ( L->next != NULL ){
		tmp = L->next;
		L->next = tmp->next;
		cout<<__func__<<"delete data:"<<tmp->data<<endl;
		delete tmp;
	}
}

void Insert( ElementType X, List L, Position P ){
	Position tmp;
	tmp = new Node;
	if( tmp == NULL ){
		cerr<<"alloc memory error."<<endl;
		exit(1);
	}

	tmp->data = X;
	cout<<__func__<<"insert data:"<<tmp->data<<endl;
	tmp->next = P->next;
	P->next = tmp;
}

void Delete( ElementType X, List L ){
	Position pre,tmp;
	pre = FindPrevious(X,L);

	if(!IsLast( pre,L )){
		tmp = pre->next;
		cout<<__func__<<"delete data:"<<tmp->data<<endl;
		pre->next = tmp->next;
		delete tmp;
	}
}

Position FindPrevious( ElementType X, List L ){
	Position tmp = L;

	while(tmp->next != NULL && tmp->next->data != X)
		tmp=tmp->next;

	return tmp;
}

Position Find( ElementType X, List L ){
	Position tmp = L->next;

	while(tmp != NULL && tmp->data != X)
		tmp=tmp->next;

	return tmp;
}

int IsEmpty( List L ){

	return L->next == NULL;
}

int IsLast( Position P, List L ){
	
	return P->next == NULL;
}

ElementType Retrieve( Position P ){
	if( P != NULL ) return P->data;
}

int main(){

	return 0;
}

