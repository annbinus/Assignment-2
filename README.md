# Minotaur's Birthday Party

## Running the Code:

To run the code, you first need to clone the repository to your local machine. Here are the general steps to do so:

1. Clone the Repository:

Open a terminal or command prompt and navigate to the directory where you want to clone the repository. Then, use the git clone command followed by the repository URL. For example:

```
git clone https://github.com/annbinus/Assignment-2.git
```

2. Navigate to the Directory:

After cloning the repository, navigate to the directory containing the code files using the cd command:

3. Compile and Run the Code:

Once inside the repository directory, you can compile and run the code files using the appropriate commands. For C++ code, you typically compile using a compiler like g++ and then execute the compiled binary.

```
g++ -o Problem1 Problem1.cpp
./Problem1
```

## The Problem

The Minotaur invited N guests to his birthday party. When the guests arrived, he made the following announcement.

The guests may enter his labyrinth, one at a time and only when he invites them to do so. At the end of the labyrinth, the Minotaur placed a birthday cupcake on a plate. When a guest finds a way out of the labyrinth, he or she may decide to eat the birthday cupcake or leave it. If the cupcake is eaten by the previous guest, the next guest will find the cupcake plate empty and may request another cupcake by asking the Minotaur's servants. When the servants bring a new cupcake the guest may decide to eat it or leave it on the plate.

The Minotaur's only request for each guest is to not talk to the other guests about her or his visit to the labyrinth after the game has started. The guests are allowed to come up with a strategy prior to the beginning of the game. There are many birthday cupcakes, so the Minotaur may pick the same guests multiple times and ask them to enter the labyrinth. Before the party is over, the Minotaur wants to know if all of his guests have had the chance to enter his labyrinth. To do so, the guests must announce that they have all visited the labyrinth at least once.

Now the guests must come up with a strategy to let the Minotaur know that every guest entered the Minotaur's labyrinth. It is known that there is already a birthday cupcake left at the labyrinth's exit at the start of the game. How would the guests do this and not disappoint his generous and a bit temperamental host?

Create a program to simulate the winning strategy (protocol) where each guest is represented by one running thread. In your program you can choose a concrete number for N or ask the user to specify N at the start.

## The Solution

Thread Creation:

- N threads are created to represent the guests at the Minotaur's birthday party.
- The first thread is responsible for counting how many times it replaces the cupcake.
- The other N - 1 threads are responsible for eating the cupcake, but each thread will only eat it once.

Thread Behavior:

- Each thread waits until it's randomly selected to enter the labyrinth.
- When a thread is selected, it eats the cupcake if it's available.
- After eating the cupcake, the thread marks itself to prevent eating another cupcake.

Termination Condition:

- The counter thread keeps track of how many guests have entered the labyrinth by counting cupcake replacements.
- Once every thread has had a chance to eat the cupcake and the counter thread counts N guests, the program terminates.

Implementation Details:

- Threads use synchronization mechanisms like mutexes or condition variables to ensure proper coordination.
- Each thread handles its own logic independently, avoiding explicit communication between threads about their visits to the labyrinth.

Conclusion:

By using a combination of a counter thread and N - 1 guest threads, the solution ensures that every guest has a chance to enter the labyrinth and eat the cupcake without violating the Minotaur's rule of not talking about it with each other.

# Proof of Correctness:
- Each guest enters the labyrinth exactly once.
- Guests do not communicate with each other directly, adhering to the Minotaur's request.
- The program tracks whether each guest has visited the labyrinth.
- The cupcake is eaten by at most one guest.

# Efficiency:
- The program minimizes busy waiting by using a condition variable.
- Locking is kept minimal to reduce contention.
- Random guest selection ensures fairness and prevents bias.

# Minotaur's Crystal Vase

## The Problem

The Minotaur decided to show his favorite crystal vase to his guests in a dedicated showroom with a single door. He did not want many guests to gather around the vase and accidentally break it. For this reason, he would allow only one guest at a time into the showroom. He asked his guests to choose from one of three possible strategies for viewing the Minotaur's favorite crystal vase:

1. Any guest could stop by and check whether the showroom's door is open at any time and try to enter the room. While this would allow the guests to roam around the castle and enjoy the party, this strategy may also cause large crowds of eager guests to gather around the door. A particular guest wanting to see the vase would also have no guarantee that she or he will be able to do so and when.

2. The Minotaur's second strategy allowed the guests to place a sign on the door indicating when the showroom is available. The sign would read "AVAILABLE" or "BUSY." Every guest is responsible to set the sign to "BUSY" when entering the showroom and back to "AVAILABLE" upon exit. That way guests would not bother trying to go to the showroom if it is not available.

3. The third strategy would allow the quests to line in a queue. Every guest exiting the room was responsible to notify the guest standing in front of the queue that the showroom is available. Guests were allowed to queue multiple times.

Which of these three strategies should the guests choose? Please discuss the advantages and disadvantages.

Implement the strategy/protocol of your choice where each guest is represented by 1 running thread. You can choose a concrete number for the number of guests or ask the user to specify it at the start.

## The Solution

The solution implements the Sign-based Availability strategy, where guests set a sign indicating the availability of the showroom. This strategy offers clarity and reduces congestion by allowing guests to enter only when the showroom is available. It utilizes a mutex for safe resource access and tracks guests' visits to ensure fairness. Compared to the Open Door Policy, it minimizes congestion and uncertainty. Unlike the Queue-based System, it avoids potential waiting times and confusion from multiple queues. Overall, this strategy balances efficiency, clarity, and guest satisfaction effectively.

- The program simulates the sign-based availability strategy using threads to represent guests.
- Guests attempt to enter the showroom only when the room is available.
- A global mutex ensures exclusive access to shared variables, including the room status and the set of guests who have already visited the vase.
- Each guest thread admires the vase for a random duration, simulating the viewing experience.

# Proof of Correctness:
- Each guest thread enters the showroom only when the room is available and has not already visited the vase.
- Guests are added to the set of visitors once they have admired the vase.
- The room status is correctly updated to indicate availability or busyness.
- The program ensures mutual exclusion when accessing shared variables, preventing race conditions.

# Efficiency:
- The program minimizes waiting time by allowing guests to enter the showroom promptly when it is available.
- Threads efficiently utilize CPU resources, as they sleep while waiting for the room to become available.
- The use of a mutex ensures efficient synchronization and prevents contention among threads.