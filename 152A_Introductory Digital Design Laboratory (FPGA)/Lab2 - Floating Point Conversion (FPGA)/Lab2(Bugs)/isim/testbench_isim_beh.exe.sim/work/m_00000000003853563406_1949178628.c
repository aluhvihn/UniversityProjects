/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "E:/CS_152A/Lab2(Bugs)/testbench.v";
static unsigned int ng1[] = {0U, 0U};
static unsigned int ng2[] = {4095U, 0U};
static unsigned int ng3[] = {1U, 0U};
static unsigned int ng4[] = {2U, 0U};
static unsigned int ng5[] = {3U, 0U};
static unsigned int ng6[] = {24U, 0U};
static unsigned int ng7[] = {2048U, 0U};
static unsigned int ng8[] = {2047U, 0U};
static unsigned int ng9[] = {44U, 0U};
static unsigned int ng10[] = {45U, 0U};
static unsigned int ng11[] = {46U, 0U};
static unsigned int ng12[] = {47U, 0U};
static const char *ng13 = "Done";



static void Initial_43_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;

LAB0:    t1 = (t0 + 2688U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(43, ng0);

LAB4:    xsi_set_current_line(45, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1768);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 12);
    xsi_set_current_line(46, ng0);
    t2 = (t0 + 2496);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB5;

LAB1:    return;
LAB5:    xsi_set_current_line(48, ng0);
    t3 = ((char*)((ng2)));
    t4 = (t0 + 1768);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 12);
    xsi_set_current_line(49, ng0);
    t2 = (t0 + 2496);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB6;
    goto LAB1;

LAB6:    xsi_set_current_line(51, ng0);
    t3 = ((char*)((ng3)));
    t4 = (t0 + 1768);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 12);
    xsi_set_current_line(52, ng0);
    t2 = (t0 + 2496);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB7;
    goto LAB1;

LAB7:    xsi_set_current_line(54, ng0);
    t3 = ((char*)((ng4)));
    t4 = (t0 + 1768);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 12);
    xsi_set_current_line(55, ng0);
    t2 = (t0 + 2496);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB8;
    goto LAB1;

LAB8:    xsi_set_current_line(57, ng0);
    t3 = ((char*)((ng5)));
    t4 = (t0 + 1768);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 12);
    xsi_set_current_line(58, ng0);
    t2 = (t0 + 2496);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB9;
    goto LAB1;

LAB9:    xsi_set_current_line(60, ng0);
    t3 = ((char*)((ng6)));
    t4 = (t0 + 1768);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 12);
    xsi_set_current_line(61, ng0);
    t2 = (t0 + 2496);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB10;
    goto LAB1;

LAB10:    xsi_set_current_line(63, ng0);
    t3 = ((char*)((ng7)));
    t4 = (t0 + 1768);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 12);
    xsi_set_current_line(64, ng0);
    t2 = (t0 + 2496);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB11;
    goto LAB1;

LAB11:    xsi_set_current_line(66, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 1768);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 12);
    xsi_set_current_line(67, ng0);
    t2 = (t0 + 2496);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB12;
    goto LAB1;

LAB12:    xsi_set_current_line(69, ng0);
    t3 = ((char*)((ng9)));
    t4 = (t0 + 1768);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 12);
    xsi_set_current_line(70, ng0);
    t2 = (t0 + 2496);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB13;
    goto LAB1;

LAB13:    xsi_set_current_line(72, ng0);
    t3 = ((char*)((ng10)));
    t4 = (t0 + 1768);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 12);
    xsi_set_current_line(73, ng0);
    t2 = (t0 + 2496);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB14;
    goto LAB1;

LAB14:    xsi_set_current_line(75, ng0);
    t3 = ((char*)((ng11)));
    t4 = (t0 + 1768);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 12);
    xsi_set_current_line(76, ng0);
    t2 = (t0 + 2496);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB15;
    goto LAB1;

LAB15:    xsi_set_current_line(78, ng0);
    t3 = ((char*)((ng12)));
    t4 = (t0 + 1768);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 12);
    xsi_set_current_line(79, ng0);
    t2 = (t0 + 2496);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB16;
    goto LAB1;

LAB16:    xsi_set_current_line(81, ng0);
    xsi_vlogfile_write(1, 0, 0, ng13, 1, t0);
    xsi_set_current_line(82, ng0);
    xsi_vlog_finish(1);
    goto LAB1;

}


extern void work_m_00000000003853563406_1949178628_init()
{
	static char *pe[] = {(void *)Initial_43_0};
	xsi_register_didat("work_m_00000000003853563406_1949178628", "isim/testbench_isim_beh.exe.sim/work/m_00000000003853563406_1949178628.didat");
	xsi_register_executes(pe);
}
