
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
ï�ܵ����֣���ʱ�ܼ�����ֻ����������������ȥ����Ȼֻ�м�˿������͸��
���룬ȴ���Ե���ɭ�ɲ���ϰϰ���粻ʱӭ�洵����ʹ�˻����泩��ʹ����������
�˯��һ����
LONG
	);
	set("exits", ([ 
  		"east" : __DIR__"pine1",
  		"west" : __DIR__"pine2",
  		"north" : __DIR__"pine2",
  		"south" : __DIR__"pine4",
	]));
	set("coor/x",-10);
	set("coor/y",45);
	set("coor/z",-40);
	setup();
	replace_program(ROOM);
}