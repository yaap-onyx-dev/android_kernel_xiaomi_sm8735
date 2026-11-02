/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2024 Sultan Alsawaf <sultan@kerneltoast.com>.
 */

#ifndef _FIE_H_
#define _FIE_H_

#include <linux/cpumask.h>
#include <linux/types.h>

struct rq;

struct fie_rate_info {
	u64 set_time;
	unsigned int freq;
};

#ifdef CONFIG_SCHED_FIE
void fie_update_rq_clock(struct rq *rq);
void fie_init_cpu_domain(const struct cpumask *cpus, unsigned int max_freq);
bool fie_cpufreq_pressure(int cpu, unsigned int capped_freq);
void fie_rate_set(int cpu, unsigned int freq);
#else
static inline void fie_update_rq_clock(struct rq *rq)
{
}

static inline void fie_init_cpu_domain(const struct cpumask *cpus,
				       unsigned int max_freq)
{
}

/* Without FIE, the caller updates the thermal pressure on its own */
static inline bool fie_cpufreq_pressure(int cpu, unsigned int capped_freq)
{
	return false;
}

static inline void fie_rate_set(int cpu, unsigned int freq)
{
}
#endif /* CONFIG_SCHED_FIE */

#endif /* _FIE_H_ */
