# Advanced Page Tables

## Overview

Simple array-based page tables (also known as linear page tables) are too big and take up too much memory. For the sake of our OS’s efficiency, let’s explore how to make tables smaller.

This section should help us answer the following questions:
* **How can we shrink page tables?**
* **What are the central ideas?**
* **What inefficiencies do these new data structures bring with them?**

## Introduction

Let’s start by imagining we have a $32$-bit address space ($2^{32}$ bytes) and $4 KB$ ($2^{12}  $ byte) pages and a $4$-byte page-table entry.

Considering the size of our page table and the size of our address space, our address space has roughly one million virtual pages ($2^{32}\div2^{12}$); multiply by the page-table entry size and we arrive at a $4 MB$ page table. In addition, each process in the database usually has one page table!

If $100$ processes are running in parallel (not uncommon on a modern system), we’ll be using hundreds of megabytes of memory for page tables alone! Therefore, we are searching for techniques to reduce this heavy burden.

### How can we make these page tables smaller?

## Larger Pages

One simple way to reduce the size of the page table is to use larger pages. Consider our 32-bit address space once more, but this time with 16-KB pages. As a result, we would have an 18-bit VPN with a 14-bit offset. Assuming that each PTE is the same size (4 bytes), our linear page table now has 218 entries and a total size of 1MB per page table, a factor of four reduction in the size of the page table (not surprisingly, the reduction exactly mirrors the factor of four increase in page size).

The major drawback to this strategy is that large pages result in waste within each page, a problem known as internal fragmentation (as the waste is internal to the unit of allocation). As a result, applications allocate pages but only use small portions of each, and memory quickly fills up with these excessively large pages. As a result, in the most common case, most systems use relatively small page sizes: 4KB (as in x86) or 8KB (as in SPARCv9). Unfortunately, our problem will not be solved so easily.

