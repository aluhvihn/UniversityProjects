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
static const char *ng0 = "E:/CS_152A/Lab4/Lab4Code/calculator/src/calculator.v";
static int ng1[] = {1, 0};
static int ng2[] = {0, 0};
static int ng3[] = {2, 0};
static int ng4[] = {3, 0};



static void Cont_23_0(char *t0)
{
    char t6[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned int t27;
    unsigned int t28;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;

LAB0:    t1 = (t0 + 7008U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(23, ng0);
    t2 = (t0 + 4968);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng1)));
    memset(t6, 0, 8);
    t7 = (t4 + 4);
    t8 = (t5 + 4);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB7;

LAB4:    if (t18 != 0)
        goto LAB6;

LAB5:    *((unsigned int *)t6) = 1;

LAB7:    t22 = (t0 + 8448);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    memset(t26, 0, 8);
    t27 = 1U;
    t28 = t27;
    t29 = (t6 + 4);
    t30 = *((unsigned int *)t6);
    t27 = (t27 & t30);
    t31 = *((unsigned int *)t29);
    t28 = (t28 & t31);
    t32 = (t26 + 4);
    t33 = *((unsigned int *)t26);
    *((unsigned int *)t26) = (t33 | t27);
    t34 = *((unsigned int *)t32);
    *((unsigned int *)t32) = (t34 | t28);
    xsi_driver_vfirst_trans(t22, 1, 1);
    t35 = (t0 + 8320);
    *((int *)t35) = 1;

LAB1:    return;
LAB6:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB7;

}

static void Cont_24_1(char *t0)
{
    char t6[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned int t27;
    unsigned int t28;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;

LAB0:    t1 = (t0 + 7256U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(24, ng0);
    t2 = (t0 + 4968);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t6, 0, 8);
    t7 = (t4 + 4);
    t8 = (t5 + 4);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB7;

LAB4:    if (t18 != 0)
        goto LAB6;

LAB5:    *((unsigned int *)t6) = 1;

LAB7:    t22 = (t0 + 8512);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    memset(t26, 0, 8);
    t27 = 1U;
    t28 = t27;
    t29 = (t6 + 4);
    t30 = *((unsigned int *)t6);
    t27 = (t27 & t30);
    t31 = *((unsigned int *)t29);
    t28 = (t28 & t31);
    t32 = (t26 + 4);
    t33 = *((unsigned int *)t26);
    *((unsigned int *)t26) = (t33 | t27);
    t34 = *((unsigned int *)t32);
    *((unsigned int *)t32) = (t34 | t28);
    xsi_driver_vfirst_trans(t22, 0, 0);
    t35 = (t0 + 8336);
    *((int *)t35) = 1;

LAB1:    return;
LAB6:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB7;

}

static void Initial_64_2(char *t0)
{
    char *t1;
    char *t2;

LAB0:    xsi_set_current_line(64, ng0);

LAB2:    xsi_set_current_line(65, ng0);
    t1 = ((char*)((ng2)));
    t2 = (t0 + 4968);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 2);
    xsi_set_current_line(66, ng0);
    t1 = ((char*)((ng2)));
    t2 = (t0 + 5288);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 1);
    xsi_set_current_line(67, ng0);
    t1 = ((char*)((ng2)));
    t2 = (t0 + 5128);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 2);

LAB1:    return;
}

static void Always_71_3(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;

LAB0:    t1 = (t0 + 7752U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(71, ng0);
    t2 = (t0 + 8352);
    *((int *)t2) = 1;
    t3 = (t0 + 7784);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(71, ng0);

LAB5:    xsi_set_current_line(72, ng0);
    t4 = (t0 + 1368U);
    t5 = *((char **)t4);
    t4 = (t0 + 5448);
    xsi_vlogvar_wait_assign_value(t4, t5, 0, 0, 1, 0LL);
    xsi_set_current_line(73, ng0);
    t2 = (t0 + 1528U);
    t3 = *((char **)t2);
    t2 = (t0 + 5608);
    xsi_vlogvar_wait_assign_value(t2, t3, 0, 0, 1, 0LL);
    xsi_set_current_line(74, ng0);
    t2 = (t0 + 1688U);
    t3 = *((char **)t2);
    t2 = (t0 + 5768);
    xsi_vlogvar_wait_assign_value(t2, t3, 0, 0, 1, 0LL);
    xsi_set_current_line(75, ng0);
    t2 = (t0 + 1848U);
    t3 = *((char **)t2);
    t2 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t2, t3, 0, 0, 1, 0LL);
    xsi_set_current_line(76, ng0);
    t2 = (t0 + 2008U);
    t3 = *((char **)t2);
    t2 = (t0 + 6088);
    xsi_vlogvar_wait_assign_value(t2, t3, 0, 0, 1, 0LL);
    goto LAB2;

}

