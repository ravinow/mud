#include <ansi.h>
#include <weapon.h>
inherit STAFF;

void create()
{
        set_name(HIY "�����" NOR, ({ "chijin zhang", "chijin", "staff", "zhang" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 200000);
                set("material", "steel");
        }
        init_staff(80);
        setup();
}

void owner_is_killed()
{
        destruct(this_object());
} 
