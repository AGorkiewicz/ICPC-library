const lf eps = 1e-9, inf = 1e9; 
struct halfplane {
	point p, pq; // Passing point and direction. Halfplane is to the left.
	lf ang;
	halfplane() {}
	halfplane(point a, point b) : p(a), pq(b - a), ang(atan2l(pq.y, pq.x)) {}
	bool out(point r) { return cross(pq, r - p) < -eps; }
};
point inter(halfplane s, halfplane t){
	return s.p + cross((t.p - s.p), t.pq) / cross(s.pq, t.pq) * s.pq;
}
vector <point> halfcoat(vector <halfplane>& H){
	point box[4] = {
		point(+inf, +inf),
		point(-inf, +inf),
		point(-inf, -inf),
		point(+inf, -inf)
	};
	for (int i = 0; i < 4; i++){
		H.push_back(halfplane(box[i], box[(i + 1) % 4]));
	}
	sort(H.begin(), H.end(), [] (halfplane a, halfplane b) { return a.ang < b.ang; });
	deque<halfplane> dq;
	int len = 0;
	for (int i = 0; i < H.size(); i++){
		while (len > 1 && H[i].out(inter(dq[len - 1], dq[len - 2]))){
			dq.pop_back();
			len--;
		}
		while (len > 1 && H[i].out(inter(dq[0], dq[1]))){
			dq.pop_front();
			len--;
		}
		if (len > 0 && abs(cross(H[i].pq, dq[len - 1].pq)) < eps){
			if (dot(H[i].pq, dq[len - 1].pq) < 0.0){
				return vector<point>();
			}
			if (H[i].out(dq[len - 1].p)){
				dq.pop_back();
				len--;
			}
			else continue;
		}
		dq.push_back(H[i]);
		len++;
	}
	while (len > 2 && dq[0].out(inter(dq[len - 1], dq[len - 2]))){
		dq.pop_back();
		len--;
	}
	while (len > 2 && dq[len - 1].out(inter(dq[0], dq[1]))){
		dq.pop_front();
		len--;
	}
	if (len < 3) return vector<point>();
	vector<point> res(len);
	for(int i = 0; i < len; i++){
		res[i] = inter(dq[i], dq[(i + 1) % len]);
	}
	return res;
}