static void Always_150_4(char *t0)
{
    char t7[8];
    char t19[8];
    char t28[8];
    char t36[8];
    char t78[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    char *t27;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    char *t40;
    char *t41;
    char *t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    char *t50;
    char *t51;
    unsigned int t52;
    unsigned int t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    int t60;
    int t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    char *t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    unsigned int t73;
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
    char *t94;
    unsigned int t95;
    unsigned int t96;
    unsigned int t97;
    unsigned int t98;
    unsigned int t99;
    char *t100;
    char *t101;

LAB0:    t1 = (t0 + 8000U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(150, ng0);
    t2 = (t0 + 8368);
    *((int *)t2) = 1;
    t3 = (t0 + 8032);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(150, ng0);

LAB5:    xsi_set_current_line(151, ng0);
    t4 = (t0 + 6088);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memset(t7, 0, 8);
    t8 = (t6 + 4);
    t9 = *((unsigned int *)t8);
    t10 = (~(t9));
    t11 = *((unsigned int *)t6);
    t12 = (t11 & t10);
    t13 = (t12 & 1U);
    if (t13 != 0)
        goto LAB6;

LAB7:    if (*((unsigned int *)t8) != 0)
        goto LAB8;

LAB9:    t15 = (t7 + 4);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t15);
    t18 = (t16 || t17);
    if (t18 > 0)
        goto LAB10;

LAB11:    memcpy(t36, t7, 8);

LAB12:    t68 = (t36 + 4);
    t69 = *((unsigned int *)t68);
    t70 = (~(t69));
    t71 = *((unsigned int *)t36);
    t72 = (t71 & t70);
    t73 = (t72 != 0);
    if (t73 > 0)
        goto LAB24;

LAB25:    xsi_set_current_line(169, ng0);
    t2 = (t0 + 5928);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t7, 0, 8);
    t5 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = (~(t9));
    t11 = *((unsigned int *)t4);
    t12 = (t11 & t10);
    t13 = (t12 & 1U);
    if (t13 != 0)
        goto LAB60;

LAB61:    if (*((unsigned int *)t5) != 0)
        goto LAB62;

LAB63:    t8 = (t7 + 4);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 || t17);
    if (t18 > 0)
        goto LAB64;

LAB65:    memcpy(t36, t7, 8);

LAB66:    t50 = (t36 + 4);
    t69 = *((unsigned int *)t50);
    t70 = (~(t69));
    t71 = *((unsigned int *)t36);
    t72 = (t71 & t70);
    t73 = (t72 != 0);
    if (t73 > 0)
        goto LAB78;

LAB79:    xsi_set_current_line(177, ng0);
    t2 = (t0 + 5768);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t7, 0, 8);
    t5 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = (~(t9));
    t11 = *((unsigned int *)t4);
    t12 = (t11 & t10);
    t13 = (t12 & 1U);
    if (t13 != 0)
        goto LAB90;

LAB91:    if (*((unsigned int *)t5) != 0)
        goto LAB92;

LAB93:    t8 = (t7 + 4);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 || t17);
    if (t18 > 0)
        goto LAB94;

LAB95:    memcpy(t36, t7, 8);

LAB96:    t50 = (t36 + 4);
    t69 = *((unsigned int *)t50);
    t70 = (~(t69));
    t71 = *((unsigned int *)t36);
    t72 = (t71 & t70);
    t73 = (t72 != 0);
    if (t73 > 0)
        goto LAB108;

LAB109:    xsi_set_current_line(185, ng0);
    t2 = (t0 + 5448);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t7, 0, 8);
    t5 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = (~(t9));
    t11 = *((unsigned int *)t4);
    t12 = (t11 & t10);
    t13 = (t12 & 1U);
    if (t13 != 0)
        goto LAB120;

LAB121:    if (*((unsigned int *)t5) != 0)
        goto LAB122;

LAB123:    t8 = (t7 + 4);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 || t17);
    if (t18 > 0)
        goto LAB124;

LAB125:    memcpy(t36, t7, 8);

LAB126:    t50 = (t36 + 4);
    t69 = *((unsigned int *)t50);
    t70 = (~(t69));
    t71 = *((unsigned int *)t36);
    t72 = (t71 & t70);
    t73 = (t72 != 0);
    if (t73 > 0)
        goto LAB138;

LAB139:    xsi_set_current_line(194, ng0);
    t2 = (t0 + 5608);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    memset(t7, 0, 8);
    t5 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = (~(t9));
    t11 = *((unsigned int *)t4);
    t12 = (t11 & t10);
    t13 = (t12 & 1U);
    if (t13 != 0)
        goto LAB150;

LAB151:    if (*((unsigned int *)t5) != 0)
        goto LAB152;

LAB153:    t8 = (t7 + 4);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 || t17);
    if (t18 > 0)
        goto LAB154;

LAB155:    memcpy(t36, t7, 8);

LAB156:    t50 = (t36 + 4);
    t69 = *((unsigned int *)t50);
    t70 = (~(t69));
    t71 = *((unsigned int *)t36);
    t72 = (t71 & t70);
    t73 = (t72 != 0);
    if (t73 > 0)
        goto LAB168;

