/* 
 * File:   utilities.c
 * Author: Mike Dawson
 *
 * Created on March 28, 2024
 */

/* The following function will map an input range to a new output range. */
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
