/*
  Greg Talotta
  2/17/2020
  cs241 lab 6

*/

#include "benchmark.h" //<- Dr. Lawlor's code

const int dataPin = 2;
const int clockPin = 3;
/// These constants give the bit numbers for each row and column.
///  (Mostly to give nice names for row/column "rc" values.)
typedef enum
{
  c0 = 0,
  c1,
  c2,
  c3,
  c4,
  c5,
  c6,
  c7,
  r0 = 8,
  r1,
  r2,
  r3,
  r4,
  r5,
  r6,
  r7,
} rc_t;

/// The shift register's output pins are hardwired to the 8x8's top pins
//  This table lets you look up the row/col bit numbers
//   that need to be fed into the shift register:
const int nshift_bits = 8;
const rc_t rc_for_shift[nshift_bits] = {c7, c6, r1, c0, r3, c5, c3, r0};

/// These are Arduino pins hardwired into the 8x8's bottom pins:
const int nhardwire = 8;
const char pin_for_hardwire[nhardwire] = {4, 5, 6, 7, 8, 9, 10, 11};
const rc_t rc_for_hardwire[nhardwire] = {r4, r6, c1, c2, r7, c4, r5, r2};

/// Each bit of this 16-bit datatype stores a value
/// for the rows (bits 15..8) and columns (bits 7..0)
/// for one fixed pattern on the LED matrix.
/// These are static patterns that can be shown without any row scanning.
typedef unsigned short LED_rc_bits_t;

/// Extract one bit from an rc_bits matrix (for a digitalWrite)
inline bool get_rc_bit(LED_rc_bits_t rc_bits, rc_t bit)
{
  return (rc_bits >> bit) & 1;
}
const int npatterns = 6 + 8 + 8;
LED_rc_bits_t patterns[npatterns] = {
    //    0=on    1=on
    //     row   column
    //  7654321076543210
    0b1111111100000000, // all LEDs off
    0b0000000011111111, // all LEDs on
    0b0111111010000001, // corner LEDs on
    0b1011110101000010, // corner inset-1
    0b1101101100100100, // corner inset-2
    0b1110011100011000, // center 4

    0b0000000010000000, // right-to-left col scan (dark background)
    0b0000000001000000,
    0b0000000000100000,
    0b0000000000010000,
    0b0000000000001000,
    0b0000000000000100,
    0b0000000000000010,
    0b0000000000000001,

    0b0111111111111111, // bottom-to-top row scan (dark background)
    0b1011111111111111,
    0b1101111111111111,
    0b1110111111111111,
    0b1111011111111111,
    0b1111101111111111,
    0b1111110111111111,
    0b1111111011111111,
};

void setup()
{
  Serial.begin(9600);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  digitalWrite(clockPin, 0);
  for (int i = 0; i < nhardwire; ++i)
  {
    pinMode(pin_for_hardwire[i], OUTPUT);
  }
}

const int nsmile = 6;
LED_rc_bits_t smile_patterns[nsmile] = {
    //    0=on    1=on
    //     row   column
    //  7654321076543210
    0b1111101101000000,
    0b1101110100100000,
    0b1111110100010000,
    0b1111110100001000,
    0b1101110100000100,
    0b1111101100000010,

};

// takes an array of patterns and displays the complex pattern
// if it is given a single patern it just displays it, and returns
void showPattern(LED_rc_bits_t pattern[], int size, bool fast)
{
  for (int i = 0; i < size; ++i)
  {
    LED_rc_bits_t pat = pattern[i];
    for (int i = nshift_bits - 1; i >= 0; --i)
    {
      digitalWrite(clockPin, 0);
      digitalWrite(dataPin, get_rc_bit(pat, rc_for_shift[i]));
      digitalWrite(clockPin, 1);
    }
    digitalWrite(clockPin, 0);
    digitalWrite(clockPin, 1);
    for (int i = 0; i < nhardwire; ++i)
    {
      digitalWrite(pin_for_hardwire[i], get_rc_bit(pat, rc_for_hardwire[i]));
    }
    if (fast)
    {
      delay(4);
    }
  }
  return;
}

int bShowPattern(int v)
{
  LED_rc_bits_t pat[1];
  pat[0] = patterns[1];
  showPattern(pat, 1, false);
  return 0;
}

int target = 0;
void loop()
{
  LED_rc_bits_t pat[1];
  pat[0] = patterns[target];
  Serial.println("Starting benchmarks...");
  benchmark("show pattern", bShowPattern, 10000);
  delay(3);
  Serial.println();
  for (int i = 0; i < 10000; i++)
  {
    showPattern(smile_patterns, nsmile, true);
  }
  target++;
  if (target >= npatterns)
  {
    target = 0;
  }
}
