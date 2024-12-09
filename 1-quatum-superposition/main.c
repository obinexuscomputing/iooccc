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
#define MAX_BAR_LEN 40
#define PI 3.14159265358979323846

typedef struct {
    int state;
    double complex amplitude;
    double probability;
    double phase;
} QuantumState;

void init_quantum_system() {
    srand(time(NULL));
}

const char* get_bar_char(int position, int max_length) {
    double ratio = (double)position / max_length;
    if (ratio < 0.25) return "░";
    if (ratio < 0.5) return "▒";
    if (ratio < 0.75) return "▓";
    return "█";
}

void print_binary_state(int state) {
    printf("|%d%d⟩", (state & 0b10) >> 1, state & 0b01);
}

void visualize_superposition(QuantumState states[], int num_states) {
    printf("\nState Distribution:\n");
    
    // Find maximum probability for scaling
    double max_prob = 0;
    for (int i = 0; i < num_states; i++) {
        max_prob = fmax(max_prob, states[i].probability);
    }
    
    for (int i = 0; i < num_states; i++) {
        printf("  ");
        print_binary_state(states[i].state);
        printf(" ");
        
        int bar_length = (int)((states[i].probability / max_prob) * MAX_BAR_LEN);
        bar_length = fmax(bar_length, 1);
        
        // Draw graduated bar
        for (int j = 0; j < bar_length; j++) {
            printf("%s", get_bar_char(j, bar_length));
        }
        
        printf(" %.3f ∠%.0f°\n", states[i].probability, states[i].phase);
    }
    printf("\n");
}

void evolve_phase(QuantumState *state, int step) {
    // Non-linear phase evolution with interference effects
    double base_shift = 45.0;  // 45 degree base shift
    double interference = 15.0 * sin(step * PI / 4);  // Oscillating component
    double random_component = (rand() % 30) - 15;  // Random ±15 degrees
    
    double phase_shift = base_shift + interference + random_component;
    state->phase += phase_shift;
    
    // Normalize phase to [0, 360)
    while (state->phase >= 360.0) state->phase -= 360.0;
    while (state->phase < 0.0) state->phase += 360.0;
    
    // Update complex amplitude
    state->amplitude = sqrt(state->probability) * cexp(I * state->phase * PI / 180.0);
}

void calculate_probabilities(QuantumState states[], int num_states, int step) {
    double total = 0.0;
    
    // Generate probabilities using interference pattern
    for (int i = 0; i < num_states; i++) {
        double base = 0.25;  // Equal superposition base
        double interference = 0.15 * sin((step + i) * PI / 2);  // Interference term
        double random = 0.1 * ((double)(rand() % 100) / 100.0 - 0.5);  // Random component
        
        states[i].probability = base + interference + random;
        states[i].probability = fmax(states[i].probability, MIN_PROB);
        total += states[i].probability;
    }
    
    // Normalize probabilities
    for (int i = 0; i < num_states; i++) {
        states[i].probability /= total;
        evolve_phase(&states[i], step);
    }
}

int main() {
    init_quantum_system();
    
    QuantumState states[] = {
        {STATE_00, 0.5 + 0.0 * I, 0.25, 0.0},
        {STATE_01, 0.5 + 0.0 * I, 0.25, 90.0},
        {STATE_10, 0.5 + 0.0 * I, 0.25, 180.0},
        {STATE_11, 0.5 + 0.0 * I, 0.25, 270.0}
    };
    int num_states = sizeof(states) / sizeof(states[0]);
    
    printf("Quantum Superposition Simulation\n");
    printf("================================\n");
    
    for (int step = 1; step <= 5; step++) {
        printf("\nStep %d:\n", step);
        calculate_probabilities(states, num_states, step);
        visualize_superposition(states, num_states);
    }
    
    return 0;
}