typedef int flow_t; typedef int cost_t;
struct edge {
    int u, v;
    flow_t flow, capa; cost_t cost; };
const int N = 10000;
const cost_t cinf = 1e9;
const flow_t finf = 1e9;
vector<int> g[N];
cost_t d[N],p[N];
int n, pre[N];
vector<edge> e;
inline bool remin(cost_t &a, cost_t b) {
    return a > b ? a = b, true : false;
}//wierzcholki numerowane od 0 do n - 1
void init(int _n) { 
    n = _n; e.clear();
    for(int i = 0; i < n; i++) g[i].clear();
}
void add_edge(int u, int v, flow_t capa, cost_t cost) {
    g[u].push_back(e.size());
    e.push_back({ u, v, 0, capa, cost });
    g[v].push_back(e.size());
    e.push_back({ v, u, 0, 0, -cost });
}
pair<flow_t, cost_t> flow(int s, int t) {
    fill(p, p + n, 0);
    bool improved = true;
    while(improved) {
        improved = false;
        for(auto &ed: e)
            if(ed.flow < ed.capa && remin(p[ed.v], p[ed.u] + ed.cost))
                improved = true;
    }
    flow_t fans = 0; cost_t cans = 0;
    while(true) {    
        fill(d, d + n, cinf);
        priority_queue<pair<cost_t, int>> q;
        d[s] = 0; q.push({ 0, s });
        while(!q.empty()) {
            auto u = q.top().second, c = -q.top().first;
            q.pop();
            if(c != d[u]) continue;
            for(int ed: g[u]) {
                if(e[ed].flow == e[ed].capa) continue;
                auto v = e[ed].v;
                if(remin(d[v], c + p[u] - p[v] + e[ed].cost)) {
                    pre[v] = ed;q.push({ -d[v], v });
                }
            }
        } if(d[t] == cinf) break;
        vector<int> path;
        int v = t, ed = pre[v];
        flow_t flow = finf;
        while(v != s) {
            path.push_back(ed);
            flow = min(flow, e[ed].capa - e[ed].flow);
            v = e[ed].u; ed = pre[v];
        }
        for(auto ed: path) {
            e[ed].flow += flow;
            e[ed^1].flow -= flow;
        }
        fans += flow;
        cans += flow * (d[t] + p[t] - p[s]);
        for(int i = 0; i < n; i++) p[i] += d[i];
    }
    return { fans, cans };
}
