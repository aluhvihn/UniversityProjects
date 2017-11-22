#include <stdio.h>
#include <stdlib.h>

#define HEAPSIZE 32768

#define hdr_payload(i)  ((struct HDR *) &heap[i])->payload
#define hdr_freeall(i)  ((struct HDR *) &heap[i])->freeall
#define hdr_succesr(i)  ((struct HDR *) &heap[i])->succesr
#define hdr_previus(i)  ((struct HDR *) &heap[i])->previus

void lfree( int *aa );

char *heap ;
int  heapsize ;

int sizehdr ;

struct HDR       // free block header/footer/linked list
{
    int  payload ;    // size of block (excluding headers)
    char freeall ;    // is this block allocated? 0=free/1=allocated
    int  succesr ;    // successor free block
    int  previus ;    // previous free block
} anchor ;

void dump_heap( char *t )   // prints all of the headers/footers on the heap
{
    int i ;

    int j=0 ;
    printf( "%s anchor= %d\n", t, anchor.succesr ) ;
    for( i=0; i<heapsize; i=i+sizehdr  )
        if ( hdr_payload(i) != 0 )
        {
            printf( "%6d %6d %6d %6d %6d\n", i, hdr_payload(i), hdr_freeall(i), hdr_previus(i), hdr_succesr(i) ) ;
            if ( j++%2==1 ) printf( "\n" ) ;
        }
}

void init_heap()   // initialize the heap
{
    heap = (char *) calloc( HEAPSIZE, 1 ) ;
    sizehdr =  16 ;
    heapsize = HEAPSIZE ;

    anchor.payload =  0 ;   // anchor
    anchor.freeall =  1 ;
    anchor.succesr =  0 ;
    anchor.previus = -1 ;

    hdr_payload(0) = heapsize-2*sizehdr ;   // header
    hdr_freeall(0) = 0 ;
    hdr_succesr(0) = heapsize ;
    hdr_previus(0) = -1 ;
    hdr_payload(heapsize-sizehdr) = heapsize-2*sizehdr ; // footer
    hdr_freeall(heapsize-sizehdr) = 0 ;
}

int lalloc( int amt )   // allocates a block of size int
{
    sizehdr =  16 ;
    int bamt = amt;     // block size (amt + boundary tags)
    bamt+=(2*sizehdr);  // + 32 space for boundary tags
    if (bamt%16!=0)     // round up size to 16
    {
        bamt+=(16-bamt%16);
    }
    // first fit
    int i;
    for( i=0; i < heapsize; i = i+sizehdr  )
    {
        // split first fit block
        if ((bamt < (hdr_payload(i)+ (2*sizehdr)) ) && hdr_freeall(i)==0 )
        {
            int i_foot = i+bamt-sizehdr;
            int split_head = i + bamt;
            int split_foot = hdr_succesr(i)-sizehdr;

            // lower address is assigned block, upper address is free block
            // HEADERS
            hdr_freeall(i) = 1;                             // free/all
            hdr_freeall(split_head) = 0;

            hdr_payload(split_head) = hdr_payload(i)-bamt;   // payload
            hdr_payload(i) = bamt-2*sizehdr;

            hdr_freeall(i_foot) = 1;     //footers
            hdr_payload(i_foot) = bamt-2*sizehdr;
            hdr_freeall(split_foot) = 0;
            hdr_payload(split_foot) = hdr_payload(split_head);

            // update list
            hdr_succesr(split_head) = hdr_succesr(i);   // update split free block
            hdr_previus(split_head) = hdr_previus(i);

            if (hdr_previus(i)==-1)                     // update previous free block
            {
                anchor.succesr = split_head;
            }
            else
            {
                hdr_succesr(hdr_previus(i)) = split_head;
            }

            if (hdr_succesr(i) != heapsize)
                hdr_previus(hdr_succesr(i)) = split_head;  // update successive free block

            hdr_previus(i)=0;           // zero out prev/succ of allocated (not maintained)
            hdr_succesr(i)=0;

            return i+sizehdr;
        }
        // if block fits request exactly, no splitting done
        else if (bamt == (hdr_payload(i)+2*sizehdr) && hdr_freeall(i)==0 )
        {
            // mark as allocated
            hdr_freeall(i) = 1;
            hdr_freeall(i+bamt-sizehdr) = 1;

            // update previous and successive free block headers
            if (hdr_previus(i)==-1)                     // update previous free block
            {
                anchor.succesr = hdr_succesr(i);
            }
            else
            {
                hdr_succesr(hdr_previus(i)) = hdr_succesr(i);
            }

            if (hdr_succesr(i) != heapsize)
                hdr_previus(hdr_succesr(i)) = hdr_previus(i);

            return i+sizehdr;
        }
    }

    // if no free block large enough, use realloc to re-allocate heap, adding HEAPSIZE additional space
    int old_end_footer = heapsize-sizehdr;
    heap = (char *)realloc(heap, heapsize + HEAPSIZE) ;
    int end_header = heapsize;        // NEW BLOCK AT END
    hdr_payload(end_header) = HEAPSIZE - 2*sizehdr;
    hdr_previus(end_header) = old_end_footer - hdr_payload(old_end_footer) - sizehdr; // old_end_header
    hdr_succesr(end_header) = heapsize + HEAPSIZE;
    hdr_freeall(end_header) = 1;
    heapsize += HEAPSIZE;
    int end_footer = heapsize - sizehdr;
    hdr_payload(end_footer) = hdr_payload(end_header);
    hdr_previus(end_footer) = 0;
    hdr_succesr(end_footer) = 0;
    hdr_freeall(end_header) = 1;
    hdr_freeall(end_footer) = 1;

    int block = end_header + sizehdr;
    lfree( &block );        // lfree to merge reallocated space

    return lalloc( amt );   // repeat until large enough block
}

