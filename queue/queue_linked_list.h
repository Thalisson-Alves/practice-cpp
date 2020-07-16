#ifndef __QUEUE_LINKED_LIST_H__
#define __QUEUE_LINKED_LIST_H__

namespace th
{
	template<class T>
	struct SingleNode{
		T data_;
		SingleNode<T> *next_;
	};
	
	template<class T>
	class Queue{
	public:
		Queue() : head{NULL}, tail{NULL}, size_{0} {}
		
		~Queue(){
			while(head){
				SingleNode<T> *temp = head->next_;
				delete head;
				head = temp;
			}
		}
		
		bool empty() const { return !head && !tail && !size_; }
		
		int size() const { return size_; }
		
		T back() const {
			if(this->empty()){
				std::cerr << "Cannot access back of empty queue.\n";
				exit(EXIT_FAILURE);
			}
			return tail->data_;
		}
		
		T front() const {
			if(this->empty()){
				std::cerr << "Cannot access front of empty queue.\n";
				exit(EXIT_FAILURE);
			}
			return head->data_;
		}
		
		void enqueue(T value){
			SingleNode<T> *node = new SingleNode<T>;
			node->data_ = value;
			node->next_ = NULL;
			if(tail){
				tail->next_ = node;
				tail = node;
			}else{
				head = node;
				tail = node;
			}
			size_++;
		}
		
		int dequeue(){
			if(this->empty()){
				std::cerr << "Cannot dequeue an empty queue.\n";
				exit(EXIT_FAILURE);
			}
			SingleNode<T> *temp = head;
			head = head->next_;
			if(tail == temp)
				tail = head;
			int front = temp->data_;
			delete temp;
			size_--;
			return front;
		}
		
	private:
		SingleNode<T> *head;
		SingleNode<T> *tail;
		int size_;
	};
}

#endif