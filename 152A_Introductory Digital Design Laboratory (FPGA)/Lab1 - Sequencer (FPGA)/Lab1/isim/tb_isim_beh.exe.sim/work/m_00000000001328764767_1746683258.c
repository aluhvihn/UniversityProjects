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
static const char *ng0 = "E:/CS_152A/Lab1/tb/model_uart.v";
static unsigned int ng1[] = {0U, 0U};
static unsigned int ng2[] = {1U, 0U};
static int ng3[] = {0, 0};
static int ng4[] = {10, 0};
static int ng5[] = {1, 0};
static int ng6[] = {8, 0};
static int ng7[] = {5, 0};
static const char *ng8 = "%d %s Received byte %s %s %s %s";
static int ng9[] = {1095914544, 0, 85, 0};
static int ng10[] = {2, 0};
static int ng11[] = {3, 0};



static int sp_tskRxData(char *t1, char *t2)
{
    int t0;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    t0 = 1;
    t3 = (t2 + 48U);
    t4 = *((char **)t3);
    if (t4 == 0)
        goto LAB2;

LAB3:    goto *t4;

LAB2:    t4 = (t1 + 1256);
    xsi_vlog_subprogram_setdisablestate(t4, &&LAB4);
    xsi_set_current_line(57, ng0);

LAB5:    xsi_set_current_line(58, ng0);
    t5 = (t2 + 88U);
    t6 = *((char **)t5);
    t7 = (t6 + 0U);
    xsi_wp_set_status(t7, 1);
    *((char **)t3) = &&LAB6;

LAB1:    return t0;
LAB4:    xsi_vlog_dispose_subprogram_invocation(t2);
    t4 = (t2 + 48U);
    *((char **)t4) = &&LAB2;
    t0 = 0;
    goto LAB1;

LAB6:    xsi_set_current_line(59, ng0);
    t4 = (t1 + 2880);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t1 + 3360);
    xsi_vlogvar_assign_value(t7, t6, 0, 0, 8);
    goto LAB4;

}

static int sp_tskTxData(char *t1, char *t2)
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

LAB0:    t0 = 1;
    t3 = (t2 + 48U);
    t4 = *((char **)t3);
    if (t4 == 0)
        goto LAB2;

LAB3:    goto *t4;

LAB2:    t4 = (t1 + 1688);
    xsi_vlog_subprogram_setdisablestate(t4, &&LAB4);
    xsi_set_current_line(67, ng0);

LAB5:    xsi_set_current_line(68, ng0);
    t6 = ((char*)((ng1)));
    t8 = (t1 + 3520);
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
    *((unsigned int *)t7) = (t17 & 255U);
    t18 = *((unsigned int *)t11);
    *((unsigned int *)t11) = (t18 & 255U);
    t19 = ((char*)((ng2)));
    xsi_vlogtype_concat(t5, 10, 10, 3U, t19, 1, t7, 8, t6, 1);
    t20 = (t1 + 3680);
    xsi_vlogvar_assign_value(t20, t5, 0, 0, 10);
    xsi_set_current_line(69, ng0);
    xsi_set_current_line(69, ng0);
    t4 = ((char*)((ng3)));
    t6 = (t1 + 3840);
    xsi_vlogvar_assign_value(t6, t4, 0, 0, 32);

LAB6:    t4 = (t1 + 3840);
    t6 = (t4 + 56U);
    t8 = *((char **)t6);
    t9 = ((char*)((ng4)));
    memset(t5, 0, 8);
    xsi_vlog_signed_less(t5, 32, t8, 32, t9, 32);
    t10 = (t5 + 4);
    t13 = *((unsigned int *)t10);
    t14 = (~(t13));
    t15 = *((unsigned int *)t5);
    t16 = (t15 & t14);
    t17 = (t16 != 0);
    if (t17 > 0)
        goto LAB7;

LAB8:    xsi_set_current_line(75, ng0);
    t4 = (t1 + 7032);
    xsi_trigger(t4, -1, -1);

LAB4:    xsi_vlog_dispose_subprogram_invocation(t2);
    t4 = (t2 + 48U);
    *((char **)t4) = &&LAB2;
    t0 = 0;

LAB1:    return t0;
LAB7:    xsi_set_current_line(70, ng0);

LAB9:    xsi_set_current_line(71, ng0);
    t11 = (t1 + 3680);
    t12 = (t11 + 56U);
    t19 = *((char **)t12);
    t20 = (t1 + 3680);
    t21 = (t20 + 72U);
    t22 = *((char **)t21);
    t23 = (t1 + 3840);
    t24 = (t23 + 56U);
    t25 = *((char **)t24);
    xsi_vlog_generic_get_index_select_value(t7, 1, t19, t22, 2, t25, 32, 1);
    t26 = (t1 + 2720);
    xsi_vlogvar_assign_value(t26, t7, 0, 0, 1);
    xsi_set_current_line(72, ng0);
    t4 = (t2 + 56U);
    t6 = *((char **)t4);
    xsi_process_wait(t6, 1000000LL);
    *((char **)t3) = &&LAB10;
    t0 = 1;
    goto LAB1;

