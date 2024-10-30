//$file${include::qxk.h} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//
// Model: qpc.qm
// File:  ${include::qxk.h}
//
// This code has been generated by QM 6.1.1 <www.state-machine.com/qm>.
// DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
//
// This code is covered by the following QP license:
// License #    : LicenseRef-QL-dual
// Issued to    : Any user of the QP/C real-time embedded framework
// Framework(s) : qpc
// Support ends : 2024-12-31
// License scope:
//
// Copyright (C) 2005 Quantum Leaps, LLC <state-machine.com>.
//
//                    Q u a n t u m  L e a P s
//                    ------------------------
//                    Modern Embedded Software
//
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-QL-commercial
//
// This software is dual-licensed under the terms of the open source GNU
// General Public License version 3 (or any later version), or alternatively,
// under the terms of one of the closed source Quantum Leaps commercial
// licenses.
//
// The terms of the open source GNU General Public License version 3
// can be found at: <www.gnu.org/licenses/gpl-3.0>
//
// The terms of the closed source Quantum Leaps commercial licenses
// can be found at: <www.state-machine.com/licensing>
//
// Redistributions in source code must retain this top-level comment block.
// Plagiarizing this software to sidestep the license obligations is illegal.
//
// Contact information:
// <www.state-machine.com/licensing>
// <info@state-machine.com>
//
//$endhead${include::qxk.h} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#ifndef QXK_H_
#define QXK_H_

//$declare${QXK::QXK} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${QXK::QXK} ................................................................
//! @class QXK
typedef struct QXK {
    //! @cond INTERNAL
    uint8_t dummy;
    //! @endcond
} QXK;
//$enddecl${QXK::QXK} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$declare${QXK::QSchedStatus} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${QXK::QSchedStatus} .......................................................
typedef uint_fast16_t QSchedStatus;
//$enddecl${QXK::QSchedStatus} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$declare${QXK::QXTHREAD_NO_TIMEOUT} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${QXK::QXTHREAD_NO_TIMEOUT} ................................................
#define QXTHREAD_NO_TIMEOUT ((QTimeEvtCtr)0)
//$enddecl${QXK::QXTHREAD_NO_TIMEOUT} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$declare${QXK::QXK-base} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${QXK::QXK-base::Attr} .....................................................
//! @class QXK_Attr
typedef struct {
// private:

    //! @memberof QXK_Attr
    struct QActive * volatile curr;

    //! @memberof QXK_Attr
    struct QActive * volatile next;

    //! @memberof QXK_Attr
    struct QActive * volatile prev;

    //! @memberof QXK_Attr
    uint_fast8_t volatile actPrio;

    //! @memberof QXK_Attr
    uint_fast8_t volatile lockCeil;

    //! @memberof QXK_Attr
    uint_fast8_t volatile lockHolder;

    //! @memberof QXK_Attr
    QPSet readySet;

#ifndef Q_UNSAFE
    //! @memberof QXK_Attr
    QPSet readySet_dis;
#endif // ndef Q_UNSAFE
} QXK_Attr;

//${QXK::QXK-base::priv_} ....................................................
//! @static @private @memberof QXK
extern QXK_Attr QXK_priv_;

//${QXK::QXK-base::onIdle} ...................................................
//! @static @public @memberof QXK
void QXK_onIdle(void);

//${QXK::QXK-base::schedLock} ................................................
//! @static @public @memberof QXK
QSchedStatus QXK_schedLock(uint_fast8_t const ceiling);

//${QXK::QXK-base::schedUnlock} ..............................................
//! @static @public @memberof QXK
void QXK_schedUnlock(QSchedStatus const stat);

//${QXK::QXK-base::current} ..................................................
//! @static @public @memberof QXK
QActive * QXK_current(void);

//${QXK::QXK-base::sched_} ...................................................
//! @static @private @memberof QXK
uint_fast8_t QXK_sched_(void);

//${QXK::QXK-base::activate_} ................................................
//! @static @private @memberof QXK
void QXK_activate_(void);

//${QXK::QXK-base::contextSw_} ...............................................
//! @static @public @memberof QXK
void QXK_contextSw_(QActive * const next);

//${QXK::QXK-base::threadExit_} ..............................................
//! @static @private @memberof QXK
void QXK_threadExit_(void);
//$enddecl${QXK::QXK-base} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$declare${QXK::QXThread} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${QXK::QXThread} ...........................................................
//! @class QXThread
//! @extends QActive
typedef struct QXThread {
// protected:
    QActive super;

// private:

    //! @private @memberof QXThread
    QTimeEvt timeEvt;
} QXThread;

