// huang ����

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

mixed ask_opinion();
mixed ask_skill();

#define ULTRA_OPINION   "��ʦ"
#define OPINION_TYPE    HIY "ȭ�Ź���" NOR 
#define MY_OPINION      "unarmed"

string  *my_opinions = ({ "unarmed", "finger",
                          "strike", "cuff", "hand", "claw" });

// ��ͷ�ļ�����������Ƕ��
#include "ultra.h"

void create()
{
        set_name("����", ({ "huang shang", "huang" }) );
        set("title", HIY "����ʦ" NOR);
        set("gender", "����");
        set("age", 92);
        set("long", "�����������ţ��������书�ߵ͡�\n");
        set("attitude", "peaceful");
        set("str", 32);
        set("int", 39);
        set("con", 37);
        set("dex", 32);

        set("max_qi", 20000);
        set("max_jing", 20000);
        set("neili", 30000);
        set("max_neili", 30000);
        set("jiali", 100);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "�����澭" : "�벻������������д��һ����ѧ�ĵþ���ΪΣ�������Ĳ���֮�",
                "����"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "��ѧ����" : "��ѧ����(martial-cognize)�����ң���̸ʲô�书�أ�",
                "���Ĵ�" : (: ask_skill :),
        ]));

        set_skill("unarmed", 500);
        set_skill("finger", 500);
        set_skill("claw", 500);
        set_skill("strike", 500);
        set_skill("hand", 500);
        set_skill("cuff", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("jiuyin-shengong", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 200);

        map_skill("parry", "jiuyin-shengong");
        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("finger", "jiuyin-shengong");
        map_skill("strike", "jiuyin-shengong");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("rank_info/self", "ĳ��");

        setup();
        carry_object("/clone/cloth/cloth")->wear();

        set("startroom", "/d/dali/lushui");
        check_clone();
}

void init()
{
        object me;

        if (! interactive(me = this_player()))
                return;

        me->delete_temp("want_opinion");
        if (ultrap(me))
        {
                message_vision(CYN "$N" CYN "΢΢һЦ����$n"
                               CYN "���˵�ͷ��\n" NOR,
                               this_object(), me);
        }
}

mixed ask_opinion()
{
        object me;
        object ob;

        me = this_player();

        if (me->query("combat_exp") < 200000)
                return "�Ǻǣ�������书��̸ʲô���ۣ�";

        if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
                return "��������ȭ�ŷ������Ϊ�Ѿ��Ƶ�������ʦ�ˣ�����Ҫ��Ҫ�����У�";

        if (is_fighting(me))
                return "��������ʲô������Ӯ���ң����Լ����Լ����۰ɣ�";

        if (me->is_fighting())
                return "��Ȼ���ɣ����Ҹ������ǡ�";

        if (objectp(ob = query_temp("opinion")))
        {
                if (ob == me)
                {
                        command("say ����ʲô������Ҫ���ҡ�");
                        return 1;
                }

                message_vision(CYN "$N" CYN "���ڳ�˼��û�лش�$n"
                               CYN "��ֻ�ǰ��˰��֡�\n" NOR,
                               this_object(), me);
                return 1;
        }

        switch(me->query_temp("want_opinion/huang"))
        {
        case 0:
                command("look " + me->query("id"));
                command("say �ðɣ�����ֹ���һ�У��ҿ������ˮƽ��Ρ�");
                break;
        case 1:
                command("say ����˵������һ���ҿ�����");
                break;
        case 2:
                message_vision(CYN "$N" CYN "��ü��$n" CYN
                               "�������ҿ��������ǹ����µġ���\n" NOR,
                               this_object(), me);
                break;
        case 3:
                command("say ���ұ�������죡");
                return 1;
        }

        me->add_temp("want_opinion/huang", 1);
        return 1;
}

int calc_level(object me, string skill)
{
        int lvl;
        string sp;
        mapping action;

        lvl = me->query_skill(skill, 1) / 2;
        sp = me->query_skill_mapped(skill);
        if (! sp) return lvl;

        lvl += me->query_skill(sp, 1);
        action = SKILL_D(sp)->query_action(me, 0);
        if (mapp(action))
                lvl += (action["force"] + action["attack"] +
                        action["parry"] + action["dodge"] - 150) / 15;
        return lvl;
}