LAB10:    xsi_set_current_line(73, ng0);
    t4 = (t1 + 6864);
    xsi_trigger(t4, -1, -1);
    xsi_set_current_line(69, ng0);
    t4 = (t1 + 3840);
    t6 = (t4 + 56U);
    t8 = *((char **)t6);
    t9 = ((char*)((ng5)));
    memset(t5, 0, 8);
    xsi_vlog_signed_add(t5, 32, t8, 32, t9, 32);
    t10 = (t1 + 3840);
    xsi_vlogvar_assign_value(t10, t5, 0, 0, 32);
    goto LAB6;

}

static void Initial_27_0(char *t0)
{
    char *t1;
    char *t2;

LAB0:    xsi_set_current_line(28, ng0);

LAB2:    xsi_set_current_line(29, ng0);
    t1 = ((char*)((ng2)));
    t2 = (t0 + 2720);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 1);
    xsi_set_current_line(30, ng0);
    t1 = ((char*)((ng3)));
    t2 = (t0 + 3200);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);

LAB1:    return;
}

static void Always_33_1(char *t0)
{
    char t12[8];
    char t13[8];
    char t21[8];
    char t32[8];
    char t43[8];
    char t54[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    int t9;
    char *t10;
    char *t11;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
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
    char *t33;
    char *t34;
    char *t35;
    char *t36;
    char *t37;
    char *t38;
    char *t39;
    char *t40;
    char *t41;
    char *t42;
    char *t44;
    char *t45;
    char *t46;
    char *t47;
    char *t48;
    char *t49;
    char *t50;
    char *t51;
    char *t52;
    char *t53;
    char *t55;
    char *t56;
    char *t57;
    char *t58;
    char *t59;
    char *t60;
    char *t61;
    int t62;
    int t63;
    int t64;
    int t65;

LAB0:    t1 = (t0 + 5008U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(33, ng0);
    t2 = (t0 + 5328);
    *((int *)t2) = 1;
    t3 = (t0 + 5040);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(34, ng0);

LAB5:    xsi_set_current_line(35, ng0);
    t4 = ((char*)((ng1)));
    t5 = (t0 + 2880);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 8);
    xsi_set_current_line(36, ng0);
    t2 = (t0 + 4816);
    xsi_process_wait(t2, 500000LL);
    *((char **)t1) = &&LAB6;
    goto LAB1;

LAB6:    xsi_set_current_line(37, ng0);
    t2 = ((char*)((ng6)));
    t3 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = (~(t6));
    t8 = *((unsigned int *)t2);
    t9 = (t8 & t7);
    t4 = (t0 + 7748);
    *((int *)t4) = t9;

LAB7:    t5 = (t0 + 7748);
    if (*((int *)t5) > 0)
        goto LAB8;

LAB9:    xsi_set_current_line(43, ng0);
    t2 = (t0 + 6696);
    xsi_trigger(t2, -1, -1);
    xsi_set_current_line(45, ng0);
    t2 = (t0 + 3200);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng7)));
    memset(t12, 0, 8);
    xsi_vlog_signed_equal(t12, 32, t4, 32, t5, 32);
    t10 = (t12 + 4);
    t6 = *((unsigned int *)t10);
    t7 = (~(t6));
    t8 = *((unsigned int *)t12);
    t14 = (t8 & t7);
    t15 = (t14 != 0);
    if (t15 > 0)
        goto LAB12;

LAB13:    xsi_set_current_line(49, ng0);

LAB16:    xsi_set_current_line(50, ng0);
    t2 = (t0 + 2880);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 3040);
    t10 = (t0 + 3040);
    t11 = (t10 + 72U);
    t17 = *((char **)t11);
    t18 = (t0 + 3040);
    t19 = (t18 + 64U);
    t20 = *((char **)t19);
    t22 = (t0 + 3200);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    xsi_vlog_generic_convert_array_indices(t12, t13, t17, t20, 2, 1, t24, 32, 1);
    t25 = (t12 + 4);
    t6 = *((unsigned int *)t25);
    t9 = (!(t6));
    t26 = (t13 + 4);
    t7 = *((unsigned int *)t26);
    t62 = (!(t7));
    t63 = (t9 && t62);
    if (t63 == 1)
        goto LAB17;

LAB18:    xsi_set_current_line(51, ng0);
    t2 = (t0 + 3200);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng5)));
    memset(t12, 0, 8);
    xsi_vlog_signed_add(t12, 32, t4, 32, t5, 32);
    t10 = (t0 + 3200);
    xsi_vlogvar_assign_value(t10, t12, 0, 0, 32);

