// medicine.c
inherit MEDICINE;

void create()
{
	set_name("�����",({"dafeng"}));
        if( clonep() )
                set_default_object(__FILE__);
	else {
	    set("long","һ�Ŵ���裬������������50���������ˡ�\n");
		set("unit","��");
		set("base_unit","��");
		set("base_weight",60);
		set("base_value", 300);
		set("type","cure");
		set("field","sen");
		set("effect",50);
		set("heal_type","sen/50");
		set("usage_type","pill");
		set("volumn",5);	
	}
	set_amount(5);
}