//! @static @private @memberof QXThread
//! dummy static member to force QM to generate 'struct QXThread'
extern QXThread const * QXThread_dummy;

// public:

//! @public @memberof QXThread
void QXThread_ctor(QXThread * const me,
    QXThreadHandler const handler,
    uint_fast8_t const tickRate);

//! @public @memberof QXThread
bool QXThread_delay(QTimeEvtCtr const nTicks);

//! @public @memberof QXThread
bool QXThread_delayCancel(QXThread * const me);

//! @static @public @memberof QXThread
QEvt const * QXThread_queueGet(QTimeEvtCtr const nTicks);

// private:

//! @private @memberof QXThread
void QXThread_block_(QXThread const * const me);

//! @private @memberof QXThread
void QXThread_unblock_(QXThread const * const me);

//! @private @memberof QXThread
void QXThread_timeout_(QActive * const act);

//! @private @memberof QXThread
void QXThread_teArm_(QXThread * const me,
    enum_t const sig,
    QTimeEvtCtr const nTicks);

//! @private @memberof QXThread
bool QXThread_teDisarm_(QXThread * const me);

// public:

//! @private @memberof QXThread
void QXThread_stackInit_(
    QActive * const me,
     QXThreadHandler const handler,
    void * const stkSto,
    uint_fast16_t const stkSize);
//$enddecl${QXK::QXThread} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$declare${QXK::QXSemaphore} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${QXK::QXSemaphore} ........................................................
//! @class QXSemaphore
typedef struct {
// private:

    //! @private @memberof QXSemaphore
    QPSet waitSet;

    //! @private @memberof QXSemaphore
    uint8_t volatile count;

    //! @private @memberof QXSemaphore
    uint8_t max_count;
} QXSemaphore;

// public:

//! @public @memberof QXSemaphore
void QXSemaphore_init(QXSemaphore * const me,
    uint_fast8_t const count,
    uint_fast8_t const max_count);

//! @public @memberof QXSemaphore
bool QXSemaphore_wait(QXSemaphore * const me,
    QTimeEvtCtr const nTicks);

//! @public @memberof QXSemaphore
bool QXSemaphore_tryWait(QXSemaphore * const me);

//! @public @memberof QXSemaphore
bool QXSemaphore_signal(QXSemaphore * const me);
//$enddecl${QXK::QXSemaphore} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$declare${QXK::QXMutex} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${QXK::QXMutex} ............................................................
//! @class QXMutex
typedef struct {
// private:

    //! @private @memberof QXMutex
    QActive ao;

    //! @private @memberof QXMutex
    QPSet waitSet;
} QXMutex;

// public:

//! @public @memberof QXMutex
void QXMutex_init(QXMutex * const me,
    QPrioSpec const prioSpec);

//! @public @memberof QXMutex
bool QXMutex_lock(QXMutex * const me,
    QTimeEvtCtr const nTicks);

//! @public @memberof QXMutex
bool QXMutex_tryLock(QXMutex * const me);

//! @public @memberof QXMutex
void QXMutex_unlock(QXMutex * const me);
//$enddecl${QXK::QXMutex} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$declare${QXK-macros} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${QXK-macros::QXTHREAD_START} ..............................................
#define QXTHREAD_START(me_, prioSpec_, qSto_, qLen_, stkSto_, stkSize_, par_) QACTIVE_START((me_), (prioSpec_), (qSto_), (qLen_), \
    (stkSto_), (stkSize_), (par_))

//${QXK-macros::QXTHREAD_POST_X} .............................................
#define QXTHREAD_POST_X(me_, e_, margin_, sender_) \
    QACTIVE_POST_X(&(me_)->super, (e_), (margin_), (sender_))
//$enddecl${QXK-macros} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//============================================================================
// interface used only for internal implementation, but not in applications
#ifdef QP_IMPL

//$declare${QXK-impl} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${QXK-impl::QF_SCHED_STAT_} ................................................
#define QF_SCHED_STAT_ QSchedStatus lockStat_;

//${QXK-impl::QF_SCHED_LOCK_} ................................................
#define QF_SCHED_LOCK_(ceil_) do { \
    if (QXK_ISR_CONTEXT_()) { \
        lockStat_ = 0xFFU; \
    } else { \
        lockStat_ = QXK_schedLock((ceil_)); \
    } \
} while (false)

//${QXK-impl::QF_SCHED_UNLOCK_} ..............................................
#define QF_SCHED_UNLOCK_() do { \
    if (lockStat_ != 0xFFU) { \
        QXK_schedUnlock(lockStat_); \
    } \
} while (false)

