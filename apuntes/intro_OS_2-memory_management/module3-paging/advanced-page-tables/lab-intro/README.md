# Lab Intro

In this lab, we’ll use a program `paging-multilevel-translate.py` to explore how **multi-level page tables** work.

We’ll start with some assumptions:
* The page size is $32$ bytes, which is absurdly little.
* The virtual address space for the process in issue is $1024$ pages, or $32$ KB (assuming there is only one).
* There are $128$ pages of physical memory.

So, a **virtual address** uses $15$ bits ($5$ for the offset, $10$ for the VPN). A **physical address** needs $12$ bits ($5$ offset, $7$ for the PFN).

The program uses a multi-level page table. To index into a page directory, a virtual address’s upper five bits are needed. Each page table page has 32 items (PTEs). If valid, each PTE holds the virtual page’s desired translation (PFN).

The example below shows how a page table entry (PTE) is formated:

```
VALID | PFN6 ... PFN0
```

This is $8$ bits($1$ byte).

A page directory entry (PDE) looks very similar:

```
VALID | PT6 ... PT0
```

We start with two pieces of information:
1. The **page directory base register (PDBR)** value - shows which page the page directory is on.
2. A dump of each memory page. This would look similar to the example below
   
   ```
   page 0: 08 00 01 15 11 1d 1d 1c 01 17 15 14 16 1b 13 0b ...
   page 1: 19 05 1e 13 02 16 1e 0c 15 09 06 16 00 19 10 03 ...
   page 2: 1d 07 11 1b 12 05 07 1e 09 1a 18 17 16 18 1a 01 ...
   ...
   ```

Pages 0, 1, 2, and on have 32 bytes. For example, on page 0, the first byte (0th byte) is 0x08, followed by 0x00, 0x01, etc.

You’ll be given a list of virtual addresses to translate

The PDBR can be used to locate the virtual page’s page table entries. Then see if its valid’. If so, use the translation to create a final address. Find the VALUE the memory reference is looking for using this address.

If the virtual address is invalid, it causes a fault.

Other useful options you can use with this program include:

```
-s SEED, --seed=SEED       the random seed
-n NUM, --addresses=NUM    number of virtual addresses to generate
-c, --solve                compute answers for me
```

