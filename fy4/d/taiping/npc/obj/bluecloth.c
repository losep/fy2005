#include <armor.h>

inherit CLOTH;

void create()
{
	set_name("����", ({ "blue cloth","cloth" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long","һ����ɫ�Ľ����¿�������ð������š��ߺ�ɽׯ���ĸ��֡�\n");
		set("material", "cloth");
		set("armor_prop/armor", 10);
		set("value",100);
	}
	::init_cloth();
}