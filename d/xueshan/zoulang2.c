inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������ѩɽ���ڵ����ȡ������е��İ����컨������һЩ
��֪��ȷ�к���ĵ�̣�ǽ�������Ǻ�ͨ�׵ķ𾭹��±ڻ��ˡ�
���ϵ��ż���󺣵�������
LONG);
        set("exits", ([
                "southdown" : __DIR__"cedian2",
                "east"      : __DIR__"dating",
                "north"     : __DIR__"zoulang4",
        ]));
        setup();
}