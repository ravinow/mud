inherit ROOM;

void create()
{
        set("short", "ũ��");
        set("long", @LONG
����һС����ͨ��ˮ�������Ϫ�����������ʮ�ַ��㡣
Χ��ũ�����һƬƬɣ�֣������˲�ɣ�����ϣ���֯�൱����
��˿֯Ʒ������������ӡ�
LONG);
        set("objects", ([
                __DIR__"npc/nongfu2" : 1,
        ]));
        set("outdoors", "dali");
        set("exits", ([
                "south"  : __DIR__"buxiongbu",
                "east"   : __DIR__"langan3",
        ]));
        setup();
        replace_program(ROOM);
}