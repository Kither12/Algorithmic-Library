template<const int N>
struct SegmentTree{
    struct node{
        node(){}
    } tree[4 * N];

    node combine(const node &left, const node &right){
        node com;
        return com;
    }

    void build(int index, int l, int r){
        if(l == r){
            return;
        }
        int mid = (l + r) / 2;
        build(index * 2, l, mid);
        build(index * 2 + 1, mid + 1, r);
        tree[index] = combine(tree[index * 2], tree[index * 2 + 1]);
    }
    void update_lazy(int index, int l, int r){
        if(l == r) return;
    }
    void update(int index, int l, int r, int u, int v){
        update_lazy(index, l, r);
        if(u > r || v < l) return;
        if(l >= u && r <= v){
            return;
        }
        int mid = (l + r) / 2;
        update(index * 2, l, mid, u, v);
        update(index * 2 + 1, mid + 1, r, u, v);
        tree[index] = combine(tree[index * 2], tree[index * 2 + 1]);
    }
    void update_point(int index, int l, int r, int u){
        update_lazy(index, l, r);
        if(u < l || u > r) return;
        if(l == r){
            return;
        }
        int mid = (l + r) / 2;
        update_point(index * 2, l, mid, u);
        update_point(index * 2 + 1, mid + 1, r, u);
        tree[index] = combine(tree[index * 2], tree[index * 2 + 1]);
    }
    void query(int index, int l, int r, int u, int v){
        update_lazy(index, l, r);
        if(u > r || v < l) return;
        if(l >= u && r <= v){
            return;
        }
        int mid = (l + r) / 2;
        query(index * 2, l, mid, u, v);
        query(index * 2 + 1, mid + 1, r, u, v);
    }
};