//${QXK-impl::QACTIVE_EQUEUE_WAIT_} ..........................................
#define QACTIVE_EQUEUE_WAIT_(me_) \
    Q_ASSERT_INCRIT(310, (me_)->eQueue.frontEvt != (QEvt *)0)

//${QXK-impl::QACTIVE_EQUEUE_SIGNAL_} ........................................
#ifndef Q_UNSAFE
#define QACTIVE_EQUEUE_SIGNAL_(me_) do { \
    QPSet_insert(&QXK_priv_.readySet, (uint_fast8_t)(me_)->prio); \
    QPSet_update_(&QXK_priv_.readySet, &QXK_priv_.readySet_dis); \
    if (!QXK_ISR_CONTEXT_()) { \
        if (QXK_sched_() != 0U) { \
            QXK_activate_(); \
        } \
    } \
} while (false)
#endif // ndef Q_UNSAFE

//${QXK-impl::QACTIVE_EQUEUE_SIGNAL_} ........................................
#ifdef Q_UNSAFE
#define QACTIVE_EQUEUE_SIGNAL_(me_) do { \
    QPSet_insert(&QXK_priv_.readySet, (uint_fast8_t)(me_)->prio); \
    if (!QXK_ISR_CONTEXT_()) { \
        if (QXK_sched_() != 0U) { \
            QXK_activate_(); \
        } \
    } \
} while (false)
#endif // def Q_UNSAFE

//${QXK-impl::QXTHREAD_EQUEUE_SIGNAL_} .......................................
#ifndef Q_UNSAFE
#define QXTHREAD_EQUEUE_SIGNAL_(me_) do { \
    if (me->super.temp.obj == QXK_PTR_CAST_(QMState*, &me->eQueue)) { \
        (void)QXThread_teDisarm_(QXTHREAD_CAST_(me)); \
        QPSet_insert(&QXK_priv_.readySet, (uint_fast8_t)me->prio); \
        QPSet_update_(&QXK_priv_.readySet, &QXK_priv_.readySet_dis); \
        if (!QXK_ISR_CONTEXT_()) { \
            (void)QXK_sched_(); \
        } \
    } \
} while (false)
#endif // ndef Q_UNSAFE

//${QXK-impl::QXTHREAD_EQUEUE_SIGNAL_} .......................................
#ifdef Q_UNSAFE
#define QXTHREAD_EQUEUE_SIGNAL_(me_) do { \
    if (me->super.temp.obj == QXK_PTR_CAST_(QMState*, &me->eQueue)) { \
        (void)QXThread_teDisarm_(QXTHREAD_CAST_(me)); \
        QPSet_insert(&QXK_priv_.readySet, (uint_fast8_t)me->prio); \
        if (!QXK_ISR_CONTEXT_()) { \
            (void)QXK_sched_(); \
        } \
    } \
} while (false)
#endif // def Q_UNSAFE

//${QXK-impl::QXK_PTR_CAST_} .................................................
#define QXK_PTR_CAST_(type_, ptr_) ((type_)(ptr_))

//${QXK-impl::QXTHREAD_CAST_} ................................................
#define QXTHREAD_CAST_(ptr_) ((QXThread *)(ptr_))
//$enddecl${QXK-impl} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//$declare${QF_EPOOL-impl} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//${QF_EPOOL-impl::QF_EPOOL_TYPE_} ...........................................
#define QF_EPOOL_TYPE_ QMPool

//${QF_EPOOL-impl::QF_EPOOL_INIT_} ...........................................
#define QF_EPOOL_INIT_(p_, poolSto_, poolSize_, evtSize_) \
    (QMPool_init(&(p_), (poolSto_), (poolSize_), (evtSize_)))

//${QF_EPOOL-impl::QF_EPOOL_EVENT_SIZE_} .....................................
#define QF_EPOOL_EVENT_SIZE_(p_) ((uint_fast16_t)(p_).blockSize)

//${QF_EPOOL-impl::QF_EPOOL_GET_} ............................................
#define QF_EPOOL_GET_(p_, e_, m_, qsId_) \
    ((e_) = (QEvt *)QMPool_get(&(p_), (m_), (qsId_)))

//${QF_EPOOL-impl::QF_EPOOL_PUT_} ............................................
#define QF_EPOOL_PUT_(p_, e_, qsId_) \
    (QMPool_put(&(p_), (e_), (qsId_)))
//$enddecl${QF_EPOOL-impl} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

enum QXK_TimeoutSigs {
    QXK_DELAY_SIG = 1,
    QXK_TIMEOUT_SIG
};

#endif // QP_IMPL

#endif // QXK_H_