LAB169:
LAB170:
LAB140:
LAB110:
LAB80:
LAB26:    goto LAB2;

LAB6:    *((unsigned int *)t7) = 1;
    goto LAB9;

LAB8:    t14 = (t7 + 4);
    *((unsigned int *)t7) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB9;

LAB10:    t20 = (t0 + 4568U);
    t21 = *((char **)t20);
    memset(t19, 0, 8);
    t20 = (t21 + 4);
    t22 = *((unsigned int *)t20);
    t23 = (~(t22));
    t24 = *((unsigned int *)t21);
    t25 = (t24 & t23);
    t26 = (t25 & 1U);
    if (t26 != 0)
        goto LAB16;

LAB14:    if (*((unsigned int *)t20) == 0)
        goto LAB13;

LAB15:    t27 = (t19 + 4);
    *((unsigned int *)t19) = 1;
    *((unsigned int *)t27) = 1;

LAB16:    memset(t28, 0, 8);
    t29 = (t19 + 4);
    t30 = *((unsigned int *)t29);
    t31 = (~(t30));
    t32 = *((unsigned int *)t19);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB17;

LAB18:    if (*((unsigned int *)t29) != 0)
        goto LAB19;

LAB20:    t37 = *((unsigned int *)t7);
    t38 = *((unsigned int *)t28);
    t39 = (t37 & t38);
    *((unsigned int *)t36) = t39;
    t40 = (t7 + 4);
    t41 = (t28 + 4);
    t42 = (t36 + 4);
    t43 = *((unsigned int *)t40);
    t44 = *((unsigned int *)t41);
    t45 = (t43 | t44);
    *((unsigned int *)t42) = t45;
    t46 = *((unsigned int *)t42);
    t47 = (t46 != 0);
    if (t47 == 1)
        goto LAB21;

LAB22:
LAB23:    goto LAB12;

LAB13:    *((unsigned int *)t19) = 1;
    goto LAB16;

LAB17:    *((unsigned int *)t28) = 1;
    goto LAB20;

LAB19:    t35 = (t28 + 4);
    *((unsigned int *)t28) = 1;
    *((unsigned int *)t35) = 1;
    goto LAB20;

LAB21:    t48 = *((unsigned int *)t36);
    t49 = *((unsigned int *)t42);
    *((unsigned int *)t36) = (t48 | t49);
    t50 = (t7 + 4);
    t51 = (t28 + 4);
    t52 = *((unsigned int *)t7);
    t53 = (~(t52));
    t54 = *((unsigned int *)t50);
    t55 = (~(t54));
    t56 = *((unsigned int *)t28);
    t57 = (~(t56));
    t58 = *((unsigned int *)t51);
    t59 = (~(t58));
    t60 = (t53 & t55);
    t61 = (t57 & t59);
    t62 = (~(t60));
    t63 = (~(t61));
    t64 = *((unsigned int *)t42);
    *((unsigned int *)t42) = (t64 & t62);
    t65 = *((unsigned int *)t42);
    *((unsigned int *)t42) = (t65 & t63);
    t66 = *((unsigned int *)t36);
    *((unsigned int *)t36) = (t66 & t62);
    t67 = *((unsigned int *)t36);
    *((unsigned int *)t36) = (t67 & t63);
    goto LAB23;

LAB24:    xsi_set_current_line(151, ng0);

LAB27:    xsi_set_current_line(152, ng0);
    t74 = (t0 + 4968);
    t75 = (t74 + 56U);
    t76 = *((char **)t75);
    t77 = ((char*)((ng2)));
    memset(t78, 0, 8);
    t79 = (t76 + 4);
    t80 = (t77 + 4);
    t81 = *((unsigned int *)t76);
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
        goto LAB31;

LAB28:    if (t90 != 0)
        goto LAB30;

LAB29:    *((unsigned int *)t78) = 1;

LAB31:    t94 = (t78 + 4);
    t95 = *((unsigned int *)t94);
    t96 = (~(t95));
    t97 = *((unsigned int *)t78);
    t98 = (t97 & t96);
    t99 = (t98 != 0);
    if (t99 > 0)
        goto LAB32;

LAB33:    xsi_set_current_line(156, ng0);
    t2 = (t0 + 4968);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng1)));
    memset(t7, 0, 8);
    t6 = (t4 + 4);
    t8 = (t5 + 4);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t6);
    t13 = *((unsigned int *)t8);
    t16 = (t12 ^ t13);
    t17 = (t11 | t16);
    t18 = *((unsigned int *)t6);
    t22 = *((unsigned int *)t8);
    t23 = (t18 | t22);
    t24 = (~(t23));
    t25 = (t17 & t24);
    if (t25 != 0)
        goto LAB39;

LAB36:    if (t23 != 0)
        goto LAB38;

LAB37:    *((unsigned int *)t7) = 1;

