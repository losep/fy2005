inherit ROOM;

void create()
{
	set("short", "���ӱ�Ե");

	set("long", @LONG
�������ӣ���һ��Ⱥɽ�ϱ��µ�Сɽ�£��ļ�������������������Ҫ������ɽ
��ˮ������һƬ�������ڱ�ĵط����ѵ����ή�Ĳ�ľ��������ȴ���������٣���
��ĵط����Ծó����滨��ݣ�������ȴ��Ŀ���ǡ�������һ���԰�ɽ��������Ȫ
ˮ�����ȱ�ĵط���������������Զ��Ȫˮ�Ե�һƬ��֪���Ļ������У����м�С
С��ľ�ݣ�һ��ǳ��ɫ�Ļ������ݶ��ϳ��˳�����
LONG);
       set("outdoors", "wolfmount");

	set("type","grassland");
	set("exits",([
        "enter":__DIR__"xiaohome",
	]) );
	set("coor/x",100);
	set("coor/y",20);
	set("coor/z",-60);

	setup();
	replace_program(ROOM);
}