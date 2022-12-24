template<const int N>
struct Fenwick{
    long long tree[N + 5];
    void update(int u, int v){
        for(int i = u; i <= N; i += i & -i){
            bit[i] += v; 
        }
    }
    long long get(int u){
        long long res = 0;
        for(int i = u; i > 0; i -= i & -i){
            res += bit[i];
        }
        return res;
    }
    long long get(int l, int r){
        return get(r) - get(l - 1);
    }
};