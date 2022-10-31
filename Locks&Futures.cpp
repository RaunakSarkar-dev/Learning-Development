#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int v = 1;
void func(int change_v)
{
    static mutex mut;
    unique_lock<mutex> lock(mut);
    //LOCKED
     v = change_v;
     cout << "F: " << v << endl;
    lock.unlock();
    //UNLOCKED
    cout << "G: " << v << endl;
    //AGAIN LOCKED
    lock.lock();
    v = 4;
    cout << "H: " << v << endl;
}

int main()
{
    thread t1(func,3), t2(func,7);
    t1.join();
    t2.join();
    return 0;
}


/////// FUTURE /////////
#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;

int func(int count){
    int sum = 0;
    for (int i = 0; i < count; i++)
        sum+=i;
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    return sum;
}


int main() {
    
    packaged_task<int(int)> task(func);
    future<int> result = task.get_future();
    thread(move(task),10).detach();
    for (int i = 0; i < 20; i++)
        cout << i <<  " " ;
    cout << endl;
   // cout << "Waiting....." << endl;
   // result.wait();
    cout << "Done... " << result.get() << endl;
    return 0;
}





/////// CONDITION VARIABLE /////////
#include <queue>
#include <chrono>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <thread>

using namespace std;
int main(){
    
    queue<int> produce_nums;
    mutex mtx;
    condition_variable cv;
    bool notified = false;
    
    auto producer = [&] () {
        
        for (int i = 0;i<10;i++){
            this_thread::sleep_for(chrono::milliseconds(500));
            unique_lock<mutex> lck(mtx);
            cout << "Producing" << i << endl;
            produce_nums.push(i);
            notified = true;
            cv.notify_all();
        }
    };
    
    
    auto consumer = [&] () {
        
        while(true){
            unique_lock<mutex> lock(mtx);
            while(!notified)  // avoid spurious wakeup
                cv.wait(lock);
        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(1000));
        lock.lock();
        if(!produce_nums.empty())
            {
                cout << "Consuming: " <<this_thread::get_id()<< " : " <<  produce_nums.front() << endl;
                produce_nums.pop();
            }
        notified = false;
        }
    };
    
    thread t1(producer);
    thread cs[2];
    
    for(int i = 0; i<2; i++)
     cs[i] = thread(consumer);
    
    t1.join();
    for(int i = 0; i<2; i++)
     cs[i].join();
    return 0;
}



/////// ATOMIC OPERATION /////////

#include <thread>
#include <iostream>
#include <atomic>

using namespace std;

atomic<int> count = {0};

int main() {
    
    thread t1([&] () {
        count.fetch_add(1);        
    });
    
    thread t2([&](){ 
        
        count++;
        count +=1;
    });
    
    t1.join();
    t2.join();
    
    cout << count << endl;
    return 1;
}



///// MEMORY ORDER /////////

>>> Memory order Relaxed

#include <thread>
#include <iostream>
#include <atomic>
#include <vector>

using namespace std;


int main() {
    atomic<int> count = {0};
    vector<thread> vect;
    for(int i= 0; i<10;i++){
        vect.emplace_back([&]() {count.fetch_add(1,memory_order_relaxed);});
        cout << count << endl;
    }
    
    for (auto&t: vect)
        t.join();
    
    cout <<"FINAL: " << count << endl;
    return 1;
}


//////// REGEX /////////

#include <thread>
#include <iostream>
#include <atomic>
#include <regex>

using namespace std;


int main() {
    
  string fnames[] = {"foo.txt","bar.txt","test","a0.txt","AAA.txt","123.abc"};
  
  regex reg("([a-z]+)\\.txt");
  smatch sm;
  for (const auto&x: fnames)
    if (regex_match(x,sm,reg)){
       /// cout << "Hi" << sm.size();
        if (sm.size()==2)
         {
             string base = sm[1].str();
             cout << "Sub match[0]: " << sm[0].str() << endl;
             cout << x << ": " << base << endl;
         }
    }
    return 1;
}

