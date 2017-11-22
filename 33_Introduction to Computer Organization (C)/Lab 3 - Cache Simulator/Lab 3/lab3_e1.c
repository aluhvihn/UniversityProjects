#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define S       16     //  (16 cache sets)
#define E       1      //  (4-way associative cache)
#define B       32     //  (32 elements in each block)
#define T       7      //  (7 tag bits)
#define M       65536  //  (65536 location memory)
#define READ    1
#define WRITE   0

int s ;
int b ;
int m ;

int rhits = 0 ;
int rmiss = 0 ;
int whits = 0 ;
int wmiss = 0 ;
int dwrit = 0 ;

struct cache_t
{
	char  dirty ;
	char  valid ;
	int   tag   ;
	int   last  ;
	int   *block;
} cache[S][E] ;

int *memory ;

int callno = 0 ;

int x  =     0 ;
int y  = 16384 ;
int z  = 32768 ;
int ni =    20 ;
int nj =    20 ;

void stats( char *t )
{
	int i,j,k,A ;

	for( i=0; i<S; i++ )
		for( j=0; j<E; j++ )
		{
			if( cache[i][j].valid & cache[i][j].dirty )
			{
				A = cache[i][j].tag*exp2(m-T)+i*B ;
				for( k=0; k<B; k++ )
					memory[A+k] = cache[i][j].block[k] ;
				dwrit = dwrit+1 ;
			}
			cache[i][j].valid = 0 ;
			cache[i][j].dirty = 0 ;
		}

	printf( "%8s y=%5d ni=%5d nj=%5d rh=%5d rm=%5d wh=%5d wm= %5d dw=%5d\n", t, y,ni,nj,
	        rhits, rmiss, whits, wmiss, dwrit ) ;
	rhits = 0 ;
	rmiss = 0 ;
	whits = 0 ;
	wmiss = 0 ;
	dwrit = 0 ;
}

void initcache()
{
	// put code to calculate s, b, m here
	//s=log(S)/log(2);
	s=log2(S);
	b=log(B)/log(2);
	m=log(M)/log(2);
	printf( "S= %d E= %d B= %d T= %d M= %d s= %d b= %d m= %d\n", S,E,B,T,M,s,b,m ) ;
	// put code to initialize cache and memory here
	int i;
	// initializing memory
	memory = (int *) malloc(sizeof(int)*M);
	for (i=0; i<M; i++)
		memory[i]=i;
	// initializing cache
	int j;
	for (i=0; i<S; i++)
		for (j=0; j<E; j++)
		{
			cache[i][j].dirty = 0;
			cache[i][j].valid = 0;
			cache[i][j].block = (int *)malloc(sizeof(int)*B);
		}
}

void readwritecache( int readwrite, int a, int *value, int *hitmiss, int voice )
{
	// readwrite = READ (1) for read, WRITE (0) for write
	// a = binary memory address ( 0 <= a < 65535 ) to read or write
	// *value is memory value returned when readwrite = READ
	//           memory value to store when readwrite = WRITE
	// hitmiss is set to 0 for a miss, 1 for a hit, in either read or write case
	int si, ta, bo, li ;
	//   compute si, ta, and bo from the address a
	si = (a>>(m-T-s))%S;   // si = stack, index
	ta = a>>(m-T);         // ta = tag
	bo = a%B;              // bo = block offset
	//      increment callno
	callno++;
	// voice is a debugging switch
	if( voice )
		printf( "%5d rw= %d a= %5d bo= %3d si= %3d ta= %3d ", callno,readwrite,a,bo,si,ta ) ;
	int lineNo;
	int LRU= 0;                         //find LRU
	int inv_Line = -10;                 //initialize invalid tracker (stay -10 if no lines invalid)
	*hitmiss=0;                         //initialize hitmiss
	//   check each line of the set:
	for (lineNo=0; lineNo<E; lineNo++)
	{
		if(cache[si][lineNo].valid && cache[si][lineNo].tag==ta)    //to find a hit
		{
			*hitmiss = 1;
			li = lineNo;
		}
		if(cache[si][lineNo].valid==0)                               //check valid bit for R/W if miss
			inv_Line=lineNo;
		if(cache[si][lineNo].last>LRU)                               //find LRU
			LRU=lineNo;
	}
	//	if hit
	if (*hitmiss==1)
	{
		if (readwrite==WRITE)				// if writing
		{
			//    copy value into line, set dirty
			cache[si][li].block[bo]=*value;
			cache[si][li].dirty=1;
			whits++;
		}
		else if (readwrite==READ)			// if reading
		{
			*value = cache[si][li].block[bo];
			rhits++;
		}
	}
	//   if no hit (miss), choose a line (not valid or LRU )
	else if (*hitmiss==0)
	{
		if (inv_Line == -10)						//if miss && all lines occupied
			li = LRU;
		else if (inv_Line != -10)					//if miss && invalid line found
			li = inv_Line;
		if (readwrite==WRITE)						// if writing
		{
			//   if chosen line dirty, copy to memory
			if (cache[si][li].dirty)
			{
				int k, A = cache[si][li].tag*exp2(m-T)+si*B ;
				for( k=0; k<B; k++ )
					memory[A+k] = cache[si][li].block[k];
				dwrit++;
			}
			//    copy from memory to chosen line
			int k, A = ta*exp2(m-T)+si*B;
			for(k=0; k<B; k++)
				cache[si][li].block[k]=memory[A+k];
			//    copy value into line, set dirty
			cache[si][li].block[bo]=*value;
			cache[si][li].tag=ta;
			cache[si][li].dirty=1;
			cache[si][li].valid=1;
			wmiss++;
		}
		else if (readwrite==READ)					// if reading
		{
			//   if chosen line dirty, copy to memory
			if (cache[si][li].dirty)
			{
				int k, A = cache[si][li].tag*exp2(m-T)+si*B ;
				for( k=0; k<B; k++ )
					memory[A+k] = cache[si][li].block[k];
				dwrit++;
			}
			//    copy from memory to chosen line
			int k, A = ta*exp2(m-T)+si*B;
			for(k=0; k<B; k++)
				cache[si][li].block[k]=memory[A+k];
			cache[si][li].tag=ta;
			cache[si][li].dirty=0;		// newly loaded line can't be dirty
			cache[si][li].valid=1;
			*value = cache[si][li].block[bo];
			rmiss++;
		}
	}
	if( voice )
		printf( "li= %d", li ) ;
	//    set last for line
	int last = cache[si][li].last;
	int i;
	if (LRU==3)
	{
		for (i=0; i<E; i++)
			if(cache[si][i].last<=last && cache[si][i].valid)
				cache[si][i].last++;
		cache[si][li].last=0;
	}
	else
	{
		for (i=0; i<E; i++)
		{
			if(cache[si][i].valid)
				cache[si][i].last++;
			if(cache[si][i].last<=last)
				cache[si][i].last++;
		}

		cache[si][li].last=0;
	}
	if( voice )
		printf( " %d %d %d\n", *value, cache[si][li].valid, cache[si][li].dirty ) ;
}

