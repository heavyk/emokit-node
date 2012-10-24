/* Emotic EPOC daemon that decrypt stream using ECB and RIJNDAEL-128 cipher
 * (well, not yet a daemon...)
 * 
 * Usage: epocd (consumer/research) /dev/emotiv/encrypted output_file
 * 
 * Make sure to pick the right type of device, as this determins the key
 * */

#include <stdio.h>
#include <string.h>

#include "emokit/emokit.h"
   

int main(int argc, char **argv)
{
	emokit_device* d;
  
	d = emokit_create();
	printf("Current epoc devices connected: %d\n", emokit_get_count(d, EMOKIT_VID, EMOKIT_PID));
	if(emokit_open(d, EMOKIT_VID, EMOKIT_PID, 0) != 0)
	{
		printf("CANNOT CONNECT\n");
		return 1;
	}
	while(1)
	{
		if(emokit_read_data(d) > 0)
		{
			emokit_get_next_frame(d);
			printf("%4d %4d %4d",
				d->current_frame.battery, d->current_frame.gyroX, d->current_frame.gyroY);
			printf("%5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d %5d\n",
				d->current_frame.F3, d->current_frame.FC6, d->current_frame.P7, d->current_frame.T8, d->current_frame.F7, d->current_frame.F8, d->current_frame.T7, d->current_frame.P8, d->current_frame.AF4, d->current_frame.F4, d->current_frame.AF3, d->current_frame.O2, d->current_frame.O1, d->current_frame.FC5);
			fflush(stdout);
		}
	}

	emokit_close(d);
	emokit_delete(d);
	return 0;
}
