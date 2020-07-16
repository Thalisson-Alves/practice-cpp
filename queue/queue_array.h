#ifndef __QUEUE_ARRAY_H__
#define __QUEUE_ARRAY_H__

namespace th{
	template<class T>
	class Queue{
	public:
		Queue(int cap){
			capacity_ = cap;
			start_ = 0;
			size_ = 0;
			data_ = new T[cap];
		}
		
		~Queue(){
			delete[] data_;
		}
		
		bool empty() const { return !size_; }
		
		bool full() const { return size_ == capacity_; }
		
		T back() const {
			if(this->empty()){
				std::cerr << "Cannot access back of empty queue.\n";
				exit(EXIT_FAILURE);
			}
			return *(data_+(start_+size_-1)%capacity_);
		}
		
		T front() const {
			if(this->empty()){
				std::cerr << "Cannot access front of empty queue.\n";
				exit(EXIT_FAILURE);
			}
			return *(data_+start_);
		}
		
		void enqueue(T value){
			if(this->full()){
				std::cerr << "Cannot enqueue a full queue.\n";
				exit(EXIT_FAILURE);
			}
			*(data_ + (start_+size_++)%capacity_) = value;
		}
		
		T dequeue(){
			if(!size_){
				std::cerr << "Cannot dequeue an empty queue.\n";
				exit(EXIT_FAILURE);
			}
			size_--;
			int temp = start_;
			start_ = (start_+1)%capacity_;
			return *(data_+temp);
		}
	
	private:
		T *data_;
		int capacity_;
		int start_;
		int size_;
	};
}

#endif