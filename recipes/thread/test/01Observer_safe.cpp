#include <memory>
#include <vector>

/*
 * 1. 聚合用weak引用
 * 2. 双向观察者　这种情况还是比较少
 * 3. 遍历的时候　什么情况适合中途 unlock 是个队列时，线程池
 */
class Observable;
// 1
class Observer
{
public:
    virtual ~Observer();
    virtual void update() = 0;

protected:
    Observable *subject_;
};

class Observable
{
public:
    void register_(std::weak_ptr<Observer> x) { observers_.push_back(x); }
    void notifyObservers()
    {
        // lock
        for (auto it = observers_.begin(); it != observers_.end(); ++it) {
            auto obj = it->lock();
            if (obj) {
                obj->update();
            }
        }
    }

private:
    std::vector<std::weak_ptr<Observer>> observers_;
};

class Foo : public Observer
{
public:
    virtual void update() { printf("Foo::update() %p\n", this); }
};

int main()
{
    Observable subject;
    {
        std::shared_ptr<Foo> p(new Foo);
        subject.register_(p);
    }
    subject.notifyObservers();
}