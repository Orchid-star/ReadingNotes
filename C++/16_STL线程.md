# STL线程

# 1 线程的创建与启动

**关键点**

- 线程std::thread创建时会立即启动
- 启动线程后，必须有对join或detach的调用（否则会导致运行出错）。join会阻塞创建线程的主线程代码运行，直至线程结束。detach使进程在后台进行，对创建线程的主线程无影响。

## 1.1 线程执行函数

情况1：函数参数列表为空

情况2：函数参数列表不为空

```c++
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <iostream>

using namespace std;

const int cout_times = 3;
const chrono::seconds seconds(1);
#define sleep_t(t) std::this_thread::sleep_for(t * seconds)

void func_th1() {
	for (int i = 0; i < cout_times; ++i) {
		cout << "func_th1" << endl;
		sleep_t(1);
	}
}

void func_th2(int thread_index, string info = "child thread") {
	for (int i = 0; i < cout_times; ++i) {
		cout << "thread:" << thread_index << " info:" << info << endl;
		sleep_t(2);
	}
}

void test_build_thread()
{
	thread th1(func_th1);
	thread th2(func_th2, 10, "child_thread");

	th1.join();
	th2.join();
}
```

**结论**

thread的创建可以根据函数的*形参列表*携带不定个数的参数。*即使函数的参数列表中有参数携带了默认值，在创建线程执行此函数时也必须指定该参数的值*。（容易理解，因为使用的是模板）



## 1.2 线程执行类或类函数

类示例代码：

```c++
class CA {
public:
	CA() {}
	
	void class_func1(int thread_index, string info = "child thread") {
		for (int i = 0; i < cout_times; ++i) {
			cout << "thread:" << thread_index << " info:" << info << endl;
			sleep_t(1);
		}
	}
	
	static void static_class_func1(int thread_index, string info = "child thread") {
		CA a;
		a.class_func1(thread_index, info);
	}
};
```

### 1.2.1 执行类静态函数

**创建线程执行类的静态函数与执行普通函数无异**。

```c++
void test_build_thread()
{
	thread th3(&CA::static_class_func1, 11, "class static functin in thread");

	th3.join();
}
```

### 1.2.2 执行类对象的普通公共函数

```c++
void test_build_thread()
{
	CA ca;
	thread th4(&CA::class_func1, &ca, 12, "public function");

	th4.join();
}
```



