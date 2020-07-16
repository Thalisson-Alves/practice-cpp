#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

namespace th
{
	template<class T>
	struct SingleNode{
		T data_;
		SingleNode<T> *next_;
	};
	
	template<class T>
	class LinkedList{
	public:
		/* === Constructors === */
		LinkedList() : head{NULL} {}
		
		LinkedList(T value){
			SingleNode<T> *node = new SingleNode<T>;
			node->data_ = value;
			node->next_ = NULL;
			head = node;
		}
		
		LinkedList(T value, SingleNode<T> *next){
			SingleNode<T> *node = new SingleNode<T>;
			node->data_ = value;
			node->next_ = next;
			head = node;
		}
		
		/* === Destructor === */
		~LinkedList(){
			while(head){
				SingleNode<T> *next = head->next_;
				delete head;
				head = next;
			}
		}
		
		/* === Element Access === */
		T front() const {
			if(!head){
				std::cerr << "Cannot access front from an empty list.\n";
				exit(EXIT_FAILURE);
			}
			return head->data_;
		}
		
		T back() const {
			if(!head){
				std::cerr << "Cannot access back from an empty list.\n";
				exit(EXIT_FAILURE);
			}
			SingleNode<T> *last = head;
			while(last->next_)
				last = last->next_;
			return last->data_;
		}
		
		T at(int index) const {
			SingleNode<T> *current = head;
			int i;
			for(i=0; i<index && current; i++, current = current->next_){}
			if(i != index){
				std::cerr << "Index out of bound.\n";
				exit(EXIT_FAILURE);
			}
			return current->data_;
		}
		
		T n_from_end(int n) const {
			SingleNode<T> *current = head;
			SingleNode<T> *target = head;
			int i;
			for(i=0; i<n; i++ && current, current = current->next_){}
			if(i != n){
				std::cerr << "List not long enought.\n";
				exit(EXIT_FAILURE);
			}
			for(; current; current = current->next_, target = target->next_){}
			return target->data_;
		}
		
		void debug() const {
			SingleNode<T> *current = head;
			std::cout << "Head at " << (head) << '\n';
			std::cout << "Element(s):\n";
			while(current){
				std::cout << current->data_ << '\n';
				current = current->next_;
			}
			std::cout << "size is " << this->size() << '\n';
			std::cout << "-------------------\n";
		}
		/* === Capacity === */
		int size() const {
			int size;
			SingleNode<T> *current = head;
			for(size=0; current; current = current->next_, size++){}
			return size;
		}
		
		bool empty() const { return !head; }
		
		/* === Modifires === */
		void push_front(T value){
			SingleNode<T> *node = new SingleNode<T>;
			node->data_ = value;
			node->next_ = head;
			head = node;
		}
		
		void pop_front(){
			if(!head){
				std::cerr << "Cannot pop front of empty list.\n";
				exit(EXIT_FAILURE);
			}
			SingleNode<T> *temp = head;
			head = head->next_;
			delete temp;
		}
		
		void push_back(T value){
			SingleNode<T> *last = head;
			if(!last){
				this->push_front(value);
				return;
			}
			while(last->next_){
				last = last->next_;
			}
			SingleNode<T> *node = new SingleNode<T>;
			node->data_ = value;
			node->next_ = NULL;
			last->next_ = node;
		}
		
		void pop_back(){
			if(!head){
				std::cerr << "Cannot pop back of empty list.\n";
				exit(EXIT_FAILURE);
			}
			SingleNode<T> *prev = NULL;
			SingleNode<T> *current = head;
			for(; current->next_; prev = current, current = current->next_){}
			if(prev)
				prev->next_ = NULL;
			else
				head = NULL;
			delete current;
		}
		
		void insert(int index, T value){
			if(!head || index < 0){
				std::cerr << "Index out of bound.\n";
				exit(EXIT_FAILURE);
			}
			if(!index){
				this->push_front(value);
				return;
			}
			SingleNode<T> *prev = NULL;
			SingleNode<T> *current = head;
			int i;
			for(i=0; i<index && current; i++, prev = current, current = current->next_){}
			if(i != index){
				std::cerr << "Index out of bound.\n";
				exit(EXIT_FAILURE);
			}
			SingleNode<T> *node = new SingleNode<T>;
			node->data_ = value;
			node->next_ = current;
			prev->next_ = node;
		}
		
		void erase(int index){
			if(!head || index < 0){
				std::cerr << "Index out of bound.\n";
				exit(EXIT_FAILURE);
			}
			if(!index){
				this->pop_front();
				return;
			}
			SingleNode<T> *prev = NULL;
			SingleNode<T> *current = head;
			int i;
			for(i=0; i<index && current; i++, prev = current, current = current->next_){}
			if(i != index && current){
				std::cerr << "Index out of bound.\n";
				exit(EXIT_FAILURE);
			}
			prev->next_ = current->next_;
			delete current;
		}
		
		void reverse(){
			SingleNode<T> *prev = NULL;
			SingleNode<T> *current = head;
			while(current){
				SingleNode<T> *next = current->next_;
				current->next_ = prev;
				prev = current;
				current = next;
			}
			head = prev;
		}
		
		void remove(T value){
			SingleNode<T> *current = head;
			SingleNode<T> *prev = NULL;
			if(current && current->data_ == value){
				this->pop_front();
				return;
			}
			while(current){
				if(current->data_ == value){
					prev->next_ = current->next_;
					delete current;
					break;
				}
				prev = current;
				current = current->next_;
			}
		}
		
	private:
		SingleNode<T> *head;
	};
}

#endif