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

    Time(){}

    Timer(const std::function<void(void)> &f) : funct (f) {}

    Timer(const std::function<void(void)> &f,
        const unsigned long &i,
        const long repeat = Timer::Infinite) : funct (f)
                                                interval(std::chrono::milliseconds(i),
                                                    CallNumber(repeat) {}

    //using this function to start the timer
    void Start(bool async = true)
    {
        if(IsAlive())
            return;
        Alive = true;
        repeat_count = CallNumber;
        if(async)
            Thread = std::thread(ThreadFunc, this);
        else
            this->ThreadFunc();
    }      

    void Stop()
    {
        Alive = false;
        Thread.join();//there will not be concurrent exectuion on one main thread
    }                                          

    void SetFunction(const std::function<void(void)> &f)
    {
        funct = f;
    }

    //finds out if timer is running or not
    bool IsAlive() const {return Alive;}

    //sets the number of repeat instances
    void RepeatCount (const long r)
    {
        if(Alive)
            return;
        CallNumber = r;
    }

    //get how many iterations are left
    long GetLeftCount() const {return repeat_count;}

    long RepeatCount() const {return CallNumber;}

    void SetInterval(const unsigned long &i)
    {
        if(Alive)
            return;
        interval = std::chrono::milliseconds(i);
    }
    
};
#endif // TIMER_H
