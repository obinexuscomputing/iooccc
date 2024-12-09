#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Define quantum states
#define STATE_00 0b00
#define STATE_01 0b01
#define STATE_10 0b10
#define STATE_11 0b11

// Buffer size for visualization
#define VIS_WIDTH 50
#define VIS_HEIGHT 10

typedef struct {
    int state;
    double probability;
} QuantumState;

// Initialize quantum system
void init_quantum_system() {
    srand(time(NULL));
}

// Print binary representation of state
void print_binary_state(int state) {
    printf("|%d%d⟩", (state & 0b10) >> 1, state & 0b01);
}

// Create visual representation of superposition
void visualize_superposition(QuantumState states[], int num_states) {
    char canvas[VIS_HEIGHT][VIS_WIDTH];
    memset(canvas, ' ', sizeof(canvas));
    
    // Draw probability distribution
    for (int i = 0; i < num_states; i++) {
        int height = (int)(states[i].probability * (VIS_HEIGHT - 2));
        int col = (VIS_WIDTH / (num_states + 1)) * (i + 1);
        
        // Draw vertical bar
        for (int j = 0; j < height; j++) {
            canvas[VIS_HEIGHT - 2 - j][col] = '|';
        }
        
        // Draw state label
        canvas[VIS_HEIGHT - 1][col - 1] = '0' + ((states[i].state & 0b10) >> 1);
        canvas[VIS_HEIGHT - 1][col] = '0' + (states[i].state & 0b01);
    }
    
    // Print visualization
    printf("\nQuantum State Visualization:\n");
    for (int i = 0; i < VIS_HEIGHT; i++) {
        for (int j = 0; j < VIS_WIDTH; j++) {
            putchar(canvas[i][j]);
        }
        putchar('\n');
    }
    for (int j = 0; j < VIS_WIDTH; j++) {
        putchar('-');
    }
    putchar('\n');
}

// Apply quantum operations
int apply_quantum_operations(int state) {
    // Complex state transition using multiple bitwise operations
    int xor_result = state ^ ((rand() % 4));  // XOR with random state
    int and_result = state & ((rand() % 4));  // AND with random state
    int or_result = state | ((rand() % 4));   // OR with random state
    
    // Combine results to create new state
    return (xor_result ^ and_result ^ or_result) & 0b11;
}

// Calculate probabilities for superposition states
void calculate_probabilities(QuantumState states[], int num_states) {
    double total = 0.0;
    
    // Generate random probabilities and calculate total
    for (int i = 0; i < num_states; i++) {
        states[i].probability = (double)(rand() % 100 + 1) / 100.0;
        total += states[i].probability;
    }
    
    // Normalize probabilities to ensure they sum to 1.0
    if (total > 0.0) {
        for (int i = 0; i < num_states; i++) {
            states[i].probability /= total;
        }
    }
}

int main() {
    init_quantum_system();
    
    QuantumState states[] = {
        {STATE_00, 0.25},
        {STATE_01, 0.25},
        {STATE_10, 0.25},
        {STATE_11, 0.25}
    };
    int num_states = sizeof(states) / sizeof(states[0]);
    
    printf("Quantum Superposition Simulation\n");
    printf("================================\n");
    
    for (int step = 0; step < 5; step++) {
        printf("\nStep %d:\n", step + 1);
        
        // Calculate new probabilities
        calculate_probabilities(states, num_states);
        
        // Apply quantum operations to each state
        for (int i = 0; i < num_states; i++) {
            printf("State ");
            print_binary_state(states[i].state);
            printf(" probability: %.3f\n", states[i].probability);
            states[i].state = apply_quantum_operations(states[i].state);
        }
        
        // Visualize the current superposition state
        visualize_superposition(states, num_states);
    }
    
    return 0;
}