#include <stdio.h>
#include "my_time.h"


int main(void)
{
    struct utc_time_t now = {10, 25, 17, 29, 2, 2020};
     utc_time  seconds = convert_utc_secs(1970, &now);
     convert_utc_time(1970, &now, seconds);
    utc_to_local_time(&now);
    
    return 0;
}