// medicine.c

inherit MEDICINE;
#include <ansi.h>

void create()
{
    	set_name(GRN"��Ҷ��β��"NOR,({"sanyecao"}));
        if( clonep() )
                set_default_object(__FILE__);
	else {
	    set("long",
                "һ���Ѿ����ɵ���Ҷ��β�ݣ�����ɢ���Ų��㣬������������1500�����ˡ�\n");
        	set("unit","��");
        	set("base_unit","��");
        	set("base_value", 6000);
        	set("base_weight",60);
				set("field","kee");
	    	set("type","cure");
	    	set("effect",1500);
	    	set("heal_type","kee/1500");
	    	set("usage_type","herb");	
	    	set("volumn", 10);
	}
	set_amount(10);
}