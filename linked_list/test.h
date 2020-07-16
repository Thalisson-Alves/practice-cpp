#include <assert.h>

#ifndef __TEST__
#define __TEST__

namespace th
{
	class Tester{
	public:
		void run_tests() const {
			test_size();
			test_push_front();
			test_empty();
			test_empty();
			test_front();
			test_back();
			test_pop_front();
			test_push_back();
			test_pop_back();
			test_value_at();
			test_insert();
			test_erase();
			test_value_n_from_end();
			test_reverse();
			test_remove();
		}
		
		void test_size() const {
			th::LinkedList<int> list;
			assert(list.size() == 0);
			list.push_front(1);
			assert(list.size() == 1);
			th::LinkedList<float> list2(10.5f);
			assert(list2.size() == 1);
			th::SingleNode<double> *node = new SingleNode<double>;
			node->data_ = 19.0;
			node->next_ = NULL;
			th::LinkedList<double> list3(20.0, node);
			assert(list3.size() == 2);
			delete node;
		}
		
		void test_push_front() const {
			th::LinkedList<int> list;
			assert(list.size() == 0);
			list.push_front(1);
			assert(list.size() == 1);
			th::LinkedList<float> list2(10.5f);
			list2.push_front(10.87f);
			assert(list2.size() == 2);
			th::SingleNode<double> *node = new SingleNode<double>;
			node->data_ = 19.0;
			node->next_ = NULL;
			th::LinkedList<double> list3(20.0, node);
			list3.push_front(21.2);
			assert(list3.size() == 3);
			delete node;
			
		}
		
		void test_empty() const {
			th::LinkedList<int> list;
			assert(list.empty());
			
			list.push_front(1);
			assert(!list.empty());
			
			list.pop_front();
			assert(list.empty());
		}
		
		void test_front() const {
			th::LinkedList<int> list(3);
			assert(list.front() == 3);
			
			list.push_front(9);
			assert(list.front() == 9);
			
			list.push_back(15);
			assert(list.front() == 9);
		}
		
		void test_back() const {
			th::LinkedList<int> list;
			list.push_front(3);
			assert(list.back() == 3);
			
			list.push_back(20);
			assert(list.back() == 20);
		}
		
		void test_pop_front() const {
			th::LinkedList<int> list;
			list.push_back(9);
			assert(list.front() == 9);
			
			list.push_front(1);
			assert(list.size() == 2);
			
			list.pop_front();
			assert(list.front() == 9);
			
			list.pop_front();
			assert(list.empty());
		}
		
		void test_push_back() const {
			th::LinkedList<int> list;
			list.push_back(9);
			assert(list.front() == 9);
			
			list.push_back(1);
			assert(list.size() == 2);
			
			list.push_back(10);
			assert(list.size() == 3 && list.back() == 10);
		}
		
		void test_pop_back() const {
			th::LinkedList<int> list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			list.push_back(4);
			assert(list.back() == 4);
			assert(list.size() == 5);
			
			list.pop_back();
			assert(list.size() == 4);
			
			list.pop_back();
			assert(list.back() == 3);
			
			list.pop_back();
			list.pop_back();
			list.pop_back();
			assert(list.empty());
		}
		
		void test_value_at() const {
			th::LinkedList<int> list;
			list.push_back(9);
			list.push_back(99);
			list.push_back(999);
			
			assert(list.at(0) == 9);
			assert(list.at(1) == 99);
			assert(list.at(2) == 999);
		}
		
		void test_insert() const {
			th::LinkedList<int> list;
			list.push_front(2);
			list.insert(0, 1);
			assert(list.size() == 2);
			assert(list.at(0) == 1);
			
			list.insert(1, 3);
			list.insert(1, 4);
			assert(list.size() == 4);
			assert(list.at(0) == 1);
			assert(list.at(1) == 4);
			assert(list.at(2) == 3);
			assert(list.at(3) == 2);
		}
		
		void test_erase() const {
			th::LinkedList<int> list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			
			list.erase(0);
			assert(list.at(0) == 2 && list.size() == 3);
			
			list.erase(2);
			assert(list.at(1) == 3 && list.size() == 2);
			
			list.push_back(10);
			list.erase(1);
			assert(list.at(1) == 10);
			
			list.erase(0);
			list.erase(0);
			assert(list.empty());
		}
		
		void test_value_n_from_end() const {
			th::LinkedList<int> list;
			list.push_back(2);
			assert(list.n_from_end(1) == 2);
			list.push_back(3);
			assert(list.n_from_end(1) == 3);
			list.push_back(4);
			list.push_front(1);
			
			assert(list.n_from_end(1) == 4);
			assert(list.n_from_end(2) == 3);
			assert(list.n_from_end(3) == 2);
			assert(list.n_from_end(4) == 1);
		}
		
		void test_reverse() const {
			th::LinkedList<int> list;
			list.reverse();
			list.push_front(1);
			list.reverse();
			list.push_front(2);
			list.push_front(3);
			list.push_front(4);
			list.push_front(5);
			
			list.reverse();
			assert(list.at(0) == 1);
			assert(list.at(1) == 2);
			assert(list.at(2) == 3);
			assert(list.at(3) == 4);
			assert(list.at(4) == 5);
		}
		
		void test_remove() const {
			th::LinkedList<char> list;
			list.push_front('a');
			list.push_front('b');
			list.push_front('c');
			list.push_front('b');
			
			list.remove('b');
			assert(list.size() == 3);
			assert(list.at(1) == 'b');
			assert(list.at(2) == 'a');
			
			list.remove('b');
			assert(list.size() == 2);
			list.remove('z');
			assert(list.size() == 2);
			
			list.remove('a');
			list.remove('c');
			
			assert(list.empty());
		}
	};
}

#endif