/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_HAVE_SMP

rt_precpu_t rt_percpu_data[RT_CPUS_NR];

#endif /*RT_HAVE_SMP*/
