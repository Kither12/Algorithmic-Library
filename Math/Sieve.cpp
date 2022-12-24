struct Sieve{
    int N = 1e7;
    vector<int> minFactor;
    vector<uint> prime;

    Sieve(){
        minFactor = vector<int>(N + 5);
        Compute();
 }
    void Compute(){
        for(int i=2; i <= N; ++i){
            if (minFactor[i] == 0) {
                minFactor[i] = i;
                prime.push_back(i);
            }
            for (int j=0; j < (int)prime.size() && prime[j] <= minFactor[i] && i*prime[j] <= N; ++j) {
                minFactor[i * prime[j]] = prime[j];
            }
        }
    }
    vector<int> factorize(int n) {
        vector<int> res;
        while (n != 1) {
            res.push_back(minFactor[n]);
               int temp = minFactor[n];
               while(n % temp == 0) n /= temp;
        }
        return res;
    }
};