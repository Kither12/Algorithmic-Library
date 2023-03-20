/*
 van Emde Boas Tree structure for holding a set of integers in a given universe.
 Complexity:    O(1) for min, max and first
                O(log log u) for member, insert, delete, pred, succ, extractMin and decreaseKey
*/

struct vEB
{
    unsigned long long u;
    
    unsigned long long *m, *M;
    vEB *summary;   // used if u != 2
    vEB **cluster;  // used if u != 2
    
public:
    vEB(unsigned long long);
    
    bool member(unsigned long long);
    void insert(unsigned long long);
    void Delete(unsigned long long);
    unsigned long long min();
    unsigned long long max();
    unsigned long long* pred(unsigned long long);
    unsigned long long* succ(unsigned long long);
    
    unsigned long long extractMin();
    unsigned long long first();
    void decreaseKey(unsigned long long, unsigned long long);
};

vEB::vEB(unsigned long long u)
{
    this -> u = u;
    this -> m = NULL;
    this -> M = NULL;
    
    if (u == 2)
    {
        this -> summary = NULL;
        this -> cluster = NULL;
    }
    
    else
    {
        unsigned long long subSize = (unsigned long long)sqrt(u);
        this -> summary = new vEB(subSize);
        this -> cluster = new vEB*[subSize];
    }
}

bool vEB::member(unsigned long long x)
{
    if (u == 2)
    {
        if (m == NULL) return false;
        if (x == 0) return ((*m) == 0);
        else if (x == 1) return ((*M) == 1);
        return false;
    }
    else
    {
        if (m == NULL) return false;
        if (x < (*m) || x > (*M)) return false;
        else if (x == (*m) || (x == (*M))) return true;
        else
        {
            unsigned long long subSize = (unsigned long long)sqrt(u);
            unsigned long long hi = x / subSize, lo = x % subSize;
            if (cluster[hi] == NULL) return false;
            else return cluster[hi] -> member(lo);
        }

    }
}

void vEB::insert(unsigned long long x)
{
    if (u == 2)
    {
        if (x == 0)
        {
            if (m == NULL)
            {
                m = new unsigned long long;
                M = new unsigned long long;
                (*m) = (*M) = x;
            }
            else (*m) = x;
        }
        else if (x == 1)
        {
            if (M == NULL)
            {
                m = new unsigned long long;
                M = new unsigned long long;
                (*m) = (*M) = x;
            }
            else (*M) = x;
        }
    }
    else
    {
        if (m == NULL)
        {
            m = new unsigned long long;
            M = new unsigned long long;
            (*m) = (*M) = x;
        }
        else
        {
            if (x < (*m))
            {
                unsigned long long currMin = (*m);
                (*m) = x;
                this -> insert(currMin);
            }
            else
            {
                unsigned long long subSize = (unsigned long long)sqrt(u);
                unsigned long long hi = x / subSize, lo = x % subSize;
                if (cluster[hi] == NULL)
                {
                    cluster[hi] = new vEB(subSize);
                    cluster[hi] -> insert(lo);
                    summary -> insert(hi);
                }
                else cluster[hi] -> insert(lo);
                
                if (x > (*M)) (*M) = x;
            }
        }
    }
}

void vEB::Delete(unsigned long long x)
{
    if (u == 2)
    {
        if (x == 0)
        {
            if ((*M) == 0)
            {
                m = M = NULL;
            }
            else (*m) = 1;
        }
        else if (x == 1)
        {
            if ((*m) == 1)
            {
                m = M = NULL;
            }
            else (*M) = 0;
        }
    }
    else
    {
        unsigned long long subSize = (unsigned long long)sqrt(u);
        unsigned long long hi = x / subSize, lo = x % subSize;
        
        if (x == (*m))
        {
            if (x == (*M))
            {
                m = M = NULL;
            }
            else
            {
                unsigned long long nextMinHi = summary -> min();
                unsigned long long nextMinLo = cluster[summary -> min()] -> min();
                unsigned long long nextMin = nextMinHi * subSize + nextMinLo;
                this -> Delete(nextMin);
                (*m) = nextMin;
            }
        }
        else
        {
            cluster[hi] -> Delete(lo);
            if (cluster[hi] -> m == NULL)
            {
                summary -> Delete(hi);
                delete cluster[hi];
                cluster[hi] = NULL;
            }
            if (x == (*M))
            {
                if (summary -> m == NULL) (*M) = (*m);
                else
                {
                    unsigned long long nextMaxHi = summary -> max();
                    unsigned long long nextMaxLo = cluster[summary -> max()] -> max();
                    (*M) = nextMaxHi * subSize + nextMaxLo;
                }
            }
        }
    }
}

