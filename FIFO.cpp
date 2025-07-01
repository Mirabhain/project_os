#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip> // For formatting output

int main() {
    int available;
    std::cout << "Enter number of available frames: ";
    std::cin >> available;
    std::cin.ignore(); // Clear newline from the buffer

    std::vector<int> frames(available, -1); // Initialize with -1 (empty)
    int faults = 0;
    int read = 0;
    std::string line;
    bool found;

    std::cout << "Enter page numbers one per line (Ctrl+D to end input on Linux/Mac, Ctrl+Z then Enter on Windows):\n";

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        int current_page = std::stoi(line);
        read++;
        found = false;

        // Check if current page is already in memory
        for (int i = 0; i < available; i++) {
            if (frames[i] == current_page) {
                found = true;
                break;
            }
        }

        if (!found) {
            faults++;

            // Shift all pages to the right
            for (int i = available - 1; i > 0; i--) {
                frames[i] = frames[i - 1];
            }
            frames[0] = current_page;

            // Show page replacement info
            std::cout << "Page " << current_page << " caused a page fault.\n";
            std::cout << "Current memory: [ ";
            for (int f : frames) {
                if (f == -1)
                    std::cout << "_ ";
                else
                    std::cout << f << " ";
            }
            std::cout << "]\n";
        }
    }

    double hit_rate = (read - faults) / static_cast<double>(read);

    std::cout << "\nTotal number of page faults: " << faults << "\n";
    std::cout << "Hit rate: " << std::fixed << std::setprecision(2) << hit_rate << "\n";

    return 0;
}
