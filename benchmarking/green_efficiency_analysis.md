# Analysis of Performance and efficiency

## Measurement Methodology

The mesures come from the output of the three tested programs. For each task, multiple execution has been done to compare execution times. All times are in seconds.

For the task 0, the program execute 100 000 000 iterations for each execution. The time noted are **0,074217 s**, **0,074956 s** and **0,075459 s**. The average is **0,074877 s**.

For the task 1, two implementations has been compared : An "naive" algorithm and a "single-pass" algorithm. Three test has been effected for each versions. The average for the program has been **0,999692 s** and **0,00004633333 s**.

For the task 2, the instrumentation lab mesured the total time and theses three phases : `BUILD_DATA`, `PROCESS` and `REDUCE`. Three tests have been also executed.


## Observed Performance Differences

The task 0 show similar timing, the difference between the lowest and the highest time is **0,001242 s**. On theses three test, the execution time seems pretty stable on the 100 millions iterations.

The difference is more flagrant on task 1. The "naive" one take in average **0,999692 s**, against the single-pass who take **0,00004633333 s** instead. This show that the second implementations is **21 576** times faster.
The three test show this difference, the naive time is between **0,989005 s** and **1,009139 s** and the single-pass is between **0,000035** and **0,000052 s**

For the task 2, the total time is between **0,000360** to **0,000373 s**, with an average of **0,0003647 s**. `BUILD_DATA` takes in average **0,000181 s**, `PROCESS` **0,000133 s** and `REDUCE` takes **0,0000507 s**. The `BUILD_DATA` takes the most times out of the three.

## Relation Between Runtime and Energy Consumption

The results let us compares the execution time, but it don't show actual energy consumption. A short execution time can reduce the time where the computer work, but it doesn't prove by itself that it is proportional to energy consuption. No results about watt usage or energy usage in general is not calculated. As such there is no way to quantify the energy gains.

## Limitations of the Experiment

The test has multiple limits. Firstly, the three execution isn't enough to do reliable test. Furthemore, the test is only done on one computer, and different material could change the timing of the code. Furthemore external parameters can also change how fast the code execute, in example, multiples app executed alongside theses test can make the tests less precise and distort the results. Also, No electrical usage has been registered.

## Practical Engineering Takeaway

The test show that a different algorithm conception can be in a majore executing difference, in the task 1, the single-pass is around **21 576** more fast. The second task show that testing separetly the phases can show which phases take the most time to be executed.
