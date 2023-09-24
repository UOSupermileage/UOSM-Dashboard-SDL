/*
 * ApplicationTypes.h
 *
 *	custom data types
 *
 *  Created on: Sep 4, 2022
 *      Author: mingye
 */

#ifndef _APPLICATIONTYPES_H_
#define _APPLICATIONTYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "SerialDebugDriver.h"
#define DebugPrint(...) SerialPrintln(__VA_ARGS__)

#include <stdint.h>

#define PUBLIC
#define PRIVATE

#define PI_T2 6.28318530718 // Pi * 2

#define MAX_PERCENTAGE 1000
#define MIN_PERCENTAGE 0

typedef enum {
    RESULT_FAIL,
    RESULT_OK
} result_t;

typedef enum {
    MOTOR_LOW_SPEED,
    MOTOR_HIGH_SPEED
} MotorCode;

typedef enum {
    THROTTLE_TOO_HIGH
} ErrorCode;

typedef enum {
    DEADMAN,
    TIMER,
    MOTOR_INITIALIZING,
    UNDERVOLTAGE,
    DRIVER_ENABLED
} EventCode;

typedef enum {
    MOTOR_MODE_NORMAL,
    MOTOR_MODE_RTMI,
    MOTOR_MODE_IDLE
} MotorMode;

typedef enum {
    Clear = 0,
    Set = 1
} flag_status_t;

typedef int16_t torque_t;
typedef uint16_t length_t;
typedef uint16_t percentage_t;
typedef int32_t velocity_t;
typedef uint16_t throttle_raw_t;
typedef uint16_t voltage_t;
typedef uint16_t speed_t;
typedef uint16_t seconds_t;
typedef uint32_t ms_t;
typedef uint16_t current_t;
typedef uint16_t watt_hour_t;

typedef struct {
    uint16_t standardMessageID; // 11 bit max
    uint8_t dataLength;            // max 8
    uint8_t data[8];
} iCommsMessage_t;

typedef struct {
    float x;
    float y;
    float z;
} acceleration_t;

typedef struct {
    float latitude;
    float longitude;
    float speed_kmh;
    float heading;
    float altitude;
} gps_coordinate_t;

typedef struct {
    double pressure;
    double temp;
} pressure_t;

#ifdef __cplusplus
}
#endif

#endif /* _APPLICATIONTYPES_H_ */
