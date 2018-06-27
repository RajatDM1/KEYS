#include <iostream>
#include<windows.h>
#include "Sec.h"
#include "Base64.h"
#include "Constants.h"
using namespace std;

int main()
{
    //hiding the terminal window
    MSG Msg;
    while(GetMessage(&Msg, NULL, 0,0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return 0;
}