void do_congration(object me)
{
        command("chat ��ϲ��λ" + RANK_D->query_respect(me) + "��������"
                "������ֹ������������Ŭ������");
}

int accept_hit(object me)
{
        if (me->query_temp("want_hit/huang") >= 2)
        {
                command("heng");
                command("say �²���������Ҫ�����Ǿ�ȥ���ɣ�");
                kill_ob(me);
                return 1;
        }

        command("shake");
        command("say ��λ" + RANK_D->query_respect(me) + "��"
                "����֮���м�óȻ���ơ�");
        me->add_temp("want_hit/huang", 1);
        return 0;
}

int accept_fight(object me)
{
        object weapon;

        if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
        {
                message_vision(CYN "$N" CYN "��ϲ����$n" CYN
                               "�������ܺã������һ�û�к���"
                               "ʦ���ֹ����У����ɣ���\n" NOR,
                               this_object(), me);
                return 1;
        }

        if (! me->query_temp("want_opinion/huang"))
        {
                command("say ƽ���޹ʶ�ʲô�֣�");
                return 0;
        }

        if (objectp(weapon = me->query_temp("weapon")))
        {
                command("say �������е�" + weapon->name() + NOR +
                        CYN "���ҷ��£�" NOR);
                return 0;
        }

        if (me->query("qi") * 100 / me->query("max_qi") < 80||
            me->query("jing") * 100 / me->query("max_jing") < 80)
        {
                command("say ������״̬���ѣ�����Ϣ������˵�ɣ�");
                return 0;
        }

        command("nod");
        COMBAT_D->do_attack(me, this_object(), 0);
        COMBAT_D->do_attack(this_object(), me, 0);

        if (me->query("qi") <= 0)
        {
                message_vision(CYN "\n$N" CYN "ҡҡͷ��$n" CYN
                               "�����������ڵ��书�����Զ����"
                               "��һ�ж��Ӳ�ס����\n" NOR,
                               this_object(), me);
                return notify_fail("����Ҫ�úõ����������ˡ�\n");
        }

        call_out("check_opinion", 2, me);
        set_temp("opinion", me);
        me->delete_temp("want_opinion");
        message_vision(CYN "\n$N" CYN "���ͷ���������ˣ����ȵ�"
                       "������������롣��\n" NOR,
                       this_object(), me);
        return notify_fail("���������ļ������õ�һ�����\n");
}

int accept_kill(object me)
{
        if (me->query("combat_exp") < 500000)
        {
                message_vision(CYN "$N" CYN "��ŭ����������С����"
                               "ʲô�ң����ҹ�����˵��һ�ư�$n" CYN
                               "�����ڵء�\n" NOR, this_object(), me);
                me->unconcious();
                return -1;
        }
        command("sigh");
        command("say �ܺã����껹��û������ʲô�Һ��ҽ����ĸ��֣�");
        return 1;
}

/*
int recognize_apprentice(object me, string skill)
{
        if (me->query("character") != "��������")
        {
                command("say ���ɷ����������ƶ�����һ��Ҫ��"
                        "�����䣬�����Բ��������ˡ�");
                return -1;
        }

        if (skill == "martial-cognize")
                return 1;

        if (! ultrap(me))
        {
                command("say ��ѧ�ҵľ����񹦣��㻹�����ʸ�"
                        "������˴���ʦ��˵�ɣ�");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say ���ˣ��Ҿͽ��㵽����ɣ��书����"
                        "Ҫ���Լ����о����ǣ�");
                return -1;
        }

        if (skill != "jiuyin-shengong")
                return 1;

        if (me->query_temp("can_learn/huang/jiuyin-shengong"))
                return 1;

        me->set_temp("can_learn/huang/jiuyin-shengong", 1);
        command("nod");
        command("say �ܺã��Ҿʹ�������񹦰ɣ��ɲ�Ҫ��������"
                "�ĸ�����");
        return 1;
}
*/

void unconcious()
{
        message("vision", "\n"HIR + name() + "��ɫһ�䣬����һ����"
                "Ѫ������һ�������Ų�����\n\n" NOR, environment());
        command("chat �գ��գ��գ��Ϸ�ȥҲ��");
        destruct(this_object());
}