LAB39:    t15 = (t7 + 4);
    t26 = *((unsigned int *)t15);
    t30 = (~(t26));
    t31 = *((unsigned int *)t7);
    t32 = (t31 & t30);
    t33 = (t32 != 0);
    if (t33 > 0)
        goto LAB40;

LAB41:    xsi_set_current_line(160, ng0);
    t2 = (t0 + 4968);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng3)));
    memset(t7, 0, 8);
    t6 = (t4 + 4);
    t8 = (t5 + 4);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t6);
    t13 = *((unsigned int *)t8);
    t16 = (t12 ^ t13);
    t17 = (t11 | t16);
    t18 = *((unsigned int *)t6);
    t22 = *((unsigned int *)t8);
    t23 = (t18 | t22);
    t24 = (~(t23));
    t25 = (t17 & t24);
    if (t25 != 0)
        goto LAB47;

LAB44:    if (t23 != 0)
        goto LAB46;

LAB45:    *((unsigned int *)t7) = 1;

LAB47:    t15 = (t7 + 4);
    t26 = *((unsigned int *)t15);
    t30 = (~(t26));
    t31 = *((unsigned int *)t7);
    t32 = (t31 & t30);
    t33 = (t32 != 0);
    if (t33 > 0)
        goto LAB48;

LAB49:    xsi_set_current_line(164, ng0);
    t2 = (t0 + 4968);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng4)));
    memset(t7, 0, 8);
    t6 = (t4 + 4);
    t8 = (t5 + 4);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t6);
    t13 = *((unsigned int *)t8);
    t16 = (t12 ^ t13);
    t17 = (t11 | t16);
    t18 = *((unsigned int *)t6);
    t22 = *((unsigned int *)t8);
    t23 = (t18 | t22);
    t24 = (~(t23));
    t25 = (t17 & t24);
    if (t25 != 0)
        goto LAB55;

LAB52:    if (t23 != 0)
        goto LAB54;

LAB53:    *((unsigned int *)t7) = 1;

LAB55:    t15 = (t7 + 4);
    t26 = *((unsigned int *)t15);
    t30 = (~(t26));
    t31 = *((unsigned int *)t7);
    t32 = (t31 & t30);
    t33 = (t32 != 0);
    if (t33 > 0)
        goto LAB56;

LAB57:
LAB58:
LAB50:
LAB42:
LAB34:    goto LAB26;

LAB30:    t93 = (t78 + 4);
    *((unsigned int *)t78) = 1;
    *((unsigned int *)t93) = 1;
    goto LAB31;

LAB32:    xsi_set_current_line(152, ng0);

LAB35:    xsi_set_current_line(153, ng0);
    t100 = ((char*)((ng3)));
    t101 = (t0 + 4968);
    xsi_vlogvar_wait_assign_value(t101, t100, 0, 0, 2, 0LL);
    xsi_set_current_line(154, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 5288);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB34;

LAB38:    t14 = (t7 + 4);
    *((unsigned int *)t7) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB39;

LAB40:    xsi_set_current_line(156, ng0);

LAB43:    xsi_set_current_line(157, ng0);
    t20 = ((char*)((ng2)));
    t21 = (t0 + 4968);
    xsi_vlogvar_wait_assign_value(t21, t20, 0, 0, 2, 0LL);
    xsi_set_current_line(158, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 5288);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB42;

LAB46:    t14 = (t7 + 4);
    *((unsigned int *)t7) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB47;

LAB48:    xsi_set_current_line(160, ng0);

LAB51:    xsi_set_current_line(161, ng0);
    t20 = ((char*)((ng2)));
    t21 = (t0 + 4968);
    xsi_vlogvar_wait_assign_value(t21, t20, 0, 0, 2, 0LL);
    xsi_set_current_line(162, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 5288);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB50;

LAB54:    t14 = (t7 + 4);
    *((unsigned int *)t7) = 1;
    *((unsigned int *)t14) = 1;
    goto LAB55;

LAB56:    xsi_set_current_line(164, ng0);

LAB59:    xsi_set_current_line(165, ng0);
    t20 = ((char*)((ng2)));
    t21 = (t0 + 5288);
    xsi_vlogvar_wait_assign_value(t21, t20, 0, 0, 1, 0LL);
    goto LAB58;

LAB60:    *((unsigned int *)t7) = 1;
    goto LAB63;

LAB62:    t6 = (t7 + 4);
    *((unsigned int *)t7) = 1;
    *((unsigned int *)t6) = 1;
    goto LAB63;

LAB64:    t14 = (t0 + 4408U);
    t15 = *((char **)t14);
    memset(t19, 0, 8);
    t14 = (t15 + 4);
    t22 = *((unsigned int *)t14);
    t23 = (~(t22));
    t24 = *((unsigned int *)t15);
    t25 = (t24 & t23);
    t26 = (t25 & 1U);
    if (t26 != 0)
        goto LAB70;

LAB68:    if (*((unsigned int *)t14) == 0)
        goto LAB67;

