#include <iostream>
#include <memory>

using namespace std;

class I {
	public:
		virtual ~I() = default;
		virtual void do_it() = 0;
};

class Top: public I {
	public:
		void do_it() override {
			cout << "Top";
		}
};

class Wrapper: public I {
	public:
		Wrapper(unique_ptr<I> i): m_wrappee{move(i)} {} 

		void do_it() override {
			m_wrappee->do_it();
		}

	private:
		unique_ptr<I> m_wrappee;
};

class X: public Wrapper {
	public:
		X(unique_ptr<I> i): Wrapper(move(i)) {}

		void do_it() override {
			Wrapper::do_it();
			cout << "X";
		}
};

class Y: public Wrapper {
	public:
		Y(unique_ptr<I> i): Wrapper(move(i)) {}

		void do_it() override {
			Wrapper::do_it();
			cout << "Y";
		}
};

int main() {
	unique_ptr<I> decorator = make_unique<Y>(make_unique<X>(make_unique<Top>()));
	decorator->do_it();
	cout << endl;
}
