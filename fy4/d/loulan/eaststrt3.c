inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
һ���ƻ�ͨ���ĳ��ȣ��ƺ�ԭ�ȱ��Ƿ����Ľֵ���������һЩ��Ժ��լ������
�����ռ�����¥���ĵ��������󣬱㽫���СС����լ���ݸĽ����Թ����¾�ɫ
������ʹ��������ʮ�����Լ��ڶ��������˺�һ�����˾�ס��
LONG
        );
        set("exits", ([ 
		"west" : __DIR__"eaststrt2",
		"east" : __DIR__"easttower",
	]));
        set("indoors", "loulan");

	set("coor/x",30);
	set("coor/y",0);
	set("coor/z",0);
	setup();
}