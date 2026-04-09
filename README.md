# DSA System Design in C++

This repository is my personal C++ practice workspace for Data Structures & Algorithms, system design fundamentals, object-oriented design, and C++ core concepts.

## 📌 What’s Included

- **DSA practice** with algorithm implementations and problem-solving code.
- **System design examples** using low-level design and design patterns.
- **C++ concepts** including smart pointers, RAII, multithreading, and custom class design.
- **Real-world case studies** such as notification systems, payment services, and clone-style apps.

## 📁 Repository Structure

### DSA/
- **Binary Search** and array-based search problems.
- **Kadane Algorithm** for maximum subarray problems.
- **Dynamic Programming**:
  - Knapsack (0/1 and Unbounded)
  - Longest Common Subsequence (LCS)
  - Longest Increasing Subsequence (LIS)
  - DP on Trees
  - Palindrome and subsequence problems
- **Graph Algorithms**:
  - Graph representations with adjacency lists and matrices
  - BFS, DFS traversals
  - Cycle detection in directed and undirected graphs
  - Dijkstra, Bellman-Ford, and Floyd-Warshall
  - Minimum spanning tree and DSU
  - Topological sort and bipartite checking

### SystemDesign/
- **Low-Level Design (LLD/)**
  - OOP fundamentals: abstraction, encapsulation, inheritance, polymorphism
  - Design patterns: Factory, Singleton, Builder, Adapter, Decorator, Facade, Command, Observer, Strategy
  - SOLID principles: SRP, OCP, LSP, ISP, DIP
- **System design problems**:
  - Document editor
  - Notification service
  - Parking lot
  - Payment system
  - Spotify clone
  - Zepto clone
  - Zomato clone
- **UML diagrams and design documentation** included as PDFs and images.

### Core C++ Files
- `SmartPointers.cpp` — completed smart pointers topic with unique_ptr, shared_ptr, weak_ptr, and ownership rules.
- `main.cpp` — sample code for smart pointer usage and demonstration.
- `MultiThreading.cpp` — basic multithreading examples.
- `StringClassImplementation.cpp` — custom string class implementation.

## 🚀 Getting Started

### Prerequisites
- C++ compiler (e.g., `g++`, `clang++`)
- Git

### Clone the repository
```bash
git clone https://github.com/NamanAgarwal016/DSA_SystemDesign_Cpp.git
cd DSA_SystemDesign_Cpp
```

### Compile and run a file
```bash
g++ SmartPointers.cpp -o SmartPointers
./SmartPointers
```

To run the general demo:
```bash
g++ main.cpp -o main
./main
```

## 🧠 Notes

- Each `.cpp` file is typically self-contained.
- Use `make` or custom build scripts only if added later.
- Avoid committing compiled binaries; keep the repository source-only when possible.

## 🤝 Contributing

This repo is for learning and sharing. Contributions, improvements, and issue reports are welcome.

## 📄 License

This project is available under the [MIT License](LICENSE).

Happy coding! 🚀