LAB69:    t20 = (t19 + 4);
    *((unsigned int *)t19) = 1;
    *((unsigned int *)t20) = 1;

LAB70:    memset(t28, 0, 8);
    t21 = (t19 + 4);
    t30 = *((unsigned int *)t21);
    t31 = (~(t30));
    t32 = *((unsigned int *)t19);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB71;

LAB72:    if (*((unsigned int *)t21) != 0)
        goto LAB73;

LAB74:    t37 = *((unsigned int *)t7);
    t38 = *((unsigned int *)t28);
    t39 = (t37 & t38);
    *((unsigned int *)t36) = t39;
    t29 = (t7 + 4);
    t35 = (t28 + 4);
    t40 = (t36 + 4);
    t43 = *((unsigned int *)t29);
    t44 = *((unsigned int *)t35);
    t45 = (t43 | t44);
    *((unsigned int *)t40) = t45;
    t46 = *((unsigned int *)t40);
    t47 = (t46 != 0);
    if (t47 == 1)
        goto LAB75;

LAB76:
LAB77:    goto LAB66;

LAB67:    *((unsigned int *)t19) = 1;
    goto LAB70;

LAB71:    *((unsigned int *)t28) = 1;
    goto LAB74;

LAB73:    t27 = (t28 + 4);
    *((unsigned int *)t28) = 1;
    *((unsigned int *)t27) = 1;
    goto LAB74;

LAB75:    t48 = *((unsigned int *)t36);
    t49 = *((unsigned int *)t40);
    *((unsigned int *)t36) = (t48 | t49);
    t41 = (t7 + 4);
    t42 = (t28 + 4);
    t52 = *((unsigned int *)t7);
    t53 = (~(t52));
    t54 = *((unsigned int *)t41);
    t55 = (~(t54));
    t56 = *((unsigned int *)t28);
    t57 = (~(t56));
    t58 = *((unsigned int *)t42);
    t59 = (~(t58));
    t60 = (t53 & t55);
    t61 = (t57 & t59);
    t62 = (~(t60));
    t63 = (~(t61));
    t64 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t64 & t62);
    t65 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t65 & t63);
    t66 = *((unsigned int *)t36);
    *((unsigned int *)t36) = (t66 & t62);
    t67 = *((unsigned int *)t36);
    *((unsigned int *)t36) = (t67 & t63);
    goto LAB77;

LAB78:    xsi_set_current_line(169, ng0);

LAB81:    xsi_set_current_line(170, ng0);
    t51 = (t0 + 4968);
    t68 = (t51 + 56U);
    t74 = *((char **)t68);
    t75 = ((char*)((ng2)));
    memset(t78, 0, 8);
    t76 = (t74 + 4);
    t77 = (t75 + 4);
    t81 = *((unsigned int *)t74);
    t82 = *((unsigned int *)t75);
    t83 = (t81 ^ t82);
    t84 = *((unsigned int *)t76);
    t85 = *((unsigned int *)t77);
    t86 = (t84 ^ t85);
    t87 = (t83 | t86);
    t88 = *((unsigned int *)t76);
    t89 = *((unsigned int *)t77);
    t90 = (t88 | t89);
    t91 = (~(t90));
    t92 = (t87 & t91);
    if (t92 != 0)
        goto LAB85;

LAB82:    if (t90 != 0)
        goto LAB84;

LAB83:    *((unsigned int *)t78) = 1;

LAB85:    t80 = (t78 + 4);
    t95 = *((unsigned int *)t80);
    t96 = (~(t95));
    t97 = *((unsigned int *)t78);
    t98 = (t97 & t96);
    t99 = (t98 != 0);
    if (t99 > 0)
        goto LAB86;

LAB87:
LAB88:    xsi_set_current_line(174, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 5288);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB80;

LAB84:    t79 = (t78 + 4);
    *((unsigned int *)t78) = 1;
    *((unsigned int *)t79) = 1;
    goto LAB85;

LAB86:    xsi_set_current_line(170, ng0);

LAB89:    xsi_set_current_line(171, ng0);
    t93 = ((char*)((ng1)));
    t94 = (t0 + 4968);
    xsi_vlogvar_wait_assign_value(t94, t93, 0, 0, 2, 0LL);
    xsi_set_current_line(172, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 5128);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);
    goto LAB88;

LAB90:    *((unsigned int *)t7) = 1;
    goto LAB93;

LAB92:    t6 = (t7 + 4);
    *((unsigned int *)t7) = 1;
    *((unsigned int *)t6) = 1;
    goto LAB93;

LAB94:    t14 = (t0 + 4248U);
    t15 = *((char **)t14);
    memset(t19, 0, 8);
    t14 = (t15 + 4);
    t22 = *((unsigned int *)t14);
    t23 = (~(t22));
    t24 = *((unsigned int *)t15);
    t25 = (t24 & t23);
    t26 = (t25 & 1U);
    if (t26 != 0)
        goto LAB100;

LAB98:    if (*((unsigned int *)t14) == 0)
        goto LAB97;

