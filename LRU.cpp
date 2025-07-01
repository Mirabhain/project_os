#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <limits>

int main() {
    int available;
    std::cout << "Enter number of available frames: ";
    std::cin >> available;
    std::cin.ignore(); // Clear newline

    std::vector<int> frames;
    std::unordered_map<int, int> last_used; // page -> last used time

    int faults = 0, read = 0, time = 0;
    std::string line;

    std::cout << "Enter page numbers one per line (Ctrl+D or Ctrl+Z to end):\n";

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        int current_page = std::stoi(line);
        read++;
        time++;

        bool found = false;

        // Check if page is in memory
        for (int page : frames) {
            if (page == current_page) {
                found = true;
                break;
            }
        }

        if (!found) {
            faults++;
            std::cout << "Page " << current_page << " caused a page fault.\n";

            // If memory full, evict LRU page
            if (frames.size() == available) {
                int lru_page = -1;
                int oldest_time = std::numeric_limits<int>::max();

                for (int page : frames) {
                    if (last_used[page] < oldest_time) {
                        oldest_time = last_used[page];
                        lru_page = page;
                    }
                }

                // Remove LRU page
                for (auto it = frames.begin(); it != frames.end(); ++it) {
                    if (*it == lru_page) {
                        frames.erase(it);
                        break;
                    }
                }
            }

            // Add current page
            frames.push_back(current_page);
        }

        // Update last used time
        last_used[current_page] = time;

        // Show memory state
        std::cout << "Current memory: [ ";
        for (int i = 0; i < available; i++) {
            if (i < frames.size()) std::cout << frames[i] << " ";
            else std::cout << "_ ";
        }
        std::cout << "]\n";
    }

    double hit_rate = (read - faults) / static_cast<double>(read);
    std::cout << "\nTotal number of page faults: " << faults << "\n";
    std::cout << "Hit rate: " << std::fixed << std::setprecision(2) << hit_rate << "\n";

    return 0;
}
