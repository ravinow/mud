inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�˼��Ǵ������������ǵ����ţ�������ʵ��������ǣ���گ�ڳ�
��������������������Ķ��ϵġ��������������Դ˳�Ϊ������ǽ��
ʯ������ݳɣ��߶����壬�����ɡ��������������������ľ�ʿ��
�����۾��۲����������������ˣ�ż�����ʼ����μ����ɷ��ӡ�
LONG);
	set("outdoors", "dali");
	set("exits", ([
                "north" : __DIR__"shizilukou",
                "east"  : __DIR__"xiaodao2",
                "south" : __DIR__"shuangheqiao",
	]));
	set("objects", ([
                __DIR__"npc/jiang": 1,
                __DIR__"npc/bing": 3,
                "/clone/npc/walker" : 1,
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