void lfree( int *aa )   // frees the block at address aa
{
    int a_head = *aa - sizehdr;
    int a_foot = a_head + hdr_payload(a_head) + sizehdr;

    // footer of previous block directly adjacent to header of block being freed
    int prev_foot = a_head-sizehdr;
    int prev_head = prev_foot - hdr_payload(prev_foot) - sizehdr;
    // header of successive block directly adjacent to footer of block being freed
    int next_head = a_foot+sizehdr;
    int next_foot = next_head + hdr_payload(next_head) + sizehdr;

    if (prev_foot == -sizehdr)      // if freeing from top of heap
    {
        if (hdr_freeall(next_head) == 0)   // coalesce with next
        {
            hdr_payload(a_head) = next_foot - a_head - sizehdr;
            hdr_payload(next_foot) = hdr_payload(a_head);
            hdr_previus(a_head) = -1;
            hdr_succesr(a_head) = hdr_succesr(next_head);

            // update neighbors
            anchor.succesr = a_head;
            int next_neigh = hdr_succesr(a_head);
            hdr_previus(next_neigh) = a_head;

            // clear values
            hdr_payload(a_foot) = 0;
            hdr_payload(next_head) = 0;
            hdr_previus(next_head) = 0;
            hdr_succesr(next_head) = 0;
            hdr_freeall(a_head) = 0;
            hdr_freeall(a_foot) = 0;
            *aa = 0;
            return;
        }
        hdr_freeall(a_head) = 0;
        hdr_freeall(a_foot) = 0;
        hdr_previus(a_head) = -1;
        hdr_succesr(a_head) = anchor.succesr;
        hdr_previus(anchor.succesr) = a_head;
        anchor.succesr = a_head;
        *aa = 0;
        return;
    }

    else if (next_head != heapsize)
    {
        // immediate coalescing
        if ( ( hdr_freeall(prev_head) == 0 ) && ( hdr_freeall(next_head) == 0 ) )   // coalesce with both
        {
            hdr_payload(prev_head) = next_foot - prev_head - sizehdr;
            hdr_payload(next_foot) = hdr_payload(prev_head);
            // update previous and next
            if ( hdr_previus(next_head) != -1 )
            {
                hdr_succesr(hdr_previus(next_head)) = hdr_succesr(next_head);
            }
            else if ( hdr_previus(next_head) == -1 )
            {
                anchor.succesr = hdr_succesr(next_head);
            }
            hdr_previus(hdr_succesr(next_head)) = hdr_previus(next_head);

            // clear values
            hdr_payload(prev_foot) = 0;
            hdr_payload(a_head) = 0;
            hdr_payload(a_foot) = 0;
            hdr_payload(next_head) = 0;
            hdr_freeall(a_head) = 0;
            hdr_freeall(a_foot) = 0;
            hdr_previus(a_head) = 0;
            hdr_succesr(a_head) = 0;
            hdr_previus(next_head) = 0;
            hdr_succesr(next_head) = 0;
            *aa = 0;
            return;
        }

        else if (hdr_freeall(prev_head) == 0)   // coalesce with previous
        {
            hdr_payload(prev_head) = a_foot - prev_head - sizehdr;
            hdr_payload(a_foot) = hdr_payload(prev_head);

            // clear values
            hdr_payload(prev_foot) = 0;
            hdr_payload(a_head) = 0;
            hdr_freeall(a_head) = 0;
            hdr_freeall(a_foot) = 0;
            *aa = 0;
            return;
        }

        else if (hdr_freeall(next_head) == 0)   // coalesce with next
        {
            hdr_payload(a_head) = next_foot - a_head - sizehdr;
            hdr_payload(next_foot) = hdr_payload(a_head);
            hdr_previus(a_head) = hdr_previus(next_head);
            hdr_succesr(a_head) = hdr_succesr(next_head);

            // update neighbors
            int prev_neigh = hdr_previus(a_head);
            int next_neigh = hdr_succesr(a_head);
            if (prev_neigh == -1)
            {
                anchor.succesr = a_head;
            }
            else
            {
                hdr_succesr(prev_neigh) = a_head;
            }
            hdr_previus(next_neigh) = a_head;

            // clear values
            hdr_payload(a_foot) = 0;
            hdr_payload(next_head) = 0;
            hdr_previus(next_head) = 0;
            hdr_succesr(next_head) = 0;
            hdr_freeall(a_head) = 0;
            hdr_freeall(a_foot) = 0;
            *aa = 0;
            return;
        }
    }


    else if (hdr_freeall(prev_head) == 0)   // coalesce with previous
    {
        hdr_payload(prev_head) = a_foot - prev_head - sizehdr;
        hdr_payload(a_foot) = hdr_payload(prev_head);
        hdr_succesr(prev_head) = heapsize;

        // clear values
        hdr_payload(prev_foot) = 0;
        hdr_payload(a_head) = 0;
        hdr_freeall(a_head) = 0;
        hdr_freeall(a_foot) = 0;
        *aa = 0;
        return;
    }

    // if no coalescing
    hdr_freeall(a_head) = 0;
    hdr_freeall(a_foot) = 0;

    // add block to beginning free block chain (LIFO)
    hdr_previus(a_head) = -1;
    hdr_succesr(a_head) = anchor.succesr;
    hdr_previus(anchor.succesr) = a_head;
    anchor.succesr = a_head;
    *aa = 0;
    return;
}

int main()
{
    int i ;
    int j = 0  ;
    int blks[100] ;

    init_heap() ;
    dump_heap( "init heap" ) ;

    for( i=0; i<20; i++ )
        blks[j++] = lalloc( rand()%500 ) ;
    dump_heap( "first allocs" ) ;

    lfree( &blks[10] ) ;
    lfree( &blks[11] ) ;
    dump_heap( "coalesce with upper" ) ;

    lfree( &blks[14] ) ;
    lfree( &blks[13] ) ;
    dump_heap( "coalesce with lower" ) ;

    lfree( &blks[5] ) ;
    lfree( &blks[7] ) ;
    lfree( &blks[6] ) ;
    dump_heap( "coalesce with both" ) ;

    blks[5] = lalloc( 80000 ) ;
    dump_heap( "blew the top off" ) ;

    for( i=0; i<20; i++ )
        if (blks[i] != 0 )
        {
            lfree( &blks[i] ) ;
        }
    dump_heap( "free everything " ) ;

    return 0 ;
}
