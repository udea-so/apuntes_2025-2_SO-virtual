# Lab 1

1. Before we start translating, let’s use the simulator to see how different parameters affect the size of linear page tables.
   * Calculate the size of linear page tables as different parameters are changed. Below are some suggested inputs. You can see how many page-table entries are filled by using the -v flag. To start, consider how the size of a linear page table changes as the address space grows:
     
     ```
     ./paging-linear-translate.py -P 1k -a 1m -p 512m -v -n 0
     ./paging-linear-translate.py -P 1k -a 2m -p 512m -v -n 0
     ./paging-linear-translate.py -P 1k -a 4m -p 512m -v -n 0
     ```

   * Then, to see how the size of a linear page table changes as the page size grows, try the following:
     
     ```
     ./paging-linear-translate.py -P 1k -a 1m -p 512m -v -n 0
     ./paging-linear-translate.py -P 2k -a 1m -p 512m -v -n 0
     ./paging-linear-translate.py -P 4k -a 1m -p 512m -v -n 0
     ```

   * Try to consider the expected trends before running any of these.
     * How should the size of page tables change as the address space grows?
     * What happens as the page size grows?
     * Why don’t we just use really large pages all the time?
     
2. Let’s get started with some translations. Begin with a few simple examples, then use the `-u` flag to alter the number of pages assigned to the address space. Consider the following:
   
   ```
   ./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 0
   ./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 25
   ./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 50
   ./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 75
   ./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 100
   ```

   What happens as you increase the percentage of pages that are allocated in each address space?

3. Now, for some spice, let’s test a few other random seeds and some different (and sometimes pretty strange) address-space parameters:   
   
   ```
   ./paging-linear-translate.py -P 8  -a 32   -p 1024 -v -s 1
   ./paging-linear-translate.py -P 8k -a 32k  -p 1m   -v -s 2
   ./paging-linear-translate.py -P 1m -a 256m -p 512m -v -s 3 
   ```
   
   Which of these parameter combinations are unrealistic? Why?


