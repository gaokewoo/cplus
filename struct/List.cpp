#include <iostream>
namespace wugk{

template <class T>
class List{
	public:
		List();
		bool isEmpty();
		bool addOneNode(List node);
		bool deleteOneNode(List node);
		bool destroyList();

	private:
		T element;
		List *next;
};

List::List(){
	
}

}

int main(){

	return 0;
}

