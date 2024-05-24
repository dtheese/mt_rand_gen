# Purpose
This program generates pseudorandom numbers in [0, 2^64 - 1]. The smallest and largest numbers seen are tracked on an ongoing basis. For each new extreme seen, that number and the total number of pseudorandom numbers generated to reach that extreme are displayed. Other information is displayed as well.

# Building the Program
To build the program from C++ source, execute the Bash script named `build`. The generated executable will have the same name as the directory it is built in.

The Bash script `clean` may be used to delete the executable and any file containing the program's output (such a file is created only if running the program in the background (described below)).

# Executing the Program
## Foreground
The program is normally run in the foreground simply by executing it directly.

## Background, Disconnected from the Terminal
If an extended run is desired and if you wish to protect against the possibility of the program getting killed if your shell session disconnects, you may start the program by running the Bash script `startup`. This will start the program in the background and detach it from your terminal. Output is sent to a file. After launching the program and before exiting, the `startup` script provides instructions on how to monitor the program's output in real time.

If `startup` is run a second time, the first instance will be killed before starting the new instance.

If the program is started in this manner, it may later be stopped by executing the Bash script `stop`.

Be aware that if the program is started in the background and if another instance is then started in the foreground without using `stop` to kill the background instance, two instances will be running and each will get only roughly half of the total available CPU cycles.

# Constants Referenced
In what follows, the following constants are referenced:
- `GLOBAL_COUNT_UPDATE_PERIOD`
- `SCREEN_UPDATE_PERIOD`

These constants are defined in `globals.h`. At the time of this writing, these values are being used:
- `GLOBAL_COUNT_UPDATE_PERIOD = 1000`
- `SCREEN_UPDATE_PERIOD = 10'000'000'000`

The use of these constants will be described below.

# Program Output
An example line of output is as follows:

`updates=37,total=12963624000,min=795692199,max=18446744070293615421,max_diff=3415936194,0.00 hours,1284934929/s`

These comma-separated fields are defined as follows:
- `updates`: The total number of new extremes (max or min) seen. The very first pseudorandom number generated (and only this number) is both a new max and a new min. This one-time special case results in the `updates` counter being incremented only by one, not by two.
- `total`: The total number of pseudorandom numbers generated to reach the most recent new extreme. For reasons described below, this is rounded up to the nearest integral multiple of `GLOBAL_COUNT_UPDATE_PERIOD`.
- `min`: The smallest number seen
- `max`: The largest number seen
- `max_diff`: (2^64 - 1) - `max` (i.e., how close you've gotten to the largest possible extreme)
- `<unnamed field 1>`: Runtime so far in hours
- `<unnamed field 2>`: The rate at which pseudorandom numbers are being generated per second

When the total number of pseudorandom numbers generated reaches an integral multiple of `SCREEN_UPDATE_PERIOD`, a periodic display update will be made. Specifically, a new line will be displayed with updated values for `total`, `<unnamed field 1>`, and `<unnamed field 2>`. This line will be **overwritten** by the next line printed (whether that next line be due to a new extreme or due to another periodic update). As new extremes become increasingly rare, this feature allows the user to see the current state on a regular basis without causing all of the previous lines showing new extremes to scroll off the screen.

# Multithreading and its Consequences
This program is  multithreaded and will use however many threads your machine's hardware will support. This was done to generate numbers at the highest rate possible.

The problem this multithreading introduces is that the counter of pseudorandom numbers generated is shared among threads and must therefore be protected with a mutex. Locking / unlocking this mutex for every single number generated slows things down drastically. So, each thread generates `GLOBAL_COUNT_UPDATE_PERIOD` pseudorandom numbers at a time before updating the counter. Therefore, the total count of numbers generated that's displayed is rounded up to the nearest integral multiple of `GLOBAL_COUNT_UPDATE_PERIOD`. This ruins the count data for early extremes but quickly becomes insignificant.