LAB99:    t20 = (t19 + 4);
    *((unsigned int *)t19) = 1;
    *((unsigned int *)t20) = 1;

LAB100:    memset(t28, 0, 8);
    t21 = (t19 + 4);
    t30 = *((unsigned int *)t21);
    t31 = (~(t30));
    t32 = *((unsigned int *)t19);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB101;

LAB102:    if (*((unsigned int *)t21) != 0)
        goto LAB103;

LAB104:    t37 = *((unsigned int *)t7);
    t38 = *((unsigned int *)t28);
    t39 = (t37 & t38);
    *((unsigned int *)t36) = t39;
    t29 = (t7 + 4);
    t35 = (t28 + 4);
    t40 = (t36 + 4);
    t43 = *((unsigned int *)t29);
    t44 = *((unsigned int *)t35);
    t45 = (t43 | t44);
    *((unsigned int *)t40) = t45;
    t46 = *((unsigned int *)t40);
    t47 = (t46 != 0);
    if (t47 == 1)
        goto LAB105;

LAB106:
LAB107:    goto LAB96;

LAB97:    *((unsigned int *)t19) = 1;
    goto LAB100;

LAB101:    *((unsigned int *)t28) = 1;
    goto LAB104;

LAB103:    t27 = (t28 + 4);
    *((unsigned int *)t28) = 1;
    *((unsigned int *)t27) = 1;
    goto LAB104;

LAB105:    t48 = *((unsigned int *)t36);
    t49 = *((unsigned int *)t40);
    *((unsigned int *)t36) = (t48 | t49);
    t41 = (t7 + 4);
    t42 = (t28 + 4);
    t52 = *((unsigned int *)t7);
    t53 = (~(t52));
    t54 = *((unsigned int *)t41);
    t55 = (~(t54));
    t56 = *((unsigned int *)t28);
    t57 = (~(t56));
    t58 = *((unsigned int *)t42);
    t59 = (~(t58));
    t60 = (t53 & t55);
    t61 = (t57 & t59);
    t62 = (~(t60));
    t63 = (~(t61));
    t64 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t64 & t62);
    t65 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t65 & t63);
    t66 = *((unsigned int *)t36);
    *((unsigned int *)t36) = (t66 & t62);
    t67 = *((unsigned int *)t36);
    *((unsigned int *)t36) = (t67 & t63);
    goto LAB107;

LAB108:    xsi_set_current_line(177, ng0);

LAB111:    xsi_set_current_line(178, ng0);
    t51 = (t0 + 4968);
    t68 = (t51 + 56U);
    t74 = *((char **)t68);
    t75 = ((char*)((ng2)));
    memset(t78, 0, 8);
    t76 = (t74 + 4);
    t77 = (t75 + 4);
    t81 = *((unsigned int *)t74);
    t82 = *((unsigned int *)t75);
    t83 = (t81 ^ t82);
    t84 = *((unsigned int *)t76);
    t85 = *((unsigned int *)t77);
    t86 = (t84 ^ t85);
    t87 = (t83 | t86);
    t88 = *((unsigned int *)t76);
    t89 = *((unsigned int *)t77);
    t90 = (t88 | t89);
    t91 = (~(t90));
    t92 = (t87 & t91);
    if (t92 != 0)
        goto LAB115;

LAB112:    if (t90 != 0)
        goto LAB114;

LAB113:    *((unsigned int *)t78) = 1;

LAB115:    t80 = (t78 + 4);
    t95 = *((unsigned int *)t80);
    t96 = (~(t95));
    t97 = *((unsigned int *)t78);
    t98 = (t97 & t96);
    t99 = (t98 != 0);
    if (t99 > 0)
        goto LAB116;

LAB117:
LAB118:    xsi_set_current_line(182, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 5288);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB110;

LAB114:    t79 = (t78 + 4);
    *((unsigned int *)t78) = 1;
    *((unsigned int *)t79) = 1;
    goto LAB115;

LAB116:    xsi_set_current_line(178, ng0);

LAB119:    xsi_set_current_line(179, ng0);
    t93 = ((char*)((ng1)));
    t94 = (t0 + 4968);
    xsi_vlogvar_wait_assign_value(t94, t93, 0, 0, 2, 0LL);
    xsi_set_current_line(180, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 5128);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);
    goto LAB118;

LAB120:    *((unsigned int *)t7) = 1;
    goto LAB123;

LAB122:    t6 = (t7 + 4);
    *((unsigned int *)t7) = 1;
    *((unsigned int *)t6) = 1;
    goto LAB123;

LAB124:    t14 = (t0 + 3928U);
    t15 = *((char **)t14);
    memset(t19, 0, 8);
    t14 = (t15 + 4);
    t22 = *((unsigned int *)t14);
    t23 = (~(t22));
    t24 = *((unsigned int *)t15);
    t25 = (t24 & t23);
    t26 = (t25 & 1U);
    if (t26 != 0)
        goto LAB130;

LAB128:    if (*((unsigned int *)t14) == 0)
        goto LAB127;

