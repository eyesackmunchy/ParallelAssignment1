# ParallelAssignment1  
`g++ -std=c++20 -pthread primes.cpp`  
to compile, then  
`.\a`
to execute. Output will get saved to primes.txt in the format  
`<execution time> <total number of primes found> <sum of all primes found> <top ten maximum primes, listed in order from lowest to highest>`   

#### Isaac Munshi is391848 5090407 1/27/2023  
#### COP 4520 Concepts of Parallel and Distributed Processing1/27/2023  

Find all primes from 0 to 10^8. 0 and 1 are not prime.   
Find num of primes, sum of primes, and top 10 biggest primes.  
Runtime for C++ must be below 5 seconds.  

# Proof of Correctness  
## Safety Property  
### Mutual Exclusion  
I divided up the 10^8 workspace linearly, into sections of 10^8/8.   
  The first thread gets indices: [(10^8/8) __* 0__, (10^8/8) __* 1__],  
  The second thread gets indices: [(10^8/8) __* 1__, (10^8/8) __* 2__],  
  ...  
  The eighth and last thread gets indices: [(10^8/8) __* 7__, (10^8/8) __* 8__].  
    
  You may notice that each thread shares an index. For example, the first thread's last index is (10^8/8), and that same index is also the second thread's first index. However, in my program, the sieve loop ensures that the thread only goes UP to the max.   
  line 30 ensures that each thread does not actually access their maximum index.  
  So, in reality, thread one only ACCESSES 0 through (10^8/8)-1, and thread two starts at (10^8/8).  
  `line 30: for (int n = start; (n < end); n++) {`  
  Notice, `(n < end)`. These approaches solve the Mutual Exclusion problem.  
    
    
    
## Liveness Property  
### No Deadlock  
Similarly to the last explanation, each thread operates in it's own space with minimal crossover. The only crossover that could occur is if two or more thread try to operate on the same index in the `primes` array at the same time.  
However, this causes no issue, as the only action any thread can take is to change the value to 0.  
So, if two threads both set the value to 0, the value is set to 0 and no harm is done.  
Futhermore, my approach utilizes no locking-method which can often cause Deadlocks.  
So, all threads are operating and no thread is waiting on another. Thus, there is no Deadlocking.  


    
I understand this is not as efficient, as some secitons have more primes than others, and given more time, I would find a faster approach. My reasoning was that this is my first program with multithreading, my first attempt, and I didn't want to risk anything before the deadline.
(With this linear approach, my program completes with an average of ~3000 ms.)  
    
  
For this program, I followed the Sieve method.  
