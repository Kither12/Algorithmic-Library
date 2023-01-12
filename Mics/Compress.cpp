template<typename T>
struct Compress{
    vector<int> mp;
    map<T, int> idx;
    Compress(vector<T>& arr){
        int n = arr.size();
        vector<pair<T, int>> pairs;
        mp = vector<int>(n);
        for(int i = 0; i < n; ++i){
            pairs.push_back({arr[i], i});
        }
        sort(pairs.begin(), pairs.end());
        int nxt = 0;
        for(int i = 0; i < n; ++i){
            if(i > 0 && pairs[i - 1].first != pairs[i].first) ++nxt;
            mp[nxt] = pairs[i].first;
            idx[pairs[i].first] = nxt;
            arr[pairs[i].second] = nxt;
        }
    }
};