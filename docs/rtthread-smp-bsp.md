# RT-Thread SMP版本移植相关实现要点

## 启动

一般的SMP方式，会有细微的主、从核之分，主核先启动，并完成系统的基本初始化（对bss段进行清理，初始化中断，启动OS等等），而从核则运行起来时则先行主动等待，需要底层BSP提供以下接口：

```c
/* 本函数用于启动从核心，当OS启动后，主核会调用这个函数来让从核进入整体的 SMP 调度 */
void rt_hw_secondy_cpu_up(void);

/* 本函数用于从核进行空转时的调用，一般是进入低功耗状态以降低功耗 */
void rt_hw_secondy_cpu_idle_exec(void);
```

## OS Tick

在RT-Thread/SMP版本中，OS Tick数值是唯一的，即主核上的OS Tick计数；但是对于每个CPU核来说，需要有独立的OS Tick机制，即每个核的时钟中断都存在，并且独立。

## IPI

在进行SMP调度时，系统需要有核间中断的通知机制，BSP需要实现以下API：

```c
/* 向CPU MASK集合发送核间中断 */
void rt_hw_ipi_send(int irq, int cpu_mask);

/* 例如向CPU1发送核间中断 */
rt_hw_ipi_send(0, (1 << 1));
```

## 中断

需要实现单核的开关中断函数

```c
/* 保存当前cpu中断状态并关闭中断 */
rt_base_t rt_hw_local_irq_disable();

/* 恢复当前cpu的中断状态 */
void rt_hw_local_irq_enable(rt_base_t level);
```

## 自旋锁

在多核系统中，考虑到高效率，自旋锁的底层实现是和CPU体系密切相关，需要由libcpu/BSP来进行实现，需要实现以下定义及接口：

```c
/* 底层自旋锁结构定义 */
typedef struct {} rt_hw_spinlock_t;

/* 对自旋锁执行锁定操作 */
void __rt_hw_spin_lock(rt_hw_spinlock_t*);

/* 对自旋锁执行解锁操作 */
void __rt_hw_spin_unlock(rt_hw_spinlock_t*);
```
