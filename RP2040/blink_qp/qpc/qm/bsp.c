//$file${.::bsp.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//
// Model: blinky_console.qm
// File:  ${.::bsp.c}
//
// This code has been generated by QM 6.2.3 <www.state-machine.com/qm>.
// DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
//
//                 ____________________________________
//                /                                   /
//               /    GGGGGGG    PPPPPPPP   LL       /
//              /   GG     GG   PP     PP  LL       /
//             /   GG          PP     PP  LL       /
//            /   GG   GGGGG  PPPPPPPP   LL       /
//           /   GG      GG  PP         LL       /
//          /     GGGGGGG   PP         LLLLLLL  /
//         /___________________________________/
//
// Copyright (c) 2005 Quantum Leaps, LLC
// SPDX-License-Identifier: GPL-3.0-or-later
//
// This generated code is open-source software licensed under the GNU
// General Public License (GPL) as published by the Free Software Foundation
// (see <https://www.gnu.org/licenses>).
//
// NOTE:
// The GPL does NOT permit the incorporation of this code into proprietary
// programs. Please contact Quantum Leaps for commercial licensing options,
// which expressly supersede the GPL and are designed explicitly for licensees
// interested in retaining the proprietary status of the generated code.
//
// Quantum Leaps contact information:
// <www.state-machine.com/licensing>
// <info@state-machine.com>
//
//$endhead${.::bsp.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Board Support Package implementation for desktop OS (Windows, Linux, MacOS)
#include "qpc.h"    // QP/C real-time embedded framework
#include "bsp.h"    // Board Support Package interface
#include <stdio.h>  // for printf()/fprintf()
#include <stdlib.h> // for exit()

#include "pico/stdlib.h"
#include "hardware/irq.h"
#include "hardware/regs/m0plus.h"
#include "hardware/structs/systick.h"

void init_systick()
{
    systick_hw->csr = 0;         //Disable
    systick_hw->rvr = 124999UL; //Standard System clock (125Mhz)/ (rvr value + 1) = 1ms
        systick_hw->csr = 0x7;      //Enable Systic, Enable Exceptions
}

// Función de interrupción para SysTick
extern void isr_systick() {
    // Coloca aquí el código que quieres ejecutar en cada interrupción
    // Por ejemplo, puedes hacer un toggle de un LED
    //gpio_xor_mask(1 << PICO_DEFAULT_LED_PIN);
    QF_TICK_X(0U, (void *)0); // QF clock tick processing for rate 0
}

//............................................................................
void BSP_init(void)   {
    printf("Simple Blinky example\n"
           "QP/C version: %s\n"
           "Press Ctrl-C to quit...\n",
           QP_VERSION_STR);
}
//............................................................................
void BSP_start(void) {
    // no need to initialize event pools
    //static QF_MPOOL_EL(QEvt) smlPoolSto[10];
    //QF_poolInit(smlPoolSto, sizeof(smlPoolSto), sizeof(smlPoolSto[0]));

    // no need to initialize publish-subscribe
    //QActive_psInit(subscrSto, Q_DIM(subscrSto));

    // instantiate and start AOs/threads...

    init_systick();

    static QEvt const *blinkyQueueSto[10];
    Blinky_ctor();
    QACTIVE_START(AO_Blinky,
        1U,                          // QP prio. of the AO
        blinkyQueueSto,              // event queue storage
        Q_DIM(blinkyQueueSto),       // queue length [events]
        (void *)0, 0U,               // no stack storage
        (void *)0);                  // no initialization param
}
//............................................................................
void BSP_ledOff(void) { printf("LED OFF\n"); }
//............................................................................
void BSP_ledOn(void)  { printf("LED ON\n");  }

// callback functions needed by the framework --------------------------------
void QF_onStartup(void) {}
void QF_onCleanup(void) {}
void QF_onClockTick(void) {
    QF_TICK_X(0U, (void *)0); // QF clock tick processing for rate 0
}
void Q_onError(char const * const module, int id) {
    fprintf(stderr, "Assertion failed in %s:%d", module, id);
    exit(-1);
}

void QV_onIdle(void) { /* entered with interrupts DISABLED, see NOTE01 */
#if defined NDEBUG
    /* Put the CPU and peripherals to the low-power mode */
    QV_CPU_SLEEP(); /* atomically go to sleep and enable interrupts */
#else
    QF_INT_ENABLE(); /* just enable interrupts */
#endif
}