LAB129:    t20 = (t19 + 4);
    *((unsigned int *)t19) = 1;
    *((unsigned int *)t20) = 1;

LAB130:    memset(t28, 0, 8);
    t21 = (t19 + 4);
    t30 = *((unsigned int *)t21);
    t31 = (~(t30));
    t32 = *((unsigned int *)t19);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB131;

LAB132:    if (*((unsigned int *)t21) != 0)
        goto LAB133;

LAB134:    t37 = *((unsigned int *)t7);
    t38 = *((unsigned int *)t28);
    t39 = (t37 & t38);
    *((unsigned int *)t36) = t39;
    t29 = (t7 + 4);
    t35 = (t28 + 4);
    t40 = (t36 + 4);
    t43 = *((unsigned int *)t29);
    t44 = *((unsigned int *)t35);
    t45 = (t43 | t44);
    *((unsigned int *)t40) = t45;
    t46 = *((unsigned int *)t40);
    t47 = (t46 != 0);
    if (t47 == 1)
        goto LAB135;

LAB136:
LAB137:    goto LAB126;

LAB127:    *((unsigned int *)t19) = 1;
    goto LAB130;

LAB131:    *((unsigned int *)t28) = 1;
    goto LAB134;

LAB133:    t27 = (t28 + 4);
    *((unsigned int *)t28) = 1;
    *((unsigned int *)t27) = 1;
    goto LAB134;

LAB135:    t48 = *((unsigned int *)t36);
    t49 = *((unsigned int *)t40);
    *((unsigned int *)t36) = (t48 | t49);
    t41 = (t7 + 4);
    t42 = (t28 + 4);
    t52 = *((unsigned int *)t7);
    t53 = (~(t52));
    t54 = *((unsigned int *)t41);
    t55 = (~(t54));
    t56 = *((unsigned int *)t28);
    t57 = (~(t56));
    t58 = *((unsigned int *)t42);
    t59 = (~(t58));
    t60 = (t53 & t55);
    t61 = (t57 & t59);
    t62 = (~(t60));
    t63 = (~(t61));
    t64 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t64 & t62);
    t65 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t65 & t63);
    t66 = *((unsigned int *)t36);
    *((unsigned int *)t36) = (t66 & t62);
    t67 = *((unsigned int *)t36);
    *((unsigned int *)t36) = (t67 & t63);
    goto LAB137;

LAB138:    xsi_set_current_line(185, ng0);

LAB141:    xsi_set_current_line(186, ng0);
    t51 = (t0 + 4968);
    t68 = (t51 + 56U);
    t74 = *((char **)t68);
    t75 = ((char*)((ng2)));
    memset(t78, 0, 8);
    t76 = (t74 + 4);
    t77 = (t75 + 4);
    t81 = *((unsigned int *)t74);
    t82 = *((unsigned int *)t75);
    t83 = (t81 ^ t82);
    t84 = *((unsigned int *)t76);
    t85 = *((unsigned int *)t77);
    t86 = (t84 ^ t85);
    t87 = (t83 | t86);
    t88 = *((unsigned int *)t76);
    t89 = *((unsigned int *)t77);
    t90 = (t88 | t89);
    t91 = (~(t90));
    t92 = (t87 & t91);
    if (t92 != 0)
        goto LAB145;

LAB142:    if (t90 != 0)
        goto LAB144;

LAB143:    *((unsigned int *)t78) = 1;

LAB145:    t80 = (t78 + 4);
    t95 = *((unsigned int *)t80);
    t96 = (~(t95));
    t97 = *((unsigned int *)t78);
    t98 = (t97 & t96);
    t99 = (t98 != 0);
    if (t99 > 0)
        goto LAB146;

LAB147:
LAB148:    xsi_set_current_line(190, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 5288);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB140;

LAB144:    t79 = (t78 + 4);
    *((unsigned int *)t78) = 1;
    *((unsigned int *)t79) = 1;
    goto LAB145;

LAB146:    xsi_set_current_line(186, ng0);

LAB149:    xsi_set_current_line(187, ng0);
    t93 = ((char*)((ng1)));
    t94 = (t0 + 4968);
    xsi_vlogvar_wait_assign_value(t94, t93, 0, 0, 2, 0LL);
    xsi_set_current_line(188, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 5128);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);
    goto LAB148;

LAB150:    *((unsigned int *)t7) = 1;
    goto LAB153;

LAB152:    t6 = (t7 + 4);
    *((unsigned int *)t7) = 1;
    *((unsigned int *)t6) = 1;
    goto LAB153;

LAB154:    t14 = (t0 + 4088U);
    t15 = *((char **)t14);
    memset(t19, 0, 8);
    t14 = (t15 + 4);
    t22 = *((unsigned int *)t14);
    t23 = (~(t22));
    t24 = *((unsigned int *)t15);
    t25 = (t24 & t23);
    t26 = (t25 & 1U);
    if (t26 != 0)
        goto LAB160;

