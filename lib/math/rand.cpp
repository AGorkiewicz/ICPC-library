int getInt(int a = INT_MIN, int b = INT_MAX){
	static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());	
	return uniform_int_distribution <int> (a, b)(rng);
}

long long getLL(long long a = LLONG_MIN, long long b = LLONG_MAX){
	static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
	return uniform_int_distribution <long long int> (a, b)(rng);
}

double getReal(double a = 0.0, double b = 1.0){
	static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());	
	return uniform_real_distribution <double> (a, b)(rng);
}
