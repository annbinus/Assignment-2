#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <algorithm>
#include <array>

#define N 50

// Global variables to track the state of cupcake availability and guests' visits
std::array<bool, N> guestsVisited; // Tracks if each guest has visited
std::mutex mtx; 

bool cupcakeAvail = true; // Indicates if the cupcake is available
int guestsEntered = 0; // Number of guests that have entered the labyrinth

unsigned int currGuestId; // Id of the current guest being processed

// Function to generate a random integer between min and max (inclusive)
unsigned int genRandom(int min, int max) {
    std::random_device randomDevice;
    std::mt19937 randomEngine(randomDevice());

    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(randomEngine);
}

// Function representing a guest eating the cupcake
void cupcakeEaten() {
    while (guestsEntered < N) {
        mtx.lock(); // Lock the mutex to ensure exclusive access to shared variables

        if (currGuestId == 0) {
            if (!cupcakeAvail) { // If the cupcake has been eaten by another guest
                guestsEntered++; // Increment the count of guests that have entered
                cupcakeAvail = true; // Reset cupcake availability
            }
            if (cupcakeAvail && !guestsVisited[0]) { // If the cupcake is available and the guest hasn't visited yet
                guestsEntered++; // Increment the count of guests that have entered
                cupcakeAvail = true;
                guestsVisited[0] = true; // Mark the guest as visited
            }
        }
        mtx.unlock(); // Unlock the mutex to allow other threads to access shared variables
    }
}

// Function representing a guest entering the labyrinth
void enterLabyrinth(unsigned int guestId) {
    while (guestsEntered < N) {
        mtx.lock(); // Lock the mutex to ensure exclusive access to shared variables

        if (currGuestId == guestId && cupcakeAvail && !guestsVisited[guestId]) {
            cupcakeAvail = false; // Reserve the cupcake
            guestsVisited[guestId] = true; // Mark the guest as visited
            std::cout << "Guest #" << guestId << " ate the cupcake!" << std::endl; // Inform that the guest ate the cupcake
        }
        mtx.unlock(); // Unlock the mutex to allow other threads to access shared variables
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now(); // Record the start time

    // Create an array of threads representing guests
    std::array<std::thread, N> threads{};
    threads[0] = std::thread(cupcakeEaten); // The first thread eats the cupcake

    // Create threads for the remaining guests to enter the labyrinth
    for (size_t i = 1; i < threads.size(); i++) {
        threads[i] = std::thread(enterLabyrinth, i);
    }

    // Wait until all guests have entered the labyrinth
    while (guestsEntered < N) {
        currGuestId = genRandom(0, N); // Randomly select a guest to enter
    }

    // Wait for all threads to finish execution
    for (auto& thread : threads)
        thread.join();

    auto end = std::chrono::high_resolution_clock::now(); // Record the end time
    auto duration = std::chrono::duration<double, std::milli>(end-start); // Calculate the duration

    // Output the completion message and the duration of execution
    std::cout << "All guests have visited the Labyrinth." << std::endl;
    std::cout << "Finished in " << duration.count() << "ms" << std::endl;
}
