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
static const char *ng0 = "E:/CS_152A/Lab1/tb/tb.v";
static const char *ng1 = "%d ... Running instruction %08b";
static int ng2[] = {1, 0};
static int ng3[] = {0, 0};
static unsigned int ng4[] = {0U, 0U};
static unsigned int ng5[] = {3U, 0U};
static unsigned int ng6[] = {1U, 0U};
static unsigned int ng7[] = {2U, 0U};
static const char *ng8 = "seq.code";
static const char *ng9 = "rb";
static const char *ng10 = "%b\n";
static int ng11[] = {7, 0};
static int ng12[] = {6, 0};
static int ng13[] = {2, 0};
static int ng14[] = {5, 0};
static int ng15[] = {4, 0};
static int ng16[] = {8, 0};
static int ng17[] = {3, 0};
static const char *ng18 = "SENDING";
static const char *ng19 = "%d ... instruction %08b executed";
static const char *ng20 = "%d ... led output changed to %08b";



static int sp_tskRunInst(char *t1, char *t2)
{
    char t5[8];
    int t0;
    char *t3;
    char *t4;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;

LAB0:    t0 = 1;
    t3 = (t2 + 48U);
    t4 = *((char **)t3);
    if (t4 == 0)
        goto LAB2;

LAB3:    goto *t4;

LAB2:    t4 = (t1 + 848);
    xsi_vlog_subprogram_setdisablestate(t4, &&LAB4);
    xsi_set_current_line(108, ng0);

LAB5:    xsi_set_current_line(109, ng0);
    *((int *)t5) = xsi_vlog_stime(1000.0000000000000, 1000.0000000000000);
    t6 = (t5 + 4);
    *((int *)t6) = 0;
    t7 = (t1 + 6008);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    t10 = (t1 + 848);
    xsi_vlogfile_write(1, 0, 0, ng1, 3, t10, (char)118, t5, 32, (char)118, t9, 8);
    xsi_set_current_line(110, ng0);
    t4 = (t1 + 6008);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t1 + 3928);
    xsi_vlogvar_assign_value(t8, t7, 0, 0, 8);
    xsi_set_current_line(111, ng0);
    t4 = (t2 + 56U);
    t6 = *((char **)t4);
    xsi_process_wait(t6, 1500000000LL);
    *((char **)t3) = &&LAB6;
    t0 = 1;

LAB1:    return t0;
LAB4:    xsi_vlog_dispose_subprogram_invocation(t2);
    t4 = (t2 + 48U);
    *((char **)t4) = &&LAB2;
    t0 = 0;
    goto LAB1;

LAB6:    xsi_set_current_line(111, ng0);
    t7 = ((char*)((ng2)));
    t8 = (t1 + 4248);
    xsi_vlogvar_assign_value(t8, t7, 0, 0, 1);
    xsi_set_current_line(112, ng0);
    t4 = (t2 + 56U);
    t6 = *((char **)t4);
    xsi_process_wait(t6, 3000000000LL);
    *((char **)t3) = &&LAB7;
    t0 = 1;
    goto LAB1;

LAB7:    xsi_set_current_line(112, ng0);
    t7 = ((char*)((ng3)));
    t8 = (t1 + 4248);
    xsi_vlogvar_assign_value(t8, t7, 0, 0, 1);
    goto LAB4;

}

static int sp_tskRunPUSH(char *t1, char *t2)
{
    char t5[8];
    char t6[8];
    char t18[8];
    int t0;
    char *t3;
    char *t4;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t30;
    char *t31;
    char *t32;
    char *t33;
    char *t34;
    char *t35;
    char *t36;
    char *t37;
    char *t38;
    int t39;
    char *t40;
    char *t41;
    char *t42;
    char *t43;

LAB0:    t0 = 1;
    t3 = (t2 + 48U);
    t4 = *((char **)t3);
    if (t4 == 0)
        goto LAB2;

LAB3:    goto *t4;

LAB2:    t4 = (t1 + 1280);
    xsi_vlog_subprogram_setdisablestate(t4, &&LAB4);
    xsi_set_current_line(120, ng0);

LAB5:    xsi_set_current_line(121, ng0);
    t7 = (t1 + 6328);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t6, 0, 8);
    t10 = (t6 + 4);
    t11 = (t9 + 4);
    t12 = *((unsigned int *)t9);
    t13 = (t12 >> 0);
    *((unsigned int *)t6) = t13;
    t14 = *((unsigned int *)t11);
    t15 = (t14 >> 0);
    *((unsigned int *)t10) = t15;
    t16 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t16 & 15U);
    t17 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t17 & 15U);
    t19 = (t1 + 6168);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    memset(t18, 0, 8);
    t22 = (t18 + 4);
    t23 = (t21 + 4);
    t24 = *((unsigned int *)t21);
    t25 = (t24 >> 0);
    *((unsigned int *)t18) = t25;
    t26 = *((unsigned int *)t23);
    t27 = (t26 >> 0);
    *((unsigned int *)t22) = t27;
    t28 = *((unsigned int *)t18);
    *((unsigned int *)t18) = (t28 & 3U);
    t29 = *((unsigned int *)t22);
    *((unsigned int *)t22) = (t29 & 3U);
    t30 = ((char*)((ng4)));
    xsi_vlogtype_concat(t5, 8, 8, 3U, t30, 2, t18, 2, t6, 4);
    t31 = (t1 + 6488);
    xsi_vlogvar_assign_value(t31, t5, 0, 0, 8);
    xsi_set_current_line(122, ng0);
    t4 = (t1 + 6488);
    t7 = (t4 + 56U);
    t8 = *((char **)t7);
    t9 = (t2 + 56U);
    t10 = *((char **)t9);
    t11 = (t2 + 56U);
    t19 = *((char **)t11);
    xsi_vlog_subprograminvocation_setJumpstate(t2, t19, &&LAB6);
    t20 = (t2 + 56U);
    t21 = *((char **)t20);
    t22 = (t1 + 848);
    t23 = xsi_create_subprogram_invocation(t21, 0, t1, t22, 0, t2);
    xsi_vlog_subprogram_pushinvocation(t22, t23);
    t30 = (t1 + 6008);
    xsi_vlogvar_assign_value(t30, t8, 0, 0, 8);

LAB8:    t31 = (t2 + 64U);
    t32 = *((char **)t31);
    t33 = (t32 + 80U);
    t34 = *((char **)t33);
    t35 = (t34 + 272U);
    t36 = *((char **)t35);
    t37 = (t36 + 0U);
    t38 = *((char **)t37);
    t39 = ((int  (*)(char *, char *))t38)(t1, t32);
    if (t39 == -1)
        goto LAB9;

LAB10:    if (t39 != 0)
        goto LAB11;

LAB6:    t32 = (t1 + 848);
    xsi_vlog_subprogram_popinvocation(t32);

LAB7:    t40 = (t2 + 64U);
    t41 = *((char **)t40);
    t40 = (t1 + 848);
    t42 = (t2 + 56U);
    t43 = *((char **)t42);
    xsi_delete_subprogram_invocation(t40, t41, t1, t43, t2);

LAB4:    xsi_vlog_dispose_subprogram_invocation(t2);
    t4 = (t2 + 48U);
    *((char **)t4) = &&LAB2;
    t0 = 0;

LAB1:    return t0;
LAB9:    t0 = -1;
    goto LAB1;

LAB11:    t31 = (t2 + 48U);
    *((char **)t31) = &&LAB8;
    goto LAB1;

}

static int sp_tskRunSEND(char *t1, char *t2)
{
    char t5[8];
    char t7[8];
    int t0;
    char *t3;
    char *t4;
    char *t6;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    char *t30;
    char *t31;
    int t32;
    char *t33;
    char *t34;
    char *t35;
    char *t36;

LAB0:    t0 = 1;
    t3 = (t2 + 48U);
    t4 = *((char **)t3);
    if (t4 == 0)
        goto LAB2;

LAB3:    goto *t4;

LAB2:    t4 = (t1 + 1712);
    xsi_vlog_subprogram_setdisablestate(t4, &&LAB4);
    xsi_set_current_line(129, ng0);

LAB5:    xsi_set_current_line(130, ng0);
    t6 = ((char*)((ng4)));
    t8 = (t1 + 6648);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memset(t7, 0, 8);
    t11 = (t7 + 4);
    t12 = (t10 + 4);
    t13 = *((unsigned int *)t10);
    t14 = (t13 >> 0);
    *((unsigned int *)t7) = t14;
    t15 = *((unsigned int *)t12);
    t16 = (t15 >> 0);
    *((unsigned int *)t11) = t16;
    t17 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t17 & 3U);
    t18 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t18 & 3U);
    t19 = ((char*)((ng5)));
    xsi_vlogtype_concat(t5, 8, 8, 3U, t19, 2, t7, 2, t6, 4);
    t20 = (t1 + 6808);
    xsi_vlogvar_assign_value(t20, t5, 0, 0, 8);
    xsi_set_current_line(131, ng0);
    t4 = (t1 + 6808);
    t6 = (t4 + 56U);
    t8 = *((char **)t6);
    t9 = (t2 + 56U);
    t10 = *((char **)t9);
    t11 = (t2 + 56U);
    t12 = *((char **)t11);
    xsi_vlog_subprograminvocation_setJumpstate(t2, t12, &&LAB6);
    t19 = (t2 + 56U);
    t20 = *((char **)t19);
    t21 = (t1 + 848);
    t22 = xsi_create_subprogram_invocation(t20, 0, t1, t21, 0, t2);
    xsi_vlog_subprogram_pushinvocation(t21, t22);
    t23 = (t1 + 6008);
    xsi_vlogvar_assign_value(t23, t8, 0, 0, 8);

LAB8:    t24 = (t2 + 64U);
    t25 = *((char **)t24);
    t26 = (t25 + 80U);
    t27 = *((char **)t26);
    t28 = (t27 + 272U);
    t29 = *((char **)t28);
    t30 = (t29 + 0U);
    t31 = *((char **)t30);
    t32 = ((int  (*)(char *, char *))t31)(t1, t25);
    if (t32 == -1)
        goto LAB9;

LAB10:    if (t32 != 0)
        goto LAB11;

LAB6:    t25 = (t1 + 848);
    xsi_vlog_subprogram_popinvocation(t25);

LAB7:    t33 = (t2 + 64U);
    t34 = *((char **)t33);
    t33 = (t1 + 848);
    t35 = (t2 + 56U);
    t36 = *((char **)t35);
    xsi_delete_subprogram_invocation(t33, t34, t1, t36, t2);

LAB4:    xsi_vlog_dispose_subprogram_invocation(t2);
    t4 = (t2 + 48U);
    *((char **)t4) = &&LAB2;
    t0 = 0;

LAB1:    return t0;
LAB9:    t0 = -1;
    goto LAB1;

