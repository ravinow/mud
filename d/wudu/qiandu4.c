#include <ansi.h> 
inherit ROOM;
string* npcs = ({
        "/clone/worm/shishixie",
        "/clone/worm/tieguxie",
        "/clone/worm/heiguafu",
        "/clone/worm/jinxianwugong",
        "/clone/worm/huabanzhu",
        "/clone/worm/changaoxie",
        "/clone/worm/huibeixie",
});

void create()
{
        set("short", HIR "ǧ����" NOR);
        set("long", @LONG
������һ����Ȼ�γɵ�ʯ�������������󡣶���������������
��ʯ����ʱ���������δ��ˮ�������ڶ��У�����������ʪ�����Ժ�
Ȼ����һ�����С���������
LONG);

        set("exits", ([
                "east" : __DIR__"qiandu2",
        ]));
        set("objects", ([
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
                npcs[random(sizeof(npcs))] : 1,
        ]));

        setup();
        //replace_program(ROOM);
}