typedef double D; const int INF = 1e9;
PII operator*(int t, PII a){return {a.st * t, a.nd * t};}
PII operator+(PII a, PII b){return {a.st + b.st, a.nd + b.nd};}
bool operator<=(PII a, PII b){
	return 1LL * a.st * b.nd <= 1LL * b.st * a.nd;
}
PII getLeft(PII &Left, PII &Right, PII &a, int &d){
	int p = 1, k = (a.nd - Left.nd) / Right.nd;
	while(p < k){
		int m = (p + k + 1) / 2;
		PII maybe = m * Right + Left;
		if(maybe <= a) p = m;
		else k = m - 1;
	}
	return p * Right + Left;
}
PII getRight(PII &Left, PII &Right, PII &a, int &d){
	int p = 1, k = (d - Right.nd - 1) / Left.nd;
	while(p < k){
		int m = (p + k + 1) / 2;
		PII maybe = m * Left + Right;
		if(maybe <= a) k = m - 1;
		else p = m;
	}
	return p * Left + Right;
}
PII getFraction(PII a, int d){	//smallest fraction > a, denom < d, d >= 2, a < 1
	PII Left = {0, 1}, Right = {1, 1};
	while(true){
		PII Mid = Left + Right;
		if(Mid <= a) Left = getLeft(Left, Right, a, d);
		else if(Mid.nd >= d) break;
		else Right = getRight(Left, Right, a, d);
	}
	assert(Right.nd < d);
	return Right;
}