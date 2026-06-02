

# ✈️ Airline Reservation System (C++ DSA)

A comprehensive, console-based Airline Reservation System built entirely in C++ to demonstrate the practical application of Data Structures and Algorithms (DSA). This project efficiently manages passenger records, flight schedules, searching/sorting operations, and network routing using fundamental computing concepts.

## 👥 Team & Contributions

This project was collaboratively developed, with specific structural responsibilities divided among the team:

* **Janmesh Rohida:** Core Passenger Management & Sequencing (Linked Lists, Stacks, Queues).
* **Tanay Shelar:** Data Retrieval & Organization (Searching, Sorting algorithms, Complexity Analysis).
* **Aditya Chouksey:** Advanced Routing & Hierarchical Data (Binary Search Trees, Graphs, BFS/DFS Traversals).

---

## 🛠️ Features & Data Structures Used

This system uses a variety of data structures to optimize different operational requirements of an airline:

### 1. Passenger Management

* **Singly Linked List:** Used to maintain dynamic passenger records (ID, Name, Flight Number, Seat, Age) allowing efficient dynamic memory allocation.
* **Stack:** Implements a robust **Undo** feature. Every `ADD` or `DELETE` passenger operation is pushed to a stack, allowing the user to seamlessly revert their last action.

### 2. Flight Scheduling

* **Queue:** Handles the flight scheduling and boarding process (FIFO - First In, First Out). Flights are enqueued when scheduled and dequeued when boarding.

### 3. Data Organization (Sorting & Searching)

* **Merge Sort $O(n \log n)$:** Sorts passenger records alphabetically by Name.
* **Quick Sort $O(n \log n)$:** Sorts passenger records numerically by Passenger ID.
* **Insertion Sort $O(n^2)$:** Sorts passengers by Age.
* **Linear Search $O(n)$:** Finds passengers by Name.
* **Binary Search $O(\log n)$:** Quickly retrieves a passenger by their ID (requires the list to be sorted first).

### 4. Advanced Flight & Route Management

* **Binary Search Tree (BST):** Organizes flights by Flight ID for highly optimized $O(\log n)$ insertions and lookups.
* **Weighted Graphs (Adjacency List):** Maps the airline route network between major cities (Mumbai, Delhi, Bangalore, Chennai, Kolkata, Hyderabad).
* **BFS (Breadth-First Search):** Calculates the minimum hops/shortest path layer-by-layer from a source city.
* **DFS (Depth-First Search):** Explores all reachable cities deeply from a starting node.



---

## 🚀 Getting Started

### Prerequisites

* A C++ compiler (e.g., GCC/G++)
* Basic command-line terminal

### Compilation & Execution

1. Open your terminal and navigate to the directory containing the source code.
2. Compile the C++ file using `g++`:
```bash
g++ airline_system.cpp -o airline_system

```


3. Run the compiled executable:
* **Windows:** `airline_system.exe`
* **Mac/Linux:** `./airline_system`



---

## 📊 Time and Space Complexity Reference

The following table summarizes the theoretical performance of the algorithms implemented in this system:

| Algorithm / Operation | Best Case | Worst Case | Space Complexity |
| --- | --- | --- | --- |
| **Linear Search** | O(1) | O(n) | O(1) |
| **Binary Search** | O(1) | O(log n) | O(1) |
| **Insertion Sort** | O(n) | O(n²) | O(1) |
| **Merge Sort** | O(n log n) | O(n log n) | O(n) |
| **Quick Sort** | O(n log n) | O(n²) | O(log n) |
| **BST Insert / Search** | O(log n) | O(n) | O(1) |
| **Graph BFS / DFS** | O(V + E) | O(V + E) | O(V) |
| **Linked List Add/Del** | O(1) | O(n) | O(1) |
| **Stack Push/Pop** | O(1) | O(1) | O(1) |
| **Queue Enq/Deq** | O(1) | O(1) | O(1) |

*(Note: V = Vertices/Cities, E = Edges/Routes)*

---

## 💻 Usage Menu Overview

Upon running the program, you will be greeted with an interactive menu spanning all modules:

1. **Janmesh's Module:** Add/Delete passengers, display records, undo actions, and manage the flight boarding queue.
2. **Tanay's Module:** Perform specific searches (Name/ID) and sort the database using various sorting techniques.
3. **Aditya's Module:** Add flights to the BST, look them up, and run network traversals (BFS/DFS) across the pre-initialized city route map.
