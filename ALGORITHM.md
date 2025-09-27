1️⃣ Các Giải Thuật Sắp Xếp (Sorting Algorithms)
QuickSort, MergeSort, HeapSort – sắp xếp O(n log n).
Counting Sort, Radix Sort, Bucket Sort – sắp xếp tuyến tính O(n) (khi dữ liệu có giới hạn).
Ứng dụng: tìm median, tối ưu hóa bài toán, chuẩn bị dữ liệu để dùng two pointers / binary search.

2️⃣ Tìm kiếm (Searching)
Binary Search – O(log n), tìm phần tử hoặc giá trị thỏa mãn điều kiện trong dãy đã sắp xếp.
Ternary Search – tìm cực trị (min/max) trên hàm đơn điệu hoặc unimodal.
Exponential Search – kết hợp khi mảng vô hạn hoặc không biết kích thước.

3️⃣ Thuật Toán Tham Lam (Greedy Algorithms)
Chọn phương án tốt nhất cục bộ để dẫn đến kết quả toàn cục tối ưu.
Ví dụ:
    Interval Scheduling (chọn nhiều khoảng thời gian nhất).
    Huffman Coding (mã hóa tối ưu).
    Prim’s / Kruskal’s Algorithm (Minimum Spanning Tree).
    Dijkstra (với Priority Queue) – tìm đường đi ngắn nhất.

4️⃣ Quy Hoạch Động (Dynamic Programming - DP)
Chia bài toán thành bài toán con, lưu kết quả trung gian.
Các mẫu DP phổ biến:
    0/1 Knapsack (cơ bản của nhiều bài).
    Coin Change / Ways to Sum.
    Longest Increasing Subsequence (LIS).
    Matrix DP (ví dụ: đường đi ngắn nhất trên lưới).
    Bitmask DP (bài toán trạng thái nhỏ, TSP).
    Digit DP (đếm số thỏa điều kiện trên đoạn).

5️⃣ Thuật Toán Đồ Thị (Graph Algorithms)
DFS, BFS – tìm kiếm đồ thị.
Dijkstra, Bellman-Ford, Floyd-Warshall – shortest path.
Topological Sort – sắp xếp đồ thị có hướng không chu trình (DAG).
Union-Find / DSU – tìm thành phần liên thông, MST.
Tarjan / Kosaraju – tìm SCC (strongly connected components).
Max Flow (Ford-Fulkerson, Edmonds-Karp, Dinic) – bài toán luồng cực đại.

6️⃣ Chia để trị (Divide & Conquer)
Binary Search on Answer (parametric search).
FFT (Fast Fourier Transform) – nhân đa thức nhanh (bài toán convolution).
Segment Tree / Fenwick Tree (BIT) – truy vấn và cập nhật nhanh.
Sparse Table – RMQ (Range Minimum Query) khi dữ liệu tĩnh.

7️⃣ Kỹ thuật Hai Con Trỏ & Sliding Window
Giải bài toán tìm dãy con, đếm số cặp thỏa điều kiện, tối ưu O(n).
Ứng dụng: subarray sum, longest substring without repeating characters.

8️⃣ Xử lý Chuỗi (String Algorithms)
KMP Algorithm – tìm pattern trong chuỗi.
Z-Algorithm – tìm các khớp pattern nhanh.
Suffix Array + LCP – xử lý chuỗi nâng cao.
Trie – tìm kiếm từ khóa.
Rabin-Karp – hashing chuỗi.

9️⃣ Toán Học (Math Algorithms)
Sàng Eratosthenes – tìm số nguyên tố.
GCD / LCM (Euclid).
Modular Exponentiation, Modular Inverse.
Combinatorics (nCr, nPr) + Fermat’s Little Theorem.
Number Theory: Chinese Remainder Theorem (CRT), phi Euler, phân tích thừa số nguyên tố.
Geometry: CCW, Convex Hull (Graham Scan, Andrew Monotone Chain), Line Intersection.

🔟 Thuật Toán Nâng Cao
Mo’s Algorithm – xử lý truy vấn offline tối ưu.
Heavy-Light Decomposition – truy vấn trên cây.
Centroid Decomposition – tối ưu trên cây.
Persistent Data Structure – lưu trạng thái nhiều phiên bản.
Suffix Automaton – xử lý chuỗi nâng cao.
Muốn luyện giải thuật thi đấu, em nên:
Bắt đầu từ Sorting, Binary Search, Greedy, DP, Graph Basics.
Luyện trên các trang như Codeforces, AtCoder, LeetCode, CSES.
Khi quen rồi hãy học Segment Tree, DSU, Mo’s Algorithm, FFT, Flow.
Em có muốn anh lập một roadmap học giải thuật thi đấu theo mức độ khó (Beginner → Advanced) để em luyện dần không?
Như kiểu tuần 1 học sort + binary search, tuần 2 học greedy + basic DP,... để dễ theo dõi.

