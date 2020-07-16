#ifndef PROJECT_CPP_TVECTOR_H
#define PROJECT_CPP_TVECTOR_H

namespace th
{
	static const int MIN_CAPACITY = 16;
	static const int GROWTH_RATE = 2;
	static const int SHRINK_RATE = 4;
	
	class TVector{
	public:
		int& operator[](int);
		void operator=(TVector&);
	
		TVector();
		TVector(const int&, const int&);
		TVector(TVector&);
		~TVector();
		
		int Back();
		int Front();
		int At(const int&);
		int Find(const int&);
		
		int Size();
		int Capacity();
		bool Empty();
		
		void Push(const int&);
		int Pop();
		void Delete(const int&);
		void Remove(const int&);
		void Insert(const int&, const int&);
		void Prepend(const int&);
		
		void Debug();
		
	private:
		int size_;
		int capacity_;
		int* data_;
		
		void Resize_for_size(const int&);
		int Determine_capacity(const int&);
	};
}

#endif