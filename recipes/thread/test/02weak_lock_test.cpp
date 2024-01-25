// weak_ptr::lock example
/* @tldr 
 * 　        auto obj = it->lock();
             if (obj) {obj->update();
                                         }
 * @details shared_ptr<element_type>  ,用来返回一个强引用
 *    1.weak 没过期时，引用系数+1
 *    2. weak 未初始化　返回的是null
 *    3. weak 已过期 返回空
 */
#include <iostream>
#include <memory>
#include "icommon/log/log.h"

void func()
{
    std::shared_ptr<int> sp2;
    std::weak_ptr<int> wp;
    std::shared_ptr<int> sp1;
    // sharing group:
    // --------------

    sp1 = std::make_shared<int>(20); // sp1
    wp = sp1;                        // sp1, wp
    LOG_INFO("wp.use_count() = %ld", wp.use_count());
    LOG_INFO("sp1.use_count() = %ld", sp1.use_count());

    sp2 = wp.lock(); // sp1, wp, sp2
    LOG_INFO("--------------");
    LOG_INFO("wp.use_count() = %ld", wp.use_count());
    LOG_INFO("sp1.use_count() = %ld", sp1.use_count());
    sp1.reset();     //      wp, sp2
    sp1 = wp.lock(); // sp1, wp, sp2
    std::cout << "*sp1: " << *sp1 << '\n';
    std::cout << "*sp2: " << *sp2 << '\n';
}

void tmp()
{
    std::weak_ptr<int> wp;

    {
        // 当wp d已经过期时，返回的value是　
        LOG_INFO("expire:%d", wp.expired());
        std::shared_ptr<int> sp = wp.lock();


        sp = std::make_shared<int>(20);
        wp = sp;
        LOG_INFO("sp.use_count() = %ld", sp.use_count()); // 1
        LOG_INFO("sp:%p  value:%d", sp.get(), *(sp.get())); // 20

    }
    LOG_INFO("expire %d", wp.expired()); // 1
    LOG_INFO("%p", wp.lock().get());
    std::shared_ptr <int> sp = wp.lock();
    if(!sp){
        LOG_INFO("yes");
    }else {
        LOG_ERROR("!!!NO");
    }
}

int main()
{
    tmp();
    return 0;
}


/*
weak_ptr通常用于解决shared_ptr的循环引用问题，其常见的场景包括：

1. 缓存：在缓存中使用weak_ptr可以避免因为缓存持有对象而导致对象无法被释放。当需要访问缓存中的对象时，可以通过lock函数获取一个有效的shared_ptr，
    如果对象已经被释放，则获取到的shared_ptr为空。

2. 观察者模式：这样可以避免观察者持有主题对象导致循环引用，同时通过lock函数可以安全地访问主题对象。  => 被聚合和对象　用weak 

3. 弱回调：在异步编程中，通常会使用回调函数来处理异步操作的结果。当使用shared_ptr来管理回调函数时，为了避免回调函数持有对象导致循环引用，可以使用weak_ptr来传递回调函数。

总之，weak_ptr通常用于解决shared_ptr的循环引用问题，避免对象被持有而无法释放的情况。在这些常见的场景中，weak_ptr可以帮助解决对象生命周期管理的问题，同时避免循环引用导致的内存泄漏。
*/