#include <weapon.h>
#include <ansi.h>
inherit SPEAR;

void create()
{
	set_name(HIW"���"NOR, ({ "silver spear","spear" }) );
	set_weight(20000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
        	set("long", "����һ����ɫ�ĳ�ꪣ��������ƺ��������ᡣ\n");
		set("value", 1000);
		set("material", "steel");
		set("wield_msg", "$N��֪��ʲô�ط�����һ��$n,��ৡ���һ���������С�\n");
		set("unwield_msg", "$N�����е�$n����\n");
	}
    ::init_spear(10);
}