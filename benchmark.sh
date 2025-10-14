#!/bin/bash

# Benchmark script for SearchNewBooks
# Runs each dataset with each search method 10 times and collects timing data

# Color codes for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo "=== SearchNewBooks Performance Benchmark ==="
echo ""

# Create datasets if they don't exist
echo "Preparing datasets..."

# Small dataset: 8 books
if [ ! -f newbooks_8.dat ]; then
    cat > newbooks_8.dat << 'EOF'
1,english,new
2,french,used
3,spanish,digital
4,german,new
5,italian,used
6,portuguese,new
7,chinese,digital
8,japanese,new
EOF
fi

# Medium dataset: 100 books
if [ ! -f newbooks_100.dat ]; then
    for i in {1..100}; do
        echo "$i,english,new" >> newbooks_100.dat
    done
fi

# Large dataset: 1000 books
if [ ! -f newbooks_1000.dat ]; then
    for i in {1..1000}; do
        echo "$i,english,new" >> newbooks_1000.dat
    done
fi

# Request file with 10 requests
if [ ! -f request_10.dat ]; then
    cat > request_10.dat << 'EOF'
5,english,new
15,english,new
25,english,new
35,english,new
45,english,new
55,english,new
65,english,new
75,english,new
85,english,new
95,english,new
EOF
fi

# Arrays for datasets and search methods
datasets=("newbooks_8.dat:8" "newbooks_100.dat:100" "newbooks_1000.dat:1000")
methods=("l:Linear" "b:Binary" "r:Recursive")

# Results file
results_file="benchmark_results.csv"
echo "Dataset,Books,Method,Run,Time_us" > $results_file

echo "Running benchmarks (10 iterations each)..."
echo ""

# Run benchmarks
for dataset_info in "${datasets[@]}"; do
    IFS=':' read -r dataset size <<< "$dataset_info"
    
    for method_info in "${methods[@]}"; do
        IFS=':' read -r method method_name <<< "$method_info"
        
        echo -e "${BLUE}Testing: $dataset ($size books) with $method_name search${NC}"
        
        for run in {1..10}; do
            # Run the program and capture output
            output=$(echo "$method" | ./SearchNewBooks "$dataset" request_10.dat output_temp.txt 2>/dev/null)
            
            # Extract the time from output (format: "CPU time: 123.45 microseconds")
            time_us=$(echo "$output" | grep "CPU time:" | awk '{print $3}')
            
            # Save to results
            echo "$dataset,$size,$method_name,$run,$time_us" >> $results_file
            
            printf "  Run %2d: %s μs\n" $run "$time_us"
        done
        echo ""
    done
done

echo -e "${GREEN}Benchmark complete! Results saved to $results_file${NC}"
echo ""

# Generate summary statistics
echo "=== Summary Statistics (Average Times in microseconds) ==="
echo ""

printf "%-20s | %-10s | %-15s | %-15s | %-15s\n" "Dataset" "Books" "Linear" "Binary" "Recursive"
printf "%-20s-+-%-10s-+-%-15s-+-%-15s-+-%-15s\n" "--------------------" "----------" "---------------" "---------------" "---------------"

for dataset_info in "${datasets[@]}"; do
    IFS=':' read -r dataset size <<< "$dataset_info"
    
    # Calculate averages for each method
    linear_avg=$(grep "$dataset,.*,Linear" $results_file | awk -F',' '{sum+=$5; count++} END {if(count>0) printf "%.2f", sum/count; else print "N/A"}')
    binary_avg=$(grep "$dataset,.*,Binary" $results_file | awk -F',' '{sum+=$5; count++} END {if(count>0) printf "%.2f", sum/count; else print "N/A"}')
    recursive_avg=$(grep "$dataset,.*,Recursive" $results_file | awk -F',' '{sum+=$5; count++} END {if(count>0) printf "%.2f", sum/count; else print "N/A"}')
    
    printf "%-20s | %-10s | %-15s | %-15s | %-15s\n" "$dataset" "$size" "$linear_avg" "$binary_avg" "$recursive_avg"
done

echo ""
echo "Detailed results available in: $results_file"

# Cleanup temp file
rm -f output_temp.txt
