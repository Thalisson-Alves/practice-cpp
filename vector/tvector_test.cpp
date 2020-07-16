#include "tvector_test.h"

namespace th{
	void TVectorTester::RunTests() const {
		TestSize();
		TestEmpty();
		TestPush();
		TestInsert();
		TestBack();
		TestPrepend();
		TestPop();
		TestDelete();
		TestFind();
		TestRemove();
		VisualTest();
	}
	
	void TVectorTester::TestSize() const {
		TVector vet;
		assert(vet.Size() == 0 && vet.Empty());
		for(int i=0; i<10; i++)
			vet.Push(1);
		assert(vet.Size() == 10);
		vet.Remove(1);
		assert(vet.Size() == 0);
	}
	
	void TVectorTester::TestEmpty() const {
		TVector vet(10);
		assert(!vet.Empty());
		vet.Remove(0);
		assert(vet.Empty());
		TVector vet2;
		assert(vet2.Empty());
	}
	
	void TVectorTester::TestPush() const {
		TVector vet;
		assert(vet.Capacity() == MIN_CAPACITY);
		for(int i=0; i<MIN_CAPACITY; i++){
			vet.Push(i);
			assert(vet.Back() == i);
		}
		assert(vet.Capacity() == MIN_CAPACITY * GROWTH_RATE);
	}
	
	void TVectorTester::TestInsert() const {
		TVector vet(10);
		vet.Insert(2, 111);
		assert(vet.At(2) == 111);
		vet.Insert(5, 14);
		assert(vet.At(5) == 14);
		vet.Insert(9, 7);
		assert(vet.At(9) == 7);
	}
	
	void TVectorTester::TestBack() const {
		TVector vet;
		for(int i=0; i<10; i++){
			vet.Push(i);
			assert(vet.Back() == i);
		}
	}
	
	void TVectorTester::TestPrepend() const {
		TVector vet;
		for(int i=0; i<=MIN_CAPACITY; i++){
			vet.Prepend(i+1);
			assert(vet.At(0) == i+1);
		}
		assert(vet.Capacity() == MIN_CAPACITY * GROWTH_RATE);
	}
	
	void TVectorTester::TestPop() const {
		TVector vet;
		for(int i=0; i<=MIN_CAPACITY; i++)
			vet.Push(i+1);
		assert(vet.Capacity() == MIN_CAPACITY * 2);
		while(vet.Size() > 0)
			assert(vet.Size() == vet.Pop());
		assert(vet.Capacity() == MIN_CAPACITY && vet.Empty());
	}
	
	void TVectorTester::TestDelete() const {
		TVector vet;
		for(int i=0; i<3; i++)
			vet.Push(i+1);
		vet.Delete(1);
		assert(vet.Size() < 3 && vet.At(1) != 2);
	}
	
	void TVectorTester::TestFind() const {
		TVector vet;
		for(int i=0; i<10; i++)
			vet.Push(i);
		assert(vet.Find(10) == -1 && vet.Find(3) == 3);
	}
	
	void TVectorTester::TestRemove() const {
		TVector vet(10, 2);
		for(int i=1; i<=4; i++)
			vet.Push(i+3);
		vet.Remove(2);
		assert(vet.Size() == vet.At(0) && vet.Capacity() == MIN_CAPACITY);
	}
	
	void TVectorTester::VisualTest() const {
		std::cout << "Creating the TVector.\n";
		TVector vet;
		vet.Debug();
		std::cout << vet.Empty() << '\n';
		std::cout << "Pushing " << MIN_CAPACITY << " elements.\n";
		for(int i=0; i<MIN_CAPACITY; i++)
			vet.Push(i+1);
		vet.Debug();
		std::cout << "Inserting the element 111 at index 5.\n";
		vet.Insert(5, 111);
		vet.Debug();
		std::cout << "The last digit is " << vet.Back() << '\n';
		std::cout << "Prepending the value 213.\n";
		vet.Prepend(213);
		vet.Debug();
		std::cout << "Poping the last element wich value is " << vet.Pop() << '\n';
		vet.Debug();
		std::cout << "Deleting the element at index 6.\n";
		vet.Delete(6);
		vet.Debug();
		std::cout << "The index of the element 9 is " << vet.Find(9) << '\n';
		std::cout << "Removing the element 9.\n";
		vet.Remove(9);
		vet.Debug();
		std::cout << "Poping the last element until the size reach 5.\n";
		while(vet.Size() > 5)
			vet.Pop();
		vet.Debug();
	}
}