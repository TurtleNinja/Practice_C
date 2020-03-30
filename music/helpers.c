// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <string.h>


#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    return (fraction[0] - '0') * (8/(fraction[2] - '0'));
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    const string NOTES[] = {"C", "C#", "D", "D#", "E", "F",
                            "F#", "G", "G#", "A", "A#", "B"};
    const int NOTE_A = 9;

    //seperate note's components
    char letter = note[0];
    int octave = note[strlen(note) - 1] - '0';
    int accidental = 0;
        if (note[1] == '#')
            accidental = 1;
        else if (note[1] == 'b')
            accidental = -1;

    //calculate number of semitones away from A4;
    int i = 0;
    while (letter != NOTES[i++][0]);
    int semitone = (--i - NOTE_A) + accidental + (octave - 4) * 12;

    //calculate and return the frequency
    return  round(pow(2, semitone/12.0) * 440);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    return strcmp(s, "") == 0;
}
