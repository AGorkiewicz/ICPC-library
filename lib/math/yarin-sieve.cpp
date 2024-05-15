#define MAXSIEVE 100000000
#define MAXSIEVEHALF (MAXSIEVE/2)
#define MAXSQRT 5000 // sqrt(MAXSIEVE)/2
char a[MAXSIEVE/16+2];
#define isprime(n) (a[(n)>>4]&(1<<(((n)>>1)&7))) // n is odd
void yarin_sieve() {
  memset(a,255,sizeof(a)); a[0]=0xFE;
  for(int i=1;i<MAXSQRT;i++) if (a[i>>3]&(1<<(i&7))) {
  for(int j=i+i+i+1;j<MAXSIEVEHALF;j+=i+i+1) a[j>>3]&=~(1<<(j&7)); }
}