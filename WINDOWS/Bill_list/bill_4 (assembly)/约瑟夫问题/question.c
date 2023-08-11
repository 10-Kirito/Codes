#include <stdio.h>

int main()
{
	int a[128],b[128];
	int i,code,k,m,n,s,t;
	printf("input the number of m:");
	scanf("%d",&m);
	if (m <= 0) {
		return 0;
	}

	printf("input the number of people n:");
	scanf("%d",&n);	
	
	for (i = 0; i < n; i++) {
		scanf("%d",&code);
		b[i] = code;
	}

	printf("design the begin counter t:");
	scanf("%d",&t);
	k = 0;
	for(i=t-1;i<n;i++)	
		a[k++]=b[i];
    for(i=0;i<t-1;i++)	
		a[k++]=b[i];
	k=0;
    while(n!=1){
        s=m%n;
        if(k!=0)
			s=(s+k-2)%n+1;
        printf(" %d ",a[s-1]);
        for(i=s-1;i<n-1;i++)a[i]=a[i+1];          
		k=s;
		n--;
    }
    printf(" %d ",a[0]);
	return 0;
}
