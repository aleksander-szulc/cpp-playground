#include <iostream>
#include <thread>

class A {
public:
	A(std::string n) : name(n) {
		std::cout << "Constructor!" << name << std::endl;
		alive = true;
		loop = std::thread(&A::Loop, this);
	}
	~A() {
		std::cout << "Destructor! " << name << std::endl;
		alive = false;
		if (loop.joinable()) {
			loop.join();
			std::cout << "Joined thread" << std::endl;
		}
	}

	void Loop() {
		while (alive) {
			std::cout << "Ping! " << name << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	std::atomic<bool> alive;
	std::string name;
	std::thread loop;
};

void Foo() {
	std::cout << "Foo() start" << std::endl;
	static A s("static obj");
	A b("regular obj");
	std::cout << "Foo() end" << std::endl;
}

int main() {
	Foo();
	Foo();
	std::string x;
	std::cin >> x;
	std::cout << "Koniec: " << x << std::endl;
}
