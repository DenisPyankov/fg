#include <iostream>
#include <list>
using namespace std;

class Queue {
public:
	list <int> q;

	void push(int n) {
		q.push_front(n);
	};
	void pop() {
		q.pop_back();
	};
	int front() {
		return q.back();
	};
	int back() {
		return q.front();
	};
	void print() {
		for (int i : q)
			cout << i << ", ";
		cout << endl;
	};
};

int main()
{
	Queue q;
	for (int i = 0; i < 10; i++)
		q.push(i);
	q.print();
	for (int i = 0; i < 2; i++)
		q.pop();
	q.print();
	cout << q.front() << " " << q.back();
}