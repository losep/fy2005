inherit ROOM;
void create()
{
        set("short", "�Ҳݵ�");
        set("long", @LONG
��������һ��Ƭ�Ҳݵأ��վ��������ϣ�����һ�߶�ߡ�ҹ��һ�����������
�ݾ�ˢ��ˢ�������ţ���Ϊ��Ժ�Ӷ�����ݣ��������������ر�󣬳�Ⱥ��ӵľ�
�������ˡ�����ëë�꣬������Ͼ��������������ʵġ�
LONG
        );
        set("exits", ([ 
		"north": __DIR__"pond",
	]));
        set("outdoors", "taiping");
        set("no_fly",1);
	set("item_desc", ([  
		"���": "��ݳ����ָ����ܣ����Ƿ�����ȥ��·�����������ֲ��ˡ�\n",
		"grass": "��ݳ����ָ����ܣ����Ƿ�����ȥ��·�����������ֲ��ˡ�\n",
	]));
	set("coor/x",60);
	set("coor/y",-90);
	set("coor/z",0);
	set("map","taiping");
	setup();
	
}