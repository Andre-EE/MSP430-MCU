#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "hardware.h"
#include "scheduler.h"
#include "buffer.h"


void fsm_update_state(void);




//
////****************************************************************************//
//// State table typedef
////****************************************************************************//
//typedef struct
//{
//  void (*ptrFunct) (void);
//  uint8_t NextState;
//} FSM_STATE_TABLE;
//
//extern uint8_t activeState;
//
//#define NR_EVENTS       6
//#define LEFT            0
//#define RIGHT           1
//#define UP              2
//#define DOWN            3
//#define BUTTON          4
//#define WIN             5
//
//#define NR_STATES       5
//#define INIT_GAME       0
//#define EMPTY_FIELD1    1
//#define EMPTY_FIELD2    2
//#define EMPTY_FIELD3    3
//#define STOP_GAME       4
//
//
////****************************************************************************//
//// Function prototypes
////****************************************************************************//
//// Initialize state machine
//void FSM_Init (void);
//
//// Event function "Left"
//void FSM_Left (void);
//
//// Event function "Right"
//void FSM_Right (void);
//
//// Event function "Up"
//void FSM_Up (void);
//
//// Event function "Down"
//void FSM_Down (void);
//
//// Event function "Button"
//void FSM_Button (void);
//
//// Event function "Win"
//void FSM_Win (void);
//
//// Transition function "StartGame"
//void FSM_StartGame (void);
//
//// Transition function "StopGame"
//void FSM_StopGame (void);
//
//// Transition function "PushLeft"
//void FSM_PushLeft (void);
//
//// Transition function "PushUp"
//void FSM_PushUp (void);
//
//// Transition function "InitGame"
//void FSM_InitGame (void);
//
//// Transition function "PushRight"
//void FSM_PushRight (void);
//
//// Transition function "PushDown"
//void FSM_PushDown (void);

#endif /* STATE_MACHINE_H_ */
