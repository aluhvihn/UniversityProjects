# UniversityProjects
Some old coursework and projects

33 – Introduction to Computer Organization
- Lab 3 – Cache Simulator (C)
  	- Implement Cache Simulator; Experiment with different sets, blocks, and lines
  	- Include “Dirty” bit to indicate cache that needs to be written to memory (write-back cache)
	- Last Recently Used (LRU) line replacement method
- Lab 4 – Dynamic Memory Allocation Using Explicit Free Lists (C)
	- Simulate malloc and free (lalloc, lfree)
	- Use heap that is array of characters
		- Initial size of HEAPSIZE characters
		- Variable which maintains current size of heap: heapsize
		- Made up of free blocks and allocated blocks, each with header, payload, and footer
	- Free list is a linked list and blocks have boundary tags

111 – Operating Systems Principles
- Lab 1 – Shell Prototype to Run Commands in Parallel (C)
	- Create shell prototype which runs common shell commands (sort, cat, tr, diff) in parallel when it is safe to do so.
	- Does not parallelize subcommands
- Lab 2 – RAM Disk Implementation (Linus Kernel Module) (C)
	- Ramdisk supporting read/write operations, as well as simple read/write locking
	- Runs on the QEMU virtual machine environment, running Linux 2.6.18
- Lab 3 – File System Driver for Linux (C)
	- Simple file system implementation, accessable through standard Unix commands (cat, dd, emacs, firefox, etc.).
	- Stores data on built-in RAM disk
	- Runs on the QEMU virtual machine environment, running Linux 2.6.18
- Lab 4 – Implementing OSP2P Peer Client with Parallel Processing (C)
	- Given peer code which uploads/downloads sequentially, modify the peer to behave in parallel.
	- Peer code is not robust, modify peer code to make it robust.
	- Give peer code option (-b) to be “evil”, in which it will try to confuse/crash peers attempting to download from it.
	- Runs on any UNIX-compatible machine.
118 – Computer Network Fundamentals
- Project 1 – Concurrent Web Server using BSD Sockets (C)
	- “Web Server” implementation that dumps request messages to console, to observe HTTP interface.
	- Upon HTTP request, create HTTP response with requested file preceded with header lines, and send to client.
- Project 2: Simple Windows-based Reliable Data Transfer (C++)
	- Implement reliable data transfer on top of UDP
	- Program acts as both network application (file transfer program) and reliable transport layer protocol built over unreliable UDP transport layer.
	- Packet loss emulation.

130 – Software Engineering
- SwipeSwap
	- Android application which allows users to trade meal swipes

131 – Programming Languages
- HW1 – ML Practice
- HW2 – ML Practice 2
- HW3 – Java Practice
	- Measuring reliability and performance of different implementation models running through Java’s shared memory model
- HW4 – Prolog Practice
	- Simple KenKen solver in Prolog
- HW 5 – Scheme Practice

132 – Compiler Construction (Java)
- HW2 –Type Checker of MiniJava
	- Use JTB and JavaCC and write in Java visitors that type check a MiniJava program
	- Using Visitor function, adds variable and methods to symbol table, which is used when resolving whether variable or expression is of correct Base or Class Type
- HW3 – Translate MiniJava to Vapor
	- Use JTB and JavaCC and write in Java visitors that compile a MiniJava program to Vapor
	- Using Visitor function, translates the MiniJava code to Vapor equivalent
- HW4 – Translate Vapor to VaporM
	- Using provided parser and AST classes, write visitors that compile Vapor program to VaporM
	- Using Visitor function, translates Vapor code to VaporM equivalent
- HW5 – Translate VaporM to MIPS
	- Using provided parser and AST classes, write visitors that compile a VaporM program to MIPS
	- Using Visitor function, translates VaporM code to MIPS equivalent

143 – Database Systems
- P1A – Simple PHP Calculator
- P1B – PHP and SQL Queries on a DB
	- Query and display records from a DB through PHP
- P1C – Modifying SQL Database through PHP
	- Display additional information about linked records from different tables.
	- Implement capability to add information to records or add new records
- P2 – Implementing BTree Structure for SQL Queries (C++)
	- Program which carries out SQL Insertions and Queries in a BTreeIndex

144 – Web Applications
- Project 1 – Environment Setup, MySQL & Java Practice
- Project 2 – Data Conversion and Loading (Java, MySQL, HTML, CSS)
	- Parse XML data and store them into relational database system
	- Create 2-column Web page w/ header and footer using CSS
- Project 3 – Search and Retrieval
	- Create SOAP Web Service: Provide “search” functions for data. Search over keyword-based text fields or items located within geographic region.
- Project 4 – Building a Website
	- Create Web site for Web service to operate on
	- SOAP-based Web service to data
	- Google Maps to display location of item
	- Google suggest to help users formulate keyword queries
- Project 5 – Enabling Secure Transaction
	- Enable users to pay for item by inputting credit card number
	- Encrypt communications with HTTPS

152A – Introductory Digital Design Laboratory
- Lab 1: Sequencer (FPGA)
- Lab 2: Floating Point Conversion (FPGA)
- Lab 3: Stopwatch (FPGA)
- Lab 4: Simple Integer Calculator (FPGA)

161 – Fundamentals of Artificial Intelligence
- Hw1 – Lisp  Practice
- HW2 – Lisp BFS Problem Solver
- HW3 – Lisp Sokoban Solver
- HW4 – Converting Coloring Problems to SAT Problems
- HW5
- HW6

CM124 – Computational Genetics
- PA1 – Association Statistiand Power of Single SNP
- PA2 – GWAS and Population Structure