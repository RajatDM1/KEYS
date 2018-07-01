#ifdef TIMER_H
#define TIMER_R
#include <thread>
#include <chrono>


class Timer
{
    //variable for async execution
    std::thread Thread
    bool Alive = false;
    long CallNumber = -1L;//number of times we'll attempt to call a function
    long repeat_count = -1L;//count the amount of times a function has already been called
    std::chromo::milliseconds interval = std::chrono::milliseconds(0);//interval between function calls
    std::function<void(void)> funct = nullptr;//nullptr- pointer that points to no function

    void SleepAndRun()
    {
        std::this_thread::sleep_for(interval);
        if(Alive)
            Function()();//the second () will execute the function returned by first ()
    }
    void ThreadFunc()
    {
        if(CallNumber == Inifinite)
            while(Alive)
                SleepAndRun();
        else
            while(repeat_count--)
                SleepAndRun();
    }

public:
    static const long Infinite = -1L;
};
#endif // TIMER_H