unsigned long long vEB::min()
{
    return (*m);
}

unsigned long long vEB::max()
{
    return (*M);
}

unsigned long long* vEB::pred(unsigned long long x)
{
    if (u == 2)
    {
        if (x == 0) return NULL;
        else if (x == 1)
        {
            if (m == NULL) return NULL;
            if ((*m) == 1) return NULL;
            return m;
        }
        else return NULL;
    }
    else
    {
        if (m == NULL) return NULL;
        if (x <= (*m)) return NULL;
        if (x > (*M)) return M;
        unsigned long long subSize = (unsigned long long)sqrt(u);
        unsigned long long hi = x / subSize;
        unsigned long long lo = x % subSize;
        if (cluster[hi] == NULL)
        {
            unsigned long long* prev = summary -> pred(hi);
            unsigned long long* ret = new unsigned long long;
            (*ret) = (*prev) * subSize + cluster[(*prev)] -> max();
            return ret;
        }
        else
        {
            unsigned long long *newLo, *newHi;
            newHi = new unsigned long long;
            newLo = new unsigned long long;
            (*newHi) = hi;
            unsigned long long minInCluster = cluster[hi] -> min();
            if (lo > minInCluster) newLo = cluster[hi] -> pred(lo);
            else
            {
                newHi = summary -> pred(hi);
                (*newLo) = cluster[(*newHi)] -> max();
            }
            unsigned long long *ret = new unsigned long long;
            (*ret) = (*newHi) * subSize + (*newLo);
            return ret;
        }
    }
}

unsigned long long* vEB::succ(unsigned long long x)
{
    if (u == 2)
    {
        if (x == 1) return NULL;
        else if (x == 0)
        {
            if (M == NULL) return NULL;
            if ((*M) == 0) return NULL;
            return M;
        }
        else return NULL;
    }
    else
    {
        if (m == NULL) return NULL;
        if (x >= (*M)) return NULL;
        if (x < (*m)) return m;
        unsigned long long subSize = (unsigned long long)sqrt(u);
        unsigned long long hi = x / subSize;
        unsigned long long lo = x % subSize;
        if (cluster[hi] == NULL)
        {
            unsigned long long* next = summary -> succ(hi);
            unsigned long long* ret = new unsigned long long;
            (*ret) = (*next) * subSize + cluster[(*next)] -> min();
            return ret;
        }
        else
        {
            unsigned long long *newLo, *newHi;
            newHi = new unsigned long long;
            newLo = new unsigned long long;
            (*newHi) = hi;
            unsigned long long maxInCluster = cluster[hi] -> max();
            if (lo < maxInCluster) newLo = cluster[hi] -> succ(lo);
            else
            {
                newHi = summary -> succ(hi);
                (*newLo) = cluster[(*newHi)] -> min();
            }
            unsigned long long *ret = new unsigned long long;
            (*ret) = (*newHi) * subSize + (*newLo);
            return ret;
        }
    }
}

unsigned long long vEB::extractMin()
{
    unsigned long long ret = this -> min();
    this -> Delete(ret);
    return ret;
}

unsigned long long vEB::first()
{
    return this -> min();
}

void vEB::decreaseKey(unsigned long long x, unsigned long long y)
{
    // Preconditions: y < x, x is in the tree, y is not in the tree
    
    this -> Delete(x);
    this -> insert(y);
}
