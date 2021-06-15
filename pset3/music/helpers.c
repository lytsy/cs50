// Helper functions for music

#include "helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator =  (int)fraction[0] - 48;
    int denominator = (int)fraction[2]- 48;
    int duration = numerator * (8/denominator);
    return duration;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    const string BASE_NOTES[] = {"C", "D", "E", "F", "G", "A", "B"};
    // Difference semitons from A to note from BASE_NOTES
    const int semitones_from_A[] = {-9, -7, -5, -4, -2, 0, 2};
    const int A4_FREQUENCY = 440;
    int note_letter = toupper(note[0]);
    int current_letter;
    int is_note_finded = 0;
    int semitones = 0;
    for (int i = 0, n = sizeof(BASE_NOTES) / sizeof(string); i < n; i++)
    {
        current_letter =  (int) BASE_NOTES[i][0];
        if (current_letter == note_letter)
        {
            is_note_finded = 1;
            semitones  = semitones_from_A[i];
        }
        
    }
    if (!is_note_finded)
    {
        printf("Incorect note input\n");
    }
    
    if (note[1] == '#')
    {
        semitones++;
    }
    if (note[1] == 'b')
    {
        semitones--;
    }

    int octave;
    if (isdigit(note[1]))
    {
        octave = (int)note[1] - 48;
    }
    else
    {
        octave = (int)note[2] - 48;
    }
    
    double frequency = A4_FREQUENCY;
    double exponent = (double) abs(semitones)/12;
    if (semitones>=0)
    {
        frequency *= pow(2.0, exponent);
    }else
    {
        frequency /= pow(2.0, exponent);
    }
    
    if (octave>4)
    {
        frequency*=pow(2.0, (double)(octave-4));
    }
    else
    {
        frequency/=pow(2.0, (double)(4-octave));
    }
    return (int)frequency;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0]=='\0' || s[0]=='\r' || s[0]=='\n')
    {
        return true;
    }
    return false;
}
