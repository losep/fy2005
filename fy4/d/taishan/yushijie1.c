// Room: yushijie1.c --- by MapMaker

inherit ROOM;

void create()
{
	set("short", "����ʯ��");

	set("long", @LONG
������ͨ���޹�ɽׯ�İ���ʯ��,��Ȼ����ȥ��������Զ,��ʯ�����ѱ�������
����ǽ���,�����Եø����ׯ�ض��ྲ,����ɫ���ߣ��������������������Ĺ⣬
��ʯ���״ӻƽ��ĸ�ǽ�䴩��ȥ������ɽׯ��������ȫ���鱦�ƽ����ɵġ�����
ɽ������,��ɽ����,���õ������£�Զ����һƬ�Ի���ΰ��ׯԺ��������������
�еĹ���һ����
LONG);

	//{{ --- by MapMaker
	set("type","road");
	set("exits",([
    "southdown":__DIR__"yushijie2",
	"north":__DIR__"damen",
	]) );
	//}}
        set("outdoors", "taishan");
	set("coor/x",0);
	set("coor/y",50);
	set("coor/z",150);

	setup();
	replace_program(ROOM);
}