LAB158:    if (*((unsigned int *)t14) == 0)
        goto LAB157;

LAB159:    t20 = (t19 + 4);
    *((unsigned int *)t19) = 1;
    *((unsigned int *)t20) = 1;

LAB160:    memset(t28, 0, 8);
    t21 = (t19 + 4);
    t30 = *((unsigned int *)t21);
    t31 = (~(t30));
    t32 = *((unsigned int *)t19);
    t33 = (t32 & t31);
    t34 = (t33 & 1U);
    if (t34 != 0)
        goto LAB161;

LAB162:    if (*((unsigned int *)t21) != 0)
        goto LAB163;

LAB164:    t37 = *((unsigned int *)t7);
    t38 = *((unsigned int *)t28);
    t39 = (t37 & t38);
    *((unsigned int *)t36) = t39;
    t29 = (t7 + 4);
    t35 = (t28 + 4);
    t40 = (t36 + 4);
    t43 = *((unsigned int *)t29);
    t44 = *((unsigned int *)t35);
    t45 = (t43 | t44);
    *((unsigned int *)t40) = t45;
    t46 = *((unsigned int *)t40);
    t47 = (t46 != 0);
    if (t47 == 1)
        goto LAB165;

LAB166:
LAB167:    goto LAB156;

LAB157:    *((unsigned int *)t19) = 1;
    goto LAB160;

LAB161:    *((unsigned int *)t28) = 1;
    goto LAB164;

LAB163:    t27 = (t28 + 4);
    *((unsigned int *)t28) = 1;
    *((unsigned int *)t27) = 1;
    goto LAB164;

LAB165:    t48 = *((unsigned int *)t36);
    t49 = *((unsigned int *)t40);
    *((unsigned int *)t36) = (t48 | t49);
    t41 = (t7 + 4);
    t42 = (t28 + 4);
    t52 = *((unsigned int *)t7);
    t53 = (~(t52));
    t54 = *((unsigned int *)t41);
    t55 = (~(t54));
    t56 = *((unsigned int *)t28);
    t57 = (~(t56));
    t58 = *((unsigned int *)t42);
    t59 = (~(t58));
    t60 = (t53 & t55);
    t61 = (t57 & t59);
    t62 = (~(t60));
    t63 = (~(t61));
    t64 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t64 & t62);
    t65 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t65 & t63);
    t66 = *((unsigned int *)t36);
    *((unsigned int *)t36) = (t66 & t62);
    t67 = *((unsigned int *)t36);
    *((unsigned int *)t36) = (t67 & t63);
    goto LAB167;

LAB168:    xsi_set_current_line(194, ng0);

LAB171:    xsi_set_current_line(195, ng0);
    t51 = (t0 + 4968);
    t68 = (t51 + 56U);
    t74 = *((char **)t68);
    t75 = ((char*)((ng2)));
    memset(t78, 0, 8);
    t76 = (t74 + 4);
    t77 = (t75 + 4);
    t81 = *((unsigned int *)t74);
    t82 = *((unsigned int *)t75);
    t83 = (t81 ^ t82);
    t84 = *((unsigned int *)t76);
    t85 = *((unsigned int *)t77);
    t86 = (t84 ^ t85);
    t87 = (t83 | t86);
    t88 = *((unsigned int *)t76);
    t89 = *((unsigned int *)t77);
    t90 = (t88 | t89);
    t91 = (~(t90));
    t92 = (t87 & t91);
    if (t92 != 0)
        goto LAB175;

LAB172:    if (t90 != 0)
        goto LAB174;

LAB173:    *((unsigned int *)t78) = 1;

LAB175:    t80 = (t78 + 4);
    t95 = *((unsigned int *)t80);
    t96 = (~(t95));
    t97 = *((unsigned int *)t78);
    t98 = (t97 & t96);
    t99 = (t98 != 0);
    if (t99 > 0)
        goto LAB176;

LAB177:
LAB178:    xsi_set_current_line(199, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 5288);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB170;

LAB174:    t79 = (t78 + 4);
    *((unsigned int *)t78) = 1;
    *((unsigned int *)t79) = 1;
    goto LAB175;

LAB176:    xsi_set_current_line(195, ng0);

LAB179:    xsi_set_current_line(196, ng0);
    t93 = ((char*)((ng1)));
    t94 = (t0 + 4968);
    xsi_vlogvar_wait_assign_value(t94, t93, 0, 0, 2, 0LL);
    xsi_set_current_line(197, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 5128);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 2, 0LL);
    goto LAB178;

}


extern void work_m_00000000003745549043_3503384701_init()
{
	static char *pe[] = {(void *)Cont_23_0,(void *)Cont_24_1,(void *)Initial_64_2,(void *)Always_71_3,(void *)Always_150_4};
	xsi_register_didat("work_m_00000000003745549043_3503384701", "isim/tb_isim_beh.exe.sim/work/m_00000000003745549043_3503384701.didat");
	xsi_register_executes(pe);
}
