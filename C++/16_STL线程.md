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

函数不可使用非常量引用。



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



# 2 线程关键词

**并发**：在同一时间段内交替执行多个线程的指令。线程切换时间片很短暂，一个时间片多数时候无法处理完成对某一资源（即内存）的访问。

**同步**：多个线程之间的若干程序片段，因为依赖特定任务的完成，必须按照先后次序来运行。（同步即有序）

**互斥**：指不同线程的程序片段不允许交替执行，或指线程对某一资源的访问（特别是写入资源）具有唯一性和排他性。（访问是无序的）

**线程间通信**：多个线程对同一共享内存数据的访问准确有序。



# 3 互斥

互斥是使不同线程的程序片段不交替运行（最最常见的目的是避免对同一内存资源的并发访问(concurrent access)）。

为了获得独占式的资源访问能力，相应的线程必须**锁定**（lock) mutex。

## 3.1 粗浅低劣的std::mutex

将concurrent access 同步化的一个粗浅做法是引入mutex。如下：

```c++
void mutex_th1(int *val, mutex *mt)
{
	while (true) {
		mt->lock();
		cout << "thread1 val--" << (*val)-- << endl;
		mt->unlock();
		sleep_t(1);
	}
}

void mutex_th2(int *val, mutex* mt)
{
	while (true) {
		mt->lock();
		cout << "thread1 val++" << (*val)++ << endl;
		mt->unlock();
		sleep_t(1);
	}
}

void test_02()
{
	int a = 10;

	mutex mt;

	thread th1(mutex_th1, &a, &mt);
	thread th2(mutex_th2, &a, &mt);

	CTRL_EXIT
	th1.detach();
	th2.detach();
}
```

粗浅的缘由：std::mutex必须成对使用lock和unlock，否则资源可能被永远锁住。正常情况下没问题，但是异常情况下，锁的释放可能变得非常复杂。

**RAII守则**：构造函数获得资源，析构函数释放资源。



## 3.2 std::lock_guard

std::lock_guard是使用了RAII原则的智能锁，类似智能指针。使用方式很简单：

```c++
mutex mt;
std::lock_guard<std::mutex> lockguard(mt); //自动调用mt的lock函数，若lock已被取走，他会阻塞，直到再次获得允许对保护区的访问。
```



## 3.3 std::mutex的尝试性try_lock

程序想要获得一个lock但如果不可能成功的话它不想永远阻塞。此时可使用mutex的try_lock()。

*try_lock()* : 试图取得一个lock，成功返回true。使用时需要对返回结果进行判断。

```c++
std::mutex mt;
//尝试获取lock
while (mt.try_lock() == false) {
    doSomeOtherStuff();
}
//获取到了lock，对一个获取到的lock使用智能锁
std::lock_guard<std::mutex> lg(mt, std::adopt_lock); //std::adopt_lock用于已lock的mutex
```

**如果想给try_lock加个时限，可以使用std::timed_mutex的try_lock_for()**，使用如下：

```c++
std::timed_mutex mt;

if (mt.try_lock_for(std::chrono::seconds(1))) {
    std::lock_guard<std::timed_mutex> lg(mt,std::adopt_lock);
    ...
} else {
    couldNotGetTheLock();
}
//实时需求还可以使用try_lock_until()
```



## 3.4 处理多个lock

```c++
std::mutex m1, m2;
...
{
    std::lock(m1, m2); //如果m1和m2没有全部获取到，就阻塞
    std::lock_guard<std::mutex> lockM1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> lockM2(m2, std::adopt_lock);
    ,,,
}
```

```c++
std::mutex m1, m2;
...
int idx = std::try_lock(m1, m2); //尝试获取两个mutex
if (idx < 0) { //获取所有lock成功时返回-1
    std::lock_guard<std::mutex> lockM1(m1, std::adopt_lock);
    std::lock_guard<std::mutex> lockM2(m2, std::adopt_lock);
} else { //失败时返回第一个失败的lock索引（从0开始计）
    
}
```

**注意**：只调用lock或try_lock而不把那些lock过继（adopt）给一个lock_guard，在离开作用域时不会自动解锁。所以lock、try_lock与lock_guard必须同时使用。



## 3.5 unique_lock

总结一下，我们可以使用mutex来lock或try_lock，或使用timed_mutez来try_lock_for()，并用lock_guard来进行管理。在尝试lock时，是先调用try_lock或try_lock_for()，获取到lock之后再过继给lock_guard。过程比较麻烦。

所以，stl提供了一个更灵活的unique_lock来管理mutex。在构建unique_lock时就指定是否lock，try_lock或try_lock_for,或已lock的mutex。

unique_lock的优点是析构后，能保证mutex没有锁住。

**（1）尝试锁住但不阻塞**

```c++
std::unique_lock<std::mutex> lock(m, std::try_to_lock);
if (lock) {
    ...
}
```

