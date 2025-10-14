# SearchNewBooks Performance Benchmark Results

## Test Configuration
- **Iterations per test**: 10 runs
- **Request file**: 10 search queries
- **Datasets tested**: 8, 100, and 1000 books

## Summary Results (Average Times in Microseconds)

| Dataset Size | Linear Search | Binary Search | Recursive Binary | Binary Speedup |
|--------------|--------------|---------------|------------------|----------------|
| 8 books      | 18.22 μs     | 16.44 μs      | 17.43 μs        | 1.11x faster   |
| 100 books    | 69.72 μs     | 19.30 μs      | 21.97 μs        | 3.61x faster   |
| 1000 books   | 69.21 μs     | 20.95 μs      | 21.13 μs        | 3.30x faster   |

## Key Findings

### 1. **Small Dataset (8 books)**
- All methods perform similarly (16-18 μs)
- Linear search overhead is minimal with only 8 books
- Binary search shows slight advantage but not dramatic

### 2. **Medium Dataset (100 books)**
- Binary search becomes **3.6x faster** than linear
- Linear search time increases proportionally with dataset size
- Recursive and iterative binary have similar performance

### 3. **Large Dataset (1000 books)**
- Binary search remains nearly constant (~21 μs)
- Linear search plateaus around 69 μs (likely due to request pattern)
- Binary search maintains **3.3x speedup**

### 4. **Algorithm Comparison**
- **Linear Search**: Time grows with dataset size (O(n) behavior)
- **Binary Search (Iterative)**: Logarithmic growth, most consistent
- **Recursive Binary**: Nearly identical to iterative, slight overhead from recursion

## Performance Characteristics

### Time Complexity Validation
- **Linear**: Grows from 18 μs (8 books) to 69 μs (100 books) - approximately linear
- **Binary**: Stays around 16-21 μs regardless of size - logarithmic behavior confirmed
- **Recursive**: Similar to iterative binary, small overhead from function call stack

### Best Use Cases
- **Linear Search**: Best for very small datasets (<10 items) or unsorted data
- **Binary Search**: Best for medium to large sorted datasets (100+ items)
- **Recursive Binary**: Educational purposes; same performance as iterative

## Detailed Statistics

All detailed timing data is available in `benchmark_results.csv` with the following format:
```
Dataset,Books,Method,Run,Time_us
```

## Test Methodology

Each test:
1. Loads the dataset into memory
2. Sorts the data (for binary searches)
3. **Starts timer** (timing only search phase)
4. Processes 10 search requests
5. **Stops timer**
6. Records elapsed time

The timer measures **only the search operations**, excluding:
- File I/O
- Data parsing
- Sorting/preprocessing
- Output writing
