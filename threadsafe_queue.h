#ifndef THREADSAFE_QUEUE_H
#define THREADSAFE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>


template<typename T>
class threadsafe_queue
{
    public:
        threadsafe_queue();
//        virtual ~threadsafe_queue();
        void push(T new_value);
        void wait_and_pop(T& value);
        std::shared_ptr<T> wait_and_pop();
        bool try_pop(T& value);
        std::shared_ptr<T> try_pop();
        bool empty() const;

    protected:

    private:
        mutable std::mutex mut;
        std::queue<T> data_queue;
        std::condition_variable data_cond;
};
#include "threadsafe_queue.tpp"
#endif // THREADSAFE_QUEUE_H
