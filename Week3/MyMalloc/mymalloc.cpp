
typedef unsigned long size_t;

class myHeap
{
    private:

    char *heap; // virtual heap that immitates heap
    char *brk;  // pointer to the top of the heap
    char *max_brk;  // maximum value of brk

    public:
    /**
     * @brief Construct a new virtual Heap object
     * 
     * @param size size of heap in Bytes
     */
    myHeap(size_t size)
    {
        heap = new char(size);
        brk = &heap[0];    // begin from 0
        max_brk = &heap[size-1];    // pointer to end of the heap
    }

    void* my_sbrk(size_t incr)
    {
        char *brk_prev = brk;   // save current brk position
        brk += incr;    // increase brk by incr
        return brk_prev;    // return brk before incresing
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
