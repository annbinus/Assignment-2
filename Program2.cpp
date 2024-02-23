#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <array>
#include <deque>
#include <unordered_set>

#define NUM_GUESTS 50

std::unordered_set<std::thread::id> guestsVisited{};
std::mutex mtx;
enum Status {
    AVAILABLE,
    BUSY
};
Status roomStatus = Status::AVAILABLE;

// Function to generate a random integer between min and max (inclusive)
unsigned int genRandom(int min, int max) {
    std::random_device randomDevice;
    std::mt19937 randomEngine(randomDevice());

    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(randomEngine);
}

// Function representing a guest admiring the vase
void admireVase(int threadIndex) {
    std::thread::id threadId = std::this_thread::get_id();

    // Loop until all guests have admired the vase
    while (guestsVisited.size() < NUM_GUESTS) {
        mtx.lock(); // Lock the mutex to ensure exclusive access to shared variables

        // If the room is available and the current guest hasn't admired the vase yet
        if (roomStatus == Status::AVAILABLE && guestsVisited.find(threadId) == guestsVisited.end()) {
            roomStatus = Status::BUSY; // Set room status to busy
            std::cout << "Guest #" << threadIndex << " is admiring the vase" << std::endl; // Inform that the guest is admiring the vase
            std::this_thread::sleep_for(std::chrono::milliseconds(genRandom(10, 500))); // Simulate the guest admiring the vase
            roomStatus = Status::AVAILABLE; // Set room status back to available

            guestsVisited.insert(threadId); // Mark the guest as having admired the vase
        }

        mtx.unlock(); // Unlock the mutex to allow other threads to access shared variables
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now(); // Record the start time

    std::array<std::thread, NUM_GUESTS> threads{}; // Array to hold threads representing guests

    // Create threads for each guest to admire the vase
    for (size_t i = 0; i < threads.size(); i++) {
        threads[i] = std::thread(admireVase, i);
    }

    // Wait for all threads to finish execution
    for (auto& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now(); // Record the end time
    auto duration = std::chrono::duration<double, std::milli>(end - start); // Calculate the duration

    // Output the completion message and the duration of execution
    std::cout << "All guests have viewed the vase." << std::endl;
    std::cout << "Finished in " << duration.count() << "ms" << std::endl;
}