LAB11:    t24 = (t2 + 48U);
    *((char **)t24) = &&LAB8;
    goto LAB1;

}

static int sp_tskRunADD(char *t1, char *t2)
{
    char t5[8];
    char t6[8];
    char t18[8];
    char t30[8];
    int t0;
    char *t3;
    char *t4;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t31;
    char *t32;
    char *t33;
    char *t34;
    char *t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    char *t42;
    char *t43;
    char *t44;
    char *t45;
    int t46;
    char *t47;
    char *t48;
    char *t49;
    char *t50;

LAB0:    t0 = 1;
    t3 = (t2 + 48U);
    t4 = *((char **)t3);
    if (t4 == 0)
        goto LAB2;

LAB3:    goto *t4;

LAB2:    t4 = (t1 + 2144);
    xsi_vlog_subprogram_setdisablestate(t4, &&LAB4);
    xsi_set_current_line(140, ng0);

LAB5:    xsi_set_current_line(141, ng0);
    t7 = (t1 + 7288);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t6, 0, 8);
    t10 = (t6 + 4);
    t11 = (t9 + 4);
    t12 = *((unsigned int *)t9);
    t13 = (t12 >> 0);
    *((unsigned int *)t6) = t13;
    t14 = *((unsigned int *)t11);
    t15 = (t14 >> 0);
    *((unsigned int *)t10) = t15;
    t16 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t16 & 3U);
    t17 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t17 & 3U);
    t19 = (t1 + 7128);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    memset(t18, 0, 8);
    t22 = (t18 + 4);
    t23 = (t21 + 4);
    t24 = *((unsigned int *)t21);
    t25 = (t24 >> 0);
    *((unsigned int *)t18) = t25;
    t26 = *((unsigned int *)t23);
    t27 = (t26 >> 0);
    *((unsigned int *)t22) = t27;
    t28 = *((unsigned int *)t18);
    *((unsigned int *)t18) = (t28 & 3U);
    t29 = *((unsigned int *)t22);
    *((unsigned int *)t22) = (t29 & 3U);
    t31 = (t1 + 6968);
    t32 = (t31 + 56U);
    t33 = *((char **)t32);
    memset(t30, 0, 8);
    t34 = (t30 + 4);
    t35 = (t33 + 4);
    t36 = *((unsigned int *)t33);
    t37 = (t36 >> 0);
    *((unsigned int *)t30) = t37;
    t38 = *((unsigned int *)t35);
    t39 = (t38 >> 0);
    *((unsigned int *)t34) = t39;
    t40 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t40 & 3U);
    t41 = *((unsigned int *)t34);
    *((unsigned int *)t34) = (t41 & 3U);
    t42 = ((char*)((ng6)));
    xsi_vlogtype_concat(t5, 8, 8, 4U, t42, 2, t30, 2, t18, 2, t6, 2);
    t43 = (t1 + 7448);
    xsi_vlogvar_assign_value(t43, t5, 0, 0, 8);
    xsi_set_current_line(142, ng0);
    t4 = (t1 + 7448);
    t7 = (t4 + 56U);
    t8 = *((char **)t7);
    t9 = (t2 + 56U);
    t10 = *((char **)t9);
    t11 = (t2 + 56U);
    t19 = *((char **)t11);
    xsi_vlog_subprograminvocation_setJumpstate(t2, t19, &&LAB6);
    t20 = (t2 + 56U);
    t21 = *((char **)t20);
    t22 = (t1 + 848);
    t23 = xsi_create_subprogram_invocation(t21, 0, t1, t22, 0, t2);
    xsi_vlog_subprogram_pushinvocation(t22, t23);
    t31 = (t1 + 6008);
    xsi_vlogvar_assign_value(t31, t8, 0, 0, 8);

LAB8:    t32 = (t2 + 64U);
    t33 = *((char **)t32);
    t34 = (t33 + 80U);
    t35 = *((char **)t34);
    t42 = (t35 + 272U);
    t43 = *((char **)t42);
    t44 = (t43 + 0U);
    t45 = *((char **)t44);
    t46 = ((int  (*)(char *, char *))t45)(t1, t33);
    if (t46 == -1)
        goto LAB9;

LAB10:    if (t46 != 0)
        goto LAB11;

LAB6:    t33 = (t1 + 848);
    xsi_vlog_subprogram_popinvocation(t33);

LAB7:    t47 = (t2 + 64U);
    t48 = *((char **)t47);
    t47 = (t1 + 848);
    t49 = (t2 + 56U);
    t50 = *((char **)t49);
    xsi_delete_subprogram_invocation(t47, t48, t1, t50, t2);

LAB4:    xsi_vlog_dispose_subprogram_invocation(t2);
    t4 = (t2 + 48U);
    *((char **)t4) = &&LAB2;
    t0 = 0;

LAB1:    return t0;
LAB9:    t0 = -1;
    goto LAB1;

LAB11:    t32 = (t2 + 48U);
    *((char **)t32) = &&LAB8;
    goto LAB1;

}

static int sp_tskRunMULT(char *t1, char *t2)
{
    char t5[8];
    char t6[8];
    char t18[8];
    char t30[8];
    int t0;
    char *t3;
    char *t4;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t31;
    char *t32;
    char *t33;
    char *t34;
    char *t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    char *t42;
    char *t43;
    char *t44;
    char *t45;
    int t46;
    char *t47;
    char *t48;
    char *t49;
    char *t50;

LAB0:    t0 = 1;
    t3 = (t2 + 48U);
    t4 = *((char **)t3);
    if (t4 == 0)
        goto LAB2;

LAB3:    goto *t4;

LAB2:    t4 = (t1 + 2576);
    xsi_vlog_subprogram_setdisablestate(t4, &&LAB4);
    xsi_set_current_line(151, ng0);

LAB5:    xsi_set_current_line(152, ng0);
    t7 = (t1 + 7928);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t6, 0, 8);
    t10 = (t6 + 4);
    t11 = (t9 + 4);
    t12 = *((unsigned int *)t9);
    t13 = (t12 >> 0);
    *((unsigned int *)t6) = t13;
    t14 = *((unsigned int *)t11);
    t15 = (t14 >> 0);
    *((unsigned int *)t10) = t15;
    t16 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t16 & 3U);
    t17 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t17 & 3U);
    t19 = (t1 + 7768);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    memset(t18, 0, 8);
    t22 = (t18 + 4);
    t23 = (t21 + 4);
    t24 = *((unsigned int *)t21);
    t25 = (t24 >> 0);
    *((unsigned int *)t18) = t25;
    t26 = *((unsigned int *)t23);
    t27 = (t26 >> 0);
    *((unsigned int *)t22) = t27;
    t28 = *((unsigned int *)t18);
    *((unsigned int *)t18) = (t28 & 3U);
    t29 = *((unsigned int *)t22);
    *((unsigned int *)t22) = (t29 & 3U);
    t31 = (t1 + 7608);
    t32 = (t31 + 56U);
    t33 = *((char **)t32);
    memset(t30, 0, 8);
    t34 = (t30 + 4);
    t35 = (t33 + 4);
    t36 = *((unsigned int *)t33);
    t37 = (t36 >> 0);
    *((unsigned int *)t30) = t37;
    t38 = *((unsigned int *)t35);
    t39 = (t38 >> 0);
    *((unsigned int *)t34) = t39;
    t40 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t40 & 3U);
    t41 = *((unsigned int *)t34);
    *((unsigned int *)t34) = (t41 & 3U);
    t42 = ((char*)((ng7)));
    xsi_vlogtype_concat(t5, 8, 8, 4U, t42, 2, t30, 2, t18, 2, t6, 2);
    t43 = (t1 + 8088);
    xsi_vlogvar_assign_value(t43, t5, 0, 0, 8);
    xsi_set_current_line(153, ng0);
    t4 = (t1 + 8088);
    t7 = (t4 + 56U);
    t8 = *((char **)t7);
    t9 = (t2 + 56U);
    t10 = *((char **)t9);
    t11 = (t2 + 56U);
    t19 = *((char **)t11);
    xsi_vlog_subprograminvocation_setJumpstate(t2, t19, &&LAB6);
    t20 = (t2 + 56U);
    t21 = *((char **)t20);
    t22 = (t1 + 848);
    t23 = xsi_create_subprogram_invocation(t21, 0, t1, t22, 0, t2);
    xsi_vlog_subprogram_pushinvocation(t22, t23);
    t31 = (t1 + 6008);
    xsi_vlogvar_assign_value(t31, t8, 0, 0, 8);

LAB8:    t32 = (t2 + 64U);
    t33 = *((char **)t32);
    t34 = (t33 + 80U);
    t35 = *((char **)t34);
    t42 = (t35 + 272U);
    t43 = *((char **)t42);
    t44 = (t43 + 0U);
    t45 = *((char **)t44);
    t46 = ((int  (*)(char *, char *))t45)(t1, t33);
    if (t46 == -1)
        goto LAB9;

LAB10:    if (t46 != 0)
        goto LAB11;

LAB6:    t33 = (t1 + 848);
    xsi_vlog_subprogram_popinvocation(t33);

LAB7:    t47 = (t2 + 64U);
    t48 = *((char **)t47);
    t47 = (t1 + 848);
    t49 = (t2 + 56U);
    t50 = *((char **)t49);
    xsi_delete_subprogram_invocation(t47, t48, t1, t50, t2);

LAB4:    xsi_vlog_dispose_subprogram_invocation(t2);
    t4 = (t2 + 48U);
    *((char **)t4) = &&LAB2;
    t0 = 0;

LAB1:    return t0;
LAB9:    t0 = -1;
    goto LAB1;

LAB11:    t32 = (t2 + 48U);
    *((char **)t32) = &&LAB8;
    goto LAB1;

}

