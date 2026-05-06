================================================================================
Annex Technologies Limited – Technical Assessment
Candidate: Harrison Okoth
Date: 06-05-2026
================================================================================

This archive contains three solutions for the SOFTWARE ENGINEER assessment.

FOLDER STRUCTURE:
-----------------
Annex_Assessment_Harrison_Okoth/
  ├── pth_factor.c          (Question 1 – C)
  ├── top_students.sql      (Question 2 – MySQL)
  ├── top_articles.cpp      (Question 3 – C++)
  └── README.txt            (this file)

================================================================================
QUESTION 1: pth_factor.c
================================================================================
Problem: Given n (1 ≤ n ≤ 10^15) and p (1 ≤ p ≤ 10^9), find the p-th smallest
positive factor of n. If fewer than p factors exist, return 0.

Solution Approach:
- Find all factor pairs (i, n/i) by iterating i up to sqrt(n).
- Store small factors (≤ sqrt(n)) in an array in ascending order.
- Store corresponding large factors (> sqrt(n)) in a separate array
  (they are naturally in descending order).
- Total factors = cnt_small + cnt_large.
- If p > total → return 0.
- If p <= cnt_small → return small[p-1].
- Else → pick from large array: large[total-p].

Time Complexity: O(√n)
Space Complexity: O(√n)

Compilation & Testing (Linux/macOS with GCC):
    gcc pth_factor.c -o pth_factor -lm
    (Add a test harness to call pthFactor(n,p) with sample inputs.)

Sample Run (if test main added):
    Input: n=10, p=3
    Output: 5

================================================================================
QUESTION 2: top_students.sql
================================================================================
Problem: Retrieve ID and NAME of the three highest-scoring students.
Sort by SCORE descending, then by ID ascending.

Solution:
    SELECT ID, NAME
    FROM STUDENT
    ORDER BY SCORE DESC, ID ASC
    LIMIT 3;



Tested against the sample input:
    Expected Output: (6, Sid), (7, Tom), (4, Dick)

================================================================================
QUESTION 3: top_articles.cpp
================================================================================
Problem: Fetch all pages from HackerRank Articles API
(https://jsonmock.hackerrank.com/api/articles?page=<pageNumber>).
Determine article name: use title if non-null, else story_title if non-null.
Skip if both are null.
Sort by num_comments descending (null = 0), then by name alphabetically descending.
Return top 'limit' article names as vector<string>.

Solution Approach:
- Use libcurl for HTTP GET requests.
- Use nlohmann/json (header-only) for JSON parsing.
- Paginate using total_pages field from first response.
- Collect all valid articles, sort with custom comparator, return first 'limit'.

Dependencies:
- libcurl development library
- nlohmann/json (header-only – just need json.hpp in include path)

Compilation (Ubuntu/Debian example):
    sudo apt install libcurl4-openssl-dev nlohmann-json3-dev
    g++ -std=c++17 top_articles.cpp -o top_articles -lcurl

If nlohmann/json is not system-installed, download json.hpp from:
    https://github.com/nlohmann/json/releases
and place it next to the .cpp file or adjust include path.

Testing (add a main function):
    #include <iostream>
    int main() {
        auto res = topArticles(2);
        for (auto& name : res) std::cout << name << std::endl;
        return 0;
    }

Expected output for limit=2:
    UK votes to leave EU
    F.C.C. Repeals Net Neutrality Rules


================================================================================
END OF README
================================================================================