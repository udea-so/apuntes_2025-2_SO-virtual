# Lab Intro

In this lab, we’ll use a program, `paging-linear-translate.py` to explore virtual-to-physical address translation with linear page tables.

Let’s run this program with the `-h` flag to see the options we have with this program.

```
./paging-linear-translate.py -h
```

Run the program without any arguments to see the natural output:

```
./paging-linear-translate.py 
```

For each **virtual address**, your job is to either:
* Write down the physical address it translates to, or
* Write down that it is an out-of-bounds address (segmentation fault)

This program gives you a page table for a particular process. Recall that, in a real system with linear page tables, there is **one page table per process**. Here we focus on:
* One process
* Its address space, and so
* A single page table

For each virtual page number of the address space, the page table tells you that the virtual page is mapped to a specific physical frame number and is either valid or invalid.

The format of the page-table entry is:
* The left-most bit is the valid bit
* The remaining bit, provided that the valid bit is $1$, is the PFN

In our example above, the page table maps:
* VPN $0$ to PFN `0xC` (decimal $12$),
* VPN $3$ to PFN `0x6` (decimal $6$), and
* leaves the other two virtual pages, $1$ and $2$, as invalid.

Because the page table is a linear array, what is printed above is a representation of what you would see in memory if you checked the bits yourself.

Running this program with the `-v` flag also prints the VPN (index) into the page table. Run the example above with the `-v` flag:

```
./paging-linear-translate.py -v
```

Your task is to use this page table to convert virtual addresses to physical addresses.
Let’s start with `VA 0x3229`. To convert this virtual address into a physical address, we have to:
* Break it down it into a virtual page number and an offset
  * We can do this by writing down the size of the **address space** and the **page size**.
* In this case, the address space is $16KB$
* The page size is $4KB$

We know that there are 14 bits in the virtual address and that the offset is 12 bits. This leaves 2 bits for the VPN. So, with our address `0x3229`, which is binary `1100100001001`
, we know the top two bits specify the VPN.

**So, `0x3229` is on virtual page `3` with an offset of `0x229`.**

Next, we check the page table to see if VPN 3 is valid and mapped to a physical frame, and we find that it is (the high bit is 1 and it is mapped to physical page 6). As a result, we can build our final physical address by adding the physical page 6 to the offset, as follows:
* `0x6000` is the physical page shifted into the correct spot, or
* `0x0229`, the offset, gives us
* the final physical address, `0x6229`
  
So we see that the virtual address, `0x3229` translates to physical address `0x6229`

After you’ve computed the solutions yourself, run the program with the `-c` flag to see the answers.

```
./paging-linear-translate.py -c
```

You can change many of these parameters to make more interesting problems to solve. Remember to run the program with the `-h` flag to see what options there are.
* The `-s` flag changes the random seed and thus generates different page table values as well as different virtual addresses to translate.
* The `-a` flag changes the size of the address space.
* The `-p` flag changes the size of physical memory.
* The `-P` flag changes the size of a page.
* The `-n` flag can be used to generate more addresses to translate (instead of the default `5`).
* The `-u` flag changes the fraction of mappings that are valid, from `0` (`-u 0`) up to `100` (`-u 100`). The default is `50`, which means that roughly $1/2$ of the pages in the virtual address space will be valid.
* The `-v` flag prints out the VPN numbers to make your life easier.