static void Initial_29_0(char *t0)
{
    char t5[8];
    char t9[8];
    char t31[8];
    char t47[8];
    char t62[8];
    char t72[8];
    char t78[8];
    char t94[8];
    char t102[8];
    char t144[8];
    char t154[8];
    char t159[8];
    char t163[8];
    char t173[8];
    char t178[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t6;
    char *t7;
    char *t8;
    char *t10;
    char *t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    int t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    char *t30;
    char *t32;
    char *t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    char *t46;
    char *t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    unsigned int t53;
    char *t54;
    char *t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    char *t59;
    char *t60;
    char *t61;
    char *t63;
    char *t64;
    char *t65;
    char *t66;
    char *t67;
    char *t68;
    char *t69;
    char *t70;
    char *t71;
    char *t73;
    char *t74;
    char *t75;
    char *t76;
    char *t77;
    char *t79;
    char *t80;
    unsigned int t81;
    unsigned int t82;
    unsigned int t83;
    unsigned int t84;
    unsigned int t85;
    unsigned int t86;
    unsigned int t87;
    unsigned int t88;
    unsigned int t89;
    unsigned int t90;
    unsigned int t91;
    unsigned int t92;
    char *t93;
    char *t95;
    unsigned int t96;
    unsigned int t97;
    unsigned int t98;
    unsigned int t99;
    unsigned int t100;
    char *t101;
    unsigned int t103;
    unsigned int t104;
    unsigned int t105;
    char *t106;
    char *t107;
    char *t108;
    unsigned int t109;
    unsigned int t110;
    unsigned int t111;
    unsigned int t112;
    unsigned int t113;
    unsigned int t114;
    unsigned int t115;
    char *t116;
    char *t117;
    unsigned int t118;
    unsigned int t119;
    unsigned int t120;
    unsigned int t121;
    unsigned int t122;
    unsigned int t123;
    unsigned int t124;
    unsigned int t125;
    int t126;
    int t127;
    unsigned int t128;
    unsigned int t129;
    unsigned int t130;
    unsigned int t131;
    unsigned int t132;
    unsigned int t133;
    char *t134;
    unsigned int t135;
    unsigned int t136;
    unsigned int t137;
    unsigned int t138;
    unsigned int t139;
    char *t140;
    char *t141;
    char *t142;
    char *t143;
    char *t145;
    char *t146;
    char *t147;
    char *t148;
    char *t149;
    char *t150;
    char *t151;
    char *t152;
    char *t153;
    char *t155;
    char *t156;
    char *t157;
    char *t158;
    char *t160;
    char *t161;
    char *t162;
    char *t164;
    char *t165;
    char *t166;
    char *t167;
    char *t168;
    char *t169;
    char *t170;
    char *t171;
    char *t172;
    char *t174;
    char *t175;
    char *t176;
    char *t177;
    char *t179;

LAB0:    t1 = (t0 + 9008U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(30, ng0);

LAB4:    xsi_set_current_line(34, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 4088);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(35, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 4408);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(36, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 4248);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(37, ng0);
    t2 = (t0 + 8816);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB5;

LAB1:    return;
LAB5:    xsi_set_current_line(37, ng0);
    t3 = ((char*)((ng3)));
    t4 = (t0 + 4408);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(38, ng0);
    t2 = (t0 + 8816);
    xsi_process_wait(t2, 1500000000LL);
    *((char **)t1) = &&LAB6;
    goto LAB1;

LAB6:    xsi_set_current_line(40, ng0);
    *((int *)t5) = xsi_vlogfile_file_open_of_cname_ctype(ng8, ng9);
    t2 = (t5 + 4);
    *((int *)t2) = 0;
    t3 = (t0 + 4728);
    xsi_vlogvar_assign_value(t3, t5, 0, 0, 32);
    xsi_set_current_line(42, ng0);
    t2 = (t0 + 4728);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t6 = (t0 + 4888);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    xsi_vlog_bit_copy(t5, 0, t8, 0, 32);
    *((int *)t9) = xsi_vlogfile_fscanf(*((unsigned int *)t4), ng10, 2, t0, (char)119, t5, 32);
    t10 = (t9 + 4);
    *((int *)t10) = 0;
    t11 = (t0 + 4888);
    xsi_vlogvar_assign_value(t11, t5, 0, 0, 32);
    xsi_set_current_line(43, ng0);
    t2 = (t0 + 5048);
    xsi_vlogfile_readmemb(ng8, 0, t2, 0, 0, 0, 0);
    xsi_set_current_line(45, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 5208);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 32);
    xsi_set_current_line(46, ng0);
    t2 = (t0 + 4888);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t6 = (t4 + 4);
    t12 = *((unsigned int *)t6);
    t13 = (~(t12));
    t14 = *((unsigned int *)t4);
    t15 = (t14 & t13);
    t7 = (t0 + 12360);
    *((int *)t7) = t15;

LAB7:    t8 = (t0 + 12360);
    if (*((int *)t8) > 0)
        goto LAB8;

LAB9:    xsi_set_current_line(79, ng0);
    t2 = (t0 + 8816);
    xsi_process_wait(t2, 1000000LL);
    *((char **)t1) = &&LAB139;
    goto LAB1;

LAB8:    xsi_set_current_line(46, ng0);

LAB10:    xsi_set_current_line(47, ng0);
    t10 = (t0 + 5048);
    t11 = (t10 + 56U);
    t16 = *((char **)t11);
    t17 = (t0 + 5048);
    t18 = (t17 + 72U);
    t19 = *((char **)t18);
    t20 = (t0 + 5048);
    t21 = (t20 + 64U);
    t22 = *((char **)t21);
    t23 = (t0 + 5208);
    t24 = (t23 + 56U);
    t25 = *((char **)t24);
    xsi_vlog_generic_get_array_select_value(t5, 8, t16, t19, t22, 2, 1, t25, 32, 1);
    t26 = (t0 + 5048);
    t27 = (t26 + 72U);
    t28 = *((char **)t27);
    t29 = ((char*)((ng11)));
    xsi_vlog_generic_get_index_select_value(t9, 32, t5, t28, 2, t29, 32, 1);
    t30 = ((char*)((ng3)));
    memset(t31, 0, 8);
    t32 = (t9 + 4);
    t33 = (t30 + 4);
    t34 = *((unsigned int *)t9);
    t35 = *((unsigned int *)t30);
    t36 = (t34 ^ t35);
    t37 = *((unsigned int *)t32);
    t38 = *((unsigned int *)t33);
    t39 = (t37 ^ t38);
    t40 = (t36 | t39);
    t41 = *((unsigned int *)t32);
    t42 = *((unsigned int *)t33);
    t43 = (t41 | t42);
    t44 = (~(t43));
    t45 = (t40 & t44);
    if (t45 != 0)
        goto LAB14;

LAB11:    if (t43 != 0)
        goto LAB13;

LAB12:    *((unsigned int *)t31) = 1;

LAB14:    memset(t47, 0, 8);
    t48 = (t31 + 4);
    t49 = *((unsigned int *)t48);
    t50 = (~(t49));
    t51 = *((unsigned int *)t31);
    t52 = (t51 & t50);
    t53 = (t52 & 1U);
    if (t53 != 0)
        goto LAB15;

LAB16:    if (*((unsigned int *)t48) != 0)
        goto LAB17;

LAB18:    t55 = (t47 + 4);
    t56 = *((unsigned int *)t47);
    t57 = *((unsigned int *)t55);
    t58 = (t56 || t57);
    if (t58 > 0)
        goto LAB19;

LAB20:    memcpy(t102, t47, 8);

LAB21:    t134 = (t102 + 4);
    t135 = *((unsigned int *)t134);
    t136 = (~(t135));
    t137 = *((unsigned int *)t102);
    t138 = (t137 & t136);
    t139 = (t138 != 0);
    if (t139 > 0)
        goto LAB33;

LAB34:    xsi_set_current_line(54, ng0);
    t2 = (t0 + 5048);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t6 = (t0 + 5048);
    t7 = (t6 + 72U);
    t8 = *((char **)t7);
    t10 = (t0 + 5048);
    t11 = (t10 + 64U);
    t16 = *((char **)t11);
    t17 = (t0 + 5208);
    t18 = (t17 + 56U);
    t19 = *((char **)t18);
    xsi_vlog_generic_get_array_select_value(t5, 8, t4, t8, t16, 2, 1, t19, 32, 1);
    t20 = (t0 + 5048);
    t21 = (t20 + 72U);
    t22 = *((char **)t21);
    t23 = ((char*)((ng11)));
    xsi_vlog_generic_get_index_select_value(t9, 32, t5, t22, 2, t23, 32, 1);
    t24 = ((char*)((ng3)));
    memset(t31, 0, 8);
    t25 = (t9 + 4);
    t26 = (t24 + 4);
    t12 = *((unsigned int *)t9);
    t13 = *((unsigned int *)t24);
    t14 = (t12 ^ t13);
    t34 = *((unsigned int *)t25);
    t35 = *((unsigned int *)t26);
    t36 = (t34 ^ t35);
    t37 = (t14 | t36);
    t38 = *((unsigned int *)t25);
    t39 = *((unsigned int *)t26);
    t40 = (t38 | t39);
    t41 = (~(t40));
    t42 = (t37 & t41);
    if (t42 != 0)
        goto LAB46;

LAB43:    if (t40 != 0)
        goto LAB45;

LAB44:    *((unsigned int *)t31) = 1;

LAB46:    memset(t47, 0, 8);
    t28 = (t31 + 4);
    t43 = *((unsigned int *)t28);
    t44 = (~(t43));
    t45 = *((unsigned int *)t31);
    t49 = (t45 & t44);
    t50 = (t49 & 1U);
    if (t50 != 0)
        goto LAB47;

LAB48:    if (*((unsigned int *)t28) != 0)
        goto LAB49;

LAB50:    t30 = (t47 + 4);
    t51 = *((unsigned int *)t47);
    t52 = *((unsigned int *)t30);
    t53 = (t51 || t52);
    if (t53 > 0)
        goto LAB51;

LAB52:    memcpy(t102, t47, 8);

LAB53:    t101 = (t102 + 4);
    t131 = *((unsigned int *)t101);
    t132 = (~(t131));
    t133 = *((unsigned int *)t102);
    t135 = (t133 & t132);
    t136 = (t135 != 0);
    if (t136 > 0)
        goto LAB65;

LAB66:    xsi_set_current_line(61, ng0);
    t2 = (t0 + 5048);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t6 = (t0 + 5048);
    t7 = (t6 + 72U);
    t8 = *((char **)t7);
    t10 = (t0 + 5048);
    t11 = (t10 + 64U);
    t16 = *((char **)t11);
    t17 = (t0 + 5208);
    t18 = (t17 + 56U);
    t19 = *((char **)t18);
    xsi_vlog_generic_get_array_select_value(t5, 8, t4, t8, t16, 2, 1, t19, 32, 1);
    t20 = (t0 + 5048);
    t21 = (t20 + 72U);
    t22 = *((char **)t21);
    t23 = ((char*)((ng11)));
    xsi_vlog_generic_get_index_select_value(t9, 32, t5, t22, 2, t23, 32, 1);
    t24 = ((char*)((ng2)));
    memset(t31, 0, 8);
    t25 = (t9 + 4);
    t26 = (t24 + 4);
    t12 = *((unsigned int *)t9);
    t13 = *((unsigned int *)t24);
    t14 = (t12 ^ t13);
    t34 = *((unsigned int *)t25);
    t35 = *((unsigned int *)t26);
    t36 = (t34 ^ t35);
    t37 = (t14 | t36);
    t38 = *((unsigned int *)t25);
    t39 = *((unsigned int *)t26);
    t40 = (t38 | t39);
    t41 = (~(t40));
    t42 = (t37 & t41);
    if (t42 != 0)
        goto LAB78;

LAB75:    if (t40 != 0)
        goto LAB77;

LAB76:    *((unsigned int *)t31) = 1;

LAB78:    memset(t47, 0, 8);
    t28 = (t31 + 4);
    t43 = *((unsigned int *)t28);
    t44 = (~(t43));
    t45 = *((unsigned int *)t31);
    t49 = (t45 & t44);
    t50 = (t49 & 1U);
    if (t50 != 0)
        goto LAB79;

LAB80:    if (*((unsigned int *)t28) != 0)
        goto LAB81;

LAB82:    t30 = (t47 + 4);
    t51 = *((unsigned int *)t47);
    t52 = *((unsigned int *)t30);
    t53 = (t51 || t52);
    if (t53 > 0)
        goto LAB83;

LAB84:    memcpy(t102, t47, 8);

LAB85:    t101 = (t102 + 4);
    t131 = *((unsigned int *)t101);
    t132 = (~(t131));
    t133 = *((unsigned int *)t102);
    t135 = (t133 & t132);
    t136 = (t135 != 0);
    if (t136 > 0)
        goto LAB97;

LAB98:    xsi_set_current_line(70, ng0);
    t2 = (t0 + 5048);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t6 = (t0 + 5048);
    t7 = (t6 + 72U);
    t8 = *((char **)t7);
    t10 = (t0 + 5048);
    t11 = (t10 + 64U);
    t16 = *((char **)t11);
    t17 = (t0 + 5208);
    t18 = (t17 + 56U);
    t19 = *((char **)t18);
    xsi_vlog_generic_get_array_select_value(t5, 8, t4, t8, t16, 2, 1, t19, 32, 1);
    t20 = (t0 + 5048);
    t21 = (t20 + 72U);
    t22 = *((char **)t21);
    t23 = ((char*)((ng11)));
    xsi_vlog_generic_get_index_select_value(t9, 32, t5, t22, 2, t23, 32, 1);
    t24 = ((char*)((ng2)));
    memset(t31, 0, 8);
    t25 = (t9 + 4);
    t26 = (t24 + 4);
    t12 = *((unsigned int *)t9);
    t13 = *((unsigned int *)t24);
    t14 = (t12 ^ t13);
    t34 = *((unsigned int *)t25);
    t35 = *((unsigned int *)t26);
    t36 = (t34 ^ t35);
    t37 = (t14 | t36);
    t38 = *((unsigned int *)t25);
    t39 = *((unsigned int *)t26);
    t40 = (t38 | t39);
    t41 = (~(t40));
    t42 = (t37 & t41);
    if (t42 != 0)
        goto LAB110;

LAB107:    if (t40 != 0)
        goto LAB109;

LAB108:    *((unsigned int *)t31) = 1;

LAB110:    memset(t47, 0, 8);
    t28 = (t31 + 4);
    t43 = *((unsigned int *)t28);
    t44 = (~(t43));
    t45 = *((unsigned int *)t31);
    t49 = (t45 & t44);
    t50 = (t49 & 1U);
    if (t50 != 0)
        goto LAB111;

LAB112:    if (*((unsigned int *)t28) != 0)
        goto LAB113;

LAB114:    t30 = (t47 + 4);
    t51 = *((unsigned int *)t47);
    t52 = *((unsigned int *)t30);
    t53 = (t51 || t52);
    if (t53 > 0)
        goto LAB115;

LAB116:    memcpy(t102, t47, 8);

LAB117:    t101 = (t102 + 4);
    t131 = *((unsigned int *)t101);
    t132 = (~(t131));
    t133 = *((unsigned int *)t102);
    t135 = (t133 & t132);
    t136 = (t135 != 0);
    if (t136 > 0)
        goto LAB129;

LAB130:
LAB131:
LAB99:
LAB67:
LAB35:    xsi_set_current_line(76, ng0);
    t2 = (t0 + 5208);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t6 = ((char*)((ng2)));
    memset(t5, 0, 8);
    xsi_vlog_signed_add(t5, 32, t4, 32, t6, 32);
    t7 = (t0 + 5208);
    xsi_vlogvar_assign_value(t7, t5, 0, 0, 32);
    t2 = (t0 + 12360);
    t15 = *((int *)t2);
    *((int *)t2) = (t15 - 1);
    goto LAB7;

LAB13:    t46 = (t31 + 4);
    *((unsigned int *)t31) = 1;
    *((unsigned int *)t46) = 1;
    goto LAB14;

LAB15:    *((unsigned int *)t47) = 1;
    goto LAB18;

LAB17:    t54 = (t47 + 4);
    *((unsigned int *)t47) = 1;
    *((unsigned int *)t54) = 1;
    goto LAB18;

LAB19:    t59 = (t0 + 5048);
    t60 = (t59 + 56U);
    t61 = *((char **)t60);
    t63 = (t0 + 5048);
    t64 = (t63 + 72U);
    t65 = *((char **)t64);
    t66 = (t0 + 5048);
    t67 = (t66 + 64U);
    t68 = *((char **)t67);
    t69 = (t0 + 5208);
    t70 = (t69 + 56U);
    t71 = *((char **)t70);
    xsi_vlog_generic_get_array_select_value(t62, 8, t61, t65, t68, 2, 1, t71, 32, 1);
    t73 = (t0 + 5048);
    t74 = (t73 + 72U);
    t75 = *((char **)t74);
    t76 = ((char*)((ng12)));
    xsi_vlog_generic_get_index_select_value(t72, 32, t62, t75, 2, t76, 32, 1);
    t77 = ((char*)((ng3)));
    memset(t78, 0, 8);
    t79 = (t72 + 4);
    t80 = (t77 + 4);
    t81 = *((unsigned int *)t72);
    t82 = *((unsigned int *)t77);
    t83 = (t81 ^ t82);
    t84 = *((unsigned int *)t79);
    t85 = *((unsigned int *)t80);
    t86 = (t84 ^ t85);
    t87 = (t83 | t86);
    t88 = *((unsigned int *)t79);
    t89 = *((unsigned int *)t80);
    t90 = (t88 | t89);
    t91 = (~(t90));
    t92 = (t87 & t91);
    if (t92 != 0)
        goto LAB25;

LAB22:    if (t90 != 0)
        goto LAB24;

LAB23:    *((unsigned int *)t78) = 1;

LAB25:    memset(t94, 0, 8);
    t95 = (t78 + 4);
    t96 = *((unsigned int *)t95);
    t97 = (~(t96));
    t98 = *((unsigned int *)t78);
    t99 = (t98 & t97);
    t100 = (t99 & 1U);
    if (t100 != 0)
        goto LAB26;

LAB27:    if (*((unsigned int *)t95) != 0)
        goto LAB28;

LAB29:    t103 = *((unsigned int *)t47);
    t104 = *((unsigned int *)t94);
    t105 = (t103 & t104);
    *((unsigned int *)t102) = t105;
    t106 = (t47 + 4);
    t107 = (t94 + 4);
    t108 = (t102 + 4);
    t109 = *((unsigned int *)t106);
    t110 = *((unsigned int *)t107);
    t111 = (t109 | t110);
    *((unsigned int *)t108) = t111;
    t112 = *((unsigned int *)t108);
    t113 = (t112 != 0);
    if (t113 == 1)
        goto LAB30;

LAB31:
LAB32:    goto LAB21;

LAB24:    t93 = (t78 + 4);
    *((unsigned int *)t78) = 1;
    *((unsigned int *)t93) = 1;
    goto LAB25;

LAB26:    *((unsigned int *)t94) = 1;
    goto LAB29;

LAB28:    t101 = (t94 + 4);
    *((unsigned int *)t94) = 1;
    *((unsigned int *)t101) = 1;
    goto LAB29;

LAB30:    t114 = *((unsigned int *)t102);
    t115 = *((unsigned int *)t108);
    *((unsigned int *)t102) = (t114 | t115);
    t116 = (t47 + 4);
    t117 = (t94 + 4);
    t118 = *((unsigned int *)t47);
    t119 = (~(t118));
    t120 = *((unsigned int *)t116);
    t121 = (~(t120));
    t122 = *((unsigned int *)t94);
    t123 = (~(t122));
    t124 = *((unsigned int *)t117);
    t125 = (~(t124));
    t126 = (t119 & t121);
    t127 = (t123 & t125);
    t128 = (~(t126));
    t129 = (~(t127));
    t130 = *((unsigned int *)t108);
    *((unsigned int *)t108) = (t130 & t128);
    t131 = *((unsigned int *)t108);
    *((unsigned int *)t108) = (t131 & t129);
    t132 = *((unsigned int *)t102);
    *((unsigned int *)t102) = (t132 & t128);
    t133 = *((unsigned int *)t102);
    *((unsigned int *)t102) = (t133 & t129);
    goto LAB32;

LAB33:    xsi_set_current_line(47, ng0);

LAB36:    xsi_set_current_line(48, ng0);
    t140 = ((char*)((ng13)));
    t141 = (t0 + 5048);
    t142 = (t141 + 56U);
    t143 = *((char **)t142);
    t145 = (t0 + 5048);
    t146 = (t145 + 72U);
    t147 = *((char **)t146);
    t148 = (t0 + 5048);
    t149 = (t148 + 64U);
    t150 = *((char **)t149);
    t151 = (t0 + 5208);
    t152 = (t151 + 56U);
    t153 = *((char **)t152);
    xsi_vlog_generic_get_array_select_value(t144, 8, t143, t147, t150, 2, 1, t153, 32, 1);
    t155 = (t0 + 5048);
    t156 = (t155 + 72U);
    t157 = *((char **)t156);
    t158 = ((char*)((ng14)));
    xsi_vlog_generic_get_index_select_value(t154, 32, t144, t157, 2, t158, 32, 1);
    memset(t159, 0, 8);
    xsi_vlog_unsigned_multiply(t159, 32, t140, 32, t154, 32);
    t160 = (t0 + 5048);
    t161 = (t160 + 56U);
    t162 = *((char **)t161);
    t164 = (t0 + 5048);
    t165 = (t164 + 72U);
    t166 = *((char **)t165);
    t167 = (t0 + 5048);
    t168 = (t167 + 64U);
    t169 = *((char **)t168);
    t170 = (t0 + 5208);
    t171 = (t170 + 56U);
    t172 = *((char **)t171);
    xsi_vlog_generic_get_array_select_value(t163, 8, t162, t166, t169, 2, 1, t172, 32, 1);
    t174 = (t0 + 5048);
    t175 = (t174 + 72U);
    t176 = *((char **)t175);
    t177 = ((char*)((ng15)));
    xsi_vlog_generic_get_index_select_value(t173, 32, t163, t176, 2, t177, 32, 1);
    memset(t178, 0, 8);
    xsi_vlog_unsigned_add(t178, 32, t159, 32, t173, 32);
    t179 = (t0 + 5368);
    xsi_vlogvar_assign_value(t179, t178, 0, 0, 32);
    xsi_set_current_line(49, ng0);
    t2 = ((char*)((ng16)));
    t3 = (t0 + 5048);
    t4 = (t3 + 56U);
    t6 = *((char **)t4);
    t7 = (t0 + 5048);
    t8 = (t7 + 72U);
    t10 = *((char **)t8);
    t11 = (t0 + 5048);
    t16 = (t11 + 64U);
    t17 = *((char **)t16);
    t18 = (t0 + 5208);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    xsi_vlog_generic_get_array_select_value(t5, 8, t6, t10, t17, 2, 1, t20, 32, 1);
    t21 = (t0 + 5048);
    t22 = (t21 + 72U);
    t23 = *((char **)t22);
    t24 = ((char*)((ng17)));
    xsi_vlog_generic_get_index_select_value(t9, 32, t5, t23, 2, t24, 32, 1);
    memset(t31, 0, 8);
    xsi_vlog_unsigned_multiply(t31, 32, t2, 32, t9, 32);
    t25 = ((char*)((ng15)));
    t26 = (t0 + 5048);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = (t0 + 5048);
    t30 = (t29 + 72U);
    t32 = *((char **)t30);
    t33 = (t0 + 5048);
    t46 = (t33 + 64U);
    t48 = *((char **)t46);
    t54 = (t0 + 5208);
    t55 = (t54 + 56U);
    t59 = *((char **)t55);
    xsi_vlog_generic_get_array_select_value(t47, 8, t28, t32, t48, 2, 1, t59, 32, 1);
    t60 = (t0 + 5048);
    t61 = (t60 + 72U);
    t63 = *((char **)t61);
    t64 = ((char*)((ng13)));
    xsi_vlog_generic_get_index_select_value(t62, 32, t47, t63, 2, t64, 32, 1);
    memset(t72, 0, 8);
    xsi_vlog_unsigned_multiply(t72, 32, t25, 32, t62, 32);
    memset(t78, 0, 8);
    xsi_vlog_unsigned_add(t78, 32, t31, 32, t72, 32);
    t65 = ((char*)((ng13)));
    t66 = (t0 + 5048);
    t67 = (t66 + 56U);
    t68 = *((char **)t67);
    t69 = (t0 + 5048);
    t70 = (t69 + 72U);
    t71 = *((char **)t70);
    t73 = (t0 + 5048);
    t74 = (t73 + 64U);
    t75 = *((char **)t74);
    t76 = (t0 + 5208);
    t77 = (t76 + 56U);
    t79 = *((char **)t77);
    xsi_vlog_generic_get_array_select_value(t94, 8, t68, t71, t75, 2, 1, t79, 32, 1);
    t80 = (t0 + 5048);
    t93 = (t80 + 72U);
    t95 = *((char **)t93);
    t101 = ((char*)((ng2)));
    xsi_vlog_generic_get_index_select_value(t102, 32, t94, t95, 2, t101, 32, 1);
    memset(t144, 0, 8);
    xsi_vlog_unsigned_multiply(t144, 32, t65, 32, t102, 32);
    memset(t154, 0, 8);
    xsi_vlog_unsigned_add(t154, 32, t78, 32, t144, 32);
    t106 = (t0 + 5048);
    t107 = (t106 + 56U);
    t108 = *((char **)t107);
    t116 = (t0 + 5048);
    t117 = (t116 + 72U);
    t134 = *((char **)t117);
    t140 = (t0 + 5048);
    t141 = (t140 + 64U);
    t142 = *((char **)t141);
    t143 = (t0 + 5208);
    t145 = (t143 + 56U);
    t146 = *((char **)t145);
    xsi_vlog_generic_get_array_select_value(t159, 8, t108, t134, t142, 2, 1, t146, 32, 1);
    t147 = (t0 + 5048);
    t148 = (t147 + 72U);
    t149 = *((char **)t148);
    t150 = ((char*)((ng3)));
    xsi_vlog_generic_get_index_select_value(t163, 32, t159, t149, 2, t150, 32, 1);
    memset(t173, 0, 8);
    xsi_vlog_unsigned_add(t173, 32, t154, 32, t163, 32);
    t151 = (t0 + 5848);
    xsi_vlogvar_assign_value(t151, t173, 0, 0, 32);
    xsi_set_current_line(50, ng0);
    t2 = (t0 + 5368);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t6 = (t0 + 5848);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t10 = (t0 + 8816);
    t11 = (t0 + 1280);
    t16 = xsi_create_subprogram_invocation(t10, 0, t0, t11, 0, 0);
    xsi_vlog_subprogram_pushinvocation(t11, t16);
    t17 = (t0 + 6168);
    xsi_vlogvar_assign_value(t17, t4, 0, 0, 2);
    t18 = (t0 + 6328);
    xsi_vlogvar_assign_value(t18, t8, 0, 0, 4);

LAB39:    t19 = (t0 + 8912);
    t20 = *((char **)t19);
    t21 = (t20 + 80U);
    t22 = *((char **)t21);
    t23 = (t22 + 272U);
    t24 = *((char **)t23);
    t25 = (t24 + 0U);
    t26 = *((char **)t25);
    t15 = ((int  (*)(char *, char *))t26)(t0, t20);

LAB41:    if (t15 != 0)
        goto LAB42;

LAB37:    t20 = (t0 + 1280);
    xsi_vlog_subprogram_popinvocation(t20);

LAB38:    t27 = (t0 + 8912);
    t28 = *((char **)t27);
    t27 = (t0 + 1280);
    t29 = (t0 + 8816);
    t30 = 0;
    xsi_delete_subprogram_invocation(t27, t28, t0, t29, t30);
    goto LAB35;

LAB40:;
LAB42:    t19 = (t0 + 9008U);
    *((char **)t19) = &&LAB39;
    goto LAB1;

LAB45:    t27 = (t31 + 4);
    *((unsigned int *)t31) = 1;
    *((unsigned int *)t27) = 1;
    goto LAB46;

LAB47:    *((unsigned int *)t47) = 1;
    goto LAB50;

LAB49:    t29 = (t47 + 4);
    *((unsigned int *)t47) = 1;
    *((unsigned int *)t29) = 1;
    goto LAB50;

LAB51:    t32 = (t0 + 5048);
    t33 = (t32 + 56U);
    t46 = *((char **)t33);
    t48 = (t0 + 5048);
    t54 = (t48 + 72U);
    t55 = *((char **)t54);
    t59 = (t0 + 5048);
    t60 = (t59 + 64U);
    t61 = *((char **)t60);
    t63 = (t0 + 5208);
    t64 = (t63 + 56U);
    t65 = *((char **)t64);
    xsi_vlog_generic_get_array_select_value(t62, 8, t46, t55, t61, 2, 1, t65, 32, 1);
    t66 = (t0 + 5048);
    t67 = (t66 + 72U);
    t68 = *((char **)t67);
    t69 = ((char*)((ng12)));
    xsi_vlog_generic_get_index_select_value(t72, 32, t62, t68, 2, t69, 32, 1);
    t70 = ((char*)((ng2)));
    memset(t78, 0, 8);
    t71 = (t72 + 4);
    t73 = (t70 + 4);
    t56 = *((unsigned int *)t72);
    t57 = *((unsigned int *)t70);
    t58 = (t56 ^ t57);
    t81 = *((unsigned int *)t71);
    t82 = *((unsigned int *)t73);
    t83 = (t81 ^ t82);
    t84 = (t58 | t83);
    t85 = *((unsigned int *)t71);
    t86 = *((unsigned int *)t73);
    t87 = (t85 | t86);
    t88 = (~(t87));
    t89 = (t84 & t88);
    if (t89 != 0)
        goto LAB57;

LAB54:    if (t87 != 0)
        goto LAB56;

LAB55:    *((unsigned int *)t78) = 1;

LAB57:    memset(t94, 0, 8);
    t75 = (t78 + 4);
    t90 = *((unsigned int *)t75);
    t91 = (~(t90));
    t92 = *((unsigned int *)t78);
    t96 = (t92 & t91);
    t97 = (t96 & 1U);
    if (t97 != 0)
        goto LAB58;

LAB59:    if (*((unsigned int *)t75) != 0)
        goto LAB60;

LAB61:    t98 = *((unsigned int *)t47);
    t99 = *((unsigned int *)t94);
    t100 = (t98 & t99);
    *((unsigned int *)t102) = t100;
    t77 = (t47 + 4);
    t79 = (t94 + 4);
    t80 = (t102 + 4);
    t103 = *((unsigned int *)t77);
    t104 = *((unsigned int *)t79);
    t105 = (t103 | t104);
    *((unsigned int *)t80) = t105;
    t109 = *((unsigned int *)t80);
    t110 = (t109 != 0);
    if (t110 == 1)
        goto LAB62;

LAB63:
LAB64:    goto LAB53;

LAB56:    t74 = (t78 + 4);
    *((unsigned int *)t78) = 1;
    *((unsigned int *)t74) = 1;
    goto LAB57;

LAB58:    *((unsigned int *)t94) = 1;
    goto LAB61;

LAB60:    t76 = (t94 + 4);
    *((unsigned int *)t94) = 1;
    *((unsigned int *)t76) = 1;
    goto LAB61;

LAB62:    t111 = *((unsigned int *)t102);
    t112 = *((unsigned int *)t80);
    *((unsigned int *)t102) = (t111 | t112);
    t93 = (t47 + 4);
    t95 = (t94 + 4);
    t113 = *((unsigned int *)t47);
    t114 = (~(t113));
    t115 = *((unsigned int *)t93);
    t118 = (~(t115));
    t119 = *((unsigned int *)t94);
    t120 = (~(t119));
    t121 = *((unsigned int *)t95);
    t122 = (~(t121));
    t15 = (t114 & t118);
    t126 = (t120 & t122);
    t123 = (~(t15));
    t124 = (~(t126));
    t125 = *((unsigned int *)t80);
    *((unsigned int *)t80) = (t125 & t123);
    t128 = *((unsigned int *)t80);
    *((unsigned int *)t80) = (t128 & t124);
    t129 = *((unsigned int *)t102);
    *((unsigned int *)t102) = (t129 & t123);
    t130 = *((unsigned int *)t102);
    *((unsigned int *)t102) = (t130 & t124);
    goto LAB64;

LAB65:    xsi_set_current_line(54, ng0);

LAB68:    xsi_set_current_line(55, ng0);
    t106 = ((char*)((ng13)));
    t107 = (t0 + 5048);
    t108 = (t107 + 56U);
    t116 = *((char **)t108);
    t117 = (t0 + 5048);
    t134 = (t117 + 72U);
    t140 = *((char **)t134);
    t141 = (t0 + 5048);
    t142 = (t141 + 64U);
    t143 = *((char **)t142);
    t145 = (t0 + 5208);
    t146 = (t145 + 56U);
    t147 = *((char **)t146);
    xsi_vlog_generic_get_array_select_value(t144, 8, t116, t140, t143, 2, 1, t147, 32, 1);
    t148 = (t0 + 5048);
    t149 = (t148 + 72U);
    t150 = *((char **)t149);
    t151 = ((char*)((ng14)));
    xsi_vlog_generic_get_index_select_value(t154, 32, t144, t150, 2, t151, 32, 1);
    memset(t159, 0, 8);
    xsi_vlog_unsigned_multiply(t159, 32, t106, 32, t154, 32);
    t152 = (t0 + 5048);
    t153 = (t152 + 56U);
    t155 = *((char **)t153);
    t156 = (t0 + 5048);
    t157 = (t156 + 72U);
    t158 = *((char **)t157);
    t160 = (t0 + 5048);
    t161 = (t160 + 64U);
    t162 = *((char **)t161);
    t164 = (t0 + 5208);
    t165 = (t164 + 56U);
    t166 = *((char **)t165);
    xsi_vlog_generic_get_array_select_value(t163, 8, t155, t158, t162, 2, 1, t166, 32, 1);
    t167 = (t0 + 5048);
    t168 = (t167 + 72U);
    t169 = *((char **)t168);
    t170 = ((char*)((ng15)));
    xsi_vlog_generic_get_index_select_value(t173, 32, t163, t169, 2, t170, 32, 1);
    memset(t178, 0, 8);
    xsi_vlog_unsigned_add(t178, 32, t159, 32, t173, 32);
    t171 = (t0 + 5368);
    xsi_vlogvar_assign_value(t171, t178, 0, 0, 32);
    xsi_set_current_line(56, ng0);
    t2 = ((char*)((ng13)));
    t3 = (t0 + 5048);
    t4 = (t3 + 56U);
    t6 = *((char **)t4);
    t7 = (t0 + 5048);
    t8 = (t7 + 72U);
    t10 = *((char **)t8);
    t11 = (t0 + 5048);
    t16 = (t11 + 64U);
    t17 = *((char **)t16);
    t18 = (t0 + 5208);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    xsi_vlog_generic_get_array_select_value(t5, 8, t6, t10, t17, 2, 1, t20, 32, 1);
    t21 = (t0 + 5048);
    t22 = (t21 + 72U);
    t23 = *((char **)t22);
    t24 = ((char*)((ng17)));
    xsi_vlog_generic_get_index_select_value(t9, 32, t5, t23, 2, t24, 32, 1);
    memset(t31, 0, 8);
    xsi_vlog_unsigned_multiply(t31, 32, t2, 32, t9, 32);
    t25 = (t0 + 5048);
    t26 = (t25 + 56U);
    t27 = *((char **)t26);
    t28 = (t0 + 5048);
    t29 = (t28 + 72U);
    t30 = *((char **)t29);
    t32 = (t0 + 5048);
    t33 = (t32 + 64U);
    t46 = *((char **)t33);
    t48 = (t0 + 5208);
    t54 = (t48 + 56U);
    t55 = *((char **)t54);
    xsi_vlog_generic_get_array_select_value(t47, 8, t27, t30, t46, 2, 1, t55, 32, 1);
    t59 = (t0 + 5048);
    t60 = (t59 + 72U);
    t61 = *((char **)t60);
    t63 = ((char*)((ng13)));
    xsi_vlog_generic_get_index_select_value(t62, 32, t47, t61, 2, t63, 32, 1);
    memset(t72, 0, 8);
    xsi_vlog_unsigned_add(t72, 32, t31, 32, t62, 32);
    t64 = (t0 + 5528);
    xsi_vlogvar_assign_value(t64, t72, 0, 0, 32);
    xsi_set_current_line(57, ng0);
    t2 = ((char*)((ng13)));
    t3 = (t0 + 5048);
    t4 = (t3 + 56U);
    t6 = *((char **)t4);
    t7 = (t0 + 5048);
    t8 = (t7 + 72U);
    t10 = *((char **)t8);
    t11 = (t0 + 5048);
    t16 = (t11 + 64U);
    t17 = *((char **)t16);
    t18 = (t0 + 5208);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    xsi_vlog_generic_get_array_select_value(t5, 8, t6, t10, t17, 2, 1, t20, 32, 1);
    t21 = (t0 + 5048);
    t22 = (t21 + 72U);
    t23 = *((char **)t22);
    t24 = ((char*)((ng2)));
    xsi_vlog_generic_get_index_select_value(t9, 32, t5, t23, 2, t24, 32, 1);
    memset(t31, 0, 8);
    xsi_vlog_unsigned_multiply(t31, 32, t2, 32, t9, 32);
    t25 = (t0 + 5048);
    t26 = (t25 + 56U);
    t27 = *((char **)t26);
    t28 = (t0 + 5048);
    t29 = (t28 + 72U);
    t30 = *((char **)t29);
    t32 = (t0 + 5048);
    t33 = (t32 + 64U);
    t46 = *((char **)t33);
    t48 = (t0 + 5208);
    t54 = (t48 + 56U);
    t55 = *((char **)t54);
    xsi_vlog_generic_get_array_select_value(t47, 8, t27, t30, t46, 2, 1, t55, 32, 1);
    t59 = (t0 + 5048);
    t60 = (t59 + 72U);
    t61 = *((char **)t60);
    t63 = ((char*)((ng3)));
    xsi_vlog_generic_get_index_select_value(t62, 32, t47, t61, 2, t63, 32, 1);
    memset(t72, 0, 8);
    xsi_vlog_unsigned_add(t72, 32, t31, 32, t62, 32);
    t64 = (t0 + 5688);
    xsi_vlogvar_assign_value(t64, t72, 0, 0, 32);
    xsi_set_current_line(58, ng0);
    t2 = (t0 + 5368);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t6 = (t0 + 5528);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t10 = (t0 + 5688);
    t11 = (t10 + 56U);
    t16 = *((char **)t11);
    t17 = (t0 + 8816);
    t18 = (t0 + 2144);
    t19 = xsi_create_subprogram_invocation(t17, 0, t0, t18, 0, 0);
    xsi_vlog_subprogram_pushinvocation(t18, t19);
    t20 = (t0 + 6968);
    xsi_vlogvar_assign_value(t20, t4, 0, 0, 2);
    t21 = (t0 + 7128);
    xsi_vlogvar_assign_value(t21, t8, 0, 0, 2);
    t22 = (t0 + 7288);
    xsi_vlogvar_assign_value(t22, t16, 0, 0, 2);

LAB71:    t23 = (t0 + 8912);
    t24 = *((char **)t23);
    t25 = (t24 + 80U);
    t26 = *((char **)t25);
    t27 = (t26 + 272U);
    t28 = *((char **)t27);
    t29 = (t28 + 0U);
    t30 = *((char **)t29);
    t15 = ((int  (*)(char *, char *))t30)(t0, t24);

LAB73:    if (t15 != 0)
        goto LAB74;

LAB69:    t24 = (t0 + 2144);
    xsi_vlog_subprogram_popinvocation(t24);

LAB70:    t32 = (t0 + 8912);
    t33 = *((char **)t32);
    t32 = (t0 + 2144);
    t46 = (t0 + 8816);
    t48 = 0;
    xsi_delete_subprogram_invocation(t32, t33, t0, t46, t48);
    goto LAB67;

LAB72:;
LAB74:    t23 = (t0 + 9008U);
    *((char **)t23) = &&LAB71;
    goto LAB1;

LAB77:    t27 = (t31 + 4);
    *((unsigned int *)t31) = 1;
    *((unsigned int *)t27) = 1;
    goto LAB78;

LAB79:    *((unsigned int *)t47) = 1;
    goto LAB82;

LAB81:    t29 = (t47 + 4);
    *((unsigned int *)t47) = 1;
    *((unsigned int *)t29) = 1;
    goto LAB82;

LAB83:    t32 = (t0 + 5048);
    t33 = (t32 + 56U);
    t46 = *((char **)t33);
    t48 = (t0 + 5048);
    t54 = (t48 + 72U);
    t55 = *((char **)t54);
    t59 = (t0 + 5048);
    t60 = (t59 + 64U);
    t61 = *((char **)t60);
    t63 = (t0 + 5208);
    t64 = (t63 + 56U);
    t65 = *((char **)t64);
    xsi_vlog_generic_get_array_select_value(t62, 8, t46, t55, t61, 2, 1, t65, 32, 1);
    t66 = (t0 + 5048);
    t67 = (t66 + 72U);
    t68 = *((char **)t67);
    t69 = ((char*)((ng12)));
    xsi_vlog_generic_get_index_select_value(t72, 32, t62, t68, 2, t69, 32, 1);
    t70 = ((char*)((ng3)));
    memset(t78, 0, 8);
    t71 = (t72 + 4);
    t73 = (t70 + 4);
    t56 = *((unsigned int *)t72);
    t57 = *((unsigned int *)t70);
    t58 = (t56 ^ t57);
    t81 = *((unsigned int *)t71);
    t82 = *((unsigned int *)t73);
    t83 = (t81 ^ t82);
    t84 = (t58 | t83);
    t85 = *((unsigned int *)t71);
    t86 = *((unsigned int *)t73);
    t87 = (t85 | t86);
    t88 = (~(t87));
    t89 = (t84 & t88);
    if (t89 != 0)
        goto LAB89;

LAB86:    if (t87 != 0)
        goto LAB88;

LAB87:    *((unsigned int *)t78) = 1;

LAB89:    memset(t94, 0, 8);
    t75 = (t78 + 4);
    t90 = *((unsigned int *)t75);
    t91 = (~(t90));
    t92 = *((unsigned int *)t78);
    t96 = (t92 & t91);
    t97 = (t96 & 1U);
    if (t97 != 0)
        goto LAB90;

LAB91:    if (*((unsigned int *)t75) != 0)
        goto LAB92;

LAB93:    t98 = *((unsigned int *)t47);
    t99 = *((unsigned int *)t94);
    t100 = (t98 & t99);
    *((unsigned int *)t102) = t100;
    t77 = (t47 + 4);
    t79 = (t94 + 4);
    t80 = (t102 + 4);
    t103 = *((unsigned int *)t77);
    t104 = *((unsigned int *)t79);
    t105 = (t103 | t104);
    *((unsigned int *)t80) = t105;
    t109 = *((unsigned int *)t80);
    t110 = (t109 != 0);
    if (t110 == 1)
        goto LAB94;

LAB95:
LAB96:    goto LAB85;

LAB88:    t74 = (t78 + 4);
    *((unsigned int *)t78) = 1;
    *((unsigned int *)t74) = 1;
    goto LAB89;

LAB90:    *((unsigned int *)t94) = 1;
    goto LAB93;

LAB92:    t76 = (t94 + 4);
    *((unsigned int *)t94) = 1;
    *((unsigned int *)t76) = 1;
    goto LAB93;

LAB94:    t111 = *((unsigned int *)t102);
    t112 = *((unsigned int *)t80);
    *((unsigned int *)t102) = (t111 | t112);
    t93 = (t47 + 4);
    t95 = (t94 + 4);
    t113 = *((unsigned int *)t47);
    t114 = (~(t113));
    t115 = *((unsigned int *)t93);
    t118 = (~(t115));
    t119 = *((unsigned int *)t94);
    t120 = (~(t119));
    t121 = *((unsigned int *)t95);
    t122 = (~(t121));
    t15 = (t114 & t118);
    t126 = (t120 & t122);
    t123 = (~(t15));
    t124 = (~(t126));
    t125 = *((unsigned int *)t80);
    *((unsigned int *)t80) = (t125 & t123);
    t128 = *((unsigned int *)t80);
    *((unsigned int *)t80) = (t128 & t124);
    t129 = *((unsigned int *)t102);
    *((unsigned int *)t102) = (t129 & t123);
    t130 = *((unsigned int *)t102);
    *((unsigned int *)t102) = (t130 & t124);
    goto LAB96;

LAB97:    xsi_set_current_line(61, ng0);

LAB100:    xsi_set_current_line(63, ng0);
    t106 = ((char*)((ng13)));
    t107 = (t0 + 5048);
    t108 = (t107 + 56U);
    t116 = *((char **)t108);
    t117 = (t0 + 5048);
    t134 = (t117 + 72U);
    t140 = *((char **)t134);
    t141 = (t0 + 5048);
    t142 = (t141 + 64U);
    t143 = *((char **)t142);
    t145 = (t0 + 5208);
    t146 = (t145 + 56U);
    t147 = *((char **)t146);
    xsi_vlog_generic_get_array_select_value(t144, 8, t116, t140, t143, 2, 1, t147, 32, 1);
    t148 = (t0 + 5048);
    t149 = (t148 + 72U);
    t150 = *((char **)t149);
    t151 = ((char*)((ng14)));
    xsi_vlog_generic_get_index_select_value(t154, 32, t144, t150, 2, t151, 32, 1);
    memset(t159, 0, 8);
    xsi_vlog_unsigned_multiply(t159, 32, t106, 32, t154, 32);
    t152 = (t0 + 5048);
    t153 = (t152 + 56U);
    t155 = *((char **)t153);
    t156 = (t0 + 5048);
    t157 = (t156 + 72U);
    t158 = *((char **)t157);
    t160 = (t0 + 5048);
    t161 = (t160 + 64U);
    t162 = *((char **)t161);
    t164 = (t0 + 5208);
    t165 = (t164 + 56U);
    t166 = *((char **)t165);
    xsi_vlog_generic_get_array_select_value(t163, 8, t155, t158, t162, 2, 1, t166, 32, 1);
    t167 = (t0 + 5048);
    t168 = (t167 + 72U);
    t169 = *((char **)t168);
    t170 = ((char*)((ng15)));
    xsi_vlog_generic_get_index_select_value(t173, 32, t163, t169, 2, t170, 32, 1);
    memset(t178, 0, 8);
    xsi_vlog_unsigned_add(t178, 32, t159, 32, t173, 32);
    t171 = (t0 + 5368);
    xsi_vlogvar_assign_value(t171, t178, 0, 0, 32);
    xsi_set_current_line(64, ng0);
    t2 = ((char*)((ng13)));
    t3 = (t0 + 5048);
    t4 = (t3 + 56U);
    t6 = *((char **)t4);
    t7 = (t0 + 5048);
    t8 = (t7 + 72U);
    t10 = *((char **)t8);
    t11 = (t0 + 5048);
    t16 = (t11 + 64U);
    t17 = *((char **)t16);
    t18 = (t0 + 5208);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    xsi_vlog_generic_get_array_select_value(t5, 8, t6, t10, t17, 2, 1, t20, 32, 1);
    t21 = (t0 + 5048);
    t22 = (t21 + 72U);
    t23 = *((char **)t22);
    t24 = ((char*)((ng17)));
    xsi_vlog_generic_get_index_select_value(t9, 32, t5, t23, 2, t24, 32, 1);
    memset(t31, 0, 8);
    xsi_vlog_unsigned_multiply(t31, 32, t2, 32, t9, 32);
    t25 = (t0 + 5048);
    t26 = (t25 + 56U);
    t27 = *((char **)t26);
    t28 = (t0 + 5048);
    t29 = (t28 + 72U);
    t30 = *((char **)t29);
    t32 = (t0 + 5048);
    t33 = (t32 + 64U);
    t46 = *((char **)t33);
    t48 = (t0 + 5208);
    t54 = (t48 + 56U);
    t55 = *((char **)t54);
    xsi_vlog_generic_get_array_select_value(t47, 8, t27, t30, t46, 2, 1, t55, 32, 1);
    t59 = (t0 + 5048);
    t60 = (t59 + 72U);
    t61 = *((char **)t60);
    t63 = ((char*)((ng13)));
    xsi_vlog_generic_get_index_select_value(t62, 32, t47, t61, 2, t63, 32, 1);
    memset(t72, 0, 8);
    xsi_vlog_unsigned_add(t72, 32, t31, 32, t62, 32);
    t64 = (t0 + 5528);
    xsi_vlogvar_assign_value(t64, t72, 0, 0, 32);
    xsi_set_current_line(65, ng0);
    t2 = ((char*)((ng13)));
    t3 = (t0 + 5048);
    t4 = (t3 + 56U);
    t6 = *((char **)t4);
    t7 = (t0 + 5048);
    t8 = (t7 + 72U);
    t10 = *((char **)t8);
    t11 = (t0 + 5048);
    t16 = (t11 + 64U);
    t17 = *((char **)t16);
    t18 = (t0 + 5208);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    xsi_vlog_generic_get_array_select_value(t5, 8, t6, t10, t17, 2, 1, t20, 32, 1);
    t21 = (t0 + 5048);
    t22 = (t21 + 72U);
    t23 = *((char **)t22);
    t24 = ((char*)((ng2)));
    xsi_vlog_generic_get_index_select_value(t9, 32, t5, t23, 2, t24, 32, 1);
    memset(t31, 0, 8);
    xsi_vlog_unsigned_multiply(t31, 32, t2, 32, t9, 32);
    t25 = (t0 + 5048);
    t26 = (t25 + 56U);
    t27 = *((char **)t26);
    t28 = (t0 + 5048);
    t29 = (t28 + 72U);
    t30 = *((char **)t29);
    t32 = (t0 + 5048);
    t33 = (t32 + 64U);
    t46 = *((char **)t33);
    t48 = (t0 + 5208);
    t54 = (t48 + 56U);
    t55 = *((char **)t54);
    xsi_vlog_generic_get_array_select_value(t47, 8, t27, t30, t46, 2, 1, t55, 32, 1);
    t59 = (t0 + 5048);
    t60 = (t59 + 72U);
    t61 = *((char **)t60);
    t63 = ((char*)((ng3)));
    xsi_vlog_generic_get_index_select_value(t62, 32, t47, t61, 2, t63, 32, 1);
    memset(t72, 0, 8);
    xsi_vlog_unsigned_add(t72, 32, t31, 32, t62, 32);
    t64 = (t0 + 5688);
    xsi_vlogvar_assign_value(t64, t72, 0, 0, 32);
    xsi_set_current_line(66, ng0);
    t2 = (t0 + 5368);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t6 = (t0 + 5528);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t10 = (t0 + 5688);
    t11 = (t10 + 56U);
    t16 = *((char **)t11);
    t17 = (t0 + 8816);
    t18 = (t0 + 2576);
    t19 = xsi_create_subprogram_invocation(t17, 0, t0, t18, 0, 0);
    xsi_vlog_subprogram_pushinvocation(t18, t19);
    t20 = (t0 + 7608);
    xsi_vlogvar_assign_value(t20, t4, 0, 0, 2);
    t21 = (t0 + 7768);
    xsi_vlogvar_assign_value(t21, t8, 0, 0, 2);
    t22 = (t0 + 7928);
    xsi_vlogvar_assign_value(t22, t16, 0, 0, 2);

LAB103:    t23 = (t0 + 8912);
    t24 = *((char **)t23);
    t25 = (t24 + 80U);
    t26 = *((char **)t25);
    t27 = (t26 + 272U);
    t28 = *((char **)t27);
    t29 = (t28 + 0U);
    t30 = *((char **)t29);
    t15 = ((int  (*)(char *, char *))t30)(t0, t24);

LAB105:    if (t15 != 0)
        goto LAB106;

LAB101:    t24 = (t0 + 2576);
    xsi_vlog_subprogram_popinvocation(t24);

LAB102:    t32 = (t0 + 8912);
    t33 = *((char **)t32);
    t32 = (t0 + 2576);
    t46 = (t0 + 8816);
    t48 = 0;
    xsi_delete_subprogram_invocation(t32, t33, t0, t46, t48);
    goto LAB99;

LAB104:;
LAB106:    t23 = (t0 + 9008U);
    *((char **)t23) = &&LAB103;
    goto LAB1;

LAB109:    t27 = (t31 + 4);
    *((unsigned int *)t31) = 1;
    *((unsigned int *)t27) = 1;
    goto LAB110;

LAB111:    *((unsigned int *)t47) = 1;
    goto LAB114;

LAB113:    t29 = (t47 + 4);
    *((unsigned int *)t47) = 1;
    *((unsigned int *)t29) = 1;
    goto LAB114;

LAB115:    t32 = (t0 + 5048);
    t33 = (t32 + 56U);
    t46 = *((char **)t33);
    t48 = (t0 + 5048);
    t54 = (t48 + 72U);
    t55 = *((char **)t54);
    t59 = (t0 + 5048);
    t60 = (t59 + 64U);
    t61 = *((char **)t60);
    t63 = (t0 + 5208);
    t64 = (t63 + 56U);
    t65 = *((char **)t64);
    xsi_vlog_generic_get_array_select_value(t62, 8, t46, t55, t61, 2, 1, t65, 32, 1);
    t66 = (t0 + 5048);
    t67 = (t66 + 72U);
    t68 = *((char **)t67);
    t69 = ((char*)((ng12)));
    xsi_vlog_generic_get_index_select_value(t72, 32, t62, t68, 2, t69, 32, 1);
    t70 = ((char*)((ng2)));
    memset(t78, 0, 8);
    t71 = (t72 + 4);
    t73 = (t70 + 4);
    t56 = *((unsigned int *)t72);
    t57 = *((unsigned int *)t70);
    t58 = (t56 ^ t57);
    t81 = *((unsigned int *)t71);
    t82 = *((unsigned int *)t73);
    t83 = (t81 ^ t82);
    t84 = (t58 | t83);
    t85 = *((unsigned int *)t71);
    t86 = *((unsigned int *)t73);
    t87 = (t85 | t86);
    t88 = (~(t87));
    t89 = (t84 & t88);
    if (t89 != 0)
        goto LAB121;

LAB118:    if (t87 != 0)
        goto LAB120;

LAB119:    *((unsigned int *)t78) = 1;

LAB121:    memset(t94, 0, 8);
    t75 = (t78 + 4);
    t90 = *((unsigned int *)t75);
    t91 = (~(t90));
    t92 = *((unsigned int *)t78);
    t96 = (t92 & t91);
    t97 = (t96 & 1U);
    if (t97 != 0)
        goto LAB122;

LAB123:    if (*((unsigned int *)t75) != 0)
        goto LAB124;

LAB125:    t98 = *((unsigned int *)t47);
    t99 = *((unsigned int *)t94);
    t100 = (t98 & t99);
    *((unsigned int *)t102) = t100;
    t77 = (t47 + 4);
    t79 = (t94 + 4);
    t80 = (t102 + 4);
    t103 = *((unsigned int *)t77);
    t104 = *((unsigned int *)t79);
    t105 = (t103 | t104);
    *((unsigned int *)t80) = t105;
    t109 = *((unsigned int *)t80);
    t110 = (t109 != 0);
    if (t110 == 1)
        goto LAB126;

LAB127:
LAB128:    goto LAB117;

LAB120:    t74 = (t78 + 4);
    *((unsigned int *)t78) = 1;
    *((unsigned int *)t74) = 1;
    goto LAB121;

LAB122:    *((unsigned int *)t94) = 1;
    goto LAB125;

LAB124:    t76 = (t94 + 4);
    *((unsigned int *)t94) = 1;
    *((unsigned int *)t76) = 1;
    goto LAB125;

LAB126:    t111 = *((unsigned int *)t102);
    t112 = *((unsigned int *)t80);
    *((unsigned int *)t102) = (t111 | t112);
    t93 = (t47 + 4);
    t95 = (t94 + 4);
    t113 = *((unsigned int *)t47);
    t114 = (~(t113));
    t115 = *((unsigned int *)t93);
    t118 = (~(t115));
    t119 = *((unsigned int *)t94);
    t120 = (~(t119));
    t121 = *((unsigned int *)t95);
    t122 = (~(t121));
    t15 = (t114 & t118);
    t126 = (t120 & t122);
    t123 = (~(t15));
    t124 = (~(t126));
    t125 = *((unsigned int *)t80);
    *((unsigned int *)t80) = (t125 & t123);
    t128 = *((unsigned int *)t80);
    *((unsigned int *)t80) = (t128 & t124);
    t129 = *((unsigned int *)t102);
    *((unsigned int *)t102) = (t129 & t123);
    t130 = *((unsigned int *)t102);
    *((unsigned int *)t102) = (t130 & t124);
    goto LAB128;

LAB129:    xsi_set_current_line(70, ng0);

LAB132:    xsi_set_current_line(72, ng0);
    t106 = ((char*)((ng13)));
    t107 = (t0 + 5048);
    t108 = (t107 + 56U);
    t116 = *((char **)t108);
    t117 = (t0 + 5048);
    t134 = (t117 + 72U);
    t140 = *((char **)t134);
    t141 = (t0 + 5048);
    t142 = (t141 + 64U);
    t143 = *((char **)t142);
    t145 = (t0 + 5208);
    t146 = (t145 + 56U);
    t147 = *((char **)t146);
    xsi_vlog_generic_get_array_select_value(t144, 8, t116, t140, t143, 2, 1, t147, 32, 1);
    t148 = (t0 + 5048);
    t149 = (t148 + 72U);
    t150 = *((char **)t149);
    t151 = ((char*)((ng14)));
    xsi_vlog_generic_get_index_select_value(t154, 32, t144, t150, 2, t151, 32, 1);
    memset(t159, 0, 8);
    xsi_vlog_unsigned_multiply(t159, 32, t106, 32, t154, 32);
    t152 = (t0 + 5048);
    t153 = (t152 + 56U);
    t155 = *((char **)t153);
    t156 = (t0 + 5048);
    t157 = (t156 + 72U);
    t158 = *((char **)t157);
    t160 = (t0 + 5048);
    t161 = (t160 + 64U);
    t162 = *((char **)t161);
    t164 = (t0 + 5208);
    t165 = (t164 + 56U);
    t166 = *((char **)t165);
    xsi_vlog_generic_get_array_select_value(t163, 8, t155, t158, t162, 2, 1, t166, 32, 1);
    t167 = (t0 + 5048);
    t168 = (t167 + 72U);
    t169 = *((char **)t168);
    t170 = ((char*)((ng15)));
    xsi_vlog_generic_get_index_select_value(t173, 32, t163, t169, 2, t170, 32, 1);
    memset(t178, 0, 8);
    xsi_vlog_unsigned_add(t178, 32, t159, 32, t173, 32);
    t171 = (t0 + 5368);
    xsi_vlogvar_assign_value(t171, t178, 0, 0, 32);
    xsi_set_current_line(73, ng0);
    t2 = (t0 + 5368);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t6 = (t0 + 8816);
    t7 = (t0 + 1712);
    t8 = xsi_create_subprogram_invocation(t6, 0, t0, t7, 0, 0);
    xsi_vlog_subprogram_pushinvocation(t7, t8);
    t10 = (t0 + 6648);
    xsi_vlogvar_assign_value(t10, t4, 0, 0, 2);

LAB135:    t11 = (t0 + 8912);
    t16 = *((char **)t11);
    t17 = (t16 + 80U);
    t18 = *((char **)t17);
    t19 = (t18 + 272U);
    t20 = *((char **)t19);
    t21 = (t20 + 0U);
    t22 = *((char **)t21);
    t15 = ((int  (*)(char *, char *))t22)(t0, t16);

LAB137:    if (t15 != 0)
        goto LAB138;

LAB133:    t16 = (t0 + 1712);
    xsi_vlog_subprogram_popinvocation(t16);

LAB134:    t23 = (t0 + 8912);
    t24 = *((char **)t23);
    t23 = (t0 + 1712);
    t25 = (t0 + 8816);
    t26 = 0;
    xsi_delete_subprogram_invocation(t23, t24, t0, t25, t26);
    xsi_set_current_line(74, ng0);
    xsi_vlogfile_write(1, 0, 0, ng18, 1, t0);
    goto LAB131;

LAB136:;
LAB138:    t11 = (t0 + 9008U);
    *((char **)t11) = &&LAB135;
    goto LAB1;

LAB139:    xsi_set_current_line(80, ng0);
    xsi_vlog_finish(1);
    goto LAB1;

}

static void Always_83_1(char *t0)
{
    char t3[8];
    char *t1;
    char *t2;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    char *t13;
    char *t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    char *t24;

LAB0:    t1 = (t0 + 9256U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(83, ng0);
    t2 = (t0 + 9064);
    xsi_process_wait(t2, 5000LL);
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(83, ng0);
    t4 = (t0 + 4088);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memset(t3, 0, 8);
    t7 = (t6 + 4);
    t8 = *((unsigned int *)t7);
    t9 = (~(t8));
    t10 = *((unsigned int *)t6);
    t11 = (t10 & t9);
    t12 = (t11 & 1U);
    if (t12 != 0)
        goto LAB8;

LAB6:    if (*((unsigned int *)t7) == 0)
        goto LAB5;

LAB7:    t13 = (t3 + 4);
    *((unsigned int *)t3) = 1;
    *((unsigned int *)t13) = 1;

LAB8:    t14 = (t3 + 4);
    t15 = (t6 + 4);
    t16 = *((unsigned int *)t6);
    t17 = (~(t16));
    *((unsigned int *)t3) = t17;
    *((unsigned int *)t14) = 0;
    if (*((unsigned int *)t15) != 0)
        goto LAB10;

LAB9:    t22 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t22 & 1U);
    t23 = *((unsigned int *)t14);
    *((unsigned int *)t14) = (t23 & 1U);
    t24 = (t0 + 4088);
    xsi_vlogvar_assign_value(t24, t3, 0, 0, 1);
    goto LAB2;

LAB5:    *((unsigned int *)t3) = 1;
    goto LAB8;

LAB10:    t18 = *((unsigned int *)t3);
    t19 = *((unsigned int *)t15);
    *((unsigned int *)t3) = (t18 | t19);
    t20 = *((unsigned int *)t14);
    t21 = *((unsigned int *)t15);
    *((unsigned int *)t14) = (t20 | t21);
    goto LAB9;

}

static void Always_157_2(char *t0)
{
    char t14[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;

LAB0:    t1 = (t0 + 9504U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(157, ng0);
    t2 = (t0 + 10072);
    *((int *)t2) = 1;
    t3 = (t0 + 9536);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(158, ng0);
    t4 = (t0 + 12384);
    t5 = *((char **)t4);
    t6 = ((((char*)(t5))) + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 4);
    t9 = *((unsigned int *)t8);
    t10 = (~(t9));
    t11 = *((unsigned int *)t7);
    t12 = (t11 & t10);
    t13 = (t12 != 0);
    if (t13 > 0)
        goto LAB5;

LAB6:
LAB7:    goto LAB2;

LAB5:    xsi_set_current_line(159, ng0);
    *((int *)t14) = xsi_vlog_stime(1000.0000000000000, 1000.0000000000000);
    t15 = (t14 + 4);
    *((int *)t15) = 0;
    t16 = (t0 + 12408);
    t17 = *((char **)t16);
    t18 = ((((char*)(t17))) + 56U);
    t19 = *((char **)t18);
    xsi_vlogfile_write(1, 0, 0, ng19, 3, t0, (char)118, t14, 32, (char)118, t19, 8);
    goto LAB7;

}

static void Always_161_3(char *t0)
{
    char t4[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    char *t7;

LAB0:    t1 = (t0 + 9752U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(161, ng0);
    t2 = (t0 + 10088);
    *((int *)t2) = 1;
    t3 = (t0 + 9784);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(162, ng0);
    *((int *)t4) = xsi_vlog_stime(1000.0000000000000, 1000.0000000000000);
    t5 = (t4 + 4);
    *((int *)t5) = 0;
    t6 = (t0 + 3528U);
    t7 = *((char **)t6);
    xsi_vlogfile_write(1, 0, 0, ng20, 3, t0, (char)118, t4, 32, (char)118, t7, 8);
    goto LAB2;

}


extern void work_m_00000000003420586555_3671711236_init()
{
	static char *pe[] = {(void *)Initial_29_0,(void *)Always_83_1,(void *)Always_157_2,(void *)Always_161_3};
	static char *se[] = {(void *)sp_tskRunInst,(void *)sp_tskRunPUSH,(void *)sp_tskRunSEND,(void *)sp_tskRunADD,(void *)sp_tskRunMULT};
	xsi_register_didat("work_m_00000000003420586555_3671711236", "isim/tb_isim_beh.exe.sim/work/m_00000000003420586555_3671711236.didat");
	xsi_register_executes(pe);
	xsi_register_subprogram_executes(se);
}
