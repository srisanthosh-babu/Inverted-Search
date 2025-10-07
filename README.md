# 🧠 Inverted Search

## 📘 Overview

**Inverted Search** is a C-based project that implements an **Inverted Index** data structure — a technique widely used in search engines and text retrieval systems.
This project reads multiple text files, indexes each word based on the files in which it appears, and allows operations like creating, displaying, searching, and updating the database efficiently.

---

## 🚀 Features

* 📂 **File Validation:** Checks for valid `.txt` files and ensures they are not empty.
* 🧾 **Database Creation:** Builds an inverted index using hash tables and linked lists.
* 🔍 **Search Functionality:** Enables searching for words across multiple files.
* 🧱 **Dynamic Data Structures:** Uses singly and doubly linked lists for efficient word–file mapping.
* 💾 **Database Update & Save Options:** Future support for updating and saving indexed data.
* 🧩 **Menu-Driven Interface:** Easy navigation through various operations.

---

## 🧩 Data Structures Used

* **Hash Table:**
  Used for indexing words based on their starting letter (`a-z` and others).

* **Main Node (`mnode`):**
  Stores each unique word and links to subnodes containing file info.

* **Sub Node (`snode`):**
  Contains filename and word count (number of occurrences).

* **File List (`flist`):**
  Maintains all validated file names provided by the user.

---

## ⚙️ Implementation Flow

1. **Input Validation**
   Validates and reads all `.txt` files passed through command-line arguments.

2. **Database Creation**
   Reads each file, tokenizes words, and indexes them in a hash table based on the first character.

3. **Inverted Index Construction**
   Each unique word links to a list of files and stores its frequency count.

4. **Database Display**
   Shows all indexed words along with filenames and their word counts.

---

## 📂 File Structure

```
InvertedSearch/
│
├── InvertedSearch.h        # Header file containing all structures and function declarations
├── InvertedSearch.c        # Core implementation of file reading, validation, and database creation
├── main.c                  # Main menu-driven program
├── sample1.txt             # Example text file 1
├── sample2.txt             # Example text file 2
└── README.md               # Project documentation
```

---

## 🧠 Example Execution

**Command:**

```bash
./inverted_search sample1.txt sample2.txt
```

**Menu:**

```
1. Create Database
2. Display Database
3. Search Database
4. Update Database
5. Save Database
6. Exit
```

**Output Example:**

```
[ 0 ]    [ apple ]  2 file(s): file: sample1.txt 3 time(s)  file: sample2.txt 2 time(s)
[ 1 ]    [ banana ] 1 file(s): file: sample2.txt 4 time(s)
```

---

## 🧑‍💻 How to Compile & Run

```bash
gcc InvertedSearch.c main.c -o inverted_search
./inverted_search file1.txt file2.txt
```

---

## 🔮 Future Enhancements

* Implement **Search and Update** functions.
* Add **Database Save/Load** feature for persistence.
* Support for **case-insensitive** indexing.
* Improve **file handling** and **error reporting**.

---

## 🧾 License

This project is open-source and available under the [MIT License](https://opensource.org/licenses/MIT).

---

