inherit ITEM;
void create()
{
	set_name("������", ({ "daocao ren","ren" }) );
	set_weight(500);
	set_max_encumbrance(80000);
	set("no_get", 1);
	if( clonep() )
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("long", "һ�������Т�ĵ����ˣ�һֻ�ֻ������ɥ������������ǰ�����Ϸ�\n��һ��ֽ����(paper)�����ݵ��ߣ���ϵ�ڵ����˵���һֻ���ϡ�\n");
		set("value", 1);
	}
	::init_item();
}