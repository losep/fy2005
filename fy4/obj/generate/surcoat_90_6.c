#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create() {
	set_name(BLK"��������"NOR, ({ "robe"}) );
	set_weight(300);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("generate_item",1);
		set("lore",1);
		set("material", "cloth");
		set("male_only", 1);
		set("level_required", 70);
		set("armor_prop/armor", 12);
		set("armor_prop/strength", 30);
		set("armor_prop/intelligence", 6);
		set("armor_prop/composure", 6);
		set("armor_prop/constitutionx", 2);	// �ѷ���
		set("armor_prop/agility", 6);
		set("armor_prop/karma", 6);
		set("armor_prop/max_gin", 88);
		set("armor_prop/max_kee", 110);
		set("armor_prop/max_sen", 88);
//		set("long","����\n");	// �ѷ���
	}
	::init_surcoat();
}

// ���p��dancing_faery@hotmail.com

