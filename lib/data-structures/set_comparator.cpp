struct Comparator { 
    bool operator()(const T a, const T b) const { 
        return a < b; 
    } 
}; 
set <T, Comparator> S;
priority_queue<T, vector <T>, Comparator> Q;