void locationexample()
{
	int i,j,k,hm, r;

	for( y=16374; y< 16395; y=y+1 )
	{
		for( i=0; i<nj; i++ )
		{
			readwritecache( READ,   x+i, &r, &hm, 0 ) ;
			readwritecache( WRITE,  y+i, &r, &hm, 0 ) ;
		}
		stats( "loc copy" ) ;
	}
	y=16374;
	// code for row wise transponse
	for (i=0; i<ni; i++)
	{
		for (j=0; j<nj; j++)
		{
			readwritecache(READ,y+i*nj+j,&r,&hm,0);
			readwritecache(WRITE,x+j*nj+i,&r,&hm,0);
		}
	}
	stats( "loc rows" ) ;
	// code for col wise transponse
	for (j=0; j<nj; j++)
	{
		for (i=0; i<ni; i++)
		{
			readwritecache(READ,y+i*nj+j,&r,&hm,0);
			readwritecache(WRITE,x+j*nj+i,&r,&hm,0);
		}
	}
	stats( "loc cols" ) ;
}

void wsexample()
{
	int i,j,ii,jj,hm,r ;
	y = 20000 ;

	// code for row wise transpose
	for( ni=88; ni<128; ni=ni+8 )
	{
		nj = ni ;
		for (i=0; i<ni; i++)
		{
			for (j=0; j<nj; j++)
			{
				readwritecache(READ,y+i*nj+j,&r,&hm,0);
				readwritecache(WRITE,x+j*nj+i,&r,&hm,0);
			}
		}
		stats( "ws rows" ) ;
	}

	// code for row wise transpose with 8x blocking
	for( ni=88; ni<128; ni=ni+8 )
	{
		nj = ni ;
		for (ii=0; ii<ni; ii+=8)
		{
			for (jj=0; jj<nj; jj+=8)
			{
				for (i=ii; i<ii+8; i++)
				{
					for (j=jj; j<jj+8; j++)
					{
						readwritecache(READ,y+i*nj+j,&r,&hm,0);
						readwritecache(WRITE,x+j*nj+i,&r,&hm,0);
					}
				}
			}
		}
		stats( "wsbrows" ) ;
	}

	// code for col wise transpose
	for( ni=88; ni<128; ni=ni+8 )
	{
		nj = ni ;
		for (j=0; j<nj; j++)
		{
			for (i=0; i<ni; i++)
			{
				readwritecache(READ,y+i*nj+j,&r,&hm,0);
				readwritecache(WRITE,x+j*nj+i,&r,&hm,0);
			}
		}
		stats( "ws cols" ) ;
	}

	// code for col wise transpose with 8x blocking
	for( ni=88; ni<128; ni=ni+8 )
	{
		nj = ni ;
		for (jj=0; jj<nj; jj+=8)
		{
			for (ii=0; ii<ni; ii+=8)
			{
				for (j=jj; j<jj+8; j++)
				{
					for (i=ii; i<ii+8; i++)
					{
						readwritecache(READ,y+i*nj+j,&r,&hm,0);
						readwritecache(WRITE,x+j*nj+i,&r,&hm,0);
					}
				}
			}
		}
		stats( "wsbcols" ) ;
	}
}

int main()
{

	initcache();
	locationexample() ;
	wsexample() ;
	return 0 ;
}
