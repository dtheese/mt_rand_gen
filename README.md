# Purpose
This program generates pseudorandom numbers in [0, 2^64 - 1]. Configurably, either the smallest and largest numbers seen or only the largest number seen are tracked on an ongoing basis. For each new extreme seen, that number and the total number of pseudorandom numbers generated to reach that extreme are displayed. Other information is displayed as well.

# Credit
In what follows, results regarding expected values are due to Christopher LaSota.

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
- `COUNT_NEW_MAX_AND_NEW_MIN`
- `SCREEN_UPDATE_PERIOD`

These constants are defined in `globals.h`. At the time of this writing, these values are being used:
- `COUNT_NEW_MAX_AND_NEW_MIN = false`
- `SCREEN_UPDATE_PERIOD = 10'000'000'000`

`SCREEN_UPDATE_PERIOD` must be an integral multiple of `GLOBAL_COUNT_FULL_UPDATE_PERIOD`. If it is not, a compilation error will result. This is done since periodic updates will not occur if this condition is not met.

The use of these constants will be described below.

# Program Output
Sample output is as follows:

`total=1,actual_updates=1,expected_updates=1.08,min=18446744073709551615,max=13541851272361631391,max_diff=4904892801347920224,0.00 hours,296/s
total=2,actual_updates=2,expected_updates=1.52,min=18446744073709551615,max=14196032910000926841,max_diff=4250711163708624774,0.00 hours,340/s
total=10,actual_updates=3,expected_updates=2.93,min=18446744073709551615,max=14777746871604456240,max_diff=3668997202105095375,0.00 hours,1683/s
total=12,actual_updates=4,expected_updates=3.10,min=18446744073709551615,max=15641374020574710402,max_diff=2805370053134841213,0.00 hours,1993/s
total=13,actual_updates=5,expected_updates=3.18,min=18446744073709551615,max=17938941541277738491,max_diff=507802532431813124,0.00 hours,2131/s
total=19,actual_updates=6,expected_updates=3.55,min=18446744073709551615,max=18193639630736302552,max_diff=253104442973249063,0.00 hours,3038/s
total=33,actual_updates=7,expected_updates=4.09,min=18446744073709551615,max=18405436519255151650,max_diff=41307554454399965,0.00 hours,5151/s
total=481,actual_updates=8,expected_updates=6.75,min=18446744073709551615,max=18433758881164560284,max_diff=12985192544991331,0.00 hours,74239/s
total=944,actual_updates=9,expected_updates=7.43,min=18446744073709551615,max=18434629981473869795,max_diff=12114092235681820,0.00 hours,143461/s
total=1459,actual_updates=10,expected_updates=7.86,min=18446744073709551615,max=18444570555342846037,max_diff=2173518366705578,0.00 hours,218886/s
total=8153,actual_updates=11,expected_updates=9.58,min=18446744073709551615,max=18446617469720114887,max_diff=126603989436728,0.00 hours,1205054/s
total=19421,actual_updates=12,expected_updates=10.45,min=18446744073709551615,max=18446725051021834416,max_diff=19022687717199,0.00 hours,2762953/s
total=104713,actual_updates=13,expected_updates=12.14,min=18446744073709551615,max=18446734697213757517,max_diff=9376495794098,0.00 hours,14410025/s
total=2993765,actual_updates=14,expected_updates=15.49,min=18446744073709551615,max=18446737073810334134,max_diff=6999899217481,0.00 hours,314930906/s
total=4263945,actual_updates=15,expected_updates=15.84,min=18446744073709551615,max=18446740724958163726,max_diff=3348751387889,0.00 hours,391165544/s
total=10855483,actual_updates=16,expected_updates=16.78,min=18446744073709551615,max=18446742513903531428,max_diff=1559806020187,0.00 hours,692951854/s
total=12329161,actual_updates=17,expected_updates=16.90,min=18446744073709551615,max=18446743584303153037,max_diff=489406398578,0.00 hours,724299767/s
total=52057060,actual_updates=18,expected_updates=18.35,min=18446744073709551615,max=18446744023256234407,max_diff=50453317208,0.00 hours,1288170326/s
total=666046272,actual_updates=19,expected_updates=20.89,min=18446744073709551615,max=18446744041483886553,max_diff=32225665062,0.00 hours,1340260183/s
total=677546510,actual_updates=20,expected_updates=20.91,min=18446744073709551615,max=18446744066748815619,max_diff=6960735996,0.00 hours,1334893473/s
total=828957321,actual_updates=21,expected_updates=21.11,min=18446744073709551615,max=18446744073020775945,max_diff=688775670,0.00 hours,1324807593/s
total=6828495682,actual_updates=22,expected_updates=23.22,min=18446744073709551615,max=18446744073055540612,max_diff=654011003,0.00 hours,1292047666/s
total=19427795670,actual_updates=23,expected_updates=24.27,min=18446744073709551615,max=18446744073471810388,max_diff=237741227,0.00 hours,1286157276/s
total=108055524614,actual_updates=24,expected_updates=25.98,min=18446744073709551615,max=18446744073515374423,max_diff=194177192,0.02 hours,1261061199/s
total=155057614482,actual_updates=25,expected_updates=26.34,min=18446744073709551615,max=18446744073591000149,max_diff=118551466,0.04 hours,1210488271/s`

These comma-separated fields are defined as follows:
- `total`: The total number of pseudorandom numbers generated to reach the most recent new extreme
- `actual_updates`: The total number of new extremes seen. The very first pseudorandom number generated (and only this number) is both a new maximum and a new minimum (new minimums are counted only if `COUNT_NEW_MAX_AND_NEW_MIN = true`). This one-time special case results in the `updates` counter being incremented only by one, not by two.
- `expected_updates`: The expected number of new extremes given `total`. If `n` = `total` pseudorandom numbers have been generated, this expected value is the `n`th harmonic number if `COUNT_NEW_MAX_AND_NEW_MIN = false`. The value of the `n`th harmonic number is estimated using the formula `ln(n) + 0.57721 + 1/(2*n)`. If `COUNT_NEW_MAX_AND_NEW_MIN = true`, this expected value is twice the `n`th harmonic number.
- `min`: The smallest number seen (meaningful only if `COUNT_NEW_MAX_AND_NEW_MIN = true`)
- `max`: The largest number seen
- `max_diff`: (2^64 - 1) - `max` (i.e., how close you've gotten to the largest possible extreme)
- `<unnamed field 1>`: Runtime so far in hours
- `<unnamed field 2>`: The rate at which pseudorandom numbers are being generated per second

When the total number of pseudorandom numbers generated reaches an integral multiple of `SCREEN_UPDATE_PERIOD`, a periodic display update will be made. Specifically, a new line will be displayed with updated values for all fields except `min`,`max`,and `max_diff`. This line will be **overwritten** by the next line printed (whether that next line be due to a new extreme or due to another periodic update). As new extremes become increasingly rare, this feature allows the user to see the current state on a regular basis without causing all of the previous lines showing new extremes to scroll off the screen.