LAB14:    goto LAB2;

LAB8:    xsi_set_current_line(38, ng0);

LAB10:    xsi_set_current_line(39, ng0);
    t10 = (t0 + 4816);
    xsi_process_wait(t10, 1000000LL);
    *((char **)t1) = &&LAB11;
    goto LAB1;

LAB11:    xsi_set_current_line(39, ng0);
    t11 = (t0 + 6528);
    xsi_trigger(t11, -1, -1);
    xsi_set_current_line(41, ng0);
    t2 = (t0 + 2880);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t13, 0, 8);
    t5 = (t13 + 4);
    t10 = (t4 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (t6 >> 1);
    *((unsigned int *)t13) = t7;
    t8 = *((unsigned int *)t10);
    t14 = (t8 >> 1);
    *((unsigned int *)t5) = t14;
    t15 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t15 & 127U);
    t16 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t16 & 127U);
    t11 = (t0 + 2320U);
    t17 = *((char **)t11);
    xsi_vlogtype_concat(t12, 8, 8, 2U, t17, 1, t13, 7);
    t11 = (t0 + 2880);
    xsi_vlogvar_assign_value(t11, t12, 0, 0, 8);
    t2 = (t0 + 7748);
    t9 = *((int *)t2);
    *((int *)t2) = (t9 - 1);
    goto LAB7;

LAB12:    xsi_set_current_line(45, ng0);

LAB15:    xsi_set_current_line(46, ng0);
    *((int *)t13) = xsi_vlog_stime(1000.0000000000000, 1000.0000000000000);
    t11 = (t13 + 4);
    *((int *)t11) = 0;
    t17 = ((char*)((ng9)));
    t18 = (t0 + 3040);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    t22 = (t0 + 3040);
    t23 = (t22 + 72U);
    t24 = *((char **)t23);
    t25 = (t0 + 3040);
    t26 = (t25 + 64U);
    t27 = *((char **)t26);
    t28 = ((char*)((ng3)));
    xsi_vlog_generic_get_array_select_value(t21, 8, t20, t24, t27, 2, 1, t28, 32, 1);
    t29 = (t0 + 3040);
    t30 = (t29 + 56U);
    t31 = *((char **)t30);
    t33 = (t0 + 3040);
    t34 = (t33 + 72U);
    t35 = *((char **)t34);
    t36 = (t0 + 3040);
    t37 = (t36 + 64U);
    t38 = *((char **)t37);
    t39 = ((char*)((ng5)));
    xsi_vlog_generic_get_array_select_value(t32, 8, t31, t35, t38, 2, 1, t39, 32, 1);
    t40 = (t0 + 3040);
    t41 = (t40 + 56U);
    t42 = *((char **)t41);
    t44 = (t0 + 3040);
    t45 = (t44 + 72U);
    t46 = *((char **)t45);
    t47 = (t0 + 3040);
    t48 = (t47 + 64U);
    t49 = *((char **)t48);
    t50 = ((char*)((ng10)));
    xsi_vlog_generic_get_array_select_value(t43, 8, t42, t46, t49, 2, 1, t50, 32, 1);
    t51 = (t0 + 3040);
    t52 = (t51 + 56U);
    t53 = *((char **)t52);
    t55 = (t0 + 3040);
    t56 = (t55 + 72U);
    t57 = *((char **)t56);
    t58 = (t0 + 3040);
    t59 = (t58 + 64U);
    t60 = *((char **)t59);
    t61 = ((char*)((ng11)));
    xsi_vlog_generic_get_array_select_value(t54, 8, t53, t57, t60, 2, 1, t61, 32, 1);
    xsi_vlogfile_write(1, 0, 0, ng8, 7, t0, (char)118, t13, 32, (char)118, t17, 40, (char)118, t21, 8, (char)118, t32, 8, (char)118, t43, 8, (char)118, t54, 8);
    xsi_set_current_line(47, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 3200);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 32);
    goto LAB14;

LAB17:    t8 = *((unsigned int *)t12);
    t14 = *((unsigned int *)t13);
    t64 = (t8 - t14);
    t65 = (t64 + 1);
    xsi_vlogvar_assign_value(t5, t4, 0, *((unsigned int *)t13), t65);
    goto LAB18;

}


extern void work_m_00000000001328764767_1746683258_init()
{
	static char *pe[] = {(void *)Initial_27_0,(void *)Always_33_1};
	static char *se[] = {(void *)sp_tskRxData,(void *)sp_tskTxData};
	xsi_register_didat("work_m_00000000001328764767_1746683258", "isim/tb_isim_beh.exe.sim/work/m_00000000001328764767_1746683258.didat");
	xsi_register_executes(pe);
	xsi_register_subprogram_executes(se);
}
