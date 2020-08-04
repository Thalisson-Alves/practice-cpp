#ifndef __MAX_HEAP_CPP_H__
#define __MAX_HEAP_CPP_H__

namespace th
{
	/* constants for dinamic allocation */
	const int kMinCapacity = 16;
	const int kShirinkRate = 4;
	const int kGrowthRate = 2;
	
	class max_heap
	{
	public:
		/* PROTOTYPE */
		// initialize the values, allocating memory for elements
		max_heap();
		// deallocate memory
		~max_heap();
		// add element to max heap
		void insert(int value);
		// return the max value of heap, -1 empty
		int get_max();
		// return size of heap
		int get_size();
		// return true if heap is empty
		bool is_empty();
		// return the max value of heap removing it, -1 if empty
		int extract_max();
		// remove a element of a given index
		void remove(int index);
		
		
		// debugging heap
		void debug();
	private:
		// indexed at 1
		int *elements_;
		int size_;
		int capacity_;
		
		// restore the heap propery
		// propagating the given node index up up the tree
		void sift_up(int index);
		// restore the heap propery
		// propagating the given node index down up the tree
		void sift_down(int index);
		// swap 2 elements by the given indices
		void swap(int index_a, int index_b);
		// resize the elements array to the given size
		// allocating memory if needed
		void resize_for_size(int new_size);
	};
	
	/* FUNCTIONS USED IN HEAP SORT */
	// sorts a given array to satisfy the heap propery
	void build_heap(int *arr, int size);
	// same of sift_down but for 0 index array
	// used for heap sort
	void heapify(int *arr, int size, int index);
	// sort a given array in non decreasing order
	void heap_sort(int *arr, int size);
	
	
	/* IMPLEMENTATION */
	max_heap::max_heap()
	{
		size_ = 0;
		capacity_ = kMinCapacity;
		elements_ = new int[kMinCapacity + 1];
	}
	
	max_heap::~max_heap()
	{
		delete[] elements_;
	}
	
	void max_heap::insert(int value)
	{
		resize_for_size(size_ + 1);
		elements_[++size_] = value;
		sift_up(size_);
	}
	
	void max_heap::sift_up(int index)
	{
		// base case
		if (index <= 1)
			return;
		int parent_index = index / 2;
		if (elements_[parent_index] < elements_[index]) {
			swap(parent_index, index);
			sift_up(parent_index);
		}
	}
	
	void max_heap::swap(int index_a, int index_b)
	{
		int tmp = elements_[index_a];
		elements_[index_a] = elements_[index_b];
		elements_[index_b] = tmp;
	}
	
	int max_heap::get_max()
	{
		if (is_empty()) {
			// ERROR
			return -1;
		}
		return elements_[1];
	}
	
	int max_heap::get_size()
	{
		return size_;
	}
	
	bool max_heap::is_empty()
	{
		return size_ == 0;
	}
	
	int max_heap::extract_max()
	{
		if (is_empty()) {
			// ERROR
			return -1;
		}
		resize_for_size(size_ - 1);
		int larger = get_max();
		elements_[1] = elements_[size_--];
		sift_down(1);
		return larger;
	}
	
	void max_heap::sift_down(int index)
	{
		// base case
		if (index > size_) {
			return;
		}
		int left_child = index * 2;
		int right_child = index * 2 + 1;
		// larger child value
		int larger;
		// no childs
		if (left_child > size_) {
			return ;
		}
		// only one left child
		if (right_child > size_) {
			larger = left_child;
		}
		else if (elements_[left_child] > elements_[right_child]) {
			larger = left_child;
		}
		else {
			larger = right_child;
		}
		// swap if needed
		if (elements_[larger] > elements_[index]) {
			swap(larger, index);
		}
	}
	
	void max_heap::remove(int index)
	{
		if (index > size_ || index < 1) {
			// ERROR
			return;
		}
		resize_for_size(size_ - 1);
		elements_[index] = elements_[size_--];
		sift_down(index);
	}
	
	void max_heap::resize_for_size(int new_size)
	{
		if (new_size > capacity_) {
			int new_capacity = capacity_ * kGrowthRate;
			// reallocating memory for new capacity
			int *new_elements = new int[new_capacity + 1];
			for (int i = 1; i <= size_; i++) {
				new_elements[i] = elements_[i];
			}
			delete[] elements_;
			elements_ = new_elements;
			capacity_ = new_capacity;
		}
		else if (new_size < capacity_ / kShirinkRate) {
			int new_capacity = capacity_ / kShirinkRate;
			if (new_capacity < kMinCapacity) {
				new_capacity = kMinCapacity;
			}
			if (new_capacity == capacity_) {
				return;
			}
			// reallocating memory for new capacity
			int *new_elements = new int[new_capacity + 1];
			for (int i = 1; i <= size_; i++) {
				new_elements[i] = elements_[i];
			}
			delete[] elements_;
			elements_ = new_elements;
			capacity_ = new_capacity;
		}
	}
	
	void max_heap::debug()
	{
		std::cout << "Capacity: " << capacity_ << '\n';
		std::cout << "Size: " << get_size() << '\n';
		std::cout << "Max: " << get_max() << '\n';
		std::cout << "Pointer at: " << (elements_) << '\n';
		std::cout << "Elements:\n";
		for(int i = 1; i <= get_size(); i++) {
			std::cout << elements_[i] << (i == size_ ? '\n' : ' ');
		}
	}
	
	void build_heap(int *arr, int size)
	{
		for (int i = size / 2 - 1; i >= 0; i--) {
			heapify(arr, size, i);
		}
	}
	
	void heapify(int *arr, int size, int index)
	{
		if (index >= size) {
			return;
		}
		int left_child = index * 2 + 1;
		int right_child = index * 2 + 2;
		int largest;
		if (left_child >= size) {
			return ;
		}
		if (right_child >= size) {
			largest = left_child;
		}
		else if (arr[left_child] > arr[right_child]) {
			largest = left_child;
		}
		else {
			largest = right_child;
		}
		
		if (arr[largest] > arr[index]) {
			int tmp = arr[largest];
			arr[largest] = arr[index];
			arr[index] = tmp;
			heapify(arr, size, largest);
		}
	}
	
	void heap_sort(int *arr, int size)
	{
		build_heap(arr, size);
		for (int i = size - 1; i >= 0; i--) {
			int tmp = arr[0];
			arr[0] = arr[i];
			arr[i] = tmp;
			heapify(arr, i, 0);
		}
	}
}

#endif