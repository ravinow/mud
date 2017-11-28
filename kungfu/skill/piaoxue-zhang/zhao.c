#include <ansi.h>
#include <combat.h>

#define ZHAO "��" HIY "�������" NOR "��"

inherit F_SSERVER; 
         
int perform(object me, object target) 
{ 
//      object weapon; 
        string msg; 
        int ap, dp; 
        int damage; 

        if (userp(me) && ! me->query("can_perform/piaoxue-zhang/zhao"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me); 
        
        if (! target || ! me->is_fighting(target)) 
                return notify_fail(ZHAO "ֻ����ս���жԶ���ʹ�á�\n"); 
         
        if (me->query_temp("weapon") || 
            me->query_temp("secondary_weapon")) 
                return notify_fail("�������ֲ���ʩչ" ZHAO "��\n"); 
         
        if (me->query_skill("force") < 300) 
                return notify_fail("����ڹ�����Ϊ�������޷�ʩչ" ZHAO "��\n"); 
        
        if (me->query_skill("piaoxue-zhang", 1) < 180) 
                return notify_fail("���Ʈѩ��������Ϊ�������޷�ʩչ" ZHAO "��\n"); 
         
        if (me->query("neili") < 1000 || me->query("max_neili") < 3500) 
                return notify_fail("��������������޷�ʩչ" ZHAO "��\n"); 

/*
        if (me->query_skill_mapped("force") != "emei-jiuyang" &&
            me->query_skill_mapped("force") != "wudang-jiuyang" &&
            me->query_skill_mapped("force") != "shaolin-jiuyang" &&
            me->query_skill_mapped("force") != "jiuyang-shengong") 
                return notify_fail("��û�м����ڹ�Ϊ�����񹦣��޷�ʩչ" ZHAO "��\n"); 
*/

        if (me->query_skill_mapped("strike") != "piaoxue-zhang") 
                return notify_fail("��û�м���Ʈѩ�����ƣ��޷�ʩչ" ZHAO "��\n"); 

        if (me->query_skill_prepared("strike") != "piaoxue-zhang")
                return notify_fail("��û��׼��Ʈѩ�����ƣ��޷�ʩչ" ZHAO "��\n"); 

        if (! me->query_temp("powerup"))
                return notify_fail("����뽫ȫ�����������������ʩչ" ZHAO "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����ȫ����������ʱ�����ŷ���ȫ��������ž��"
              "�죬��Ȼһ����$n" HIY "\nȫ���ĳ�������һ���еУ�����һ"
              "�С�������ա���\n" NOR;
         
        ap = me->query_skill("strike") +
             me->query_skill("force") +
             me->query("str") * 5;

        dp = target->query_skill("dodge") +
             target->query_skill("force") +
             target->query("con") * 5;

        //damage = random(ap / 3) + ap / 3;
        damage = random(ap / 2) + ap / 2;

        if (target->query_skill_mapped("force") == "jiuyang-shengong")
        {
                me->add("neili", -600);
                me->start_busy(3);
                msg += HIW "ֻ����Ȼһ�����죬$n" HIW "�ѱ�һ�����У���$N"
                       HIW "ֻ��ȫ���������罭����\n��������ˮ�齻�ڣ���"
                       "ʱ��ʧ����Ӱ���١�\n" NOR; 
        } else
        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -600);
                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                           HIR "ֻ����Ȼһ�����죬$n" HIR "��$N"
                                           HIR "һ�����У����ӱ��絾�ݰ�ƽƽ�ɳ�"
                                           "����\n��ˤ�ڵ��£�Ż��һ�����Ѫ����"
                                           "Ҳ������\n" NOR);
        } else 
        { 
                me->add("neili", -400);
                me->start_busy(4);
                msg += CYN "����$p" CYN "������񣬼�ʱ������" 
                       CYN "$P" CYN "������ǣ�����㿪����һ����\n" NOR; 
        }
        message_combatd(msg, me, target);
       
        return 1; 
}