-----------------------------------------------------------------------------------------------------------------------
🛣 Roadmap Học Giải Thuật Thi Đấu
📍 Giai Đoạn 1: Cơ Bản (Weeks 1–4)
Mục tiêu: Làm quen với tư duy thuật toán, xử lý input/output nhanh, các kỹ thuật nền tảng.

✅ Tuần 1 – Cấu trúc dữ liệu & Sort/Search
Ôn lại C/C++ STL: vector, set, map, priority_queue.
Sorting: Selection, Bubble, Insertion → MergeSort, QuickSort.
Binary Search & ứng dụng.
Bài tập: tìm số trong mảng, lower_bound, upper_bound, tìm giá trị nhỏ nhất/lớn nhất thỏa điều kiện.

✅ Tuần 2 – Two Pointers & Sliding Window
Two pointers để đếm số cặp, subarray sum ≤ k.
Sliding Window để tìm dãy con dài nhất (ví dụ: longest substring không trùng ký tự).

✅ Tuần 3 – Toán Cơ Bản & Hashing
GCD/LCM (Euclid).
Modular Arithmetic, Modular Exponentiation.
Prime Sieve (Sàng Eratosthenes).
Prefix Sum / Difference Array.
Hashing cơ bản (Rabin–Karp).

✅ Tuần 4 – Đệ Quy & Backtracking
Sinh hoán vị, tổ hợp, subset.
Bài toán n-queens, sudoku cơ bản.
Làm quen với tư duy trạng thái (sẽ dùng cho DP).

📍 Giai Đoạn 2: Trung Cấp (Weeks 5–12)
Mục tiêu: Làm chủ Greedy, DP, Graph cơ bản.

✅ Tuần 5 – Greedy
Interval Scheduling (chọn số lượng đoạn lớn nhất).
Minimum Number of Platforms.
Activity Selection, Huffman Coding.

✅ Tuần 6–7 – Dynamic Programming (DP)
1D DP: Fibonacci, Coin Change, LIS O(n²).
2D DP: Knapsack, Grid Path, Edit Distance.
Optimization: prefix sum để giảm độ phức tạp.

✅ Tuần 8 – DP Nâng Cao
LIS O(n log n).
Bitmask DP (Traveling Salesman Problem).
Digit DP (đếm số thỏa mãn điều kiện trên [L, R]).

✅ Tuần 9–10 – Đồ Thị Cơ Bản
DFS, BFS – tìm thành phần liên thông, shortest path không trọng số.
Topological Sort (Kahn + DFS).
Union-Find / DSU – tìm thành phần liên thông nhanh.

✅ Tuần 11–12 – Đồ Thị Nâng Cao
Dijkstra, Bellman-Ford, Floyd-Warshall – shortest path có trọng số.
Prim/Kruskal – MST.
Tarjan / Kosaraju – tìm SCC.

📍 Giai Đoạn 3: Nâng Cao (Weeks 13–24)
Mục tiêu: Làm quen với giải thuật phức tạp, tối ưu hóa query, xử lý chuỗi nâng cao.

✅ Tuần 13–14 – Segment Tree & Fenwick Tree
Range Sum / Range Min Query.
Lazy Propagation để cập nhật range nhanh.

✅ Tuần 15 – Sparse Table
RMQ cho dữ liệu tĩnh.
So sánh với Segment Tree.

✅ Tuần 16–17 – String Algorithms
KMP, Z-Algorithm.
Suffix Array + LCP.
Trie.

✅ Tuần 18–19 – Thuật Toán Trên Cây
DFS order, Binary Lifting (LCA).
Subtree Query với Segment Tree.

✅ Tuần 20 – Chia Để Trị Nâng Cao
Binary Search on Answer.
Divide & Conquer DP Optimization.

✅ Tuần 21–22 – Thuật Toán Luồng & Matching
Ford-Fulkerson, Edmonds-Karp, Dinic.
Bipartite Matching (Hungarian Algorithm).

✅ Tuần 23–24 – Các Thuật Toán Đặc Biệt
Mo’s Algorithm (query offline).
Centroid Decomposition.
FFT (Fast Fourier Transform).

📍 Giai Đoạn 4: Chuyên Gia (Sau 6 tháng)
Mục tiêu: Chuẩn bị cho contest khó (CF Div.1, ICPC Regional).
Persistent Data Structures (Segment Tree, DSU).
Suffix Automaton (xử lý chuỗi cực mạnh).
Treap / Splay Tree – cây tự cân bằng.
Number Theory nâng cao:
Chinese Remainder Theorem.
Pollard Rho (factorization).
NTT (Number Theoretic Transform).

📌 Lời khuyên:
Duy trì luyện giải ít nhất 5–10 bài/tuần trên Codeforces, AtCoder hoặc CSES.
Ghi chú lại mẫu lời giải (template) cho từng giải thuật.
Mỗi khi gặp bài khó, đọc editorial, phân tích vì sao mình không nghĩ ra.