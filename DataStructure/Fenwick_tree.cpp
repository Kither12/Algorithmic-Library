template<typename T>
struct Fenwick{
    vector<T> tree;
    int n;
    Fenwick(int n) : n(n), tree(n + 5, 0){
    }
    void update(int u, T v){
        for(int i = u; i <= n; i += i & -i){
            tree[i] += v; 
        }
    }
    T get(int u){
        T res = 0;
        for(int i = u; i > 0; i -= i & -i){
            res += tree[i];
        }
        return res;
    }
    T get(int l, int r){
        return get(r) - get(l - 1);
    }
};