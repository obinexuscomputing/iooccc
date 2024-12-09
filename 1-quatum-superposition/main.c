#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <complex.h>

#define STATE_00 0b00
#define STATE_01 0b01
#define STATE_10 0b10
#define STATE_11 0b11

#define MIN_PROB 0.1
#define PROB_SCALE 6
#define MAX_BAR_LEN 40

typedef struct {
    int state;
    double complex amplitude;
    double probability;
    double phase;
} QuantumState;

void init_quantum_system() {
    srand(time(NULL));
}

void print_binary_state(int state) {
    printf("|%d%d⟩", (state & 0b10) >> 1, state & 0b01);
}

void visualize_superposition(QuantumState states[], int num_states) {
    printf("\nState Distribution:\n");
    
    for (int i = 0; i < num_states; i++) {
        printf("  ");
        print_binary_state(states[i].state);
        printf(" ");
        
        int bar_length = (int)(states[i].probability * MAX_BAR_LEN);
        bar_length = fmax(bar_length, 1);
        for (int j = 0; j < bar_length; j++) {
            printf("*");
        }
        
        printf(" %.3f ∠%.0f°\n", states[i].probability, states[i].phase);
    }
    printf("\n");
}

void ensure_unique_states(QuantumState states[], int num_states) {
    for (int i = 0; i < num_states; i++) {
        int new_state = i;  // Assign states in order (00, 01, 10, 11)
        states[i].state = new_state;
    }
}

void evolve_phase(QuantumState *state) {
    // Coherent phase evolution
    double phase_shift = (30.0 + (rand() % 60)) * M_PI / 180.0;  // 30-90 degrees
    state->phase += phase_shift;
    if (state->phase >= 360.0) {
        state->phase -= 360.0;
    }
    
    // Update complex amplitude with new phase
    state->amplitude = sqrt(state->probability) * cexp(I * state->phase * M_PI / 180.0);
}

void calculate_probabilities(QuantumState states[], int num_states) {
    double total = 0.0;
    
    // Generate balanced probabilities
    for (int i = 0; i < num_states; i++) {
        // Smoother probability distribution
        double r = (double)(rand() % 100) / 100.0;
        states[i].probability = 0.15 + r * 0.35;  // Range: 0.15 to 0.50
        total += states[i].probability;
    }
    
    // Normalize probabilities
    for (int i = 0; i < num_states; i++) {
        states[i].probability /= total;
        evolve_phase(&states[i]);
    }
}

int main() {
    init_quantum_system();
    
    QuantumState states[] = {
        {STATE_00, 0.5 + 0.0 * I, 0.25, 0.0},
        {STATE_01, 0.5 + 0.0 * I, 0.25, 0.0},
        {STATE_10, 0.5 + 0.0 * I, 0.25, 0.0},
        {STATE_11, 0.5 + 0.0 * I, 0.25, 0.0}
    };
    int num_states = sizeof(states) / sizeof(states[0]);
    
    printf("Quantum Superposition Simulation\n");
    printf("================================\n");
    
    for (int step = 1; step <= 5; step++) {
        printf("\nStep %d:\n", step);
        
        ensure_unique_states(states, num_states);
        calculate_probabilities(states, num_states);
        visualize_superposition(states, num_states);
    }
    
    return 0;
}