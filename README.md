# Newspeak Word Firewall Scanner

## Overview

Welcome to the *Newspeak Word Firewall Scanner* project! This program serves as a word scanner, checking for the use of unacceptable words or words with new translations. The tool can be invoked by linking a file or entering text directly. The program provides feedback on the usage of words and additional statistics.

## Implementation

The word scanner employs a firewall approach using a hash table with linked lists to represent buckets, a bloom filter to confirm potentially problematic words, and linked lists for efficient memory management. The program supports various user arguments for customization, such as specifying the size of the hash table, bloom filter, enabling/disabling the move-to-front rule, and more.

## Usage

To use the program, follow these steps:

- Run `make` or `make all` to compile the program.
- Use `./newspeak` followed by optional arguments and input methods:
  - `./newspeak <insert.txt>`: Link a file for scanning.
  - `./newspeak`: Enter words directly, and terminate input with Ctrl+D.
  - Optional arguments:
    - `-s`: Print statistics only.
    - `-h <size>`: Set the size of the hash table.
    - `-f <size>`: Set the size of the bloom filter.
    - `-m`: Enable the move-to-front rule.
    - `-b`: Disable the move-to-front rule.

  Note: Avoid using both `-m` and `-b` simultaneously.

## Project Details

This project involved creating a firewall utilizing hash tables, bloom filters, and linked lists for efficient word scanning. The implementation was inspired by the concept of a lexical analyzer, allowing the program to read both standard input and text documents. Challenges included addressing memory leaks and optimizing memory usage.

A critique was made regarding the assignment document's specificity, urging clearer instructions to avoid confusion among students. The project showcased the trade-off between high efficiency and low memory usage, emphasizing the importance of understanding such trade-offs in software development.
