# Discrete Mathematics & Graph Theory Solutions

This repository contains C++ programs that implement classic problems from discrete structures and graph theory. Each program demonstrates important theoretical concepts through practical coding exercises.

---

## Contents

1. **Graph Bipartite Checker**
2. **Graph Walks and Paths Analyzer**
3. **Relation Properties with Pair Suggestions(Symmetric, Reflexive, Transitive Checks)**
4. **Equivalence Check for Logical Expressions**


## Tasks Overview

### 1. Graph Bipartite Checker

**Purpose:**
Determines if a given graph is bipartite — i.e., if its vertices can be divided into two sets such that no edge connects vertices within the same set.

**Input:**

* Number of vertices and edges
* List of edges

**Output:**

* Confirms whether the graph is bipartite or not.

---

### 2. Graph Type Checker

**Purpose:**
Analyzes a graph to detect the presence of specific walk and path types including:

* Walk
* Closed Walk
* Circuit
* Simple Circuit
* Path
* Simple Path

**Input:**

* Number of vertices and edges
* List of edges

**Output:**

* Indicates which types of walks and paths exist in the graph.

---

### 3. Logic Equivalence Checker

**Purpose:**
Checks if two logical expressions are equivalent by evaluating their truth tables or structural equivalence.

**Input:**

* Two logical expressions (or truth tables)

**Output:**

* Confirms whether the expressions are logically equivalent or not.

---

### 4. Matrix Relation Analyzer

**Purpose:**
Analyzes a binary relation represented as a matrix for key properties:

* Symmetry
* Reflexivity
* Transitivity

**Input:**

* Size of matrix
* Matrix elements (0/1 indicating relation presence)

**Output:**

* States whether the relation satisfies each property.
* Suggests missing pairs to make the relation symmetric, reflexive, or transitive.

---

## Example (Matrix Relation Analyzer)

```
Enter size of matrix: 3
Enter matrix elements:
1 0 1
0 1 0
1 0 1
```

Output:

```
Symmetric: YES  
Reflexive: YES  
Transitive: NO  
Pairs to make it Transitive: (1, 2)
```
---

## How to Use

* Compile with a standard C++ compiler (e.g., g++).
* Input the size and adjacency matrix as prompted.
* Review output for properties and pair suggestions.

---

## Example Input (for relation properties)

```
4
1 0 0 1
0 1 0 0
0 0 1 0
1 0 0 1
```

---

## Technologies

* C++
* Windows Console API (for colored output)

---

## Notes

* Programs assume input matrices are square and contain only 0 or 1 values.
* For graph walks, vertices are assumed zero-indexed.

---
##Credits 
* Rafay Adeel

If you want, I can help you generate actual filenames or additional instructions for compiling and running each file! Would you like that?
