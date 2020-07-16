#include "tvector.h"

namespace th
{
	void TVector::operator=(TVector &vet){
		this->size_ = vet.Size();
		this->capacity_ = vet.Capacity();
		int *new_data = new int[capacity_];
		this->data_ = new_data;
		for(int i=0; i<size_; i++)
			*(data_+i) = vet.At(i);
	}
	
	int& TVector::operator[](int index){
		if(index < 0 || index >= size_){
			std::cerr << "Index out of bound.\n";
			exit(EXIT_FAILURE);
		}
		return data_[index];
	}
	
	TVector::TVector(){
		size_ = 0;
		capacity_ = MIN_CAPACITY;
		data_ = new int[capacity_];
	}
	
	TVector::TVector(const int &size, const int &init_value=0){
		if(size < 0){
			std::cerr << "The size must be greater or equal to 0.\n";
			exit(EXIT_FAILURE);
		}	
		size_ = size;
		capacity_ = Determine_capacity(size_);
		data_ = new int[capacity_];
		for(int i=0; i<size_; i++)
			*(data_+i) = init_value;
	}
	
	TVector::TVector(TVector &vet){
		size_ = vet.Size();
		capacity_ = vet.Capacity();
		data_ = new int[capacity_];
		for(int i=0; i<size_; i++)
			*(data_+i) = vet.At(i);
	}
	
	TVector::~TVector(){
		delete[] data_;
	}
	
	int TVector::Back(){
		if(this->Empty()){
			std::cerr << "TVector of size 0 does not have a last element.\n";
			exit(EXIT_FAILURE);
		}
		return *(data_+size_-1);
	}
	
	int TVector::Front(){
		if(this->Empty()){
			std::cerr << "TVector of size 0 does not have a first element.\n";
			exit(EXIT_FAILURE);
		}
		return *data_;
	}
	
	int TVector::At(const int &index){
		if(index < 0 || index >= size_){
			std::cerr << "Index out of bound.\n";
			exit(EXIT_FAILURE);
		}
		return *(data_+index);
	}
	
	int TVector::Find(const int &element){
		int index = -1;
		for(int i=0; i<size_; i++)
			if(*(data_+i) == element){
				index = i;
				break;
			}
		return index;
	}
	
	
	int TVector::Size(){ return size_; }
	
	int TVector::Capacity(){ return capacity_; }
	
	bool TVector::Empty(){ return size_ == 0; }
	
	
	void TVector::Push(const int &element){
		this->Resize_for_size(size_+1);
		*(data_+size_++) = element;
	}
	
	int TVector::Pop(){
		if(this->Empty()){
			std::cerr << "TVector is already empty.\n";
			exit(EXIT_FAILURE);
		}
		int value = this->Back();
		this->Resize_for_size(--size_);
		return value;
	}
	
	void TVector::Delete(const int &index){
		if(index < 0 || index >= size_--){
			std::cerr << "Index out of bound.\n";
			exit(EXIT_FAILURE);
		}
		this->Resize_for_size(size_);
		for(int i=index; i<size_; i++)
			*(data_+i) = *(data_+i+1);
	}
	
	void TVector::Remove(const int &element){
		int new_size = 0;
		int old_size = size_;
		for(int i=0; i<old_size; i++)
			if(*(data_+i) != element)
				*(data_+new_size++) = *(data_+i);
		size_ = new_size;
		this->Resize_for_size(size_);
	}
	
	void TVector::Insert(const int &index, const int &element){
		if(index < 0 || index >= size_){
			std::cerr << "Index out of bound.\n";
			exit(EXIT_FAILURE);
		}
		this->Push(element);
		for(int i=size_-1; i>index; i--){
			int temp = *(data_+i);
			*(data_+i) = *(data_+i-1);
			*(data_+i-1) = temp;
		}
	}
	
	void TVector::Prepend(const int &element){
		if(!size_)
			this->Push(element);
		else
			this->Insert(0, element);
	}
	
	
	void TVector::Debug(){
		std::cout << "Size = " << this->Size() << '\n';
		std::cout << "Capacity = " << this->Capacity() << '\n';
		std::cout << "Elements:\n";
		for(int i=0; i<size_; i++)
			std::cout << "TVector[" << i << "] = " << this->At(i) << '\n';
		std::cout << "-------------------------------------\n";
	}
	
	
	void TVector::Resize_for_size(const int &new_size){
		if(new_size == capacity_ || new_size < capacity_ / SHRINK_RATE){
			int new_capacity = this->Determine_capacity(size_);
			int *new_data = new(data_) int[new_capacity];
			data_ = new_data;
			capacity_ = new_capacity;
		}
	}
	
	int TVector::Determine_capacity(const int &size){
		int actual_capacity = MIN_CAPACITY;
		while(size > actual_capacity / GROWTH_RATE)
			actual_capacity *= GROWTH_RATE;
		return actual_capacity;
	}
}