#include "../template.h"

#define TREAP_FUNCTION //okresla czy potrzebna jest funkcja na przedziale (np. suma)
struct treap
{
    typedef int T;
    
    treap *left = nullptr, *right = nullptr;
    static const T eps = 1;
    
    int rank;
    T value;
    
    treap(T val = T()) : value(val), rank(rand()) { recalc(); }
    
#ifdef TREAP_FUNCTION
    inline static T f(T a, T b) //na przyklad suma
    {
        return a + b;
    }
    inline T single()
    {
        return 1; //dla liczby elementow na przedziale
        //return value; //dla sumy wartosci na przedziale
    }
    T fval;
    static const T defval = 0; //dla pustego przedzialu
    
    inline void recalc()
    {
        fval = f(f(left ? left->fval : defval, single()), right ? right->fval : defval);
    }
#else
    inline void recalc() { }
#endif

    inline static bool cmp(const T &a, const T &b)
    {
        return a < b;
    }
};

pair<treap*, treap*> split(treap *t, treap::T val) //dzieli na czesc < val oraz >= val
{
    if(!t) return make_pair(nullptr, nullptr);
    //t = new treap(*t); //odkomentowac zeby zrobic strukture trwala
    if(treap::cmp(t->value, val))
    {
        auto p = split(t->right, val);
        t->right = p.first;
        t->recalc();
        return make_pair(t, p.second);
    }
    else
    {
        auto p = split(t->left, val);
        t->left = p.second;
        t->recalc();
        return make_pair(p.first, t);
    }
}

treap* merge(treap *a, treap *b) //wszystkie elementy a <= elementy b
{
    if(!a) return b;
    if(!b) return a;
    if(a->rank > b->rank)
    {
        //a = new treap(*a); //odkomentowac zeby zrobic strukture trwala
        a->right = merge(a->right, b);
        a->recalc();
        return a;
    }
    else
    {
        //b = new treap(*b); //odkomentowac zeby zrobic strukture trwala
        b->left = merge(a, b->left);
        b->recalc();
        return b;
    }
}

bool find(treap *t, treap::T val)
{
    if(!t) return false;
    if(t->value == val) return true;
    return t->value > val ? find(t->left, val) : find(t->right, val);
}

treap* insert(treap *t, treap::T val)
{
    auto p = split(t, val);
    return merge(merge(p.first, new treap(val)), p.second);
}

treap* erase(treap *t, treap::T val)
{
    //if(find(t, val)) return; //odkomentowac zeby zapobiegac duplikowaniu elementow
    auto p1 = split(t, val);
    auto p2 = split(p1.second, val + treap::eps);
    return merge(p1.first, p2.second);
}

#ifdef TREAP_FUNCTION
//wartosc funkcji f na przedziale wartosci <a, b)
//UWAGA - wartosc wskaznika t (czyli korzen) moze ulec zmianie!!!
treap::T segment_ans(treap *&t, treap::T a, treap::T b)
{
    //niezbyt wydajna implementacja, da sie to przyspieszyc
    auto p1 = split(t, a);
    auto p2 = split(p1.second, b);
    treap::T ans = p2.first ? p2.first->fval : treap::defval;
    t = merge(p1.first, merge(p2.first, p2.second));
    return ans;
}
#endif

void write(treap *t)
{
    if(!t) return;
    write(t->left);
    cout << t->value << " ";
    write(t->right);
}

int main()
{
    treap *t = 0;
    while(true)
    {
        string str;
        int k;
        cin >> str >> k;
        if(str == "insert")
            t = insert(t, k);
        if(str == "erase")
            t = erase(t, k);
        if(str == "count")
        {
            int l;
            cin >> l;
            cout << segment_ans(t, k, l) << endl;
        }
        write(t);
        cout << endl;
    }
}