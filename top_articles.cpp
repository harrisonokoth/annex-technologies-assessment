#include <string>
#include <vector>
#include <algorithm>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Callback for libcurl to write response into a string
static size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
    size_t total = size * nmemb;
    output->append((char*)contents, total);
    return total;
}

// Fetch JSON from URL
static std::string fetchJSON(const std::string& url) {
    CURL *curl = curl_easy_init();
    std::string response;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}

struct Article {
    std::string name;
    int comments;
};

// Sort: decreasing comments, then decreasing name alphabetically
static bool compareArticles(const Article& a, const Article& b) {
    if (a.comments != b.comments) return a.comments > b.comments;
    return a.name > b.name;
}

std::vector<std::string> topArticles(int limit) {
    std::vector<Article> allArticles;
    int page = 1;
    int totalPages = 1;
    
    do {
        std::string url = "https://jsonmock.hackerrank.com/api/articles?page=" + std::to_string(page);
        std::string jsonData = fetchJSON(url);
        if (jsonData.empty()) break;
        
        json root = json::parse(jsonData);
        if (page == 1) {
            totalPages = root["total_pages"].get<int>();
        }
        
        for (auto& item : root["data"]) {
            std::string title = item.value("title", "");
            std::string storyTitle = item.value("story_title", "");
            std::string articleName;
            
            if (!title.empty()) articleName = title;
            else if (!storyTitle.empty()) articleName = storyTitle;
            else continue;  // skip if both are null
            
            int comments = item.value("num_comments", 0); // null treated as 0
            allArticles.push_back({articleName, comments});
        }
        page++;
    } while (page <= totalPages);
    
    std::sort(allArticles.begin(), allArticles.end(), compareArticles);
    
    std::vector<std::string> result;
    for (int i = 0; i < limit && i < (int)allArticles.size(); ++i) {
        result.push_back(allArticles[i].name);
    }
    return result;
}