mixed ask_skill()
{
        object me;
        
        me = this_player();

        if (me->query("can_perform/jiuyin-shengong/xin"))
        {
             command("say �㲻���Ѿ�������");
             return 1;
        }

        if (! me->query("can_learn/jiuyin-shengong/xin"))
        {               
               message_sort(HIM "\n����̾����������������д��һ����ѧ�ĵã���Ի�������澭��������"
                            "��������о���ѧ֮�ã����Ͼ���ΪΣ�������Ĳ���֮���������ܽ����ϡ�"
                            "�������ռ��뽻�����ң��ұ㴫����С����Ĵ󷨡���\n", me);
               command("tan");

               return "����������Σ�";
        }

        
        if (me->query_skill("jiuyin-shengong", 1) < 240)
        {
               command("say ������񹦻�򻹲������һ����ܴ������У�");
               return 1;
        }
        if (me->query_skill("martial-cognize", 1) < 240)
        {
               command("say ����ѧ�������㣬������ȥ��ĥ��һ�°ɣ�");
               return 1;
        }
        if (  ! me->query("can_perform/jiuyin-shengong/shou")
           || ! me->query("can_perform/jiuyin-shengong/zhi")
           || ! me->query("can_perform/jiuyin-shengong/zhua")
           || ! me->query("can_perform/jiuyin-shengong/zhang") )
        {
               command("shake");
               command("say ���㽫��������������������������Ұɣ�");
               return 1; 
        }

        command("nod");
        command("say �ܺã��ܺã�");
        command("say ��Ȼ�����Ҿʹ������Ĵ󷨣�");
        message_sort(HIC "\n���ѽ�$N" HIC "�������ԣ�����$N" HIC "����С���ֹ��˼��䡣"
                       "���Ѳ�ʱ������������ֵı��飬$N" HIC "�����߿������ã�$N" HIC
                       "һ����Х���������Ƕ�Ȼ��ʧ���������� ����\n", me);
        command("haha");
        
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("jiuyin-shengong"))
                me->improve_skill("jiuyin-shengong", 1500000);
        if (me->can_improve_skill("martial-cognize"))
                me->improve_skill("martial-cognize", 1500000);

        tell_object(me, HIG "��ѧ���ˡ����Ĵ󷨡���\n" NOR);
        me->set("can_perform/jiuyin-shengong/xin", 1);
        return 1;
}
void die()
{
        message("vision", "\n"HIR + name() + "���һ����������һ����"
                "Ѫ������һ�����ʹ˲�����\n\n" NOR, environment());
        command("chat �Ϸ�ȥҲ��");
        destruct(this_object());
}

int accept_object(object me, object ob) 
{
        if (base_name(ob) != "/clone/lonely/book/zhenjing1"
          && base_name(ob) != "/clone/lonely/book/zhenjing2")
        {
               command("say ��������ֶ�����ʲô��");
               return 0;
        } 
      
        if (base_name(ob) == "/clone/lonely/book/zhenjing1")
        {
               command("nod");
               command("say �ܺã��ܺã�");
               if (me->query("give_zhenjing2"))
               {
                     command("haha");
                     command("say ��Ȼ�����Ҿʹ�����У��������ʱ�����ң�");
                     tell_object(me, HIG "���Ѿ������㡸���Ĵ󷨡���\n" NOR); 
                     me->set("can_learn/jiuyin-shengong/xin", 1);
                     me->delete("give_zhenjing1");
                     me->delete("give_zhenjing2");
                     destruct(ob);
                     return 1;
               }
               me->set("give_zhenjing1", 1);
               command("say ����һ���������澭�²᡹���㾡���ҵ��������ң�");
               destruct(ob);
               return 1;
        } 

        if (base_name(ob) == "/clone/lonely/book/zhenjing2")
        {
               command("nod");
               command("say �ܺã��ܺã�");
               if (me->query("give_zhenjing1"))
               {
                     command("haha");
                     command("say ��Ȼ�����Ҿʹ�����У��������ʱ�����ң�");
                     tell_object(me, HIG "���Ѿ������㡸���Ĵ󷨡���\n" NOR); 
                     me->set("can_learn/jiuyin-shengong/xin", 1);
                     me->delete("give_zhenjing1");
                     me->delete("give_zhenjing2");
                     destruct(ob);
                     return 1;
               }
               me->set("give_zhenjing2", 1);
               command("say ����һ���������澭�ϲ᡹���㾡���ҵ��������ң�");
               destruct(ob);
               return 1;
        } 
 
}