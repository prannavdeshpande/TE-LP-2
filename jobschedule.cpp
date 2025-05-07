#include <iostream>
#include <vector>
#include <algorithm>

// Structure to represent a job
struct Job {
    int id;
    int deadline;
    int profit;
};

// Comparison function to sort jobs by profit in descending order
bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

// Function to schedule jobs to maximize profit
int jobScheduling(std::vector<Job>& jobs) {
    // Sort jobs by profit in descending order
    std::sort(jobs.begin(), jobs.end(), compare);

    // Find the maximum deadline, capped at number of jobs
    int maxDeadline = 0;
    for (const auto& job : jobs) {
        maxDeadline = std::max(maxDeadline, job.deadline);
    }
    maxDeadline = std::min(maxDeadline, static_cast<int>(jobs.size()));

    // Initialize time slots and selected jobs
    std::vector<bool> slot(maxDeadline, false);
    std::vector<std::pair<int, int>> selectedJobs; // Stores (job ID, slot)
    int totalProfit = 0;

    // Schedule each job in the latest possible free slot
    for (const auto& job : jobs) {
        // Try to find a free slot from deadline-1 to 0
        for (int j = std::min(job.deadline, maxDeadline) - 1; j >= 0; j--) {
            if (!slot[j]) {
                slot[j] = true;
                selectedJobs.emplace_back(job.id, j);
                totalProfit += job.profit;
                break;
            }
        }
    }

    // Print selected jobs and their assigned slots
    std::cout << "Selected Job IDs and Slots:\n";
    for (const auto& [id, slot] : selectedJobs) {
        std::cout << "Job " << id << " scheduled at slot " << slot << "\n";
    }
    std::cout << "Number of jobs scheduled: " << selectedJobs.size() << "\n";

    return totalProfit;
}

// Main function
int main() {
    int n;
    std::cout << "Enter number of jobs: ";
    while (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid input. Enter a positive number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::vector<Job> jobs(n);
    std::cout << "Enter deadline and profit for each job (e.g., 2 100):\n";
    for (int i = 0; i < n; ++i) {
        int deadline, profit;
        while (!(std::cin >> deadline >> profit) || deadline <= 0 || profit < 0) {
            std::cout << "Invalid input. Enter positive deadline and non-negative profit: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        jobs[i] = {i + 1, deadline, profit}; // Assign 1-based job ID
    }

    int maxProfit = jobScheduling(jobs);
    std::cout << "Maximum Profit: " << maxProfit << "\n";

    return 0;
}

// Greedy Concept:
// Jobs are sorted by profit in descending order. Each job is scheduled in the latest
// possible free slot before its deadline to maximize total profit. This ensures the
// optimal selection of high-profit jobs within time constraints.

// Time Complexity:
// - Sorting: O(n log n)
// - Scheduling: O(n * min(n, maxDeadline)) where maxDeadline is the maximum job deadline
// - Overall: O(n log n + n * min(n, maxDeadline))
// Space Complexity:
// - O(n) for slot tracking and selected jobs