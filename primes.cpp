// Find all primes between 1 and 10^8
//     1 is not prime, 2 is
//     spawn 8 threads
//     equivalent work among threads
//     AT MOST 15 seconds
//     Goal: 5-10 seconds

#include <iostream>

// for square root
#include <cmath>

// For Input/output files
#include <fstream>

// for threads
#include <thread>

#include <vector>
using namespace std;

const int MAX = pow(10,8);


void sieve(vector <int> &primes, int start, int end) {
    //remember for 'primes', 
    // 1 = prime, 0 = composite

    //(n*n <= MAX) &&
    for (int n = start; (n < end); n++) {
        
        if (primes[n] == 1)
            for (int j = n*n; j <= MAX; j+=n) // increment by n
                primes[j] = 0;
    }
}





/*bool isPrime(int n) {
    if (n < 2)
        return false;

    if (n == 2)
        return true;
    
    if (n % 2 == 0)
        return false;
    
    // increment by 2 to stay on the odd numbers ( because we already checked for mod 2 )
    // and stop once i is the square root of n
    for (int i = 3; i <= sqrt(n); i+=2) 
        if (n % i == 0) 
            return false;
        
    return true;
}*/






int main()
{

    //int MAX = pow(10,8);
    // make an array for primes where 
    // 1 = PRIME, 0 = not prime/composite
    vector<int> primes(MAX + 1, 1);
    clock_t start, end;
    start = clock();
    // Start of program - start clock
    

    //cout << "Hello World TESTING\n g++ -std=c++20 -pthread test.cpp then do .\\a" << endl;

    
    primes[0] = primes[1] = 0; // not prime
    //primes[2] = 1; // prime!

    //vector <int> &primes, int start, int end

    int sqrtMAX = int(sqrt(MAX));
    int sqrtMAXdiv8 = int(sqrtMAX/8);

    vector<thread> threads;
    for (int i = 0; i < 8; i++) 
        //vector <int> &primes, int start, int end
        threads.emplace_back(sieve, ref(primes), sqrtMAXdiv8*i, sqrtMAXdiv8*(i+1));
    
    vector<thread> joinThreads = move(threads);

     for (thread &th : joinThreads) {
        th.join();
    }



/*
    thread th1(sieve, primes, 2, sqrtMAXdiv8);
    thread th2(sieve, primes, sqrtMAXdiv8, sqrtMAXdiv8*2);
    thread th3(sieve, primes, sqrtMAXdiv8*2, sqrtMAXdiv8*3);
    thread th4(sieve, primes, sqrtMAXdiv8*3, sqrtMAXdiv8*4);
    thread th5(sieve, primes, sqrtMAXdiv8*4, sqrtMAXdiv8*5);
    thread th6(sieve, primes, sqrtMAXdiv8*5, sqrtMAXdiv8*6);
    thread th7(sieve, primes, sqrtMAXdiv8*6, sqrtMAXdiv8*7);
    thread th8(sieve, primes, sqrtMAXdiv8*7, sqrtMAXdiv8*8);
*/







    // End of program - stop clock
    end = clock();

    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

    //cout << "hi1" << endl;
    
    uint64_t primesLength = primes.size();
    uint64_t sumPrimes = 0;
    uint64_t numPrimes = 0;

    //cout << "hi2" << endl;

    for (uint64_t l = 0; l < primesLength; l++)
        if (primes[l] == 1) {
            numPrimes++;
            sumPrimes += l;
        }

    //cout << "hi3" << endl;

    uint64_t top10[10] = {0};

    //cout << "h4" << endl;

    /*uint64_t l2 = primesLength;
    top10[0] = l2;
    cout << l2 << endl;
    cout << top10[0] << endl;*/

    int index = 0;
    for (uint64_t l = primesLength-1; l >= 0; l--) {
        if (primes[l] == 1){
            top10[index] = l;
            index += 1;
        }
        if (index == 10)
            break;
    } 

    //cout << "hi5" << endl;

    string top10s = "";
    for (int i = 0; i < 10; i++)
        top10s = to_string(top10[i]) + " " + top10s;

    //cout << "hi6" << endl;

    ofstream myfile;
    myfile.open ("primes.txt");
    myfile << "<" << time_taken * 1000 << "ms> <" << numPrimes << "> <" << sumPrimes << "> <" << top10s << ">";
    myfile.close();

    //cout << "hi7" << endl;

    //cout << "Time taken by program is : " << time_taken * 1000 << " ms " << endl;
    //cout << "Time taken by program is : " << time_taken << " sec " << endl;

}

