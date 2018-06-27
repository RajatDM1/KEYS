#ifndef SEC_H
#define SEC_H

#include <string>
#include <ctime>
#include <sstream>
#include <fstream>

//using this function to create strings form any type of data
namespace Sec{
    template <class T>
    std::string ToString(const T &);

    struct DateTime
    {
        //constructor
        DateTime()
        {
            time_t ms;//time_t is a type located in ctime library
            time (&ms);//function of ctime library that takes time from system and copies in ms variable
            struct tm *info = localtime(&ms);

            D=info->tm_mday;
            m = info->tm_mon +1;//adding 1 as month starts from 0
            y = 1900+ info->tm_year;
            M= info->tm_min;
            H = info->tm_hour;
            S = info->tm_sec;
        }
        //DateTime(int D, int m, int y, int M, int H, int S) : D{D}, m{m}, y{y}, M{M}, H{H}, S{S} {}
        DateTime(int D, int m, int y, int M, int H, int S) : D(D), m(m), y(y), M(M), H(H), S(S) {}
        //DateTime(int D, int m, int y) : D{D}, m{m}, y{y}, H{0}, M{0}, S{0} {}
        DateTime(int D, int m, int y) : D(D), m(m), y(y), M(0), H(0), S(0) {}


        DateTime Now() const
        {
            return DateTime();
        }
        int D, m, y, M, H, S;

        //returning the date in the format DD.mm.YYYY
        std::string GetDateString() const
        {
            return std::string(D<10?"0":"")+ToString(D)+
                    std::string(m<10?".0":".") + ToString(m)+"."+
                    ToString(y);
        }

        //returns time in format HH:MM:SS
        std::string GetTimeString(const std::string &sep= ":") const
        {
            return std::string(H<10?"0":"")+ToString(H)+sep+
                    std::string(M<10?"0":"")+ToString(M)+sep+
                    std::string(S<10?sep:"")+ToString(S);
        }

        std::string GetDateTimeString(const std::string &sep=":") const
        {
            return GetDateString()+ " "+ GetTimeString(sep);
        }
    };

    template <class T>

    std::string ToString(const T &e)
    {
        std::ostringstream s;//variable of type output string stream
        s << e;
        return s.str();
    }

    void WriteAppLog( const std::string &s)
    {
        //ios - InputOutputStream app- Appends
        std::ofstream file("AppLog.txt", std::ios::app);
        file<< "[" << Sec::DateTime().GetDateTimeString()<<"]"<<
        "\n"<<s<<std::endl<<"\n";
        file.close();
    }
}






#endif // SEC_H
