# Lab

1. With a linear page table, you only need one register to find it if the TLB misses. To find a two-level page table, how many registers do you need? What about 3 levels?
   
2. Using the simulator, translate random seeds 0, 1, and 2, and then check your answers with the `-c` flag.
   * For each memory lookup, how many references are needed?
  
3. Considering what you know about cache memory, how do you expect memory references to the page table to operate in the cache?
   * Will they result in a high number of cache hits (and fast accesses)?
   * Or are there a lot of misses (and slow accesses)?
