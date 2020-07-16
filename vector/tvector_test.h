#ifndef PROJECT_CPP_TVECTOR_TESTER_H
#define PROJECT_CPP_TVECTOR_TESTER_H

namespace th{
	class TVectorTester{
	public:
		void RunTests() const;
		void TestSize() const;
		void TestEmpty() const;
		void TestPush() const;
		void TestInsert() const;
		void TestBack() const;
		void TestPrepend() const;
		void TestPop() const;
		void TestDelete() const;
		void TestFind() const;
		void TestRemove() const;
		void VisualTest() const;
	};
}

#endif