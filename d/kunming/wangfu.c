#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",  "��������" );
        set("long", @LONG
�����������ƽ�������Ĵ��ţ����߸���һ������Ĵ�ʯ
ʨ�ӣ��ߴ��������Ž����ı��ţ������ױ����ܵ�ע������
�����ˣ�ûʲô�£���ñ���������
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "south"    :__DIR__"beidajie",
                "north"   :__DIR__"wangfu1",
        ]));

        set("objects",([
                __DIR__"npc/qinbing":4,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" &&
           objectp(present("qin bing", environment(me))))
                return notify_fail(CYN "�ױ���ס��˵����������Ժ��������"
                                   "��һ�ɻرܡ�\n" NOR);                
        return ::valid_leave(me, dir);
}