```c++
std::unique_lock<std::timed_mutex> lock(m, std::chrono::sencond(1));
if (lock) {
    
}
```

**（2）尚不打算锁住mutex**

```c++
std::unique_lock<std::mutex> lock(m, std::defer_lock);
...
lock.lock();
...
```



## 3.6 std::once_flag与std::call_once()

对于一个在程序运行期间只需要执行一次的函数（如初始化函数），单线程内，我们的常规做法是：

```c++
bool flag = false;
...
if (!flag) {
    init_once();
    flag = true;
}
```

但是如果多个线程同时在执行，都依赖某一对象初始化，如果使用这种判断共享标识的方法，就需要通过mutex来对concurrent access提供保护。针对这种情况，stl提供了一个方便的办法。

```c++
#include <mutex>

std::once_flag g_flag;

//th1
{
    std::call_once(g_flag, init_once);
}

//th2
{
    std::call_once(g_flag, init_once);
}

//th3
...
//保证了init_once()只被执行一次，且提供了concurrent access保护。
```

即使是单线程内，也可以简化我们的代码：

```c++
//常规方式
void fo()
{
	static bool flag = false;
    if (!flag) {
        ///
        flag = true;
    }
}
//新方式
void fo()
{
    static std::once_flag flag;
    std::call_once(flag, ...);
}
```



# 4 Condition Variable

## 4.1 条件变量产生的背景

在处理**”让一个线程等待另一个线程“**的粗浅办法是使用ready flag之类的东西。这意味着等待中的线程需要poll其所需要的数据或条件是否已达到。

```c++
bool readyFlag;
std::mutex readyFlagMutex;
//
{
    std::unique_lock<std::mutex> ul(readyFlagMutex);
    while (!readyFlag) {
        ul.unclock();
        ...
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ul.lock();
    }
}
```

针对目标条件轮询的缺点在于：waiting thread消耗宝贵的CPU时间重复检验flag，其当它锁住mutex时负责设置ready flag的那个线程会blocked。我们也很难找到合适的sleep周期（该周期控制轮询的间隔）：两次检查若间隔太短则线程仍旧太浪费CPU时间于检查动作上，若太长则也许等待的task已完成而线程却还继续sleeping，导致发生延误。

基于此背景，产生了条件变量，即Condition Variable。



## 4.2 条件变量的使用

- 包含头文件mutex和condition_variable，并各自声明一个需要同步的线程都能访问的变量

  ```c++
  #include <mutex>
  #include <condition_variable>
  std::mutex g_mutex;
  std::condition_variable g_cond_var;
  ```

- 提醒”条件已满足“的线程，调用notify_one或notify_all

  ```c++
  g_cond_var.notify_one;
  //g_cond_var.notify_all;
  ```

- 等待条件被满足的线程，调用wait

  ```c++
  std::unique_lock<std::mutex> lock(g_mutex);
  g_cond_var.wait(lock);
  ```

  

## 4.3 条件变量示例分析

### 4.3.1 变量访问

```c++
#include <mutex>
#include <condition_variable>

bool g_ready_flag = false;
std::mutex g_mutex;
std::condition_variable g_cond_var;

//thread 1
void thread_1()
{
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_ready_flag = true;
    }
    g_cond_var.notify_one(); //因为线程2的唤醒需同时满足锁空闲且notify被调用，所以此处在锁被释放后调用notify
}

//thread 2
void thread_2()
{
    {
        std::unique<std::mutex> lock(g_mutex);
        g_cond_var.wait(lock, [](){return g_ready_flag;});
    }
    //do something else when g_ready_flag is true
}
```

**分析**

线程2需要判断ready flag是否满足条件，满足条件时继续往下执行，否则会进入睡眠，等待线程1的notify唤醒。

线程2首先获取锁，获取到后，调用wait时，在已获得锁的情况下检查条件是否满足（如果已满足则不会有睡眠动作，继续向下执行）。条件不满足，则*释放锁，自身睡眠*，当其他线程*释放了锁且调用了notify*两个条件同时满足时，线程2会再次获取到锁并检查条件是否满足，满足则线程继续向下执行，否则继续释放锁并等待唤醒。



### 4.3.2 多线程Queue

基于*生产者-消费者*程序，多线程队列描述的是多个生产者线程往队列push数据，push完后，notify_one进行通知；消费者程序在队列empty时睡眠并等待生产者的notify唤醒。此类单向同步程序逻辑清楚，很简单。

但考虑到线程2和线程1需要双向同步时（如生产者线程要求队列长度不能过长，否则需睡眠等待；消费者线程要求队列不能为空），问题稍稍复杂，需要仔细。（两个线程中的wait条件不能相同，应该互斥。否则可能出现两个线程同时睡眠的情况）



### 4.3.3 事件驱动系统（event-driven system)

多个consumer必须处理相同数据，则可以调用notify_all。典型的例子是*事件驱动系统*，其事件event必须被发布给所有曾经登录的consumer。

```c++

```

